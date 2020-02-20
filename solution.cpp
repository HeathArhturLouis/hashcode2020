using namespace std;

#include <set>

typedef struct Book
{
    int id;
    int score;
} Book;

class Library
{
public:
    Library()
    {
    }

private:
    set<Book *> books;
    int id;
    int setupTime;
    float avgBookVal;
    int numBooksPerDay;
    float evalScore(float alpha, float beta, float gamma)
    {
        return (alpha * this->avgBookVal + beta * this->numBooksPerDay) / gamma * this->setupTime;
    };
    float calcAvgBookValue(set<Book *> usedBooks)
    {
        this->avgBookVal = 0;
        for (Book *book : this->books)
        {
            if (usedBooks.find(book) != usedBooks.end())
            {
                continue;
            }
            else
            {
                this->avgBookVal += book->score / books.size();
            }
        }
        return this->avgBookVal;
    };
    set<Book *> getBooksToSend()
    {
        set<Book *> toSend;
        for (int i = 0; i < this->numBooksPerDay; i++)
        {
            Book *maxBook = this->getMaxBook();
            toSend.insert(maxBook);
            this->books.erase(maxBook);
        }
        return toSend;
    }
    Book *getMaxBook()
    {
        int max_seen = -1;
        Book *maxBook;
        for (Book *b : this->books)
        {
            if (b->score > max_seen)
            {
                max_seen = b->score;
                maxBook = b;
            }
        }
        return maxBook;
    }
};

class Evaluator
{
public:
    set<Library *> libraries;
    set<Book *> usedBooks;
    int numDays;
    float alpha, beta, gamma;
    int lambda;
    Evaluator(float alpha, float beta, float gamma, int lambda)
    {
        this->alpha = alpha;
        this->beta = beta;
        this->gamma = gamma;
        this->lambda = lambda;
    }
};

int main()
{

    return 0;
}