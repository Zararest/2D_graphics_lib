#include "headers/Vector_lib.hpp"

Matrix::Matrix(int vertical_size, int horizontal_size, float* numbers){//копирует данные из массива

    //printf("Конструктор матрицы по массиву\n\n");

    assert((vertical_size >= 0) && (horizontal_size >= 0));

    if (numbers != NULL){

        data = (float*)calloc(horizontal_size * vertical_size, sizeof(float));
        rows_count = vertical_size;
        columns_count = horizontal_size;

        memcpy(data, numbers, horizontal_size * vertical_size * sizeof(float));
    } else{

        printf("WARNING: in constructor Matrix(int, int, float*) float pointer is NULL\n");
        data = (float*)calloc(horizontal_size * vertical_size, sizeof(float));
        rows_count = vertical_size;
        columns_count = horizontal_size;

        for (int i = 0; i < horizontal_size * vertical_size; i++){

            data[i] = 0;
        }
    }
}

Matrix::Matrix(int vertical_size, int horizontal_size, float diag_elem){//заполняет таблицу нулями и если матрица квадратная, то диагональ это diag_elem

    //printf("Конструктор диагональной матрицы\n\n");

    assert((vertical_size >= 0) && (horizontal_size >= 0));

    if (horizontal_size * vertical_size != 0){

        data = (float*)calloc(horizontal_size * vertical_size, sizeof(float));
    } else{

        data = NULL;
    }
    
    rows_count = vertical_size;
    columns_count = horizontal_size;

    for (int i = 0; i < horizontal_size * vertical_size; i++){

        data[i] = 0;
    }

    if (rows_count == columns_count){

        for (int i = 0; i < rows_count; i++){

            data[i * rows_count + i] = diag_elem;
        }
    }
}

char my_getc(FILE* input){

    char c = '\0';
    int count = 0;

    if (input == NULL){
        
        return EOF;
    }

    while (((c = getc(input)) == ' ') || (c == '\t')){
        
        count++;
    }

    if (count != 0){

        fseek(input, -1, SEEK_CUR);
    }

    //fseek(input, -1, SEEK_CUR);
    
    if (c == EOF){

        c = '\n';
    }
    
    return c;
}

Matrix::Matrix(FILE* input){

    //printf("Конструктор по файлу\n\n");

    int cur_size = 0, tmp_columns_count = 0;
    char next_symbol = '\0';
    float tmp = 0;

    data = NULL;
    rows_count = 0;
    columns_count = 0;

    if (input != NULL){

        int scanf_ret = fscanf(input, "%f", &tmp);
        
        while (scanf_ret != -1){

            cur_size++;

            data = (float*)realloc(data, cur_size * sizeof(float));
            data[cur_size - 1] = tmp;

            if (my_getc(input) == '\n'){
                
                if (columns_count != 0){

                    assert(cur_size - rows_count * columns_count == columns_count);
                } else{

                    columns_count = cur_size;
                }

                rows_count++;
            }

            scanf_ret = fscanf(input, "%f", &tmp);
        }

        fseek(input, 0, SEEK_SET); 
    }
}

Matrix::Matrix(const Matrix& old_obj){

    //printf("Конструктор глубокого копирования\n\n");

    data = (float*)calloc(old_obj.rows_count * old_obj.columns_count, sizeof(float));

    rows_count = old_obj.rows_count;
    columns_count = old_obj.columns_count;

    memcpy(data, old_obj.data, rows_count * columns_count * sizeof(float));
}

Matrix::Matrix(Matrix&& old_obj){

    //printf("Конструктор перемещения\n\n");

    data = old_obj.data;
    rows_count = old_obj.rows_count;
    columns_count = old_obj.columns_count;

    old_obj.data = NULL;
    old_obj.rows_count = 0;
    old_obj.columns_count = 0;
}

Matrix::~Matrix(){

    if (data != NULL){

        data[0] = -228; //проверка что старые данные не используются
    }
    
    free(data);
}

void Matrix::print(FILE* output_stream = stdout){

    for (int i = 0; i < rows_count * columns_count; i++){

        fprintf(output_stream, "%f ", data[i]);

        if ((i + 1) % columns_count == 0){

            fprintf(output_stream, "\n");
        }
    }
}

int max(int left, int right){

    if (left > right){

        return left;
    } else{

        return right;
    }
}

