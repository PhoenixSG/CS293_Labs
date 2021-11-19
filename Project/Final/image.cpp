#ifndef IMAGE_OBJECT
#define IMAGE_OBJECT

#include "image.h"
#include "dimension_set.h"
#include <string>


void image_sfml::save_image_parameters(int x_shift, int y_shift, int resolution, float zoom, sf::VertexArray vertexarray)
{
    this->resolution = resolution;
    this->x_shift = x_shift;
    this->y_shift = y_shift;
    this->zoom = zoom;

    this->vertexarray = vertexarray;
}

void image_sfml::retrieve_image_parameters(int &x_shift, int &y_shift, int &resolution, float &zoom, sf::VertexArray &vertexarray)
{
    x_shift = this->x_shift;
    y_shift = this->y_shift;
    zoom = this->zoom;
    resolution = this->resolution;
    vertexarray = this->vertexarray;
}

image_sfml::image_sfml()
{
    this->x_shift = -width / 2;
    this->y_shift = -height / 2;
    this->zoom = 256;
    this->resolution = 100;
    this->name = "";
}
void image_sfml::set_name(std::string name_input)
{
    this->name.assign(name_input);
    std::cout<<this->name<<std::endl;
}
std::string image_sfml::get_name()
{
    return std::string(this->name);
}
#endif