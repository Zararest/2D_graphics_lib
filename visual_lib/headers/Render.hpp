#include <SFML/Graphics.hpp>
#include <ctime>
#include <unistd.h>
#include "../../vector_lib/headers/Vector_lib.hpp"

class Render{

private:

    sf::RenderWindow window;

    sf::Uint8* screen_pixels;

    sf::Texture screen;

    sf::Sprite sprite;

    sf::Event cur_event;

    sf::Color brush_color;

    int vertical_window_size;

    double frame_time;

    long int time_of_last_frame;

    int horizontal_window_size;

    bool in_focus;

public:

    Render(int horizontal_size, int vertical_size);

    Render(const Render&) = delete;

    Render(Render&&) = delete;

    ~Render();

    Render& operator = (Render&&) = delete;

    Render& operator = (const Render&) = delete;

    void check_event();

    bool check_open();

    void resize_pixels_arr(int new_hor_size, int new_vert_size);

    void new_frame(sf::Uint8* new_pixels, int size_x, int size_y);

    void new_fast_frame(sf::Uint8* new_pixels);

    void hold_frame();

    void set_brush_color(sf::Color new_color);

    void set_frame_rate(int frames_per_second);

    void set_pixel_color(int x ,int y, sf::Color pixel_color);

    sf::Color get_pixel_color(int x, int y);

    void draw_line(Point& starting_point, Point& end_point, int width);

    void draw_line(Point& starting_point, Vector& line_vector, int width);

    void draw_segment(Point& starting_point, Point& end_point, int width);

    void draw_segment(Point& starting_point, Vector& line_vector, int width);

    void set_background_color(sf::Color background_color);
};
