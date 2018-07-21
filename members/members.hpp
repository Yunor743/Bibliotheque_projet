#pragma once
#include <unordered_map>
#include <string>
#include <ctime>
#include <random>

using uint = unsigned int;

enum class MemberState : bool {
  BANNED,
  NORMAL
};

struct MemberInfo //on stocke toute les informations relatives à un membre
{
    std::string nom;    //nom de famille
    std::string prenom; // prénom
    MemberState state;  // état (banni, neutre)
    std::time_t joined_on; // timestamp à laquelle le membre a été ajouté
};

struct Members //contient une table de tous les membres ainsi que des fonctions pour edit/lire celle-ci
{
  protected:          //On crée notre générateur, il sera privé, donc inapellable en dehors de cette classe
    std::mt19937 generator;
  public:           //On retourne au public, les éléments sont à nouveau appelables
    std::unordered_map<uint, MemberInfo> table;   // table de tout les membres
    void insert(std::string nom, std::string prenom, MemberState state = MemberState::NORMAL); //cette fonction membre permet d'insérer une nouvelle entrée dans la table
    void disp() const;
};
