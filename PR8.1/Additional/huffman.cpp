#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Cấu trúc cho một node trong cây Huffman
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr) {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

// So sánh để sắp xếp trong hàng đợi đầu tiên
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Duyệt cây Huffman và mã hóa các kí tự
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Duyệt cây Huffman để giải mã
void decode(Node* root, int &index, string str) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

// Hàm để xây dựng cây Huffman và thực hiện mã hóa
void buildHuffmanTree(string text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "\nHuffman algorithm" << endl;

    cout << "----------------" << endl;
    cout << "Original string:\n" << text << endl;
    cout << "Size in bits: " << text.length() * 8 << endl;

    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch];
    }

    cout << "\nEncoded string:\n" << str << endl;
    cout << "Size in bits: " << str.length() << endl;

    int index = -1;
    cout << "\nDecoded string:\n";
    while (index < (int)str.size() - 1) {
        decode(root, index, str);
    }
    cout << "\n----------------\n" << endl;
}

int main() {
    string data = "Suni";

    while (data != "-1") {
        cout << "Write the string (write -1 to exit): ";
        getline(cin, data);

        if (data != "-1") {
            buildHuffmanTree(data);
        }
    }

    cout << "Program exited" << endl;
    return 0;
}
