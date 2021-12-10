#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <iterator>
#include <algorithm>
#include <random>

#include "driver/landscape/landscape.h"

namespace perlin
{
    //fade function f(t) = 6t^5 - 15t^4 + 10t^3
    double fade(double t){
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    //bilinear interpolation
    double lerp(double t, double a, double b){
        //std::cout << "a = " << a << ", b = " << b << ", t = " << t << std::endl;
        return a + t * (b - a);
    }

    //map function
    double map(double value, double old_min, double old_max, double new_min, double new_max)
    {
        //get proportion in original range
        double proportion = (value - old_min) / (old_max - old_min);
        /*std::cout << "proportion = " << proportion << std::endl;
        std::cout << "proportion = " << new_min << std::endl;
        std::cout << "proportion = " << new_max << std::endl;
        std::cout << "lerp(proportion, new_min, new_max) = " << lerp(proportion, new_min, new_max) << std::endl;*/
        return lerp(proportion, new_min, new_max);
    }

    //gradient function - calculate dot product between gradient vector and distanse vector
    double gradient(int hash, double x, double y, double z)
    {
        //convert the last 4 bits of the hash into one of 12 possible gradients
        int h = hash & 0b1111; //hash & 15 = hash % 16 = get last 4 bits

        //if first bit is 1, set to x, otherwise set to y
        double u = h < 0b1000 ? x : y;

        // if first/second bits 0, set to y
        // if first/second bits 1, set to x
        // else set to z
        double v = h < 0b0100 ? y : h == 0b1100 || h == 0b1110 ? x : z;

        // make u, v negative based on the last 2 bits, the add results
        // adding results is like adding dot product because gradient components are 1,
        // so results of dot product is adding distance components
        return ((h & 0b0001) == 0 ? u : -u) + ((h & 0b0010) == 0 ? v : -v);
    }

    class Perlin
    {
        private:
            //permutation table
            unsigned char p[512];

            //current seed
            unsigned int seed;

        public:
            //constructor
            Perlin(unsigned int seed){
                reseed(seed);
            }

            //reseed the class
            void reseed(unsigned int _seed)
            {
                seed = _seed;

                //populate permutation table in order
                for (unsigned int i = 0; i < 256; i++){
                    p[i] = i;
                }

                //shuffle
                std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

                //duplicate array for overflow
                for (unsigned int i = 0; i < 256; i++)
                    p[256 + i] = p[i];
            }

            /*
             * perlin methods
            */

            // 1D Perlin noise
            double noise1D(double x)
            {
                  //find the smallest point of interval containing target
                int xi = (int)(std::floor(x)) & 255; // = % 256

                //get decimal value of each component
                x -= std::floor(x);

                //get smooth value from fade function (becomes weight for each dimension)
                double sx = fade(x);

                //get hash value for all neighboring points
                int a; //, b;
                a = p[xi];
                // b = p[xi + 1];

                //get weighted average
                double average = lerp(sx, gradient(a, x, 0, 0), gradient(a, x - 1, 0, 0));

                //return average mapped from [-1, 1] to [0, 1]
                return map(average, -1, 1, 0, 1);
            }

            // 2D Perlin noise
            double noise2D(double x, double y)
            {
                //find the smallest point of square containing target
                int xi = (int)(std::floor(x)) & 255;
                int yi = (int)(std::floor(x)) & 255;

                //get decimal value of each component
                x -= std::floor(x);
                y -= std::floor(y);

                //get smooth value from fade function (becomes weight for each dimension)
                double sx = fade(x);
                double sy = fade(y);

                unsigned char aa, ab, ba, bb;
                aa = p[p[xi      ] + yi      ];
                ab = p[p[xi      ] + yi + 1];
                ba = p[p[xi + 1] + yi      ];
                bb = p[p[xi + 1] + yi + 1];

                //get weighted average
                double average = lerp(sy, lerp(sx, gradient(aa, x, y, 0), gradient(ab, x - 1, y, 0)),
                                                      lerp(sx, gradient(ba, x, y - 1, 0), gradient(bb, x - 1, y - 1, 0)));

                //std::cout << "RETURN VALUE: " << "\\" << map(average, -1, 1, 0, 1) << "\\" << std::endl;
                return map(average, -1, 1, 0, 1);
            }

            double accumulatedNoise2D(double x, double y, meta_data_t &meta_data)
             {
                 double gain = meta_data.gain;
                 double lacunarity = meta_data.lacunarity;
                 double amplitude = meta_data.amplitude;
                 double frequency = meta_data.frequency;

                 double result = 0.0;
                 double maxVal = 0.0; // used to normalize result

                 //qDebug() << "count_octaves = " << meta_data.octaves;
                 int octaves = meta_data.octaves;
                 for (; octaves > 0; octaves--) {
                     result += noise2D(x * frequency, y * frequency) * amplitude;

                     maxVal += amplitude;

                     amplitude *= gain;
                     frequency *= lacunarity;
                 }

                 // return normalized result
                 return result / maxVal;
             }
    };
}

#endif
