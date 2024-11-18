#include <iostream>

using namespace std;

int main()
{
    unsigned char x = 255;            // 8-разрядное двоичное число 11111111 
    unsigned char maska = 1;          // 1 = 00000001 - 8-разрядная маска
    x = x & (~(maska << 4));   

    // maska << 4 = 00010000 
    // ~(00010000) => 11101111 
    // 11111111 & 11101111 = 11101111 
    // 11101111(2) = 239(10) 
    // результат x = 239

    cout << static_cast<int>(x);

    return 0;
}
