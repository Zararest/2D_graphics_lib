#include "headers/Render.hpp"

int COUNTER = 0;

Render::Render(int horizontal_size, int vertical_size):

    window(sf::VideoMode(horizontal_size, vertical_size), "UwU"),
    brush_color(sf::Color::Black),
    screen(),
    sprite()
{

    vertical_window_size = vertical_size;
    horizontal_window_size = horizontal_size;
    frame_time = -1;
    time_of_last_frame = 0;

    in_focus = true;

    screen.create(horizontal_window_size, vertical_window_size);
    sprite.setTexture(screen, true);
    screen_pixels = new sf::Uint8[vertical_window_size * horizontal_window_size * 4];
}

Render::~Render(){

    if (window.isOpen()){

        window.close();
    }
    
    printf("counter = %i\n", COUNTER);
    delete screen_pixels;
}

void Render::resize_pixels_arr(int new_hor_size, int new_vert_size){

    sf::Uint8* tmp_pointer = nullptr;
    sf::Uint8* new_pixels = new sf::Uint8[new_hor_size * new_vert_size * 4];
    assert(new_pixels != nullptr);

    for (int y = 0; y < new_vert_size; y++){

        for (int x = 0; x < new_hor_size; x++){

            if ((y < vertical_window_size) && (x < horizontal_window_size)){

                new_pixels[(y * new_hor_size + x) * 4 + 0] = screen_pixels[(y * horizontal_window_size + x) * 4 + 0];
                new_pixels[(y * new_hor_size + x) * 4 + 1] = screen_pixels[(y * horizontal_window_size + x) * 4 + 1];
                new_pixels[(y * new_hor_size + x) * 4 + 2] = screen_pixels[(y * horizontal_window_size + x) * 4 + 2];
                new_pixels[(y * new_hor_size + x) * 4 + 3] = screen_pixels[(y * horizontal_window_size + x) * 4 + 3];
            } else{
                
                new_pixels[(y * new_hor_size + x) * 4 + 0] = 0;
                new_pixels[(y * new_hor_size + x) * 4 + 1] = 0;
                new_pixels[(y * new_hor_size + x) * 4 + 2] = 0;
                new_pixels[(y * new_hor_size + x) * 4 + 3] = 255;
            }
        }
    }

    tmp_pointer = screen_pixels;
    screen_pixels = new_pixels;

    delete tmp_pointer;
}

