#include <iostream>
#include <queue>

using namespace std;

// Структура узла дерева AVL
struct Node {
    int key;      // Значение узла
    Node* left;   // Указатель на левый дочерний элемент
    Node* right;  // Указатель на правый дочерний элемент
    Node* parent; // Указатель на родительский узел
    int height;   // Высота узла
};

// Возвращает значение узла
int getKey(Node* node) {
    if (node) {
        return node->key;
    } else {
        return 0;
    }
}

// Возвращает высоту узла
int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Создаёт новый узел
Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->height = 1;   // Установить начальную высоту на 1
    return node;
}

// Вычисляет равновесное значение узла
int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Поворачивается вправо (Right Rotate)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Выполнить вращение
    x->right = y;
    y->left = T2;

    // Обновить родительский указатель
    if (T2 != nullptr) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;

    // Обновить высоту
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Поворачивается влево (Left Rotate)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Выполнить вращение
    y->left = x;
    x->right = T2;

    // Обновить родительский указатель
    if (T2 != nullptr) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    // Обновить высоту
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Вставляет узел в дерево AVL
Node* insert(Node* node, int key) {
    // Выполнить вставку узла, как в двоичном дереве поиска (BST).
    if (node == nullptr)
        return createNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
        node->left->parent = node;  // Обновить родительский указатель для дочернего узла
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
        node->right->parent = node; // Обновить родительский указатель для дочернего узла
    }
    else
        return node;                // Дублирование ключей не допускается

    // Обновить высоту родительского узла
    node->height = 1 + max(height(node->left), height(node->right));

    // Проверить значение баланса этого узла, чтобы убедиться, что он несбалансирован.
    int balance = getBalance(node);

    // Дисбаланс слева (Left Left)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Дисбаланс справа (Right Right)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Дисбаланс левого и правого (Left Right)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Дисбаланс правого и левого (Right Left)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // Возвращает указатель узла без изменений
}

// Печатает дерево в порядке LNR. (Left-Node-Right)
void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// Печатает дерево в порядке BFS (Breadth First Search)
void breadthFirstSearch(Node* root) {
    if (root == nullptr) {
        return;
    }

    queue<Node*> q;   // Очередь для обхода в ширину
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->key << " ";

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

// Суммирует значении листьев
int sum(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int sum = 0;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->left == nullptr && current->right == nullptr)
            sum += current->key;

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
    
    return sum;
}

// Сделает левый дочерний узел текущего узла текущим узлом
Node* turnLeft(Node* curr) {
    if (curr->left) {
        cout << "Conpleted\n";
        return curr->left;
    } else {
        cout << "Left node not found\n";
        return curr;
    }
}

// Сделает правый дочерний узел текущего узла текущим узлом
Node* turnRight(Node* curr) {
    if (curr->right) {
        cout << "Conpleted\n";
        return curr->right;
    } else {
        cout << "Right node not found\n";
        return curr;
    }
}

// Сделает родительский узел текущего узла текущим узлом
Node* toParent(Node* curr) {
    if (curr->parent) {
        cout << "Conpleted\n";
        return curr->parent;
    } else {
        cout << "Parent node not found\n";
        return curr;
    }
}

// Удалит все дерево и освободит память
void deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    // Рекурсивно удалять левый и правый дочерние узлы
    deleteTree(node->left);
    deleteTree(node->right);

    // Освобождает память текущего узла.
    delete node;
}

int main() {
    Node* root = nullptr;   // Корневой узел
    Node* curr = nullptr;   // Текущий узел
    
    int choice, num;
    
    cout << "Menu:";
    cout << "\n1) Insert node.";
    cout << "\n2) Print system (LNR)";
    cout << "\n3) Print system (BFS)";
    cout << "\n4) Print sum of leaf nodes";
    cout << "\n5) Print the height of current node";
    cout << "\n6) Move the current node to the left";
    cout << "\n7) Move the current node to the right";
    cout << "\n8) Move the current node to the parent node";
    cout << "\n9) Print the number in the root node";
    cout << "\n10) Print the number in the current node";
    
    cout << "\n---";
    cout << "\n0) Exit\n";

    do {
        cout << "\nChoice: "; cin >> choice;

        switch (choice) {
            case 1:
                cout << "Write the number for adding: "; cin >> num;
                root = insert(root, num);
                if (!curr)
                    curr = root;
                break;
                  
            case 2:
                inOrder(root);
                cout << endl;
                break;
            
            case 3:
                breadthFirstSearch(root);
                cout << endl;
                break;
                
            case 4:
                cout << "The sum of leaf nodes: " << sum(root) << endl;
                break;
                
            case 5:
                cout << "The height of current node: " << height(curr) << endl;
                break;
                
            case 6:
                if (curr)
                    curr = turnLeft(curr);
                else
                    cout << "Current node doesn't exist (Tree is not created)." << endl;
                break;
                
            case 7:
                if (curr)
                    curr = turnRight(curr);
                else
                    cout << "Current node doesn't exist (Tree is not created)." << endl;
                break;
                
            case 8:
                if (curr)
                    curr = toParent(curr);
                else
                    cout << "Current node doesn't exist (Tree is not created)." << endl;
                break;
                
            case 9:
                cout << "The key of root node: " << getKey(root) << endl;
                break;
                
            case 10:
                cout << "The key of current node: " << getKey(curr) << endl;
                break;
        }
    } while (choice != 0);
    
    deleteTree(root);

    return 0;
}
