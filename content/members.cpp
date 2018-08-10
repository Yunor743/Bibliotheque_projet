#include <iostream>
#include <stdexcept>
#include "classic_content.hpp"
#include "members.hpp"

void Members::save() //On défini la fonction permetant de sauvegarder notre table de Members dans un fichier
{
  if(save_path != "")
  {
    std::ofstream save_members_file(save_path);  //we make an instance of the stream
    for (auto [key, val] : table)  //On inscrit les valeurs de toute les iterations jusqu'à arriver à la dernière
    {
      save_members_file << key << "/";
      save_members_file << val.nom << "/";
      save_members_file << val.prenom << "/";
      save_members_file << static_cast<std::underlying_type<MemberState>::type>(val.state) << "/";
      save_members_file << val.book_returned << "/";
      save_members_file << val.joined_on << "\\";
      save_members_file << std::endl;
    }
    save_members_file.close();   //On ferme le fichier
  }
  else
  {
    std::cout << "ERROR: \n" << "members_savefile must be found to save it" << std::endl;
  }
}
void Members::load(char delimiter, char end_line)  //On définit la fonction permettant de charger la table de Members
{
  if(save_path != "")
  {
    std::string str1, str2;

    uint key, book_returned;
    std::string nom, prenom;
    MemberState state;
    std::time_t joined_on;

    std::ifstream stream(save_path);
    std::getline(stream, str1);     //we get the stream
    while (str1.find(end_line) != std::string::npos)   //we read the stream
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
  else
  {
    std::cout << "ERROR: \n" << "members_savefile must be found to load it" << std::endl;
  }
}
void Members::insert(std::string nom, std::string prenom, MemberState state, uint book_returned, time_t joined_on) //on définit la fonction membre qui permet d'insérer une nouvelle ligne dans la table
{
  uint key; //on va générer aléatoirement la clé avec notre générateur generator
  do
  {
    key = generator();
  } while (table.find(key) != table.end()); // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
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
  std::cout << " \n \n \n \n \n " << std::endl;
  for (auto [key, val] : table)  //On affiche les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    std::cout << "key: " << key << " / ";
    std::cout << "nom: " << val.nom << " / ";
    std::cout << "prenom: " << val.prenom << " / ";
    std::cout << "etat: " << interpretState(val.state) << " / ";
    std::cout << "livres_empreintes: " << val.book_returned << " / ";
    std::cout << "date_arrivee: " << std::put_time(std::localtime(&val.joined_on), "%Y %m %d");
    std::cout << std::endl;
  }
}
uint Members::ReturnedBooksByMember(uint member_id) //déclaration de la fonction me permetant de savoir combiens de livres le membre à déjà rapporté sans y avoir d'incident
{
  if(auto it = table.find(member_id); it != table.end()) //on vérifie que le membre existe
  {
    return it->second.book_returned;
  } else
	throw std::runtime_error("Members::ReturnedBooksByMember: Invalid member id");
}