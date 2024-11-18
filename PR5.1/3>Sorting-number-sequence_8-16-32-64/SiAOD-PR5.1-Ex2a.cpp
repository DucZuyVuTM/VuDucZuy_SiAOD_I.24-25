#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

const int U_CHAR = 8;
const int U_SHORT = 16;
const int U_LONG = 32;
const int U_LONG_LONG = 64;

void add_byte(int new_byte, int &old_byte) {
    if (new_byte > old_byte) {
        old_byte = new_byte;
    }
}

int main() {
	vector<int> numbers;
	vector<int> sorted_nums;
	vector<int> bit_arr;
	int inp;
	int byte_amount = 0;

	cout << "Write the list of numbers, write -1 or any numbers smaller than 0 to end the list:\n";
	
	cin >> inp;
	while (inp >= 0) {
		numbers.push_back(inp);
		cin >> inp;
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
	
	cout << "Sorted list: ";
	for (int &x : sorted_nums) {
	    cout << x << " ";
	} cout << endl;
	
	unsigned long long bit_num = 0;
	
	for (int i = 0; i < bit_arr.size(); i++) {
	    if (bit_arr[i]) {
	        if (bit_arr.size() <= U_CHAR) {
        	    bit_num = bit_num | (1ULL << (U_CHAR - 1 - i));
        	} else if (bit_arr.size() <= U_SHORT) {
        	    bit_num = bit_num | (1ULL << (U_SHORT - 1 - i));
        	} else if (bit_arr.size() <= U_LONG) {
        	    bit_num = bit_num | (1ULL << (U_LONG - 1 - i));
        	} else if (bit_arr.size() <= U_LONG_LONG) {
        	    bit_num = bit_num | (1ULL << (U_LONG_LONG - 1 - i));
        	}
	    }
	}
	
	cout << "Bit array:  ";
	for (int i = 0; i < bit_arr.size(); i++) {
	    cout << bit_arr[i];
	} cout << endl;
	
	if (bit_arr.size() <= U_CHAR) {
	    cout << "Bit number: " << bitset<U_CHAR> (bit_num) << endl;
	} else if (bit_arr.size() <= U_SHORT) {
	    cout << "Bit number: " << bitset<U_SHORT> (bit_num) << endl;
	} else if (bit_arr.size() <= U_LONG) {
	    cout << "Bit number: " << bitset<U_LONG> (bit_num) << endl;
	} else if (bit_arr.size() <= U_LONG_LONG) {
	    cout << "Bit number: " << bitset<U_LONG_LONG> (bit_num) << endl;
	} else {
	    cout << "Cannot store any number bigger than 63 by bit number." << endl;
	}
	
	return 0;
}
