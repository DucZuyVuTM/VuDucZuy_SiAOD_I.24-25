#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int bit_size = 64;

int main() {
    vector<int> numbers;
    vector<int> sorted_nums;
    vector<int> bit_arr;
    int inp;
    unsigned long long bit_num = 0;
    unsigned long long maska = 1;
    
    cout << "Write the list of numbers, write -1 or any number smaller than 0 to end the list:\n";
    
    cin >> inp;
    while (inp >= 0) {
    numbers.push_back(inp);
    cin >> inp;
    }
    
    bool toVector = false;
    
    for (int &x : numbers) {
       if (x > 63) {
           toVector = true;
       }
    }
    
    bool not_approved = false;
    int sorted_amount = 0; int old_amount = 0;
    
    for (int i = 0; i <= *std::max_element(numbers.begin(), numbers.end()); i++) {
          for (int &x : numbers) {
              if (i == x) {
                  for (int &y : sorted_nums) {
                      if (i == y) {
                          not_approved = true;
                          break;
                      }
                  }
                  if (!not_approved) {
                      sorted_nums.push_back(i);
                  } else {
                      not_approved = false;
                  }
              }
          }
          sorted_amount = sorted_nums.size();
          if (sorted_amount == old_amount) {
              bit_arr.push_back(0);
          } else {
              bit_arr.push_back(1);
              old_amount = sorted_amount;
          }
    }
    
    if (toVector) {
       cout << endl << "Bit array: ";
          for (int &x : bit_arr) {
           cout << x;
       }
    } else {
       for (int i = 1; i <= bit_size; i++) {
           for (int &x : numbers) {
                  if (x == (i - 1)) {
                      bit_num = bit_num | (maska << (bit_size - i));
                  }
              }
          }
          cout << "Bit number: " << bitset<bit_size> (bit_num) << endl;
          cout << "Number from bit number: " << bit_num << endl;
    }
    return 0;
}
