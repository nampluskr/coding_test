#include <cstdio>
#include "list_iterative.h"

using NODE = LIST<DATA>::NODE;

void LIST<DATA>::clear() {
    while (head != nullptr) {
        // pop front
        NODE* temp = head;
        head = head->next;
        delete_node(temp);
    }
}

void LIST<DATA>::preorder() {
    NODE* ptr = head;
    while (ptr != nullptr) {
        printf("%d[%d]->", ptr->data.value, ptr->data.idx);
        ptr = ptr->next;
    }
}

void LIST<DATA>::insert(const DATA& data) {
    if (head == nullptr) { head = new_node(data, nullptr); return; }
    // insert data before head
    if (head->data < data) { head = new_node(data, head); return; }
    NODE* ptr = head;
    while (ptr != nullptr) {
        // insert data after ptr
        if (data < ptr->data) { ptr->next = new_node(data, ptr->next); return; }
        if (ptr->next == nullptr) { ptr = new_node(data, nullptr); return; }
        ptr = ptr->next;
    }
}

void LIST<DATA>::remove(const DATA& data) {
    NODE *temp, *prev, *ptr;
    if (head->data == data) { // pop front
        temp = head; head = head->next;
        delete_node(temp); return;
    }
    prev = head; ptr = head->next;
    while (ptr != nullptr) { // erase after prev
        if (ptr->data == data) {
            temp = ptr; prev->next = ptr->next;
            delete_node(temp); return; 
        }
        prev = ptr; ptr = ptr->next;
    }
}

NODE* LIST<DATA>::find(const DATA& data) {
    if (head == nullptr) { return nullptr; }
    NODE* ptr = head;
    while (ptr->next != nullptr) {
        if (ptr->data == data) { return ptr; }
        ptr = ptr->next;
    }
    return nullptr;
}

NODE* LIST<DATA>::find_min() {
    if (head == nullptr) { return nullptr; }
    NODE* ptr = head;
    while (ptr->next != nullptr) { ptr = ptr->next; }
    return ptr;
}