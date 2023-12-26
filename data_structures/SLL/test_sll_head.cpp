#include "sll_head.h"

SLL<DATA> sll;

void init() {
    sll.push_front({ -1, -1 });
    sll.push_front({ 30, 3 });
    sll.push_front({ 20, 2 });
    sll.push_front({ 10, 1 });
    sll.print();
}

int main()
{
    init();

    //sll.show(sll.find_before({ 10, 1 }));
    //sll.show(sll.find_before({ 20, 2 }));
    //sll.show(sll.find_before({ 30, 3 }));
    //sll.show(sll.find_before({ -1, -1 }));

    //sll.show(sll.find({ 10, 1 }));
    //sll.show(sll.find({ 20, 2 }));
    //sll.show(sll.find({ 30, 3 }));
    //sll.show(sll.find({ -1, -1 }));

    auto iter = sll.find({ 10, 1 });
    if (iter == sll.end())
        printf("nullptr\n");
    else {
        (*iter).print(); printf("\n");
    }


    return 0;
}