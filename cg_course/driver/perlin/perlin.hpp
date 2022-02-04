#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <iterator>
#include <algorithm>
#include <random>
#include <cmath>
#include <cstdlib> // для функций rand() и srand()
#include <ctime>

#include "driver/landscape/landscape.h"

namespace perlin
{
    //функция сглаживания f(t) = 6t^5 - 15t^4 + 10t^3
    double fade(double t){
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double lerp(double t, double a, double b){
        return a + t * (b - a);
    }

    double map(double value, double old_min, double old_max, double new_min, double new_max)
    {
        //получить коэффициент масштабирования в исходном интервале
        double proportion = (value - old_min) / (old_max - old_min);
        return lerp(proportion, new_min, new_max);
    }

    //вычисление градиента - скалярное произведение между вектором градиента и вектором расстояния от узла до точки
    double gradient(int hash, double x, double y, double z)
    {
        int h = hash & 0b1111; //hash & 15 = hash % 16 - оптимизация
        double u = h < 0b1000 ? x : y;
        double v = h < 0b0100 ? y : h == 0b1100 || h == 0b1110 ? x : z;

        return ((h & 0b0001) == 0 ? u : -u) + ((h & 0b0010) == 0 ? v : -v);
    }

    class Perlin
    {
        private:
            unsigned char p[512];
            unsigned int seed;

        public:
            Perlin(unsigned int seed){
                reseed(seed);
            }

            void reseed(unsigned int _seed)
            {
                seed = _seed;

                for (unsigned int i = 0; i < 256; i++){
                    p[i] = i;
                }
                std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

                for (unsigned int i = 0; i < 256; i++)
                    p[256 + i] = p[i];
            }

            double noise1D(double x)
            {
                int xi = (int)(std::floor(x)) & 255; // = % 256

                x -= std::floor(x);

                double sx = fade(x);

                int a;
                a = p[xi];

                double average = lerp(sx, gradient(a, x, 0, 0), gradient(a, x - 1, 0, 0));
                return map(average, -1, 1, 0, 1);
            }

            double noise2D(double x, double y)
            {
                //нахождение наименьшей точки из квадрата
                int xi = (int)(std::floor(x)) & 255;
                int yi = (int)(std::floor(y)) & 255;

                x -= std::floor(x);
                y -= std::floor(y);

                double sx = fade(x);
                double sy = fade(y);

                unsigned char aa, ab, ba, bb;
                aa = p[p[xi] + yi];
                ab = p[p[xi] + yi + 1];
                ba = p[p[xi + 1] + yi];
                bb = p[p[xi + 1] + yi + 1];

                //нахождение взвешенного среднего
                double average = lerp(sy, lerp(sx,
                                                                 gradient(aa, x, y, 0),
                                                                 gradient(ba, x - 1, y, 0)),
                                                          lerp(sx,
                                                                 gradient(ab, x, y - 1, 0),
                                                                 gradient(bb, x - 1, y - 1, 0)));

                return map(average, -1, 1, 0, 1);
            }

            double accumulatedNoise2D(double x, double y, meta_data_t &meta_data)
            {
                 double lacunarity = meta_data.lacunarity;
                 double gain = meta_data.gain;
                 int octaves = meta_data.octaves;

                 double amplitude = 1;
                 double frequency = 1;
                 double result = 0.0;
                 double maxVal = 0.0;

                 for (; octaves > 0; octaves--)
                 {
                     result += noise2D(x * frequency, y * frequency) * amplitude;
                     maxVal += amplitude;

                     amplitude *= gain;
                     frequency *= lacunarity;
                 }

                 double e = result / maxVal;
                 return e;
            }
    };
}

#endif