int not_del_elem(int size, int* array){

    int i_has_found = 0;

    for (int i = 0; i < (size + 1); i++){

        for (int j = 0; j < size; j++){

            if (array[j] == i){

                i_has_found = 1;
            }
        }        
        
        if (i_has_found == 0){

            return i;
        } else{

            i_has_found = 0;
        }
    }

    return -1;
}

int check_deleted(int number, int size, int* array){//если 1, то  удален

    for (int i = 0; i < size; i++){

        if (array[i] == number){

            return 1;
        }
    }

    return 0;
}

void print_minor(const Matrix& init_matr, int deleted_rows_count, int* deleted_columns){

    for (int i = deleted_rows_count; i < init_matr.rows_count; i++){

        for (int j = 0; j < init_matr.rows_count; j++){

            if (check_deleted(j, deleted_rows_count, deleted_columns) == 0){

                printf("%f ", init_matr[i][j]);
            }
        }

        printf("\n");
    }
}

float minor(const Matrix& init_matr, int deleted_rows_count, int* deleted_columns){ //можно убрать список удаленных строк тк он  последовательные

    int i = deleted_rows_count, j = 0;
    float determ = 0;

    if ((deleted_rows_count + 1) != init_matr.rows_count){

        while (i < init_matr.rows_count){
            
            assert(j < init_matr.rows_count);
            if (check_deleted(j, deleted_rows_count, deleted_columns) == 0){//проверяем номера столбцов, которые еще не удалены, поэтому проверяем первые deleted_rows_count элементов

                deleted_columns[deleted_rows_count] = j;

                if ((i - deleted_rows_count) % 2 == 0){

                    determ += init_matr[deleted_rows_count][j] * minor(init_matr, deleted_rows_count + 1, deleted_columns);
                } else{
                    
                    determ += (-1) * init_matr[deleted_rows_count][j] * minor(init_matr, deleted_rows_count + 1, deleted_columns);
                }

                i++;
                j++;
            } else{

                j++;
            }
        }
        
        return determ;
    } else{

        assert(not_del_elem(deleted_rows_count, deleted_columns) != -1);
        return init_matr[deleted_rows_count][not_del_elem(deleted_rows_count, deleted_columns)];
    }
}

float Matrix::determinant(){

    assert(rows_count == columns_count);

    float determ = 0;

    int* deleted_columns = (int*)calloc(columns_count, sizeof(int));

    for (int i = 0; i < rows_count; i++){ //разложение по первой строчке

        deleted_columns[0] = i;
        
        if ((i % 2) == 0){
            
            determ += data[i] * minor(*this, 1, deleted_columns);
        } else{

            determ += (-1) * data[i] * minor(*this, 1, deleted_columns);
        }
    }

    free(deleted_columns);
    return determ;
}

bool Matrix::is_quadratic(){

    if (rows_count == columns_count){

        return true;
    } else{

        return false;
    }
}

void Matrix::transpose(){

    int tmp = 0;

    if ((rows_count == 1) || (columns_count == 1)){

        tmp = rows_count;
        rows_count = columns_count;
        columns_count  = tmp;
    } else{

        float* new_data = (float*)calloc(rows_count * columns_count, sizeof(float));

        for (int i = 0; i < rows_count; i++){

            for (int j = 0; j < columns_count; j++){

                assert(i * columns_count + j < rows_count * columns_count);

                new_data[j * rows_count + i] = data[i * columns_count + j];
            }
        }

        tmp = columns_count;
        columns_count = rows_count;
        rows_count = tmp;

        free(data);
        data = new_data;
    }
}

Matrix& Matrix::operator = (const Matrix& rv){

    //printf("Оператор присваивания lvalue = lvalue\n\n");

    if (this == &rv){

        return *this;
    }
        
    data = (float*)calloc(rv.rows_count * rv.columns_count, sizeof(float));
    
    rows_count = rv.rows_count;
    columns_count = rv.columns_count;

    memcpy(data, rv.data, rows_count * columns_count * sizeof(float));

    return *this;
}

Matrix& Matrix::operator = (Matrix&& rv){

    //printf("Оператор присваивания перемещения lvalue = rvalue\n\n");

    free(data);   //вроде без этого утечка памяти
    data = rv.data;
    rows_count = rv.rows_count;
    columns_count = rv.columns_count;

    rv.data = NULL;
    rv.rows_count = 0;
    rv.columns_count = 0;

    return *this;
}

