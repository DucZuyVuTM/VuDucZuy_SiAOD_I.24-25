#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int bit_size = 8;

int main() {
    vector<int> numbers;
    int inp;
    unsigned char bit_num[8] = {}; // Инициализация массива начальными значениями 0
    unsigned long long maska = 1;
    
    cout << "Write the list of numbers, write -1 or any numbers smaller than 0 to end the list:\n";
    
    cin >> inp;
    while (inp >= 0 && inp < bit_size * 8) { // Ограничить значения допустимым диапазоном
        numbers.push_back(inp);
        cin >> inp;
    }
    
    // Перебегать bit_size * 8 бит, чтобы создать bit_num.
    for (int h = 0; h < 8; h++) {  // В bit_num 8 элементов.
        for (int i = 1 + 8 * h; i <= bit_size * (h + 1); i++) {
            for (int &x : numbers) {
                if (x == (i - 1)) {
                    bit_num[h] = bit_num[h] | (maska << (bit_size - (i - 8 * h)));  
                    // Установить бит в правильное положение
                }
            }
        }
    }
    
    // Распечатать биты из bit_num
    cout << "Bit number: ";
    for (int h = 0; h < 8; h++) {
        cout << bitset<bit_size>(bit_num[h]);  // Распечатать каждый элемент bit_num как набор битов.
    }
    cout << endl;
    
    return 0;
}
