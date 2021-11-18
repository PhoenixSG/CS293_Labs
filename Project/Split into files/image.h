#include "SFML/Graphics.hpp"

class image_sfml
{
private:
    long double x_shift;
    long double y_shift;
    int resolution;
    float zoom; 
    sf::VertexArray vertexarray;

public:
    image_sfml();
    void save_image_parameters(long double x_shift, long double y_shift, int resolution,float zoom,sf::VertexArray vertexarray);
    void retrieve_image_parameters(long double &x_shift, long double &y_shift, int &resolution,float &zoom,sf::VertexArray &vertexarray);
};