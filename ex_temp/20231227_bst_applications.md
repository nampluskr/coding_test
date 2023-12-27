### Expression Tree 계산

```cpp
template<typename T>
int eval(NODE<T>* ptr) {
    if (ptr == nullptr) { return 0; }
    if (!ptr->left && !ptr->right) { return ptr->data; }

    int op = ptr->data;
    int val1 = eval(ptr->left);
    int val2 = eval(ptr->right);

    printf(">> %d %c %d\n", val1, op, val2);
    switch (op) {
    case '+': return val1 + val2;
    case '-': return val1 - val2;
    case '*': return val1 * val2;
    case '/': return val1 / val2;
    }
    return 0;
}
```

### 노드 합 / 개수 / 리프 개수 / 높이 계산

```cpp
int get_sum(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    return ptr->data + get_sum(ptr->left) + get_sum(ptr->right);
}

int get_count(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    return 1 + get_count(ptr->left) + get_count(ptr->right);
}

int get_leaf_count(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    if (!ptr->left && !ptr->right) return 1;
    return get_leaf_count(ptr->left) + get_leaf_count(ptr->right);
}

int max(int a, int b) { return (a < b) ? b : a; }

int get_height(NODE<int>* ptr) {
    if (ptr == nullptr) return 0;
    return 1 + max(get_height(ptr->left), get_height(ptr->right));
}
```
