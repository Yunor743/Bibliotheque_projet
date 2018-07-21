#include <iostream> // For debug purposes
#include "headers/books.hpp"
#include "headers/members.hpp"

using uint = unsigned int;


struct Books //contient une table de tous les livres ainsi que des fonctions pour edit/lire celle-ci
{
    std::unordered_map<uint, BookInfo> table;    // table de tout les livres
    void insert()
    {

    }
    void disp()
    {

    }
};




int main(int, char**)
{
    Members members;
    Books books;
    return 0;
}
