#include <iostream>
#include <fstream>
using namespace std;

int no_books;
int no_libraries;
int no_days;

//declaring variables make sure that the memory used is within
// limits
//can declare it after we know how much memory we need
int book_scores[100000]; //0.38 mb ? this is sent in order

/// maybe optimize memory usage
struct Library
{
    int no_books;
    int sign_up_duration;
    int ship_books_per_day;
    int books[10000]; // can adapt it if memory becomes a problem
};

Library libraries[10000];
int main()
{
    ofstream out_file;
    ifstream in_file;
    //give the result file
    // might change it based on the problem solved
    out_file.open("results.out");

    //pass the input of the problem you want to solve

    in_file.open("a_ex.in");
    in_file >> no_books;
    in_file >> no_libraries;
    in_file >> no_days;

    //read book scores
    for (int i = 0; i < no_books; i++)
    {
        in_file >> book_scores[i];
    }

    //read libraries
    for (int i = 0; i < no_libraries; i++)
    {
        in_file >> libraries[i].no_books;
        in_file >> libraries[i].sign_up_duration;
        in_file >> libraries[i].ship_books_per_day;
        for (int j = 0; j < libraries[i].no_books; j++)
        {
            in_file >> libraries[i].books[j];
        }
    }

    for (int i; i < no_libraries; i++)
    {
        cout << "No Books in Lib: " << libraries[i].no_books << endl;
        cout << " Sign up Duration: " << libraries[i].sign_up_duration << endl;
        cout << " Books to ship per day: " << libraries[i].ship_books_per_day << endl;
        cout << "Books in library [" << i << "] : "; 
        for (int j = 0; j < libraries[i].no_books; j++)
        {
            cout << libraries[i].books[j]<<" ";
        }
        cout << endl;
    }

    return 0;
}