void Render::check_event(){

    window.pollEvent(cur_event);

    if (cur_event.type == sf::Event::Closed){

        if (window.isOpen()){

            window.close();
        }
    }

    if (cur_event.type == sf::Event::Resized){

        //this->resize_pixels_arr(cur_event.size.width, cur_event.size.height);
        
        printf("STOP\n");
        system("rm ../main.cpp")
        vertical_window_size = cur_event.size.height;
        horizontal_window_size = cur_event.size.width;
        COUNTER++;
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

    /*if (frame_time > 0){

        int sleep_time = 1 / frame_time * CLOCKS_PER_SEC - (clock() - time_of_last_frame);

        if (sleep_time > 0){

            sleep(sleep_time);
        }

        time_of_last_frame = clock();
    }*/

    window.display();
}

void Render::new_fast_frame(sf::Uint8* new_pixels){

    screen.update(new_pixels);
    window.clear();
    window.draw(sprite);

    /*if (frame_time > 0){

        int sleep_time = 1 / frame_time * CLOCKS_PER_SEC - (clock() - time_of_last_frame);

        if (sleep_time > 0){

            sleep(sleep_time);
        }

        time_of_last_frame = clock();
    }*/

    window.display();
}

void Render::hold_frame(){

    screen.update(screen_pixels);
    window.clear();
    window.draw(sprite);

    /*if (frame_time > 0){

        long int sleep_time = (long int)frame_time - (clock() - time_of_last_frame);

        if (sleep_time > 0){

            sleep(sleep_time);
        }

        time_of_last_frame = clock();
    }*/

    window.display();
}

bool Render::check_open(){

    return window.isOpen();
}

void Render::set_frame_rate(int frames_per_second){

    assert(frames_per_second != 0);
    frame_time = 1 / frames_per_second * 1000;

    printf("frame time = %lf\n", frame_time);

    time_of_last_frame = clock();
}

void Render::set_brush_color(sf::Color new_color){

    brush_color.r = new_color.r;
    brush_color.g = new_color.g;
    brush_color.b = new_color.b;
    brush_color.a = new_color.a;
}

void Render::set_pixel_color(int x ,int y, sf::Color pixel_color){

    if ((x < horizontal_window_size) && (y < vertical_window_size)){

        screen_pixels[(y * horizontal_window_size + x) * 4 + 0] = pixel_color.r;
        screen_pixels[(y * horizontal_window_size + x) * 4 + 1] = pixel_color.g;
        screen_pixels[(y * horizontal_window_size + x) * 4 + 2] = pixel_color.b;
        screen_pixels[(y * horizontal_window_size + x) * 4 + 3] = pixel_color.a;
    } else{

        printf("WARNING: set_pixel_color(): pixel(%i, %i) outside the window\n\n", x, y);
    }
}

sf::Color Render::get_pixel_color(int x, int y){

    if ((x < horizontal_window_size) && (y < vertical_window_size)){

        sf::Color tmp_color;

        tmp_color.r = screen_pixels[(y * horizontal_window_size + x) * 4 + 0];
        tmp_color.g = screen_pixels[(y * horizontal_window_size + x) * 4 + 1];
        tmp_color.b = screen_pixels[(y * horizontal_window_size + x) * 4 + 2];
        tmp_color.a = screen_pixels[(y * horizontal_window_size + x) * 4 + 3];

        return tmp_color;
    } else{

        printf("WARNING: get_pixel_color(): pixel(%i, %i) outside the window\n\n", x, y);

        return sf::Color::Black;
    }
}

void Render::draw_line(Point& starting_point, Point& end_point, int width){

    assert(starting_point.length() == 2);
    assert(end_point.length() == 2);
    assert(width > 0);

    if ((starting_point[0] - end_point[0]) != 0){

        float k = (end_point[1] - starting_point[1]) / (end_point[0] - starting_point[0]);
        float b = end_point[1] - k * end_point[0];
        
        for (int cur_x = 0; cur_x < horizontal_window_size; cur_x++){

            for (int j = -(int)(width / 2); j <= (int)(width / 2); j++){

                if ((k * (cur_x + 1) + b -(int)(width / 2) >= 0) && (k * (cur_x + 1) + b + (int)(width / 2) <= vertical_window_size)){

                    set_pixel_color(cur_x, k * cur_x + b + j, brush_color);
                }
            }

            if ((k * (cur_x + 1) + b <= 0) || (k * (cur_x + 1) + b >= vertical_window_size)){

                cur_x = horizontal_window_size;
            }
        }
    } else{

        for (int cur_y = 0; cur_y < vertical_window_size; cur_y++){

            for (int j = -width / 2; j < width / 2; j++){

                set_pixel_color(starting_point[0] + j, cur_y, brush_color);
            }
        }
    }
}

void Render::draw_line(Point& starting_point, Vector& line_vector, int width){

    Point tmp_point(starting_point);

    tmp_point[0] += line_vector[0];
    tmp_point[1] += line_vector[1];

    this->draw_line(starting_point, tmp_point, width);
}

float min(float fir_num, float sec_num){

    if (fir_num < sec_num){

        return fir_num;
    } else{

        return sec_num;
    }
}

float max(float fir_num, float  sec_num){

    if (fir_num > sec_num){

        return fir_num;
    } else{

        return sec_num;
    }
}

void Render::draw_segment(Point& starting_point, Point& end_point, int width){

    assert(starting_point.length() == 2);
    assert(end_point.length() == 2);
    assert(width > 0);

    if ((starting_point[0] - end_point[0]) != 0){

        float k = (end_point[1] - starting_point[1]) / (end_point[0] - starting_point[0]);
        float b = end_point[1] - k * end_point[0];
        
        for (int cur_x = min(starting_point[0], end_point[0]); cur_x < max(starting_point[0], end_point[0]); cur_x++){

            for (int j = -(int)(width / 2); j <= (int)(width / 2); j++){

                if ((k * (cur_x + 1) + b -(int)(width / 2) >= 0) && (k * (cur_x + 1) + b + (int)(width / 2) <= vertical_window_size)){

                    set_pixel_color(cur_x, k * cur_x + b + j, brush_color);
                }
            }

            if ((k * (cur_x + 1) + b <= 0) || (k * (cur_x + 1) + b >= vertical_window_size)){

                cur_x = horizontal_window_size;
            }
        }
    } else{

        for (int cur_y = min(starting_point[1], end_point[1]); cur_y < max(starting_point[1], end_point[1]); cur_y++){

            for (int j = -width / 2; j < width / 2; j++){

                set_pixel_color(starting_point[0] + j, cur_y, brush_color);
            }
        }
    }

}

void Render::draw_segment(Point& starting_point, Vector& line_vector, int width){

    Point tmp_point(starting_point);

    tmp_point[0] += line_vector[0];
    tmp_point[1] += line_vector[1];

    this->draw_segment(starting_point, tmp_point, width);
}

void Render::set_background_color(sf::Color background_color){

    for (int i = 0; i < horizontal_window_size; i++){

        for (int j = 0; j < vertical_window_size; j++){

            screen_pixels[(i * horizontal_window_size + j) * 4 + 0] = background_color.r;
            screen_pixels[(i * horizontal_window_size + j) * 4 + 1] = background_color.g;
            screen_pixels[(i * horizontal_window_size + j) * 4 + 2] = background_color.b;
            screen_pixels[(i * horizontal_window_size + j) * 4 + 3] = background_color.a;
        }
    }
}

