#include "members.hpp"
#include "books.hpp"
#include "classic_content.hpp"
#include "system.hpp"
#include <iostream> // For debug purposes


int main(int, char**)
{
    /*On crée nos objets*/
    Members members;
    Books books;
    System lib_system;

    /*On charge les fichiers de sauvegarde*/
    books.load();
    members.load();

    /*On insère dans nos tables*/
    //members.insert("PERINAZZO", "christian");
    //books.insert("La vie est un long fleuve tranqile", 20.0);

    /*On supprime une ligne de nos table se trouvant à l'id cible*/
    //books.delOne(4161255391);
    //members.delOne(545404204);

    /*On sauvegarde nos tables*/
    //books.save();
    //members.save();

    /*Opération system*/
    //lib_system.borrow(books, members, 545404204, 3499211612, 90);
    //lib_system.return_book(books, members, 545404204);
    //lib_system.ifReturnLate(books, members, 3586334585);
    //lib_system.returned(books, members, 545404204);
    //lib_system.check(books, members);

    /*On affiche nos tables*/
    books.disp();
    members.disp();

    std::cin.ignore();
    std::cin.get();

    return 0;
}