float* Matrix::operator [] (const int row_number){

    assert(row_number < rows_count);
    return &data[row_number * columns_count];
}

const float* Matrix::operator [] (const int row_number) const{

    assert(row_number < rows_count);
    return &data[row_number * columns_count];
}

Matrix operator * (const Matrix& L_matr, const Matrix& R_matr){

    //printf("Оператор *\n\n");

    assert(L_matr.columns_count == R_matr.rows_count);

    Matrix tmp_obj(L_matr.rows_count, R_matr.columns_count, (float)0);

    for (int i = 0; i < L_matr.rows_count; i++){

        for (int j = 0; j < R_matr.columns_count; j++){

            for (int k = 0; k < L_matr.columns_count; k++){

                tmp_obj[i][j] += L_matr[i][k] * R_matr[k][j];
            }
        }
    }

    return static_cast<Matrix&&>(tmp_obj); 
}

Matrix operator * (float number, const Matrix& matr){

    //printf("Оператор число * матрица\n\n");

    Matrix tmp_obj(matr.rows_count, matr.columns_count, (float)0);

    for (int i = 0; i < matr.rows_count * matr.columns_count; i++){

        tmp_obj.data[i] = matr.data[i] * number;
    }

    return static_cast<Matrix&&>(tmp_obj);
}

Matrix operator * (const Matrix& matr, float number){

    //printf("Оператор матрица * число\n\n");

    return number * matr;
}

Matrix operator + (const Matrix& L_matr, const Matrix& R_matr){

    //printf("Оператор +\n\n");

    assert((L_matr.rows_count == R_matr.rows_count) && (L_matr.columns_count == R_matr.columns_count));

    float* new_data = (float*)calloc(L_matr.rows_count * L_matr.columns_count, sizeof(float));

    for (int i = 0; i < L_matr.rows_count * L_matr.columns_count; i++){

        new_data[i] = L_matr.data[i] + R_matr.data[i];
    }

    Matrix tmp_obj(L_matr.rows_count, L_matr.columns_count, new_data);
        
    free(new_data);

    return static_cast<Matrix&&>(tmp_obj); 
}

Matrix operator - (const Matrix& L_matr, const Matrix& R_matr){

    //printf("Оператор -\n\n");

    assert((L_matr.rows_count == R_matr.rows_count) && (L_matr.columns_count == R_matr.columns_count));

    float* new_data = (float*)calloc(L_matr.rows_count * L_matr.columns_count, sizeof(float));

    for (int i = 0; i < L_matr.rows_count * L_matr.columns_count; i++){

        new_data[i] = L_matr.data[i] - R_matr.data[i];
    }

    Matrix tmp_obj(L_matr.rows_count, L_matr.columns_count, new_data);
        
    free(new_data);

    return static_cast<Matrix&&>(tmp_obj); 
}

float cos(const Matrix& L_matr, const Matrix& R_matr){

    //printf("Косинус\n\n");

    assert((L_matr.columns_count == 1) && (R_matr.columns_count == 1));
    assert((R_matr.rows_count == L_matr.rows_count));

    float scalar_mult = 0, L_abs = 0, R_abs = 0;
    
    for(int i = 0; i < L_matr.rows_count; i++){

        scalar_mult += L_matr.data[i] * R_matr.data[i];
        L_abs += L_matr.data[i] * L_matr.data[i];
        R_abs += R_matr.data[i] * R_matr.data[i];
    }
    
    if (L_abs * R_abs == 0){

        return 2;
    } else{

        return (scalar_mult / sqrt(L_abs * R_abs));
    }
}

bool same_size(const Matrix& L_matr, const Matrix& R_matr){

    if ((L_matr.rows_count == R_matr.rows_count) && (L_matr.columns_count == R_matr.columns_count)){

        return true;
    } else{

        return false;
    }
}

bool could_be_mult(const Matrix& L_matr, const Matrix& R_matr){

    if (L_matr.columns_count == R_matr.rows_count){

        return true;
    } else{

        return false;
    }
}


Vector::Vector(float x , float y):

    Matrix(2, 1, -1)
{
    data[0] = x;
    data[1] = y;
}

Vector::Vector(float x , float y, float z):

    Matrix(3, 1, -1)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

