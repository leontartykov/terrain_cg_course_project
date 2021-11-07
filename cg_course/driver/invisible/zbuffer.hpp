#include "driver/invisible/zbuffer.h"

ZBuffer::ZBuffer(){
    //что да придумается сюда
}

ZBuffer::ZBuffer(int width, int height)
{
    for (int i = 0; i < width; i++)
    {
        std::vector<int> temp;
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

double ZBuffer::get_z_point(int index_i, int index_j){
    return _zbuffer_matrix[index_i][index_j];
}
