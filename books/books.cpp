<<<<<<< HEAD
/*include temporaire pour debug intelliSense*/
#include "header/books.hpp"

struct BookInfo // on stock toute les informations relatives à un livre
{
    std::string title;          //titre du livre
    int state;                  //état du livre (empreinté, perdu, en achat, dispo)
    int id_member;              //id du membre qui à empreinté le livre
    float price;                //prix théorique du livre si il doit y avoir un remboursement
    std::time_t return_date;    //Date où le livre doit être returner à la bibliothèque
};
=======
#include "books.hpp"
>>>>>>> cfe4b39232fd5de3c5f3e288dd5987008fd51598

void Books::insert()
{

}
void Books::disp() const
{

}
