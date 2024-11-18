#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <limits>

using namespace std;

// Cấu trúc biểu diễn cạnh của đồ thị
struct Edge {
    int destination;
    int weight;
};

// Hàm thực hiện thuật toán Dijkstra
vector<int> dijkstra(int n, vector<vector<Edge>>& graph, int start) {
    vector<int> distance(n, INT_MAX); // Khoảng cách từ start đến các đỉnh khác
    distance[start] = 0;

    // Priority queue dùng để chọn đỉnh có khoảng cách nhỏ nhất
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start}); // Đỉnh bắt đầu với khoảng cách 0

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        // Bỏ qua nếu khoảng cách không cập nhật
        if (current_distance > distance[current_vertex]) continue;

        // Duyệt các cạnh kề của current_vertex
        for (const Edge& edge : graph[current_vertex]) {
            int neighbor = edge.destination;
            int weight = edge.weight;
            int new_distance = current_distance + weight;

            // Nếu tìm thấy đường đi ngắn hơn
            if (new_distance < distance[neighbor]) {
                distance[neighbor] = new_distance;
                pq.push({new_distance, neighbor});
            }
        }
    }

    return distance;
}

int main() {
    int n; // Số lượng đỉnh
    cout << "Write the amount of vertices: ";
    cin >> n;

    if (n <= 1) {
        cout << "The number of vertices must be greater than 1. Exiting." << endl;
        return 0;
    }

    vector<vector<Edge>> graph(n); // Vector chứa các đỉnh và các đường kết nối của chúng

    int startVertex, endVertex, weight;
    cout << "Write the start vertex of the connection, write -1 to end: ";
    cin >> startVertex;

    while (startVertex != -1) {
        if (startVertex < 1 || startVertex > n) {
            cout << "Invalid start vertex. Have to enter a vertex between 1 and " << n << "." << endl;
            break;
        }

        cout << "Write the end vertex of the connection, write -1 to end: ";
        cin >> endVertex;

        if (endVertex == -1) break;

        if (endVertex < 1 || endVertex > n || endVertex == startVertex) {
            cout << "Invalid end vertex. Have to enter a different vertex between 1 and " << n << "." << endl;
            break;
        }

        cout << "Write the weight of the connection, write -1 to end: ";
        cin >> weight;

        if (weight == -1) break;

        if (weight < 0) {
            cout << "Invalid weight. Have to enter a non-negative value." << endl;
            break;
        }

        // Đỉnh startVertex kết nối với đỉnh endVertex (trọng số weight)
        graph[startVertex - 1].push_back({endVertex - 1, weight});

        cout << "Write the start vertex of the connection, write -1 to end: ";
        cin >> startVertex;
    }

    int start; // Đỉnh bắt đầu
    cout << "Write the start vertex to begin finding ways, write non-positive number to exit: ";
    cin >> start;

    if (start < 1 || start > n) {
        cout << "Invalid start vertex. Exiting." << endl;
        return 0;
    }

    // Thực hiện thuật toán Dijkstra
    vector<int> distances = dijkstra(n, graph, start - 1);

    // In khoảng cách từ đỉnh bắt đầu đến các đỉnh khác
    cout << "Distances from vertex " << start << " to other vertices:\n";
    for (int i = 0; i < n; ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Cannot reach vertex " << i + 1 << endl;
        } else {
            cout << "To vertex " << i + 1 << ": " << distances[i] << endl;
        }
    }

    cout << "...Program finished" << endl;
    cout << "Press any key + ENTER to exit console." << endl;

    // Đợi người dùng nhấn phím bất kỳ và nhấn Enter
    cin.ignore();  // Bỏ qua ký tự newline còn sót lại trong bộ đệm
    cin.get();     // Chờ nhập Enter

    return 0;
}
