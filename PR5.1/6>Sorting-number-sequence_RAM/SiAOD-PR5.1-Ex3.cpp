#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

const int MAX_NUM = 10000000;        // Максимальное количество чисел
const int MAX_BIT_IN_1_MB = 8388608; // Максимальное количество битов в 1 МБ

int main() {
    vector<int> numbers;

    string input_fname, output_fname;
    cout << "The name of input file: "; cin >> input_fname;
    cout << "The name of output file: "; cin >> output_fname;

    // Вектор для хранения битов, инициализированный нулями
    vector<bool>* bit_arr = new vector<bool>(MAX_NUM, false);

    // Переменная, содержащая количество входных чисел
    int inp;
    cout << "The amount of input number: "; cin >> inp;

    if (inp > MAX_NUM) {
        cout << "Cannot sort more than 10^7 numbers" << endl;
        delete bit_arr;
        return 1;
    }

    for (int i = 0; i < inp; ++i) {
        numbers.push_back(i);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));

    // Передать номера в файл
    ofstream start_file(input_fname);
    if (!start_file) {
        cerr << "Cannot open file " << input_fname << endl;
        delete bit_arr;
        return 1;
    }

    for (int i = 0; i < numbers.size(); i++) {
        start_file << numbers[i] << endl;
    }

    start_file.close();

    // Засекаем время выполнения
    auto start = chrono::high_resolution_clock::now();

    // Чтение входного файла
    ifstream input_file(input_fname);
    if (!input_file) {
        cerr << "Cannot open file " << input_fname << endl;
        delete bit_arr;
        return 1;
    }

    int num;
    while (input_file >> num) {
        if (num >= 0 && num < MAX_NUM) {
            (*bit_arr)[num] = true;  // Устанавливаем бит для каждого прочитанного числа
        }
    }
    input_file.close();

    // Запись отсортированных чисел в выходной файл
    ofstream output_file(output_fname);
    if (!output_file) {
        cerr << "Cannot open file " << output_fname << endl;
        delete bit_arr;
        return 1;
    }

    for (int i = 0; i < MAX_NUM; ++i) {
        if ((*bit_arr)[i]) {
            output_file << i << endl;  // Записываем отсортированные числа
        }
    }
    output_file.close();

    // Засекаем время окончания
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Sorting completed. Lead time: " << elapsed_time.count() << " seconds." << endl;

    unsigned long long bit_size = 0;  // Инициализировать переменную bit_size
    for (int i = 0; i < bit_arr->size(); i++) {
        if ((*bit_arr)[i]) {
            bit_size++;  // Увеличить значение bit_size для каждого бита 1.
        }
    }
    cout << "The amount of bit in RAM: " << bit_size << endl;

    delete bit_arr;
    return 0;
}
