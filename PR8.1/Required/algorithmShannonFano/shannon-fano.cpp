#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Hàm tính tần số các ký tự
vector<pair<char, int>> calculateFrequency(const string &data) {
    unordered_map<char, int> frequency_map;
    for (char c : data) {
        frequency_map[c]++;
    }

    // Chuyển dữ liệu từ unordered_map sang vector
    vector<pair<char, int>> frequency(frequency_map.begin(), frequency_map.end());

    // Sắp xếp vector theo tần suất giảm dần
    sort(frequency.begin(), frequency.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
        return a.second > b.second;
    });

    return frequency;
}

// Hàm phân chia ký tự theo phương pháp Shannon–Fano
void shannonFano(const vector<pair<char, int>> &freqs, map<char, string> &encoding, string prefix = "") {
    if (freqs.size() == 1) {
        encoding[freqs[0].first] = prefix;
        return;
    }

    // Tính tổng tần suất
    int totalFreq = 0;
    for (const auto &p : freqs) {
        totalFreq += p.second;
    }

    // Tính chỉ số phân chia sao cho tổng tần suất mỗi phần không chênh lệch quá nhiều
    int cumulativeFreq = 0;
    int splitIdx = 0;
    for (size_t i = 0; i < freqs.size(); ++i) {
        cumulativeFreq += freqs[i].second;
        if (cumulativeFreq >= totalFreq / 2) {
            splitIdx = i + 1;
            break;
        }
    }

    // Chia thành hai phần
    vector<pair<char, int>> leftPart(freqs.begin(), freqs.begin() + splitIdx);
    vector<pair<char, int>> rightPart(freqs.begin() + splitIdx, freqs.end());

    // Gọi đệ quy cho hai phần đã chia
    shannonFano(leftPart, encoding, prefix + "0");
    shannonFano(rightPart, encoding, prefix + "1");
}

// Hàm mã hóa dữ liệu
string encodeData(const string &data, const map<char, string> &encoding) {
    string encodedData;
    for (char c : data) {
        encodedData += encoding.at(c);
    }
    return encodedData;
}

// Hàm giải mã dữ liệu
string decodeData(const string &encoded_data, const map<string, char> &decoding) {
    string decoded_output;
    string current_bits;
    for (char bit : encoded_data) {
        current_bits += bit;
        if (decoding.find(current_bits) != decoding.end()) {
            decoded_output += decoding.at(current_bits);
            current_bits.clear();
        }
    }
    return decoded_output;
}

int main() {
    string data;

    while (data != "-1") {
        cout << "Write the string (write -1 to exit): ";
        getline(cin, data);

        if (data != "-1") {
            vector<pair<char, int>> freqs = calculateFrequency(data);
            map<char, string> encoding;

            shannonFano(freqs, encoding);

            // In tần suất xuất hiện của từng kí tự
            cout << "Frequencies:\n";
            for (const auto &pair : freqs) {
                cout << pair.first << ": " << pair.second << "\n";
            }

            int sum = 0;
            // In kết quả mã hóa Shannon–Fano cho từng ký tự
            cout << "Shannon-Fano Encoding:\n";
            for (const auto &pair : encoding) {
                cout << pair.first << ": " << pair.second << "\n";
                sum += pair.second.length();
            }
            cout << "Sum of encoding bits: " << sum << endl;

            // Tính số bit chính xác
            int totalBits = 0;
            for (const auto &pair : freqs) {
                totalBits += pair.second * encoding.at(pair.first).length();
            }

            cout << "\nShannon-Fano algorithm" << endl;
            cout << "-----" << endl;
            cout << "Data:" << endl << data << endl;
            cout << "Size in bits: " << data.length() * 8 << endl << endl;

            // In chuỗi mã hóa
            string encodedData = encodeData(data, encoding);
            cout << "Encoded Data: " << endl << encodedData << endl;
            cout << "Size in bits: " << totalBits << endl << endl;

            map<string, char> decoding;
            for (const auto &pair : encoding) {
                decoding[pair.second] = pair.first;
            }

            string decodedData = decodeData(encodedData, decoding);
            cout << "Decoded Data: " << endl << decodedData << endl;
            cout << "-----" << endl << endl;
        }
    }

    cout << "Program exited" << endl;
    return 0;
}
