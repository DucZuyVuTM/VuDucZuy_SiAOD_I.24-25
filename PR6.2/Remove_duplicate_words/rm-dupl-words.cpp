#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Hàm tách câu thành các từ
vector<string> split(string str) {
    vector<string> words;
    string word = "";
    for (char ch : str) {
        if (ch == ' ') {
            if (!word.empty()) words.push_back(word);
            word = "";
        } else {
            word += ch;
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

// Hàm xóa các từ trùng lặp
string removeDuplicateWords(string sentence) {
    vector<string> words = split(sentence);
    string result = "";

    for (int i = 0; i < words.size(); i++) {
        bool isDuplicate = false;

        // Kiểm tra xem từ này có trùng lặp với các từ khác không
        for (int j = 0; j < words.size(); j++) {
            if (i == j)
                continue;
            if (words[j] == words[i]) {
                isDuplicate = true;
                break;
            }
        }

        // Nếu không trùng lặp, thêm từ vào kết quả
        if (!isDuplicate) {
            if (!result.empty()) result += " ";
            result += words[i];
        }
    }
    return result;
}

int main() {
    string sentence;
    cout << "Write the sentence: "; getline(cin, sentence);
    cout << "Original sentence: " << sentence << endl;
    
    string newSentence = removeDuplicateWords(sentence);
    cout << "After removing duplicates: " << newSentence << endl;
    
    return 0;
}
