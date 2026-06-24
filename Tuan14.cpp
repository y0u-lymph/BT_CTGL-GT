#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Cấu trúc một nút trong cây AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Hàm tạo một nút mới
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // Nút mới được thêm vào ban đầu có chiều cao là 1
    return node;
}

// Hàm lấy chiều cao của nút
int getHeight(Node* n) {
    if (n == nullptr) return 0;
    return n->height;
}

// Hàm lấy hệ số cân bằng (Balance Factor) của nút
int getBalance(Node* n) {
    if (n == nullptr) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// Quay phải (Right Rotate) nhánh con tại y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Thực hiện quay
    x->right = y;
    y->left = T2;

    // Cập nhật lại chiều cao
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Trả về gốc mới
    return x;
}

// Quay trái (Left Rotate) nhánh con tại x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Thực hiện quay
    y->left = x;
    x->right = T2;

    // Cập nhật lại chiều cao
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Trả về gốc mới
    return y;
}

// Hàm chèn một khóa vào cây AVL và tự động cân bằng
Node* insert(Node* node, int key) {
    // 1. Thực hiện chèn như cây BST thông thường
    if (node == nullptr) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Không cho phép trùng giá trị trong cây AVL này
        return node;

    // 2. Cập nhật chiều cao của nút tổ tiên này
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Lấy hệ số cân bằng để kiểm tra xem nút có bị mất cân bằng không
    int balance = getBalance(node);

    // Nếu mất cân bằng, có 4 trường hợp xảy ra:

    // Trường hợp Trái - Trái (Left Left - LL)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Trường hợp Phải - Phải (Right Right - RR)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Trường hợp Trái - Phải (Left Right - LR)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Phải - Trái (Right Left - RL)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Trả về con trỏ nút (không thay đổi)
    return node;
}

// --- CÁC HÀM DUYỆT CÂY ---

// 1. Duyệt Tiền thứ tự (Pre-order / NLR)
void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// 2. Duyệt Trung thứ tự (In-order / LNR) -> Sẽ in ra dãy tăng dần
void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// 3. Duyệt Hậu thứ tự (Post-order / LRD)
void postOrder(Node* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

int main() {
    Node* root = nullptr;

    // Dãy số đầu vào từ bảng trong ảnh
    vector<int> input_sequence = {32, 51, 27, 83, 96, 11, 45, 75, 66};

    cout << "Bat dau chen cac phan tu vao cay AVL:\n";
    for (int num : input_sequence) {
        root = insert(root, num);
        cout << "Da chen: " << num << "\n";
    }

    cout << "\n-----------------------------------------\n";
    cout << "KET QUA DUYET CAY AVL SAK KHI CHEN:\n";
    
    cout << "\n1. Duyet Tien thu tu (NLR): ";
    preOrder(root);
    
    cout << "\n2. Duyet Trung thu tu (LNR - Tang dan): ";
    inOrder(root);
    
    cout << "\n3. Duyet Hau thu tu (LRD): ";
    postOrder(root);
    cout << "\n";

    return 0;
}
