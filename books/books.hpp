#pragma once
#include <unordered_map>
#include <string>
#include <ctime>
#include <random>

using uint = unsigned int;

enum class BookState : int {
  AVAILABLE,
  BORROWED,
  LOST,
  ORDERED
};

struct BookInfo // on stock toute les informations relatives à un livre
{
    std::string title;          //titre du livre
    BookState state;                  //état du livre (empreinté, perdu, en achat, dispo)
    int id_member;              //id du membre qui à empreinté le livre
    float price;                //prix théorique du livre si il doit y avoir un remboursement
    std::time_t return_date;    //Date où le livre doit être returner à la bibliothèque
};

struct Books
{
  protected:
    std::mt19937 generator;
  public:
    std::unordered_map<uint, BookInfo> table;
    void insert();
    void disp() const;
};
