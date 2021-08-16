#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <math.h>
#include <cmath>
#include <string.h>

char my_getc(FILE* input);
class Point;
class Vector;
class Matrix;

class Matrix{

protected:

    int rows_count;
    int columns_count;

    float* data;

public:

    Matrix(int vertical_size, int horizontal_size, float* numbers);

    Matrix(int vertical_size, int horizontal_size, float diag_elem);             //диагональная матрица с элементом diag_elem

    Matrix(FILE* input);

    Matrix(const Matrix& old_obj);                                               //конструктор копирования

    Matrix(Matrix&& old_obj);                                                     //конструктор перемещения(для подачи в оператор присвыаивания итд)

    ~Matrix();
    
    void print(FILE* output_stream);

    float determinant();

    bool is_quadratic();

    void transpose();

    Matrix& operator = (const Matrix& rv);                                         //оператор присваивания для lvalue = lvalue

    Matrix& operator = (Matrix&& rv);                                              //оператор присваивания перемещением

    float* operator [] (const int row_number);                                           //после выполения этого оператора будет еще одно обращение [](нет проверки на выход за границы)(номера строк с 0)

    const float* operator [] (const int row_number) const;                         //оператор для константных объектов класса

    friend Matrix operator * (const Matrix& L_matr, const Matrix& R_matr);

    friend Matrix operator * (const Matrix& matr, float number);

    friend Matrix operator * (float number, const Matrix& matr);
 
    friend Matrix operator + (const Matrix& L_matr, const Matrix& R_matr);         //если не совпадают размеры, то ассерт

    friend Matrix operator - (const Matrix& L_matr, const Matrix& R_matr);    

    friend float cos(const Matrix& L_matr, const Matrix& R_matr);

    friend bool same_size(const Matrix& L_matr, const Matrix& R_matr);   

    friend bool could_be_mult(const Matrix& L_matr, const Matrix& R_matr);

    friend float minor(const Matrix& init_matr, int deleted_rows_count, int* deleted_columns);

    friend void print_minor(const Matrix& init_matr, int deleted_rows_count, int* deleted_columns);

    friend class Vector;

    friend class Point;
};


class Vector: protected Matrix{

public:

    Vector(float x, float y);

    Vector(float x, float y, float z);

    Vector(int number_of_coordinates, float* arr_of_coordinates);

    Vector(Point& fir_point, Point& sec_point);

    ~Vector();

    int length();

    float modul();

    void normalize();

    void print(FILE* output_stream);

    float& operator [] (const int coordinate_number); 

    const float& operator[](const int coordinate_number) const;

    friend Vector operator * (const Vector& vectr, float number);

    friend Vector operator * (float number, const Vector& vectr);

    friend Vector operator * (Matrix& matr, Vector& vectr);

    friend Vector operator * (Vector& vectr, Matrix& matr);
 
    friend Vector operator + (const Vector& L_vectr, const Vector& R_vectr);         //если не совпадают размеры, то ассерт

    friend Vector operator - (const Vector& L_vectr, const Vector& R_vectr);

    friend class Matrix;

    friend class Point;
};


class Point: protected Vector{

public:

    Point(float x, float y);

    Point(float x, float y, float z);

    Point(int num_of_coordinates, float* arr_of_coordinates);

    ~Point();

    int length();

    void print(FILE* output_stream);

    const float& operator [] (const int coordinate_number) const; 

    float& operator [] (const int coordinate_number);

    friend bool operator == (const Point& L_point, const Point& R_point);

    friend bool operator != (const Point& L_point, const Point& R_point);

    friend float distance(Point& fir_point, Point& sec_point);

    friend class Vector;

    friend class Matrix;
};

#endif
