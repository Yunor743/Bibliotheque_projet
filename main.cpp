#pragma once
#include <iostream> // For debug purposes
#include <tuple>
#include <map>
#include <string>
#include <ctime>


struct MemberInfo //on stock toute les informations relatives à un membre
{
    std::string nom;    //nom de famille
    std::string prenom; // prénom
    bool state;         // état (banni, neutre)
};
struct BookInfo // on stock toute les informations relatives à un livre
{
    std::string title;          //titre du livre
    int state;                  //état du livre (empreinté, perdu, en achat, dispo)
    int id_member;              //id du membre qui à empreinté le livre
    float price;                //prix théorique du livre si il doit y avoir un remboursement
    std::time_t return_date;    //Date où le livre doit être returner à la bibliothèque
};
struct Members //contien une table de tous les membres ainsi que des fonctions pour edit/lire celle-ci
{
    static std::map<int, MemberInfo> table;   // table de tout les membres
    void insert()
    {
        MemberInfo member;
        table.insert();
    }
    void edit()
    {

    }
    void disp()
    {
        
    }
};
struct Books //contien une table de tous les livres ainsi que des fonctions pour edit/lire celle-ci
{
    static std::map<int, BookInfo> table;    // table de tout les livres
    void insert()
    {
        
    }
    void edit()
    {

    }
    void disp()
    {

    }
};




int main(int, char**)
{
  /* Je mettrais mon code ici */
  return 0;
}
