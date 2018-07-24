/*classic_content.hpp*/

//#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>

using uint = unsigned int; //on pourra utiliser uint pour représenter un unsigned int
enum class DateDivision : uint
{
    YEAR,
    MONTH,
    DAY,
    HOUR,
    MIN,
    SEC
};
int get_date_spec(DateDivision date_div);
std::time_t parse_days_in_date(uint nb_of_days, std::time_t start_date);

















/*books.hpp*/

//#pragma once
#include <unordered_map>
#include <string>
#include <ctime>
#include <random>

using uint = unsigned int; //on pourra utiliser uint pour représenter un unsigned int

enum class BookState : int //état du livre (empreinté, perdu, en achat, dispo)
{
  AVAILABLE,
  BORROWED,
  LOST,
  ORDERED
};
struct BookInfo // on stock toute les informations relatives à un livre
{
    std::string title;          //titre du livre
    BookState state;            //état du livre (empreinté, perdu, en achat, dispo)
    uint id_member;             //id du membre qui à empreinté le livre
    float price;                //prix théorique du livre si il doit y avoir un remboursement
    std::time_t return_date;    //Date où le livre doit être retourner à la bibliothèque
};
struct Books
{
  protected:                                      //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
    std::mt19937 generator; 
  public:                                         //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
    std::unordered_map<uint, BookInfo> table;     // table de tout les livres
    void insert(std::string title, BookState state, uint id_borrower, float price, std::time_t return_date);                                //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
    void disp() const;
};





















/*members.hpp*/

//#pragma once
//#include <unordered_map>
//#include <string>
//#include <ctime>
//#include <random>
#include <chrono>

//using uint = unsigned int;  //on poura utiliser uint pour représenter un unsigned int

enum class MemberState : bool // état du membre (banni, neutre)
{
  BANNED,
  NORMAL
};
struct MemberInfo //on stocke toute les informations relatives à un membre
{
    std::string nom;       //nom de famille
    std::string prenom;    // prénom
    MemberState state;     // état du membre (banni, neutre)
    std::time_t joined_on; // timestamp à laquelle le membre a été ajouté
};
struct Members //contient une table de tous les membres ainsi que des fonctions pour edit/lire celle-ci
{
  protected:                                      //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
    std::mt19937 generator;
  public:                                         //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
    std::unordered_map<uint, MemberInfo> table;   // table de tout les membres
    void insert(std::string nom, std::string prenom, MemberState state); //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
    void disp() const;
};















/*system.hpp*/

//using uint = unsigned int;  //on poura utiliser uint pour représenter un unsigned int

struct System
{
  void borrow(Books book_inst, uint book_id, uint member_id, uint days_of_borrowing);
  void return_book();
};


















/*classic_content.cpp*/
int get_date_spec(DateDivision date_div = DateDivision::YEAR)
{
    std::time_t result = std::time(nullptr);
    tm full_date = *std::localtime(&result);
    switch(date_div)
    {
        case DateDivision::YEAR:
            return full_date.tm_year + 1900; //Les années commence à se compter à partir de l'année 1900
            break;
        case DateDivision::MONTH:
            return full_date.tm_mon + 1; //les mois se compte à partir du moi 0
            break;
        case DateDivision::DAY:
            return full_date.tm_mday; //Les jours
            break;
        case DateDivision::HOUR:
            return full_date.tm_hour; // les heures
            break;
        case DateDivision::MIN:
            return full_date.tm_min; // les minutes
            break;
        case DateDivision::SEC:
            return full_date.tm_sec; // les secondes
            break;
    }
    return 1;
}
std::time_t parse_days_in_date(uint nb_of_days, std::time_t start_date = std::time(nullptr))
{

}


















/*books.cpp*/


void Books::insert(std::string title, BookState state = BookState::AVAILABLE, uint id_borrower, float price, std::time_t return_date)
{
  uint key;
  do
  {
    key = generator();
  } 
  while (table.find(key) == table.end());
  table.emplace(key, BookInfo{title, state, id_borrower, price, return_date});
}
void Books::disp() const
{

}

















/*members.cpp*/

void Members::insert(std::string nom, std::string prenom, MemberState state = MemberState::NORMAL) //on défini la fonction membre qui permet d'insérer une nouvelle ligne dans la table
{
  uint key; //on va générer aléatoirement la clé avec notre générateur generator
  do
  {
    key = generator();
  }
  while (table.find(key) == table.end()); // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
  table.emplace(key, MemberInfo{nom, prenom, state, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())}); //
}
void Members::disp() const
{


}













/*system.cpp*/

void System::borrow(Books book_inst, uint book_id, uint member_id, uint days_of_borrowing = 30) //function permettant l'emprunt d'un livre
{
  if(book_inst.table.find(book_id) != book_inst.table.end())            //On s'assure que le livre demandé existe
  {
    BookInfo one_bookinfo = book_inst.table[book_id];                   //on instancie toute les informations sur ce livre dans one_bookinfo
    if(one_bookinfo.state == BookState::AVAILABLE)                      //on s'assure que le livre est disponible
    {
      one_bookinfo.state = BookState::BORROWED;                         //On déclare le livre comme empreinté
      one_bookinfo.id_member = member_id;                               //On défini qui est le dernier empreinteur
      one_bookinfo.return_date = parse_days_in_date(days_of_borrowing); //On défini la date de retour
    }
    else
    {
      //Erreur: le livre n'est actuellement pas disponible
    }
  }
  else
  {
    //Erreur: le livre à empreinter n'éxiste pas
  }
}
















/*main.cpp*/
#include <iostream> // For debug purposes


int main(int, char**)
{
    Members members;
    Books books;

    Members mes_membres;
    auto myactor = mes_membres.table.find(13);



    return 0;
}
