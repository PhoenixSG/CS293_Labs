#include "SFML/Graphics.hpp"
#include <string>

//This is the image class which stores all the data required to initialise the variables and also plot the image.
//It basically stores everything for a snapshot in order to prevent redundant calculation.
class image_sfml
{
private:
    int x_shift;
    int y_shift;
    int resolution;
    float zoom;
    std::string name;
    sf::VertexArray vertexarray;

public:
    image_sfml();
    void save_image_parameters(int x_shift, int y_shift, int resolution, float zoom, sf::VertexArray vertexarray);
    void retrieve_image_parameters(int &x_shift, int &y_shift, int &resolution, float &zoom, sf::VertexArray &vertexarray);
    void set_name(std::string name_input);
    std::string get_name();
};