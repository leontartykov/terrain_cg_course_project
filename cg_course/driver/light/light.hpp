#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "light.h"


Light::Light()
{
    _position.set_vector(150, 100, 150);
    _direction.set_vector(0, 0, 0);
}

Light::~Light(){
}

void Light::adjust_illumination()
{
    /*
    int width = zbuffer.get_width();
    int height = zbuffer.get_height();

    std::cout << width << " " << height << std::endl;
    std::vector<std::vector<QColor>> color = zbuffer.get_color_matrix();
    int r = 0, g = 0, b = 0;

    double i_ambient = 0, i_diffuse = 0, i_specular = 0;
    double i_result = 0;

    i_ambient = (*this).ia() * (*this).ka();
    i_result = i_ambient;



    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++)
        {
            if (zbuffer.is_background(i, j) == false)
            {
                color[i][j].getRgb(&r, &g, &b);
                r *= i_result;
                g *= i_result;
                b *= i_result;
                QRgb rgb = qRgb(r, g, b);
                zbuffer.set_color(i, j, rgb);
            }
        }
    }

    /*
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++)
        {
            if (zbuffer.is_background(i, j) == false && i < width - 1 && j < height - 1)
            {
                std::cout << "i = " << i << " j = " << j << std::endl;
                std::cout << "Точки (исходная и соседняя):";
                Point<double> point_1(i, j, zbuffer.get_z_point(i, j));
                Point<double> point_2(i, j + 1, zbuffer.get_z_point(i, j +1));
                Point<double> point_3(i + 1, j, zbuffer.get_z_point(i + 1, j));
                point_1.output_point();
                point_2.output_point();
                point_3.output_point();
                Vector3D normal_vector = normal(point_1, point_2, point_3);
                std::cout << "Вектор нормали к точке: ";
                normal_vector.output();
                return;
            }
        }
    }*/
}

Vector3D<int> Light::get_position(){
    return _position;
}

void Light::set_position(int x, int y, int z){
    _position.set_vector(x, y, z);
}

void Light::output_light_position(){
    _position.output();
}

#endif
