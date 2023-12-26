#include <cstdio>
#include "sll_head_tail.h"

using NODE = SLL<DATA>::NODE;

NODE* SLL<DATA>::new_node(const DATA& data, NODE* ptr) {
    printf(">> Insert % d[%d]\n", data.value, data.idx);
    NODE* node = new NODE{ data, ptr };
    listSize += 1;
    return node;
}

void SLL<DATA>::delete_node(NODE* ptr) {
    printf(">> Remove % d[%d]\n", ptr->data.value, ptr->data.idx);
    delete ptr;
    listSize -= 1;
}

void SLL<DATA>::preorder(NODE* ptr) {
    if (ptr == nullptr) return;
    printf("%d[%d]->", ptr->data.value, ptr->data.idx);
    preorder(ptr->next);
}

// 기본 연산
void SLL<DATA>::push_front(const DATA& data) {
    NODE* node = new_node(data);
    if (head == nullptr) { head = node; tail = node; }
    else { node->next = head; head = node; }
}

void SLL<DATA>::push_back(const DATA& data) {
    NODE* node = new_node(data);
    if (head == nullptr) { head = node; tail = node; }
    else { tail->next = node; tail = node; }
}

void SLL<DATA>::pop_front() {
    NODE* temp = head;
    head = head->next;
    delete_node(temp);
}

void SLL<DATA>::pop_back() {
    if (head->next == nullptr) { pop_front(); return; }
    NODE* ptr = head->next;
    while (ptr->next->next != nullptr) { ptr = ptr->next; }
    NODE* temp = ptr->next;
    ptr->next = nullptr;
    tail = ptr;
    delete_node(temp);
}

NODE* SLL<DATA>::find(const DATA& data) {
    if (head == nullptr) { return nullptr; }
    NODE* ptr = head;
    while (ptr->next != nullptr) {
        if (ptr->data == data) { return ptr; }
        ptr = ptr->next;
    }
    return nullptr;
}

void SLL<DATA>::remove(const DATA& data) {
    NODE* temp, * prev, * ptr;
    if (head->data == data) { pop_front(); return; }
    prev = head; ptr = head->next;
    while (ptr != nullptr) { // erase after prev
        if (ptr->data == data) {
            temp = ptr; prev->next = ptr->next;
            if (tail == temp) { tail = prev; }
            delete_node(temp); return;
        }
        prev = ptr; ptr = ptr->next;
    }
}

// 보조 함수
NODE* SLL<DATA>::find_before(const DATA& data) {
    NODE* ptr = head;
    while (ptr->next != nullptr) {
        if (ptr->next->data == data) return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

void SLL<DATA>::insert_after(NODE* ptr, const DATA& data) {
    if (ptr) {
        ptr->next = new_node(data, ptr->next);
        if (tail == ptr) { tail = ptr->next; }
    }
}

void SLL<DATA>::erase_after(NODE* ptr) {
    if (ptr && ptr->next) {
        NODE* temp = ptr->next;
        ptr->next = ptr->next->next;
        delete_node(temp);
    }
}

// 데이터 접근
DATA& SLL<DATA>::operator[](int idx) {
    if (head) {   // !empty()
        if (idx == 0) { return head->data; }
        if (idx == listSize - 1) { return tail->data; }
        int cnt = 0;
        NODE* ptr = head;
        while (ptr != nullptr && cnt <= idx) {
            if (cnt == idx) return ptr->data;
            ptr = ptr->next;
            cnt += 1;
        }
    }
}
