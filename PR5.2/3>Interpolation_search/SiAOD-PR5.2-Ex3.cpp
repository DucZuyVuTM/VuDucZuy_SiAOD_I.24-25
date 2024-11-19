#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()
#include <set>     // Для проверки уникальности ключей
#include <string>

#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

struct Patient {
    int key;                // Уникальный ключ
    string diseaseCode;
    string doctorFName;
};

int interpolationSearch(vector<int> indexTable, int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high && key >= indexTable[low] && key <= indexTable[high]) {
        if (indexTable[high] == indexTable[low]) {
            // Tránh phép chia cho 0
            if (indexTable[low] == key)
                return low;
            else
                return -1;
        }

        // Tính vị trí dự đoán dựa trên nội suy tuyến tính
        int pos = low + ((double)(high - low) / (indexTable[high] - indexTable[low])) * (key - indexTable[low]);

        // Nếu tìm thấy khóa
        if (indexTable[pos] == key)
            return pos;

        // Nếu khóa lớn hơn, tìm ở nửa trên
        if (indexTable[pos] < key)
            low = pos + 1;
        // Nếu khóa nhỏ hơn, tìm ở nửa dưới
        else
            high = pos - 1;
    }

    // Khóa không tồn tại
    return -1;
}

void readRecordFromFile(string filename, long offset) {
    ifstream file(filename);
    if (!file) {
        cerr << "Cannot open file!" << endl;
        return;
    }

    string line;

    for (int i = 0; i <= offset; i++) {
        getline(file, line);   // Đọc một dòng từ file
    }

    cout << "Info about patient: " << line << endl;
    
    file.close();
}

int main() {
    int key_gen = 0;

    string input_fname;
    cout << "Write the name of file for clinic recording: ";
    cin >> input_fname;

    ofstream textFile(input_fname);
    if (!textFile) {
        cerr << "Error from making file!" << endl;
        return 1;
    }

    string disease[] = { "GOLOD-253", "HIV-428  ", "VGB-496  ", "SUG-782  ", "BRN-257  ", "DEP-178  ", "ANX-581  " };
    string docFamilyName[] = { "Ivanov   ", "Nikolayev", "Novachyov", "Chuzheva ", "Vitov    " };
    vector<int> keys;

    srand(time(0)); // Инициализация случайного числа
    set<int> uniqueKeys; // Для хранения уникальных ключей

    int numRecords = 0;
    cout << "Write the amount of clinic record (less than 100001): ";
    cin >> numRecords;

    if (numRecords > 100000) {
        cerr << "The amount of clinic records must be less than 100001." << endl;
        return 1;
    }

    for (int i = 0; i < numRecords; ++i) {
        Patient patient;

        // Генерация уникального ключа
        key_gen = key_gen + rand() % 9 + 1;
        patient.key = key_gen;
        keys.push_back(key_gen);

        patient.diseaseCode = disease[rand() % 7];

        patient.doctorFName = docFamilyName[rand() % 5];

        // Запись в текстовый файл
        textFile << setfill('0') << setw(6) << patient.key << " " << patient.diseaseCode << " " << patient.doctorFName << endl;
    }

    textFile.close();
    cout << "Text document " << input_fname << " created." << endl;

    ifstream inputFile(input_fname);
    if (!inputFile) {
        cerr << "Cannot open file " << input_fname << " to read!" << endl;
        return 1;
    }

    string output_fname;
    cout << "Write the name of binary file for clinic record: ";
    cin >> output_fname;

    // Mở file .bin để ghi dưới dạng nhị phân
    ofstream outputFile(output_fname, ios::binary);
    if (!outputFile) {
        cerr << "Cannot open file " << output_fname << " to write!" << endl;
        return 1;
    }

    char ch;

    // Đọc từng ký tự từ file .txt và ghi mã ASCII của nó vào file nhị phân
    while (inputFile.get(ch)) {
        int asciiCode = static_cast<int>(ch);

        // Lấy mã ASCII của ký tự và ghi vào file nhị phân
        outputFile << hex << uppercase << asciiCode << " ";
    }

    // Đóng các file
    inputFile.close();
    outputFile.close();

    cout << "File " << input_fname << " has been changed to file "
        << output_fname << " with ASCII code (HEX)." << endl;

    // Mở file để đọc
    ifstream inputFile2(output_fname, ios::binary);
    if (!inputFile2) {
        cerr << "Cannot open file for reading!" << endl;
        return 1;
    }

    // Khóa cần tìm
    int mykey;
    cout << "Write the key you want to find: ";
    cin >> mykey;

    // Засекаем время выполнения
    auto start = chrono::high_resolution_clock::now();

    int pos = interpolationSearch(keys, numRecords, mykey);    

    if (pos != -1) {
        cout << "Key " << mykey << " was found at position " << pos + 1 << endl;
        readRecordFromFile(input_fname, pos);
    }
    else {
        cout << "Key " << mykey << " not found" << endl;
    }

    // Засекаем время окончания
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Finding completed. Lead time: " << elapsed_time.count() << " miliseconds." << endl;

    return 0;
}
