
/*include temporaire pour debug intelliSense*/
#include "header/members.hpp"

struct MemberInfo //on stock toute les informations relatives à un membre
#include <chrono>

void Members::insert(std::string nom, std::string prenom, MemberState state = MemberState::NORMAL) //on défini la fonction membre qui permet d'insérer une nouvelle ligne dans la table
{
  unsigned int key; //on va générer aléatoirement la clé avec notre générateur generator
  do
  {
    key = generator();
  }
  while (table.find(key) == table.end()); // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
  table.emplace(key, MemberInfo{nom, prenom, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())}); //
}

void Members::disp() const
{


}
