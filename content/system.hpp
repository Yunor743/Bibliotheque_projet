
#pragma once
#include <unordered_map>
#include <cmath>
#include <iostream>
#include "members.hpp"
#include "books.hpp"
#include "classic_content.hpp"

using uint = unsigned int;  //on poura utiliser uint pour représenter un unsigned int

struct System
{
private:
  int ifReturnLate(Books &book_inst, uint book_id);   //Cette fonction permettra de répondre à la condition: est ce que le livre à été rendu en retard ?
  void return_book(Books &book_inst, Members &member_inst, uint book_id);   //Déclaration de la fonction permettant de déclaré un livre comme rapporté
  void pay_tax(Books &book_inst, Members &member_inst, uint book_id, bool is_booklost, float tax_coef = 0.5);   //Cette fonction permet de définir la taxe a payer en cas d'oublie de la part du membre
public:
  void saveSearch(std::string save_filename, std::string &save_path);    //cette fonction me permet de rechercher le fichier spécifique a différents chemins
  void borrow(Books &book_inst, Members &member_inst, uint book_id, uint member_id, uint days_of_borrowing = 30);  //Déclaration de la fonction permettant l'empreint d'un livre
  void returned(Books &book_inst, Members &member_inst, uint book_id, bool is_booklost);    //Dans le cas ou le membre rapporte un livre ou viens payer sa taxe
  void order(Books &book_inst, uint book_id, uint days_before_arrival);
  void check(Books &book_inst, Members &member_inst);   //Cette fonction va s'itéré une fois par jour pour actualiser l'état de l'emprein de chaque membres
};