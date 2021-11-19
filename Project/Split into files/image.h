#include "SFML/Graphics.hpp"

class image_sfml
{
private:
    int x_shift;
    int y_shift;
    int resolution;
    float zoom; 
    sf::VertexArray vertexarray;

public:
    image_sfml();
    void save_image_parameters(int x_shift, int y_shift, int resolution,float zoom,sf::VertexArray vertexarray);
    void retrieve_image_parameters(int &x_shift, int &y_shift, int &resolution,float &zoom,sf::VertexArray &vertexarray);
};