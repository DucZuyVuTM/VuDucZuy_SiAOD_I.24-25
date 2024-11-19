#include <iostream>
#include <string>

using namespace std;

// Hàm tìm kiếm trực tiếp
int directSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    // Duyệt qua từng vị trí trong chuỗi lớn
    for (int i = 0; i <= n - m; i++) {
        int j = 0;

        // So sánh từng ký tự của chuỗi con với chuỗi lớn
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }

        // Nếu chuỗi con khớp hoàn toàn
        if (j == m) {
            return i; // Trả về vị trí bắt đầu của chuỗi con trong chuỗi lớn
        }
    }

    // Nếu không tìm thấy
    return -1;
}

int main() {
    string text = "the quick brown fox jumps over the lazy dog";
    string pattern = "fox";

    int result = directSearch(text, pattern);

    if (result != -1) {
        cout << "Pattern found at index " << result << endl;
    } else {
        cout << "Pattern not found" << endl;
    }

    return 0;
}
