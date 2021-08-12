#include "Render.hpp"
#include "vector_lib/headers/Matrix.hpp"
#include <math.h>
#include <cassert>

#define HOR_SIZE 1200
#define VERT_SIZE 700

Vector func(Vector tmp){

    Vector cur_vector(11, 22);

    return cur_vector;
}

int main(){

    Vector new_vector(20, 1);
    Point new_point(2, 2);

    new_vector = 3 * new_vector + new_vector;

    if (new_point == new_point){

        printf("OK\n");
    }
    //sec_vector.print(stdout);
    //new_vector.print(stdout);
    /*Render new_window(HOR_SIZE, VERT_SIZE);
    sf::Uint8* main_arr = new sf::Uint8[HOR_SIZE * VERT_SIZE * 4];
    int count = 0;

    for (int i = 0; i  < VERT_SIZE; i++){

        for (int j = 0; j < HOR_SIZE; j++){

            if (i + j > 300){

                main_arr[(i * HOR_SIZE + j) * 4 + 0] = 255;
                main_arr[(i * HOR_SIZE + j) * 4 + 1] = 255;
                main_arr[(i * HOR_SIZE + j) * 4 + 2] = 255;
                main_arr[(i * HOR_SIZE + j) * 4 + 3] = 255;
            } else{

                main_arr[(i * HOR_SIZE + j) * 4 + 0] = 0;
                main_arr[(i * HOR_SIZE + j) * 4 + 1] = 0;
                main_arr[(i * HOR_SIZE + j) * 4 + 2] = 0;
                main_arr[(i * HOR_SIZE + j) * 4 + 3] = 255;
            }
        }
    }

    count = 0;
    new_window.new_frame(main_arr, HOR_SIZE, VERT_SIZE);

    while (new_window.check_open() == true){

        new_window.hold_frame();
        count++;
        new_window.check_event();
    }
    
    printf("count = %i\n", count);*/
}
