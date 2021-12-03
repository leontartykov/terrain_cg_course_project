#include "vector_3.hpp"
#include "driver/geometry/point/point.hpp"

Vector3D normal(Point<double> point_1, Point<double> point_2, Point<double> point_3)
{
    Vector3D normal_vector;
    Point<int> int_point_1(point_1.get_x(), point_1.get_y(), point_1.get_z());
    Point<int> int_point_2(point_3.get_x(), point_2.get_y(), point_2.get_z());
    Point<int> int_point_3(point_2.get_x(), point_3.get_y(), point_3.get_z());

    double vector_1_x = 0, vector_1_y = 0, vector_1_z = 0;
    double vector_2_x = 0, vector_2_y = 0, vector_2_z = 0;

    vector_1_x = int_point_2.get_x() - int_point_1.get_x();
    vector_1_y = int_point_2.get_y() - int_point_1.get_y();
    vector_1_z = int_point_2.get_z() - int_point_1.get_z();

    vector_2_x = int_point_3.get_x() - int_point_1.get_x();
    vector_2_y = int_point_3.get_y() - int_point_1.get_y();
    vector_2_z = int_point_3.get_z() - int_point_1.get_z();

    double a = vector_1_y * vector_2_z - vector_1_z * vector_2_y;
    double b = vector_2_x * vector_1_z - vector_2_z * vector_1_x;
    double c = vector_1_x * vector_2_y - vector_1_y * vector_2_x;

    normal_vector.set_vector(a, b, c);

    return normal_vector;
}

double dot_product(Vector3D &vector_1, Vector3D &vector_2){
    return vector_1.X() * vector_2.X() + vector_1.Y() * vector_2.Y() + vector_1.Z() * vector_2.Z();
}
