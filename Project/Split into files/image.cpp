#include "image.h"

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
