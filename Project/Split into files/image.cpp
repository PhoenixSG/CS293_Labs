#include "image.h"
#include "dimension_set.h"

void image_sfml::save_image_parameters(long double x_shift, long double y_shift, int resolution, float zoom, sf::VertexArray vertexarray)
{
    this->resolution = resolution;
    this->x_shift = x_shift;
    this->y_shift = y_shift;
    this->zoom = zoom;

    this->vertexarray;
}

void image_sfml::retrieve_image_parameters(long double &x_shift, long double &y_shift, int &resolution, float &zoom, sf::VertexArray &vertexarray)
{
    x_shift = this->x_shift;
    y_shift = this->y_shift;
    zoom = this->zoom;
    resolution = this->resolution;
}

image_sfml::image_sfml()
{
    this->x_shift = -width/2;
    this->y_shift = -height/2;
    this->zoom = 256;
    this->resolution = 100;
}
