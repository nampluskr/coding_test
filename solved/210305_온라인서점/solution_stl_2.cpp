#if 0
// STL 38 ms: 데이터 추가/삭제시 우큐에 저장
#include <vector>
#include <queue>
using namespace std;

#define NUM_BOOKS		(100000 + 1)
#define NUM_AUTHORS		(10000 + 1)
#define NUM_CATEGORIES	(20 + 1)
#define DELETED 1

struct Book {
	int cID;
	int price;
	int num_authors;
	vector<int> authorList;
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
struct Category {
	int num_books;
	priority_queue<Data> bookPQ;
};

vector<Book> books;
vector<Author> authors;
vector<Category> categories;

priority_queue<Author> authorPQ;

//////////////////////////////////////////////////////////////
void init(int N, int C)
{
	books.clear();		books.resize(NUM_BOOKS);
	authors.clear();	authors.resize(NUM_AUTHORS);
	categories.clear(); categories.resize(NUM_CATEGORIES);

	for (int aID = 1; aID <= N; aID++) { authors[aID].aID = aID; }

	while (!authorPQ.empty()) { authorPQ.pop(); }
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

		for (int aID : books[bID].authorList) {
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
	priority_queue<Data>& Q = categories[cID].bookPQ;
	vector<int> popped;
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
	for (int bID : popped)
		Q.push({ bID, books[bID].sales });

	return min(categories[cID].num_books, 3);
}

void getBestAuthors(int aIDs[]) {
	vector<int> popped;
	int cnt = 0;

	while (!authorPQ.empty() && cnt < 3) {
		Author author = authorPQ.top(); authorPQ.pop();

		if (authors[author.aID].profit != author.profit) continue;

		popped.push_back(author.aID);
		aIDs[cnt] = author.aID;
		cnt += 1;
	}
	for (int aID : popped)
		authorPQ.push({ aID, authors[aID].profit });
}
#endif