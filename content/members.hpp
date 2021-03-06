
#pragma once
#include <unordered_map>
#include <string>
#include <ctime>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using uint = unsigned int;  //on poura utiliser uint pour représenter un unsigned int

enum class MemberState : bool // état du membre (banni, neutre)
{
  BANNED,
  NORMAL
};
struct MemberInfo //on stocke toute les informations relatives à un membre
{
  std::string nom;       //Nom de famille
  std::string prenom;    //Prénom
  MemberState state;     //Etat du membre (banni, neutre)
  uint book_returned;    //Nombre de livre que le membre à ramené à la suite sans avoir de retard ou pire
  std::time_t joined_on; //Timestamp à laquelle le membre a été ajouté
};
struct Members //contient une table de tous les membres ainsi que des fonctions pour edit/lire celle-ci
{
protected: //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
  std::mt19937 generator;
public:   //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
  std::unordered_map<uint, MemberInfo> table;   //table de tout les membres
  std::string save_path = "";   //cette variable contient le chemin d'accès au fichier de sauvegarde de la table (il faut set cette variable grace a fileSearch())
  void save();    //cette fonction sauvegarde la table dans un fichier externe
  void load(char delimiter = '/', char end_line = '\\');    //cette fonction charge la table depuis un fichier externe
  void insert(std::string nom, std::string prenom, MemberState state = MemberState::NORMAL, uint book_returned = 0, time_t joined_on = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));   //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
  void delOne(uint id);   //fonction permettant de supprimer une ligne précise en fonction de l'id de la key
  void disp() const;    //fonction permettant l'affichage de la table
  uint ReturnedBooksByMember(uint member_id);   //définition de la fonction me permetant de savoir combiens de livres le membre à déjà rapporté sans y avoir d'incident
};