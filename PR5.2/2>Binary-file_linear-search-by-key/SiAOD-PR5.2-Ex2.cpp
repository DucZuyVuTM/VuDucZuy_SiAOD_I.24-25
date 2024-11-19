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

int main() {
    string input_fname;
    cout << "Write the name of file for clinic recording: ";
    cin >> input_fname;

    ofstream textFile(input_fname);
    if (!textFile) {
        cerr << "Error from making file!" << endl;
        return 1;
    }

    string disease[] = {"GOLOD-253", "HIV-428", "VGB-496", "SUG-782", "BRN-257", "DEP-178", "ANX-581"};
    string docFamilyName[] = {"Ivanov", "Nikolayev", "Novachyov", "Chuzheva", "Vitov"};

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
        do {
            patient.key = rand() % 100000 + 1; // Случайный ключ от 1 до 100000
        } while (uniqueKeys.find(patient.key) != uniqueKeys.end());
        uniqueKeys.insert(patient.key);

        patient.diseaseCode = disease[rand() % 7];

        patient.doctorFName = docFamilyName[rand() % 5];

        // Запись в текстовый файл
        textFile << patient.key << " " << patient.diseaseCode << " " << patient.doctorFName << endl;
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

    string mykey;
    cout << "Write the key you want to find: ";
    cin >> mykey;

    string hexValue;
    string currKey;
    string info;
    bool found = false;

    // Засекаем время выполнения
    auto start = chrono::high_resolution_clock::now();

    // Đọc từng giá trị thập lục phân từ file cho đến khi hết dữ liệu
    while (inputFile2 >> hexValue) {
        currKey = "";
        info = "";

        // Đọc từng giá trị thập lục phân và chuyển thành ký tự cho đến khi gặp "20" (ký tự space)
        do {
            unsigned int intValue;
            stringstream ss;
            ss << hex << hexValue; // Chuyển chuỗi thành hệ thập lục phân
            ss >> intValue;        // Lấy giá trị thập lục phân dưới dạng số

            // Chuyển đổi giá trị thập lục phân thành ký tự
            unsigned char character = static_cast<unsigned char>(intValue);
            currKey += string(1, character);  // Nối ký tự vào chuỗi currKey
        } while (inputFile2 >> hexValue && hexValue != "20");

        // Kiểm tra nếu khóa khớp với khóa cần tìm
        if (currKey == mykey) {
            // Đọc tiếp thông tin đến khi gặp ký tự "A" (end of info)
            while (inputFile2 >> hexValue && hexValue != "A") {
                unsigned int intValue;
                stringstream ss;
                ss << hex << hexValue; // Chuyển chuỗi thành hệ thập lục phân
                ss >> intValue;        // Lấy giá trị thập lục phân dưới dạng số

                // Chuyển đổi giá trị thập lục phân thành ký tự
                unsigned char character = static_cast<unsigned char>(intValue);
                info += string(1, character);  // Nối ký tự vào chuỗi info
            }
            // In kết quả ra nếu khóa tìm thấy
            cout << currKey << " " << info << endl;
            found = true;
        }
        else {
            // Bỏ qua phần info khi khóa không khớp
            while (inputFile2 >> hexValue && hexValue != "A");
        }
    }

    inputFile2.close(); // Đóng file

    if (!found) {
        cout << "Cannot find the key you want." << endl;
    }

    // Засекаем время окончания
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Finding completed. Lead time: " << elapsed_time.count() << " miliseconds." << endl;

    return 0;
}
