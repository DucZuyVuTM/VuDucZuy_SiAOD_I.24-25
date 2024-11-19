#include <iostream>
#include <fstream>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()
#include <set>     // Для проверки уникальности ключей
#include <string>

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

    srand(time(0)); // Инициализация случайного числа
    set<int> uniqueKeys; // Для хранения уникальных ключей
    
    int numRecords = 0;
    cout << "Write the amount of clinic record (less than 1001): ";
    cin >> numRecords;
    
    if (numRecords > 1000) {
        cerr << "The amount of clinic records must be less than 1001." << endl;
        return 1;
    }
    
    for (int i = 0; i < numRecords; ++i) {
        Patient patient;

        // Генерация уникального ключа
        do {
            patient.key = rand() % 1000 + 1; // Случайный ключ от 1 до 1000
        } while (uniqueKeys.find(patient.key) != uniqueKeys.end());
        uniqueKeys.insert(patient.key);

        cout << "Patient No " << i + 1 << endl;
        
        // Ввод данных пациента
        cout << "Disease code: ";
        cin >> patient.diseaseCode;
        
        cout << "Doctor family name: ";
        cin >> patient.doctorFName;

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

    return 0;
}
