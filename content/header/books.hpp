#pragma once
#include <unordered_map>
#include <string>
#include <ctime>
#include <random>

using uint = unsigned int; //on poura utiliser uint pour représenter un unsigned int

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
    int id_member;              //id du membre qui à empreinté le livre
    float price;                //prix théorique du livre si il doit y avoir un remboursement
    std::time_t return_date;    //Date où le livre doit être returner à la bibliothèque
};
struct Books
{
  protected:                                      //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
    std::mt19937 generator; 
  public:                                         //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
    std::unordered_map<uint, BookInfo> table;     // table de tout les livres
    void insert();                                //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
    void disp() const;
};
