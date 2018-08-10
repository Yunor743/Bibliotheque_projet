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

    /*le system cherche les fichiers de sauvegarde*/
    lib_system.saveSearch("members.irdl", members.save_path);
    lib_system.saveSearch("books.irdl", books.save_path);

    /*On charge les fichiers de sauvegarde*/
    books.load();
    members.load();

    /*On insère dans nos tables*/
    //members.insert("PERINAZZO", "christian");
    //books.insert("La vie est un long fleuve tranqile", 20.0);

    /*On supprime une ligne de nos table se trouvant à l'id cible*/
    //books.delOne(4161255391);
    //members.delOne(545404204);

    /*Opération system*/
    //lib_system.borrow(books, members, 3890346734, 3499211612, 10);
    //lib_system.returned(books, members, 545404204);
    //lib_system.check(books, members);

    /*On sauvegarde nos tables*/
    books.save();
    members.save();

    /*On affiche nos tables*/
    books.disp();
    members.disp();

    std::cin.ignore();
    std::cin.get();

    return 0;
}