#include <iostream>
#include <new>
#include <cstdlib> // для функций rand() и srand()
#include "driver/geometry/matrix/matrix.h"

double **form_matrix_double(int size_matrix)
{
    std::srand(static_cast<unsigned int>(time(0)));
    double **matrix = nullptr;
    matrix = new double *[size_matrix];

    for (int i = 0; i < size_matrix; i++){
        matrix[i] = new double[size_matrix]{};
    }

    return matrix;
}

void output_matrix(double **matrix, int size_matrix)
{
    for (int i = 0; i < size_matrix; i++)
    {
        for (int j = 0; j < size_matrix; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}
