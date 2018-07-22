<<<<<<< HEAD
/*include temporaire pour debug intelliSense*/
#include "header/members.hpp"


struct MemberInfo //on stock toute les informations relatives à un membre
=======
#include <chrono>
#include "../members.hpp"

void Members::insert(std::string nom, std::string prenom, MemberState state = MemberState::NORMAL) //cette fonction membre permet d'insérer une nouvelle ligne dans la table
>>>>>>> cfe4b39232fd5de3c5f3e288dd5987008fd51598
{
  unsigned int key; //on va générer aléatoirement la clé avec notre générateur gen
  do {
    key = generator();
  }
  while (table.find(key) == table.end()); // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
  table.emplace(key, MemberInfo{nom, prenom, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())}); //
}

void Members::disp() const
{

<<<<<<< HEAD
    }
};

int main()
{
    Members mes_membres;
    MemberInfo myactor = mes_membres.table.find(13)
}
=======
}
>>>>>>> cfe4b39232fd5de3c5f3e288dd5987008fd51598
