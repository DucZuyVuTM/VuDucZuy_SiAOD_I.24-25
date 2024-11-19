#include <iostream>
#include <vector>

using namespace std;

// Hàm tính toán hàm tiền tố (prefix function)
vector<int> computePrefixFunction(const string &pattern) {
    int m = pattern.size();
    vector<int> pi(m, 0); // Tạo mảng lưu giá trị của hàm tiền tố
    int k = 0;

    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i])
            k = pi[k - 1];
        if (pattern[k] == pattern[i])
            k++;
        pi[i] = k;
    }

    return pi;
}

// Hàm KMP tìm kiếm chuỗi con trong chuỗi lớn
string removeAllOccurrencesKMP(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    // Tính hàm tiền tố cho chuỗi pattern
    vector<int> pi = computePrefixFunction(pattern);
    string result = text;
    int q = 0; // Số lượng ký tự trùng khớp
    int i = 0;

    while (i < result.size()) {
        // Khi có sự không khớp, sử dụng hàm tiền tố để bỏ qua các ký tự đã so sánh
        while (q > 0 && pattern[q] != result[i])
            q = pi[q - 1];

        if (pattern[q] == result[i])
            q++;

        // Nếu tìm thấy một khớp hoàn chỉnh
        if (q == m) {
            result.erase(i - m + 1, m); // Xóa từ tìm thấy
            i = i - m; // Quay lại kiểm tra từ sau vị trí đã xóa
            q = 0; // Đặt lại chỉ số khớp
        }
        i++;
    }
    return result;
}

int main() {
    string text, pattern;
    cout << "Write the text: "; getline(cin, text);
    cout << "Write the pattern: "; getline(cin, pattern);

    string updatedText = removeAllOccurrencesKMP(text, pattern);
    cout << "New text: " << updatedText << endl;

    return 0;
}
