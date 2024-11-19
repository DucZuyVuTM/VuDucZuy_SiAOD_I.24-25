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
void KMPsearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    // Tính hàm tiền tố cho chuỗi pattern
    vector<int> pi = computePrefixFunction(pattern);
    int q = 0; // Số lượng ký tự trùng khớp
    
    for (auto num : pi) {
        cout << num << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        // Khi có sự không khớp, sử dụng hàm tiền tố để bỏ qua các ký tự đã so sánh
        while (q > 0 && pattern[q] != text[i])
            q = pi[q - 1];

        if (pattern[q] == text[i])
            q++;

        // Nếu tìm thấy một khớp hoàn chỉnh
        if (q == m) {
            cout << "Substring found at index " << i - m + 1 << endl;
            q = pi[q - 1]; // Tiếp tục tìm kiếm
        }
        cout << q << " ";
    }
}

int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    cout << "String: " << text << endl;
    cout << "Substring: " << pattern << endl;
    
    KMPsearch(text, pattern);

    return 0;
}
