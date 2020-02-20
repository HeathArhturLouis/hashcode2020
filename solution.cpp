using namespace std;

#include <set>
#include <vector>
#include <fstream>

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

class SolutionLibrary
{
public:
    int id;
    int numBooksToScan;
    vector<int> bookIDs;
};

class Evaluator
{
public:
    set<Library *> libraries;
    set<Book *> usedBooks;
    int numDays;
    float alpha, beta, gamma;
    int lambda;
    Evaluator(set<Library *> libraries, float alpha, float beta, float gamma, int lambda)
    {
        this->libraries = libraries;
        this->alpha = alpha;
        this->beta = beta;
        this->gamma = gamma;
        this->lambda = lambda;
    }

    vector<Library *> eval()
    {
        for (Library *lib : this->libraries)
        {
            lib->calcAvgBookValue(set<Book *>());
        }
        vector<Library *> solutionLibraries;
        // Optimize later 1
        while (this->numDays)
        {
            float maxScore = 0;
            Library *bestLibrary;
            for (auto it = this->libraries.begin(); it != this->libraries.end(); it++)
            {
                Library *lib = *it;
                float score = lib->evalScore(this->alpha, this->beta, this->gamma);
                if (score > maxScore)
                {
                    maxScore = score;
                    bestLibrary = lib;
                    this->libraries.erase(it);
                }
            }
            // Create solution library object  /// just a library for now fam
            solutionLibraries.push_back(bestLibrary);
            // Add it to vector
        }
        return solutionLibraries;
    };
};

void parseOutput(vector<Library *> libraries)
{
    ofstream solution;
    solution.open("solution.txt");
    solution << libraries.size() << "\n";
    for (Library *lib : libraries)
    {
        vector<Book *> mistakesWereMade(lib->books.begin(), lib->books.end());
        sort(mistakesWereMade.begin(), mistakesWereMade.end());
        solution << lib->id << " " << lib->books.size() << "\n";
        for (Book *book : mistakesWereMade)
        {
            solution << book->id << " ";
        }
        solution << "\n";
    }
    solution.close();
}

int main()
{
    parseOutput(vector<Library *>());
    return 0;
}