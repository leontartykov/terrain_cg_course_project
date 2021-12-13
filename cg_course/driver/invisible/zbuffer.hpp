#include "driver/invisible/zbuffer.h"
#include "driver/transform/transform.h"

ZBuffer::ZBuffer():ZBuffer(SCREEN_WIDTH, SCREEN_HEIGHT){
    //что-то да придумается сюда
}

ZBuffer::ZBuffer(int width, int height)
{
    _width = width;
    _height = height;

    std::vector<double> temp;
    std::vector<QColor> temp_color;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            temp.push_back(std::numeric_limits<int>::min());
            temp_color.push_back(QColor(255, 255, 255));
        }
        _zbuffer_matrix.push_back(temp);
        _color_matrix.push_back(temp_color);
        temp.clear();
        temp_color.clear();
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

std::vector<std::vector<QColor>> &ZBuffer::get_color_matrix(){
    return _color_matrix;
}

double ZBuffer::get_width(){
    return _width;
}

double ZBuffer::get_height(){
    return _height;
}

bool ZBuffer::is_background(int index_i, int index_j)
{
    bool is_background = false;
    int r = 0, g = 0, b = 0;
    _color_matrix[index_i][index_j].getRgb(&r, &g, &b);
    if (r == 255 && g == 255 && b == 255)
        is_background = true;
    //qDebug() << "is_background = " << is_background;
    return is_background;
}

bool ZBuffer::is_equal_colors(int index_i, int index_j, QColor rgb)
{
    bool is_equal = false;
    int r_matrix = 0, g_matrix = 0, b_matrix = 0;
    _color_matrix[index_i][index_j].getRgb(&r_matrix, &g_matrix, &b_matrix);

    int r = 0, g = 0, b = 0;
    rgb.getRgb(&r, &g, &b);
    if (r_matrix == r && g_matrix == g && b_matrix == b){
        is_equal = true;
    }

    return is_equal;
}

void ZBuffer::set_color(int index_i, int index_j, QRgb rgb){
    _color_matrix[index_i][index_j].setRgb(rgb);
}

void ZBuffer::clear()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _zbuffer_matrix[i][j] = std::numeric_limits<int>::min();
            _color_matrix[i][j] = QColor(255, 255, 255);
        }
    }
}
