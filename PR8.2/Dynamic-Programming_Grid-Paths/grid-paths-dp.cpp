#include <iostream>
#include <vector>
using namespace std;

// Hàm tính số cách đi từ ô (0,0) đến ô (n-1,m-1)
int countPaths(int n, int m) {
    // Tạo bảng dp với kích thước n x m, khởi tạo giá trị ban đầu là 0
    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Gán số cách cho hàng đầu và cột đầu là 1 (chỉ có 1 cách để đến mỗi ô)
    for (int i = 0; i < n; i++) dp[i][0] = 1;
    for (int j = 0; j < m; j++) dp[0][j] = 1;

    // Tính số cách cho từng ô còn lại
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    // Số cách đi đến ô (n-1, m-1)
    return dp[n - 1][m - 1];
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

            cout << "The amount of ways from cell (0,0) to cell (" << n - 1 << "," << m - 1 << ") is ";
            cout << countPaths(n, m) << endl << endl;
        }
    }

    return 0;
}
