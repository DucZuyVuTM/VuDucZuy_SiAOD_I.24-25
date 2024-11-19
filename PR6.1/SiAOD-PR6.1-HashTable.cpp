#include <iostream>
#include <vector>
#include <cstdlib> // Cho rand() và srand()
#include <optional>

using namespace std;

// Cấu trúc lưu trữ thông tin về sản phẩm
struct Product {
    int Code;
    string name;
    double price;
};

// HashTable với phương pháp giải quyết xung đột bằng Double Hashing (băm đôi)
class DoubleHashing_HashTable {
private:
    vector<optional<Product>> table;
    int tableSize;
    int count;  // Số lượng phần tử hiện có

    // Hàm băm đầu tiên tính toán chỉ số dựa trên mã số sản phẩm
    int hash1(int key) const {
        return key % tableSize;
    }

    // Hàm băm thứ hai cho Double Hashing
    int hash2(int key) const {
        return 1 + (key % (tableSize - 1));
    }
    
    // Mở rộng bảng băm và rehash lại toàn bộ bảng
    void rehash() {
        cout << "Rehashing...\n";
        vector<optional<Product>> oldTable = table;
        tableSize *= 2;
        table = vector<optional<Product>>(tableSize);
        count = 0;

        for (auto &entry : oldTable) {
            if (entry) {
                insert(entry->Code, entry->name, entry->price);
            }
        }
    }

public:
    // Constructor khởi tạo bảng băm với kích thước cho trước
    DoubleHashing_HashTable(int size) : tableSize(size), count(0) {
        table.resize(size);
    }

    // Hàm chèn một sản phẩm vào bảng băm
    void insert(int Code, const string &name, const double &price) {
        if (count >= tableSize * 0.75) {
            rehash();
        }

        int index = hash1(Code);
        int step = hash2(Code);

        // Double Hashing để tìm vị trí trống
        while (table[index]) {
            index = (index + step) % tableSize;  // Chuyển chỉ số theo bước của hàm băm thứ hai
        }

        table[index] = Product{Code, name, price};
        ++count;
        cout << "Inserted: " << name << " at index " << index << "\n";
    }

    // Hàm tìm kiếm sản phảm dựa trên mã số
    optional<Product> search(int Code) const {
        int index = hash1(Code);
        int step = hash2(Code);

        // Tìm kiếm với Double Hashing
        for (int i = 0; i < tableSize; ++i) {
            if (!table[index]) {  // Nếu gặp ô trống, không tìm thấy
                return nullopt;
            }
            if (table[index] -> Code == Code) {
                return table[index];  // Trả về sản phẩm nếu tìm thấy
            }
            index = (index + step) % tableSize;  // Chuyển chỉ số theo băm thứ hai
        }

        return nullopt;  // Không tìm thấy sau khi tìm toàn bộ bảng
    }

    // Hàm xóa một sản phẩm dựa trên mã số
    void del(int Code) {
        int index = hash1(Code);
        int step = hash2(Code);
        
        // Tìm sản phẩm để xóa với Double Hashing
        for (int i = 0; i < tableSize; ++i) {
            if (!table[index]) {  // Nếu gặp ô trống, không tìm thấy
                cout << "Product code " << Code << " not found.\n";
                return;
            }
            if (table[index] -> Code == Code) {
                cout << "Removed: " << table[index] -> name << " from index " << index << "\n";
                table[index] = nullopt;  // Đặt lại ô thành rỗng
                --count;
                return;
            }
            index = (index + step) % tableSize;  // Chuyển chỉ số theo băm thứ hai
        }

        std::cout << "Product code " << Code << " not found.\n";
    }
    
