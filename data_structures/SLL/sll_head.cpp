#include "sll_head.h"

using NODE = SLL<DATA>::NODE;

/////////////////////////////////////////////////////////////////////
// 리스트 정보, 첫/마지막 원소 접근
DATA SLL<DATA>::front() {
    return head->data;
}

DATA SLL<DATA>::back() {
    if (head->next == nullptr) return front();
    else {
        NODE* ptr = head;
        while (ptr->next != nullptr) { ptr = ptr->next; }
        return ptr->data;
    }
}

DATA& SLL<DATA>::operator[](int idx) {
    if (0 <= idx && idx < listSize) {
        int cnt = 0;
        NODE* ptr = head;
        while (ptr != nullptr && cnt <= idx) {
            if (cnt == idx) return ptr->data;
            ptr = ptr->next;
            cnt += 1;
        }
    }
}

bool SLL<DATA>::empty() {
    return listSize == 0;   // return head == nullptr;
}

int SLL<DATA>::size() {
    return listSize;
}

/////////////////////////////////////////////////////////////////////
// 초기화, 맨 처음 삽입/삭제, 맨 마지막 삽입/삭제
void SLL<DATA>::push_front(const DATA& data) {
    NODE* node = new NODE{ data, nullptr };
    if (!head) { head = node; }
    else { node->next = head; head = node; }
    listSize += 1;
}

void SLL<DATA>::pop_front() {
    NODE* temp = head;
    head = head->next;
    delete temp;
    listSize -= 1;
}

void SLL<DATA>::insert_after(NODE* ptr, const DATA& data) {
    if (ptr) {
        NODE* node = new NODE{ data, nullptr };
        node->next = ptr->next;
        ptr->next = node;
        listSize += 1;
    }
}

void SLL<DATA>::erase_after(NODE* ptr) {
    if (ptr && ptr->next) {
        NODE* temp = ptr->next;
        ptr->next = temp->next;
        delete temp;
        listSize -= 1;
    }
}

void SLL<DATA>::clear() {
    while (!empty()) pop_front();
}

void SLL<DATA>::push_back(const DATA& data) {
    if (head == nullptr) push_front(data);
    else {
        NODE* ptr = head;
        while (ptr->next != nullptr) { ptr = ptr->next; }
        ptr->next = new NODE{ data, nullptr };
        listSize += 1;
    }
}

void SLL<DATA>::pop_back() {
    if (head->next == nullptr) pop_front();
    else {
        NODE* prev = head;
        NODE* ptr = head->next;
        while (ptr->next != nullptr) {
            prev = ptr;
            ptr = ptr->next;
        }
        erase_after(prev);
    }
}

/////////////////////////////////////////////////////////////////////
// 검색 / 삽입 / 삭제
NODE* SLL<DATA>::find_ptr(const DATA& data) {
    NODE* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

NODE* SLL<DATA>::find_before(const DATA& data) {
    NODE* ptr = head;
    while (ptr->next != nullptr) {
        if (ptr->next->data == data) return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

void SLL<DATA>::remove(const DATA& data) {
    if (head->data == data) { pop_front(); }
    else {
        NODE* prev = head;
        NODE* ptr = head->next;
        while (ptr != nullptr) {
            if (ptr->data == data) {
                erase_after(prev);
                return;
            }
            prev = ptr;
            ptr = ptr->next;
        }
    }
}

int SLL<DATA>::count(const DATA& data) {
    int cnt = 0;
    NODE* ptr = head;
    while (ptr != nullptr) {
        if (ptr->data == data) cnt += 1;
        ptr = ptr->next;
    }
    return cnt;
}

/////////////////////////////////////////////////////////////////////
// 보조 멤버 함수
void SLL<DATA>::print() {
    if (empty()) { printf(">> Empty!\n"); }
    else {
        printf(">> ");
        for (auto ptr = head; ptr != nullptr; ptr = ptr->next) {
            ptr->data.print();
            printf(", ");
        }
        printf("\n");
    }
}

void SLL<DATA>::preorder(NODE* ptr) {
    if (!ptr) return;
    ptr->data.print();
    printf(", ");
    preorder(ptr->next);
}

void SLL<DATA>::postorder(NODE* ptr) {
    if (!ptr) return;
    postorder(ptr->next);
    ptr->data.print();
    printf(", ");
}

void SLL<DATA>::show(NODE* ptr) {
    if (ptr == nullptr) printf(">> nullptr\n");
    else {
        printf(">> ");
        ptr->data.print();
        printf("\n");
    }
}