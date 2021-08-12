#include <SFML/Graphics.hpp>

class Render{

private:

    sf::RenderWindow window;

    sf::Uint8* screen_pixels;

    sf::Texture screen;

    sf::Sprite sprite;

    sf::Event cur_event;

    int vertical_window_size;

    int horizontal_window_size;

    bool in_focus;

public:

    Render(int horizontal_size, int vertical_size);

    Render(const Render&) = delete;

    Render(Render&&) = delete;

    ~Render();

    Render& operator = (Render&&) = delete;

    Render& operator = (const Render&) = delete;

    virtual void check_event();

    bool check_open();

    void resize_pixels_arr(int new_hor_size, int new_vert_size);

    void new_frame(sf::Uint8* new_pixels, int size_x, int size_y);

    void new_fast_frame(sf::Uint8* new_pixels);

    void hold_frame();
};
