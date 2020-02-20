using namespace std;
#include <set>
#include <vector>
#include <fstream>
#include <fstream>
#include <iostream>

int no_books;
int no_libraries;
int no_days;
ofstream out_file;
ifstream in_file;

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

class ReadInput
{

public:
    void start_files()
    {
        in_file.open("a_ex.in");
    }

    set<Library *> readBookScoresAndLibraries()
    {

        in_file >> no_books;
        in_file >> no_libraries;
        in_file >> no_days;

        // read the books score

        vector<int> book_scores;

        int temp;
        for (int i = 0; i < no_books; i++)
        {
            in_file >> temp;
            book_scores.push_back(temp);
        }

        set<Library *> libraries;
        set<Book *> books_local;
        // start reading the libraries
        int no_books_in_lib;

        for (int i = 0; i < no_libraries; i++)
        {
            Library *one_lib = new Library();
            in_file >> no_books_in_lib;
            in_file >> one_lib->setupTime;
            in_file >> one_lib->numBooksPerDay;

            for (int j = 0; j < no_books_in_lib; j++)
            {
                Book *one_book = new Book();
                one_book->id = j;
                one_book->score = book_scores[j];
                books_local.insert(one_book);
            }
            one_lib->books = books_local;
            //where save the books
            libraries.insert(one_lib);
        }

        //check if librarie sprint something

        return libraries;
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
    ReadInput *rinput = new ReadInput();
    rinput->start_files();

    set<Library *> libraries = rinput->readBookScoresAndLibraries();
    Evaluator *eval = new Evaluator(libraries, 1.0, 1.0, 1.0, 1);
    vector<Library *> libs(eval->libraries.begin(), eval->libraries.end());
    for (auto lib : libs)
    {
        for (auto b : lib->books)
        {
            cout << b->score << "\n";
        }
    }
    parseOutput(libs);

    return 0;
}