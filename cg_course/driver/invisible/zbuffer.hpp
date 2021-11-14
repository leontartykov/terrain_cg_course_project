#include "driver/invisible/zbuffer.h"

ZBuffer::ZBuffer(){
    //что да придумается сюда
}

ZBuffer::ZBuffer(int width, int height)
{
    for (int i = 0; i < width; i++)
    {
        std::vector<double> temp;
        for (int j = 0; j < height; j++){
            temp.push_back(std::numeric_limits<int>::min());
        }
        _zbuffer_matrix.push_back(temp);
    }
}

ZBuffer::~ZBuffer(){
    //что да придумается сюда
}

void ZBuffer::output()
{
    int row = _zbuffer_matrix.size(),
         column = _zbuffer_matrix[0].size();
    for (int i = 0; i < row; i++)
    {
        std::cout << "(";
        for (int j = 0; j < column; j++){
            std::cout << _zbuffer_matrix[i][j] << ", ";
        }
        std::cout << ");" << std::endl;
    }
}

double ZBuffer::get_z_point(int index_i, int index_j) const{
    return _zbuffer_matrix[index_i][index_j];
}

void ZBuffer::set_z_point(double value, int index_i, int index_j){
    _zbuffer_matrix[index_i][index_j] = value;
}

std::vector<std::vector<double>> &ZBuffer::get_zbuffer_matrix(){
    return _zbuffer_matrix;
}
