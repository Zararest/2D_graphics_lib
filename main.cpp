#include "visual_lib/headers/Render.hpp"
#include "vector_lib/headers/Vector_lib.hpp"
#include <math.h>
#include <cassert>
#include <random> 

#define HOR_SIZE 1200
#define VERT_SIZE 700

Vector func(Vector tmp){

    Vector cur_vector(11, 22);

    return cur_vector;
}

int main(){

    std::mt19937 mersenne(static_cast<unsigned int>(time(0))); 

    Render new_window(HOR_SIZE, VERT_SIZE);
    sf::Uint8* main_arr = new sf::Uint8[HOR_SIZE * VERT_SIZE * 4];
    Point fir_point(300, 300), sec_point(50, 50), thrd_point(300, 200);
    int count = 0, cur_number = 0;

    for (int i = 0; i  < VERT_SIZE; i++){

        for (int j = 0; j < HOR_SIZE; j++){
            
            cur_number = mersenne() % 255;

            main_arr[(i * HOR_SIZE + j) * 4 + 0] = 255;
            main_arr[(i * HOR_SIZE + j) * 4 + 1] = 255;
            main_arr[(i * HOR_SIZE + j) * 4 + 2] = 255;
            main_arr[(i * HOR_SIZE + j) * 4 + 3] = 255;
        }
    }

    count = 0;
    new_window.new_frame(main_arr, HOR_SIZE, VERT_SIZE);

    new_window.draw_segment(fir_point, sec_point, 3);

    new_window.set_frame_rate(30);

    while (new_window.check_open() == true){

        new_window.hold_frame();
        count++;
        new_window.check_event();
    }
    
    printf("count = %i\n", count);
}