    void printInfo() {
        cout << "-----" << endl;
        for (auto &output : table) {
            if (output) {
                cout << output->Code << " " << output->name << " " << output->price << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
    
    void deleteAll() {
        for (auto &element : table) {
            element = nullopt;
        }
    }
    
    void test(int oldSize) {
        deleteAll();
        
        cout << endl;
        cout << "-------" << endl;
        cout << "Testing: Resize table" << endl;
        table.resize(5);
        tableSize = 5;
        count = 0;
        cout << "Table size after resizing: " << table.size() << endl;
        
        cout << endl;
        cout << "-------" << endl;
        cout << "Testing: Rehash" << endl;
        insert(123427, "Apple", 69.9);
        insert(453683, "Watermelon", 429.9);
        insert(789254, "Banana", 54.9);
        insert(472883, "Coconut", 129.9);
        cout << "Before:" << endl;
        printInfo();
        insert(342133, "Lychee", 109.9);
        cout << "After:" << endl;
        printInfo();
        
        deleteAll();
        table.resize(5);
        tableSize = 5;
        count = 0;
        
        cout << endl;
        cout << "-------" << endl;
        cout << "Testing: Insert element" << endl;
        cout << "Before:" << endl;
        printInfo();
        insert(453683, "Watermelon", 429.9);
        cout << "After:" << endl;
        printInfo();
        
        cout << endl;
        cout << "-------" << endl;
        cout << "Testing: Delete element" << endl;
        cout << "Before:" << endl;
        printInfo();
        del(453683);
        cout << "After:" << endl;
        printInfo();
        
        cout << endl;
        cout << "-------" << endl;
        cout << "Testing: Find element" << endl;
        insert(123427, "Apple", 69.9);
        insert(453683, "Watermelon", 429.9);
        insert(789254, "Banana", 54.9);
        printInfo();
        auto result = search(789254);
        if (result) {
            cout << "Found: " << result->name << ". Price: " << result->price << " rubles \n";
        } else {
            cout << "Product not found.\n";
        }
        
        cout << endl;
        cout << "-------" << endl;
        cout << "Testing: Print table" << endl;
        printInfo();
        
        cout << "Test ended." << endl;
        deleteAll();
        table.resize(oldSize);
        tableSize = oldSize;
        count = 0;
    }
};

int main() {
    int size; string opt;
    
    srand(time(0));
    string names[] = {"Apple", "Watermelon", "Banana", "Table", "Chopsticks",
                     "Computer", "Cup", "Wardrobe", "Noodles", "Spoon"};
    
    int code;
    string n;
    double p;
    
    cout << "Write the size of hash table: "; cin >> size;
    // Tạo bảng băm với kích thước cho trước
    DoubleHashing_HashTable hashTable(size);
    
    cout << "---------------------------------" << endl
         << "Choose an option:"                 << endl
         << "1) Insert product."                << endl
         << "2) Delete product."                << endl
         << "3) Find product by code."          << endl
         << "4) Print all the table."           << endl
         << "5) Automatic input (5 products)."  << endl
         << "6) Test the program."              << endl
         << "E) Exit the program."              << endl
         << "---------------------------------" << endl;
    
    cout << "Write the option: "; cin >> opt;
    while (opt != "E") {
        if (opt == "1") {
            cout << "Write the product code: "; cin >> code;
            
            if (code < 100000 || code > 999999) {
                cout << "Code must be a 6 digit number." << endl;
                
                cout << "---" << endl;
                cout << "Write the option: "; cin >> opt;
                continue;
            }
            
            cout << "Write the product name: "; cin >> n;
            cout << "Write the product price: "; cin >> p;
            
            // Chèn các sản phẩm vào bảng băm
            hashTable.insert(code, n, p);
        }
        
        if (opt == "2") {
            cout << "Write the product code to delete: "; cin >> code;
            // Xóa sản phẩm
            hashTable.del(code);
        }
        
        if (opt == "3") {
            cout << "Write the product code to find: "; cin >> code;
            
            // Tìm kiếm sản phẩm
            auto result = hashTable.search(code);
            if (result) {
                cout << "Found: " << result->name << ". Price: " << result->price << " rubles \n";
            } else {
                cout << "Product not found.\n";
            }
        }
        
        if (opt == "4") {
            hashTable.printInfo();
        }
        
        if (opt == "5") {
            for (int i = 0; i < 5; i++) {
                code = rand() % 900000 + 100000; // Code ngẫu nhiên từ 100000 đến 999999
            
                n = names[rand() % 7];
                p = rand() % 201 + 100; // Giá ngẫu nhiên từ 100 đến 300
                
                p -= 0.1;
            
                hashTable.insert(code, n, p);
            }
        }
        
        if (opt == "6") {
            // Kiểm tra chương trình
            hashTable.test(size);
        }
        
        cout << "Write the option: "; cin >> opt;
    }

    return 0;
}
