#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void create_file_matrix(const string& file_name, const vector<vector<int>>& matrix) {
    ofstream out("/Users/margogusarova/Paralell_prog/lab_1/" + file_name);
    if (!out.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << file_name << " для записи." << endl;
        return;
    }

    for (const auto& row : matrix) {
        for (int element : row) {
            out << element << " ";
        }
        out << endl;
    }
    out.close();
    cout << "Матрица размером " << matrix.size() << "x" << matrix[0].size() << " успешно создана и записана в файл " << file_name << endl;
}


void create_matrix(const string& file_name, int size, int min_value, int max_value) {
    vector<vector<int>> matrix(size, vector<int>(size));

    srand(time(nullptr)); // Инициализируем генератор случайных чисел
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % (max_value - min_value + 1) + min_value; // Генерируем случайное число в диапазоне [min_value, max_value]
        }
    }

    create_file_matrix(file_name, matrix); // Записываем матрицу в файл
    cout << "Матрица размером " << size << "x" << size << " успешно создана и записана в файл " << file_name << endl;
}

void read_matrix(vector<vector<int>>& matrix, int size, const string& file_name) {
    ifstream data("/Users/margogusarova/Paralell_prog/lab_1/" + file_name);
    if (data.is_open()) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                data >> matrix[i][j];
            }
        }
        data.close();
    }
    cout << "Матрица размером " << size << "x" << size << " успешно считана из файла " << file_name << endl;
}

void mul_matrix(const vector<vector<int>>& matrix_1, const vector<vector<int>>& matrix_2, vector<vector<int>>& matrix_result) {
    int size = matrix_result.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix_result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                matrix_result[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }
}

void write_result(string str, vector<vector<int>>& matrix_result, int size, clock_t end, clock_t start) {
    ofstream data("/Users/margogusarova/Paralell_prog/lab_1/" +str);
    if (!data.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << str << " для записи." << endl;
        return;
    }

    ofstream result("/Users/margogusarova/Paralell_prog/lab_1/result.txt", ios::app);
    if (!result.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл result.txt для записи." << endl;
        data.close(); // Закрываем data перед выходом из функции
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            data << matrix_result[i][j] << " ";
        }
        data << endl;
    }

    result << "Размер: " << size << " Время: " << (double(end - start)) / (double(CLOCKS_PER_SEC)) << endl;
    data.close();
    result.close();
    cout << "Результаты записаны в файлы." << endl;
}


int main() {
    srand(time(nullptr));
    int SIZE = 2000;
    int min_value = 100;
    int max_value = 10;
    vector<vector<int>> matrix_1(SIZE, vector<int>(SIZE));
    vector<vector<int>> matrix_2(SIZE, vector<int>(SIZE));
    vector<vector<int>> matrix_result(SIZE, vector<int>(SIZE));
    create_matrix("Matrix_1.txt", SIZE, min_value, max_value);
    create_matrix("Matrix_2.txt", SIZE, min_value, max_value);
    read_matrix(matrix_1, SIZE, "Matrix_1.txt");
    read_matrix(matrix_2, SIZE, "Matrix_2.txt");

    clock_t start, end;
    start = clock();
    mul_matrix(matrix_1, matrix_2, matrix_result);
    end = clock();

    write_result("Matrix_res.txt", matrix_result, SIZE, end, start);

    return 0;
}

