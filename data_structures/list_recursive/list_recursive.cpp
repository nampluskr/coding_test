#include <cstdio>
#include "list_recursive.h"

using NODE = LIST<DATA>::NODE;

NODE* LIST<DATA>::clear(NODE* ptr) {
    if (ptr == nullptr) { return nullptr; }
    ptr->next = clear(ptr->next);
    // pop back
    delete_node(ptr);
    return nullptr;
}

void LIST<DATA>::preorder(NODE* ptr) {
    if (ptr == nullptr) return;
    printf("%d[%d]->", ptr->data.value, ptr->data.idx);
    preorder(ptr->next);
}

NODE* LIST<DATA>::remove(NODE* ptr, const DATA& data) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->data == data) {
        NODE* temp = ptr->next;
        delete_node(ptr);
        return temp;
    }
    ptr->next = remove(ptr->next, data);
    return ptr;
}

NODE* LIST<DATA>::find(NODE* ptr, const DATA& data) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->data == data) { return ptr; }
    return find(ptr->next, data);
}

NODE* LIST<DATA>::find_min(NODE* ptr) {
    if (ptr == nullptr) { return nullptr; }
    if (ptr->next == nullptr) { return ptr; }
    return find_min(ptr->next);
}