#include "visual_lib/headers/Render.hpp"
#include "vector_lib/headers/Vector_lib.hpp"
#include <iostream>

#define HOR_SIZE 1200
#define VERT_SIZE 500
#define VECTOR_LEN 5

Matrix ninety_degree_rotation(){

    float tmp_data[4] = {0, -1, 1, 0};
    Matrix rotation_matr(2, 2, tmp_data);

    return rotation_matr;
}

Point draw_line(Point base_point, int number_of_rotation, Render& cur_canvas){

    Matrix rot_matrix(2, 2, 1);
    Vector vector_of_line((float)VECTOR_LEN, 0);
    Point end_point(base_point);

    for (int i = 0; i < number_of_rotation; i++){

        rot_matrix = rot_matrix * ninety_degree_rotation();
    }

    vector_of_line = rot_matrix * vector_of_line ;
    cur_canvas.draw_segment(base_point, vector_of_line, 1);

    end_point[0] += vector_of_line[0];
    end_point[1] += vector_of_line[1];

    return end_point;
}

Point fractal(int iteration_number, int number_of_rotation, Point cur_base_point, Render& cur_canvas){

    Point tmp_point(2, -1);
    
    number_of_rotation = number_of_rotation % 4;

    if (iteration_number > 1){

        tmp_point = fractal(iteration_number - 1, number_of_rotation, cur_base_point, cur_canvas);
        tmp_point = fractal(iteration_number - 1, number_of_rotation + 1, tmp_point, cur_canvas);

        return tmp_point;
    } else{

        return draw_line(cur_base_point, number_of_rotation, cur_canvas);
    }
}

int main(){ 

    Render new_window(HOR_SIZE, VERT_SIZE);
    Point base_point(900, 500);
    
    new_window.set_brush_color(sf::Color::White);

    fractal(14, 0, base_point, new_window);

    while (new_window.check_open() == true){

        new_window.hold_frame();

        new_window.check_event();
    }
}
