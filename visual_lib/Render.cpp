#include "headers/Render.hpp"

int resize_count = 0;

Render::Render(int horizontal_size, int vertical_size):

    window(sf::VideoMode(horizontal_size, vertical_size), "UwU"),
    screen(),
    sprite()
{

    vertical_window_size = vertical_size;
    horizontal_window_size = horizontal_size;

    in_focus = true;

    screen.create(horizontal_window_size, vertical_window_size);
    sprite.setTexture(screen, true);
    screen_pixels = new sf::Uint8[vertical_window_size * horizontal_window_size * 4];
}

Render::~Render(){

    if (window.isOpen()){

        window.close();
    }
    
    delete screen_pixels;
}

void Render::resize_pixels_arr(int new_hor_size, int new_vert_size){

    sf::Uint8* new_pixels = new sf::Uint8[new_hor_size * new_hor_size * 4];

    for (int i = 0; i < new_vert_size; i++){

        for (int j = 0; j < new_hor_size; j++){

            if ((i <= vertical_window_size) && (j <= horizontal_window_size)){

                new_pixels[(i * new_hor_size + j) * 4 + 0] = screen_pixels[(i * horizontal_window_size + j) * 4 + 0];
                new_pixels[(i * new_hor_size + j) * 4 + 1] = screen_pixels[(i * horizontal_window_size + j) * 4 + 1];
                new_pixels[(i * new_hor_size + j) * 4 + 2] = screen_pixels[(i * horizontal_window_size + j) * 4 + 2];
                new_pixels[(i * new_hor_size + j) * 4 + 3] = screen_pixels[(i * horizontal_window_size + j) * 4 + 3];
            } else{
                
                new_pixels[(i * new_hor_size + j) * 4 + 0] = 0;
                new_pixels[(i * new_hor_size + j) * 4 + 1] = 0;
                new_pixels[(i * new_hor_size + j) * 4 + 2] = 0;
                new_pixels[(i * new_hor_size + j) * 4 + 3] = 255;
            }
        }
    }
}

void Render::check_event(){

    window.pollEvent(cur_event);

    if (cur_event.type == sf::Event::Closed){

        if (window.isOpen()){

            window.close();
        }
    }

    if (cur_event.type == sf::Event::Resized){

        this->resize_pixels_arr(cur_event.size.width, cur_event.size.height);
        resize_count++;
        vertical_window_size = cur_event.size.height;
        horizontal_window_size = cur_event.size.width;
    }

    if (cur_event.type == sf::Event::LostFocus){

        in_focus = false;
    }

    if (cur_event.type == sf::Event::GainedFocus){

        in_focus = true;
    }
}

void Render::new_frame(sf::Uint8* new_pixels, int size_x, int size_y){

    if (new_pixels != NULL){

        for (int i = 0; i < vertical_window_size; i++){

            for (int j = 0; j < horizontal_window_size; j++){

                if ((j <= size_x) || (i <= size_y)){
                    
                    screen_pixels[(i * horizontal_window_size + j) * 4 + 0] = new_pixels[(i * size_x + j) * 4 + 0];
                    screen_pixels[(i * horizontal_window_size + j) * 4 + 1] = new_pixels[(i * size_x + j) * 4 + 1];
                    screen_pixels[(i * horizontal_window_size + j) * 4 + 2] = new_pixels[(i * size_x + j) * 4 + 2];
                    screen_pixels[(i * horizontal_window_size + j) * 4 + 3] = new_pixels[(i * size_x + j) * 4 + 3];
                } else{

                    screen_pixels[(i * horizontal_window_size + j) * 4 + 0] = 0;
                    screen_pixels[(i * horizontal_window_size + j) * 4 + 1] = 0;
                    screen_pixels[(i * horizontal_window_size + j) * 4 + 2] = 0;
                    screen_pixels[(i * horizontal_window_size + j) * 4 + 3] = 0;
                }
            }  
        }
    }

    screen.update(screen_pixels);
    window.clear();
    window.draw(sprite);
    window.display();
}

void Render::new_fast_frame(sf::Uint8* new_pixels){

    screen.update(new_pixels);
    window.clear();
    window.draw(sprite);
    window.display();
}

void Render::hold_frame(){

    screen.update(screen_pixels);
    window.clear();
    window.draw(sprite);
    window.display();
}

bool Render::check_open(){

    return window.isOpen();
}
