#include <iostream>
#include "classic_content.hpp"
#include "members.hpp"


void Members::save(std::string path) //On défini la fonction permetant de sauvegarder notre table de Members dans un fichier
{
  std::ofstream save_members_file;  //On instancie le flux
  save_members_file.open (path);    //On ouvre le fichier au chemin spécifique
  for (auto iter = table.begin(); iter != table.end(); ++iter)  //On inscrit les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    save_members_file << iter->first << "/";
    save_members_file << iter->second.nom << "/";
    save_members_file << iter->second.prenom << "/";
    save_members_file << static_cast<std::underlying_type<MemberState>::type>(iter->second.state) << "/";
    save_members_file << iter->second.book_returned << "/";
    save_members_file << iter->second.joined_on << "\\";
    save_members_file << std::endl;
  }
  save_members_file.close();   //On ferme le fichier
}
void Members::load(const std::string path, char delimiter, char end_line)  //On défini la fonction permettant de charger la table de Members
{
    std::string str1, str2;

    uint key, book_returned;
    std::string nom, prenom;
    MemberState state;
    std::time_t joined_on;

    std::ifstream stream(path);

    std::getline(stream, str1);
    while (str1.find(end_line) != std::string::npos)
    {
      str2 = str1.substr(str1.find(delimiter));
      key = stoul(str1.substr(0, str1.size() - str2.size()));
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      nom = str1.substr(0, str1.size() - str2.size());
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      prenom = str1.substr(0, str1.size() - str2.size());
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      state = static_cast<MemberState>(std::stoul(str1.substr(0, str1.size() - str2.size())));
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      book_returned = stoul(str1.substr(0, str1.size() - str2.size()));
      str1 = str2.substr(1);

      joined_on = std::stoul(str1.substr(0, str1.size() - 1));

      table.emplace(key, MemberInfo{nom, prenom, state, book_returned, joined_on});
      std::getline(stream, str1);
    }
}
void Members::insert(std::string nom, std::string prenom, MemberState state, uint book_returned, time_t joined_on) //on défini la fonction membre qui permet d'insérer une nouvelle ligne dans la table
{
  uint key; //on va générer aléatoirement la clé avec notre générateur generator
  do
  {
    key = generator();
  } while (table.find(key) != table.end() && table.begin() != table.end() ); // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
  table.emplace(key, MemberInfo{nom, prenom, state, book_returned, joined_on});             // On insère notre nouvelle ligne
  save(); //On sauvegarde les changements apportés
}
void Members::delOne(uint id) //Définition de la fonction supprimant une ligne de la table Members
{
  table.erase(id);    //On supprime la ligne correspondant à l'id cible
  save();             //On sauvegarde le changement apporté
}
void Members::disp() const //Définition de la fonction AFFICHER
{
  for (auto iter = table.begin(); iter != table.end(); ++iter)  //On affiche les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    std::cout << "key: " << iter->first << " / ";
    std::cout << "nom: " << iter->second.nom << " / ";
    std::cout << "prenom: " << iter->second.prenom << " / ";
    std::cout << "etat: " << interpretMemberState(static_cast<std::underlying_type<MemberState>::type>(iter->second.state)) << " / ";
    std::cout << "livres_empreintes: " << iter->second.book_returned << " / ";
    std::cout << "date_arrivee: " << std::put_time(std::localtime(&iter->second.joined_on), "%Y %m %d");
    std::cout << std::endl;
  }
}
uint Members::ReturnedBooksByMember(uint member_id) //déclaration de la fonction me permetant de savoir combiens de livres le membre à déjà rapporté sans y avoir d'incident
{
  if(table.find(member_id) != table.end()) //on vérifie que le membre existe
  {
    std::unordered_map<uint, MemberInfo>::iterator member_iter = table.find(member_id);
    return member_iter->second.book_returned;
  }
  else
  {
    //Erreur: le membre n'existe pas
    return 0;
  }
}