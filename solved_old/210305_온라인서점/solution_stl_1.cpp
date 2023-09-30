#if 0
// STL 2266 ms: 함수 호출시 힙정렬
#include <vector>
#include <queue>
using namespace std;

#define NUM_BOOKS       (100000 + 1)
#define NUM_AUTHORS     (10000 + 1)
#define NUM_CATEGORIES  (20 + 1)

#define DELETED         1

// 판매량, 재고량
struct Book {
    int price;
    int num_authors;
    vector<int> authorList;
    int category;
    int sales;
    int stock;
    int state;
};
vector<Book> books;
int bookCnt;

struct Author {
    int aID;
    int profit;

    bool operator<(const Author& author) const {
        return (profit < author.profit) || (profit == author.profit && aID > author.aID);
    }
};
vector<Author> authors;
int authorCnt;

struct Data {
    int bID;
    int sales;

    bool operator<(const Data& data) const {
        return (sales < data.sales) || (sales == data.sales && bID < data.bID);
    }
};

struct Category {
    int num_books;
    vector<int> bookList;
};
vector<Category> categories;
int categoryCnt;

///////////////////////////////////////////////////////////////////////////////
void init(int N, int C)
{
    books.clear();      books.resize(NUM_BOOKS);
    authors.clear();    authors.resize(NUM_AUTHORS);
    categories.clear(); categories.resize(NUM_CATEGORIES);

    bookCnt = 0;
    authorCnt = N;
    categoryCnt = C;
    for (int i = 1; i <= authorCnt; i++) { authors[i].aID = i; }
}

void addBookInfo(int bID, int cID, int price, int num, int aIDs[])
{
    books[bID].price = price;
    books[bID].category = cID;
    books[bID].num_authors = num;
    books[bID].stock += 1;

    for (int i = 0; i < num; i++) { 
        books[bID].authorList.push_back(aIDs[i]);
        authors[aIDs[i]].aID = aIDs[i];
    }
    bookCnt += 1;

    categories[cID].num_books += 1;
    categories[0].num_books += 1;

    categories[cID].bookList.push_back(bID);
    categories[0].bookList.push_back(bID);
}

void addBookStock(int bID, int cnt)
{
    books[bID].stock += cnt;
}

void removeBookInfo(int bID)
{
    books[bID].state = DELETED;

    categories[books[bID].category].num_books -= 1;
    categories[0].num_books -= 1;
}

// 책 bID 의 재고가 cnt 권 이상 남아 있다면 판매가 성공 처리되며 책의 재고가 cnt 권 감소한다.
// 판매가 성공 처리되었다면 1, 그렇지 않다면 0 을 반환한다.
int sellBooks(int bID, int cnt)
{
    int ret = 0;
    if (books[bID].stock > cnt) {
        books[bID].stock -= cnt;
        books[bID].sales += cnt;
        for (int aIdx: books[bID].authorList) {
            authors[aIdx].profit += books[bID].price * cnt / books[bID].num_authors;
        }
        ret = 1;
    }
    return ret;
}

// bIDs[] 배열에는 절판 되지 않은 책들만 저장되어 있어야 함에 유의하라.
int getBestSeller(int cID, int bIDs[])
{
    priority_queue<Data> Q;
    for (int bID: categories[cID].bookList) {
        if (books[bID].state != DELETED)
            Q.push({bID, books[bID].sales});
    }

    int cnt = 0;
    while (!Q.empty() && cnt < 3) {
        auto data = Q.top(); Q.pop();

        bIDs[cnt] = data.bID;
        cnt += 1;
    }
    return min(categories[cID].num_books, 3);
}

void getBestAuthors(int aIDs[])
{
    priority_queue<Author> Q;
    for (int aID = 1; aID <= authorCnt; aID++) { Q.push(authors[aID]); }

    int cnt = 0;
    while (!Q.empty() && cnt < 3) {
        auto author = Q.top(); Q.pop();

        aIDs[cnt] = author.aID;
        cnt += 1;
    }
}
#endif