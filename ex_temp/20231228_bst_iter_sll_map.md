### BST 반복문 

```cpp
template<typename T>
struct NODE {
    T data;
    NODE<T>* left = nullptr;
    NODE<T>* right = nullptr;
};

template<typename T>
struct BST {
    NODE<T>* root = nullptr;

    NODE<T>* find(NODE<T>* root, const T& data) {
        NODE<T>* ptr = root;
        while (ptr != nullptr) {
            if (ptr->data == data) { return ptr; }  // 찾은 노드 반환 (찾기 성공)
            if (data < ptr->data) { ptr = ptr->left; }
            else if (ptr->data < data) { ptr = ptr->right; }
        }
        // 찾기 실패 (ptr == nullptr)
        return nullptr;
    }
    void insert(const T& data) {
        NODE<T>* parent = nullptr;
        NODE<T>* ptr = root;
        while (ptr != nullptr) {
            if (ptr->data == data) { return; }  // 삽입 실패 (중복)
            parent = ptr;   // 현재 노드 저장하고, 다음 노드로 이동
            if (data < ptr->data) { ptr = ptr->left; }
            else if (ptr->data < data) { ptr = ptr->right; }
        } // 찾기 실패 (ptr == nullptr)

        // parent 자식 노드로 새 노드 붙이기 (parent == 실패 직전 노드)
        NODE<T>* node = new NODE<T>{ data, nullptr, nullptr };
        if (parent != nullptr) {
            if (data < parent->data) { parent->left = node; }
            else if (parent->data < data) { parent->right = node; }
        }
        else { root = node; }
    }
    void remove(const T& data) {
        NODE<T>* parent = nullptr;
        NODE<T>* ptr = root;
        while (ptr != nullptr) {
            if (ptr->data == data) { break; }   // 삭제할 노드 찾기 성공
            parent = ptr;
            if (data < ptr->data) { ptr = ptr->left; }
            else if (ptr->data < data) { ptr = ptr->right; }
        }
        if (ptr == nullptr) { return; }         // 삭제할 노드 찾기 실패

        // 찾은 노드 ptr 삭제 (parent 노드와 ptr 다음 노드 연결)
        if (!ptr->left && !ptr->right) {        // ptr 노드 차수 0
            if (parent == nullptr) { root = nullptr; }
            else {
                if (parent->left == ptr) { parent->left = nullptr; }
                else { parent->right = nullptr; }
            }
        }
        else if (!ptr->left || !ptr->right) {   // ptr 노드 차수 1
            NODE<T>* child = (ptr->left) ? ptr->left : ptr->right;
            if (parent == nullptr) { root = child; }
            else {
                if (parent->left == ptr) { parent->left = child; }
                else { parent->right = child; }
            }
        }
        else { // succ: ptr 오른쪽 서브트리에서 최소값 노드
            NODE<T>* succ_parent = ptr;
            NODE<T>* succ = ptr->right;
            while (succ->left != nullptr) {
                succ_parent = succ;
                succ = succ->left;
            }
            ptr->data = succ->data;
            if (succ_parent->left == succ) { succ_parent->left = succ->right; }
            else { succ_parent->right = succ->right; }
            ptr = succ;
        }
        delete ptr;
    }
    void inorder(NODE<T>* ptr) {
        if (ptr == nullptr) return;
        inorder(ptr->left);
        printf("%d ", ptr->data);
        inorder(ptr->right);
    }
};

void show() {
    printf(">> ");
    bst.inorder(bst.root);
    printf("\n");
}
```

### SLL 반복문

```cpp
template<typename T>
struct SLL {
    NODE<T>* head;

    NODE<T>* find(NODE<T>* head, const T& data) {
        NODE<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { return ptr; }  // 검색 성공
            if (data < ptr->data) { ptr = ptr->next; }
            else { break; }
        }   // 검색 실패
        return nullptr;
    }
    void insert(const T& data) {
        NODE<T>* parent = nullptr;
        NODE<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { return; }  // 삽입 실패 (중복)
            if (data < ptr->data) { // 내림차순으로 계속 검색
                parent = ptr;
                ptr = ptr->next;
            }
            else { break; }
        } // 검색 실패

        // parent 노드와 ptr 노드 사이에 새로운 노드 삽입
        NODE<T>* node = new NODE<T>{ data, nullptr };
        if (parent == nullptr) {
            node->next = head;
            head = node;
        }
        else {    // parent 다음에 노드 추가
            node->next = parent->next;
            parent->next = node;
        }
    }
    void remove(const T& data) {
        NODE<T>* parent = nullptr;
        NODE<T>* ptr = head;
        while (ptr != nullptr) {
            if (ptr->data == data) { break; }   // 삭제할 노드 찾기 성공
            if (data < ptr->data) {             // 내림차순으로 계속 검색
                parent = ptr;
                ptr = ptr->next;
            }
            else { break; }
        }
        if (ptr == nullptr) { return; }         // 삭제할 노드 찾기 실패
        
        // 찾은 노드 ptr 삭제 (parent 노드와 ptr 다음 노드 연결)
        if (parent == nullptr) { head = ptr->next; }
        else { parent->next = ptr->next; }
        delete ptr;
    }
    void clear() { while (head != nullptr) remove(head->data); }
    void preorder(NODE<T>* ptr) {
        if (ptr == nullptr) { return; }
        printf("%d ", ptr->data);
        preorder(ptr->next);
    }
};

void show() {
    printf(">> ");
    sll.preorder(sll.head);
    printf("\n");
}
```

### HASH MAP

```cpp
#define MAX_TABLE   10

template<typename KEY, typename DATA>
struct MAP {
    struct LUT {
        KEY key;
        DATA data;
    };
    vector<LUT> table[MAX_TABLE];

    int hashfunc(const KEY& key) { return key % MAX_TABLE; }
    void emplace(const KEY& key, const DATA& data) {
        int hash = hashfunc(key);
        table[hash].push_back({ key, data });
    }
    LUT* find(const KEY& key) {
        int hash = hashfunc(key);
        for (auto& x : table[hash]) {
            if (x.key == key)
                return &x;  // key, data
        }
        return nullptr;
    }
    DATA& operator[](const KEY& key) {
        auto ptr = find(key);
        if (ptr == nullptr) {
            emplace(key, {});
            return find(key)->data;
        }
        else { return ptr->data; }
    }
};
```
