#include <iostream>

using namespace std;

int main()
{
    unsigned char x = 42;                               // 8-разрядное двоичное число 00101010
    unsigned char maska = 1;                             // 1 = 00000001 – 8-разрядная маска
    x = x | (maska << 7);   
    
    // maska << 7 = 10000000
    // 00101010 | 10000000 = 10101010(2) = 170(10)
    
    cout << static_cast<int>(x);

    return 0;
}
