#include <iostream>
using namespace std;

// Hàm đệ quy để tính số cách đi từ (i, j) đến ô cuối cùng (n-1, m-1)
int countWays(int i, int j, int n, int m) {
    // Nếu chúng ta đã đến được ô cuối cùng (n-1, m-1), trả về 1
    if (i == n - 1 && j == m - 1) {
        return 1;
    }

    int ways = 0;

    // Nếu chưa đến cuối hàng, đi xuống
    if (i < n - 1) {
        ways += countWays(i + 1, j, n, m); // Di chuyển xuống
    }

    // Nếu chưa đến cuối cột, đi sang phải
    if (j < m - 1) {
        ways += countWays(i, j + 1, n, m); // Di chuyển sang phải
    }

    return ways;
}

int main() {
    int ctrl = 1;
    cout << "\"Grid Paths\" - classic Programming exercise." << endl;
    cout << "Write 1 to continue, 0 to exit." << endl << endl;

    while (ctrl != 0) {
        cout << "Your choice: "; cin >> ctrl;

        if (ctrl == 1) {
            int n, m;
            cout << "Write the amount of rows n: ";
            cin >> n;
            cout << "Write the amount of columns m: ";
            cin >> m;

            cout << "Number of ways to reach the bottom-right corner: ";
            cout << countWays(0, 0, n, m) << endl << endl;
        }
    }

    return 0;
}