Vector::Vector(int number_of_coordinates, float* arr_of_coordinates):

    Matrix(number_of_coordinates, 1, arr_of_coordinates)
{
    
}

Vector::Vector(Point& fir_point, Point& sec_point):

    Vector(dynamic_cast<Vector&>(sec_point) - dynamic_cast<Vector&>(fir_point))
{

}

Vector::~Vector(){

    
}

float& Vector::operator [] (const int coordinate_number){

    assert(coordinate_number < rows_count);

    return data[coordinate_number];
}

const float& Vector::operator[](const int coordinate_number) const{

    assert(coordinate_number < rows_count);

    return data[coordinate_number];
}

void Vector::print(FILE* output_stream){

    Matrix& tmp_matr = *this;
    tmp_matr.print(output_stream);
}

int Vector::length(){

    return rows_count;
}

float Vector::modul(){

    float tmp = 0;

    for (int i = 0; i < rows_count; i++){

        tmp += data[i] * data[i];
    }

    assert(tmp >= 0);

    return sqrt(tmp);
}

void Vector::normalize(){

    if (this->modul() != 0){

        *this = (1 / this->modul()) * (*this);
    }
}

Vector operator * (const Vector& vectr, float number){

    return number * vectr;
}

Vector operator * (float number, const Vector& vectr){

    Vector tmp(0, -1);
    dynamic_cast<Matrix&>(tmp) = dynamic_cast<Matrix&>(const_cast<Vector&>(vectr)) * number;

    return tmp;
}

Vector operator * (Matrix& matr, Vector& vectr){

    Vector tmp(0, -1);
    dynamic_cast<Matrix&>(tmp) = matr * dynamic_cast<Matrix&>(vectr);

    return tmp;
}

Vector operator * (Vector& vectr, Matrix& matr){

    Vector tmp(0, -1);
    dynamic_cast<Matrix&>(tmp) = dynamic_cast<Matrix&>(vectr) * matr;

    return tmp;
}

Vector operator + (const Vector& L_vectr, const Vector& R_vectr){

    printf("vector + vector\n");

    Vector tmp(0, -1);
    dynamic_cast<Matrix&>(tmp) = dynamic_cast<Matrix&>(const_cast<Vector&>(L_vectr)) + dynamic_cast<Matrix&>(const_cast<Vector&>(R_vectr));

    return tmp;
}

Vector operator - (const Vector& L_vectr, const Vector& R_vectr){

    Vector tmp(0, -1);
    dynamic_cast<Matrix&>(tmp) = dynamic_cast<Matrix&>(const_cast<Vector&>(L_vectr)) - dynamic_cast<Matrix&>(const_cast<Vector&>(R_vectr));
    
    return tmp;
}


Point::Point(float x, float y):

    Vector(x, y)
{

}

Point::Point(float x_data, float y_data, float z_data):

    Vector(x_data, y_data, z_data)
{

}

Point::Point(int num_of_coordinates, float* arr_of_coordinates):

    Vector(num_of_coordinates, arr_of_coordinates)
{

}

Point::~Point(){

}

int Point::length(){

    Vector& tmp = *this;

    return tmp.length();
}

void Point::print(FILE* output_stream){

    Vector& tmp = *this;

    return tmp.print(output_stream);
}

float& Point::operator [] (const int coordinate_number){

    Vector& tmp = *this;

    return tmp[coordinate_number];
}

const float& Point::operator [] (const int coordinate_number) const{

    const Vector& tmp = *this;

    return tmp[coordinate_number];
}

bool operator == (const Point& L_point, const Point& R_point){

    bool coordinates_unequal = false;

    if (L_point.rows_count != R_point.rows_count){

        return false;
    }

    for (int i = 0; i < L_point.rows_count; i++){

        if (L_point[i] != R_point[i]){

            coordinates_unequal = true;
        }
    }

    return !coordinates_unequal;
}

bool operator != (const Point& L_point, const Point& R_point){

    return !(L_point == R_point);
}

float distance(Point& fir_point, Point& sec_point){

    assert(fir_point.rows_count == sec_point.rows_count);

    float tmp = 0;

    for (int i = 0; i < fir_point.rows_count; i++){

        tmp += (fir_point[i] - sec_point[i]) * (fir_point[i] - sec_point[i]);
    }

    return sqrt(tmp);
}

