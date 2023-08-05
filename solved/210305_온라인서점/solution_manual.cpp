#if 1
// STL 38 ms: 데이터 추가/삭제시 우큐에 저장
// Array 51 ms
// LinkedList 46 ms
//#include <vector>
#include <queue>
using namespace std;

#define NUM_BOOKS		(100000 + 1)
#define NUM_AUTHORS		(10000 + 1)
#define NUM_CATEGORIES	(20 + 1)
#define DELETED 1

inline int min(int a, int b) { return (a < b) ? a : b; }

template<typename Type>
struct LinkedList {
    struct Node {
        Type data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

    void clear() { head = nullptr; tail = nullptr; }
    void push_back(const Type& data) {
        Node* node = new Node({ data, nullptr });
        if (head == nullptr) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
};

struct Book {
    int cID;
    int price;
    int num_authors;
    LinkedList<int> authorList;
    int stock;
    int sales;
    int state;
};
struct Author {
    int aID;
    int profit;

    bool operator<(const Author& author) const {
        return (profit < author.profit) ||
            (profit == author.profit && aID > author.aID);
    }
};

struct Data {
    int bID;
    int sales;

    bool operator<(const Data& data) const {
        return (sales < data.sales) || (sales == data.sales && bID < data.bID);
    }
};

#if 0
template<typename Type>
struct PriorityQueue{
    priority_queue<Type> heap;

    void init() { while (!heap.empty()) { heap.pop(); } }
    void push(const Type& data) { heap.push(data); }
    void pop() { heap.pop(); }
    Type top() { return heap.top(); }
    bool empty() { return heap.empty(); }
};
#else
template<typename Type>
struct PriorityQueue{
    Type heap[NUM_BOOKS];
    int heapSize = 0;

    void init() { heapSize = 0; }
    void push(const Type& data) {
        heap[heapSize] = data;
        int current = heapSize;

        while (current > 0 && heap[(current - 1) / 2] < heap[current])
        {
            Type temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
        heapSize = heapSize + 1;
    }
    void pop() {
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];
        int current = 0;

        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize) {
                child = current * 2 + 1;
            }
            else {
                child = heap[current * 2 + 2] < heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[child] < heap[current]) {
                break;
            }
            Type temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
            current = child;
        }
    }
    Type top() { return heap[0]; }
    bool empty() { return heapSize == 0; }
};
#endif

struct Category {
    int num_books;
    PriorityQueue<Data> bookPQ;
};

Book books[NUM_BOOKS];
Author authors[NUM_AUTHORS];
Category categories[NUM_CATEGORIES];

PriorityQueue<Author> authorPQ;

//////////////////////////////////////////////////////////////
void init(int N, int C)
{
    for (int i = 0; i < NUM_BOOKS; i++) { books[i] = {}; books[i].authorList.clear(); }
    for (int i = 0; i < NUM_AUTHORS; i++) { authors[i] = {}; }
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        categories[i] = {};
        categories[i].bookPQ.init();
    }

    for (int aID = 1; aID <= N; aID++) { authors[aID].aID = aID; }

    //while (!authorPQ.empty()) { authorPQ.pop(); }
    authorPQ.init();
    for (int i = 1; i <= N; i++) { authorPQ.push({ i, 0 }); }
}

void addBookInfo(int bID, int cID, int price, int num, int aIDs[])
{
    books[bID].cID = cID;
    books[bID].price = price;
    books[bID].num_authors = num;
    books[bID].stock += 1;

    for (int i = 0; i < num; i++) {
        books[bID].authorList.push_back(aIDs[i]);
        authors[aIDs[i]].aID = aIDs[i];
    }

    categories[cID].num_books += 1;
    categories[0].num_books += 1;

    categories[cID].bookPQ.push({ bID, 0 });
    categories[0].bookPQ.push({ bID, 0 });
}

void addBookStock(int bID, int cnt)
{
    books[bID].stock += cnt;
}

void removeBookInfo(int bID)
{
    books[bID].state = DELETED;

    categories[books[bID].cID].num_books -= 1;
    categories[0].num_books -= 1;
}

int sellBooks(int bID, int cnt)
{
    int ret = 0;
    if (books[bID].stock >= cnt) {
        books[bID].stock -= cnt;
        books[bID].sales += cnt;

        for (auto ptr = books[bID].authorList.head; ptr; ptr = ptr->next) {
            int aID = ptr->data;
            authors[aID].profit += books[bID].price * cnt / books[bID].num_authors;
            authorPQ.push({ aID, authors[aID].profit });
        }
        categories[books[bID].cID].bookPQ.push({ bID, books[bID].sales });
        categories[0].bookPQ.push({ bID, books[bID].sales });
        ret = 1;
    }
    return ret;
}

int getBestSeller(int cID, int bIDs[]) {
    auto& Q = categories[cID].bookPQ;
    LinkedList<int> popped;
    int cnt = 0;

    while (!Q.empty() && cnt < 3) {
        Data book = Q.top(); Q.pop();

        if (books[book.bID].sales != book.sales) continue;

        popped.push_back(book.bID);
        if (books[book.bID].state != DELETED) {
            bIDs[cnt] = book.bID;
            cnt += 1;
        }
    }
    for (auto ptr = popped.head; ptr; ptr = ptr->next) {
        int bID = ptr->data;
        Q.push({ bID, books[bID].sales });
    }

    return min(categories[cID].num_books, 3);
}

void getBestAuthors(int aIDs[]) {
    LinkedList<int> popped;
    int cnt = 0;

    while (!authorPQ.empty() && cnt < 3) {
        Author author = authorPQ.top(); authorPQ.pop();

        if (authors[author.aID].profit != author.profit) continue;

        popped.push_back(author.aID);
        aIDs[cnt] = author.aID;
        cnt += 1;
    }
    for (auto ptr = popped.head; ptr; ptr = ptr->next) {
        int aID = ptr->data;
        authorPQ.push({ aID, authors[aID].profit });
    }
}
#endif