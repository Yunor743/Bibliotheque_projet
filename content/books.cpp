#include <iostream>
#include "classic_content.hpp"
#include "books.hpp"

void Books::save(std::string path) //On défini la fonction permetant de sauvegarder notre table de Books dans un fichier
{
  std::ofstream save_books_file;    //On instancie le flux
  save_books_file.open (path);      //On ouvre le fichier au chemin spécifique
  for (auto iter = table.begin(); iter != table.end(); ++iter)    //On inscrit les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    save_books_file << iter->first << "/";
    save_books_file << iter->second.title << "/";
    save_books_file << iter->second.price << "/";
    save_books_file << static_cast<std::underlying_type<BookState>::type>(iter->second.state) << "/";
    save_books_file << iter->second.id_borrower << "/";
    save_books_file << iter->second.return_date << "\\";
    save_books_file << std::endl;
  }
  save_books_file.close();    //On ferme le fichier
}
void Books::load(std::string path, char delimiter, char end_line)  //On défini la fonction permettant de charger la table de Books
{
    std::string str1, str2;

    uint key, id_borrower;
    std::string title;
    float price;
    BookState state;
    std::time_t return_date;

    std::ifstream stream(path);

    std::getline(stream, str1);
    while (str1.find(end_line) != std::string::npos)
    {
      str2 = str1.substr(str1.find(delimiter));
      key = stoul(str1.substr(0, str1.size() - str2.size()));
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      title = str1.substr(0, str1.size() - str2.size());
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      price = std::strtof(str1.substr(0, str1.size() - str2.size()).c_str(), 0);
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      state = static_cast<BookState>(std::stoul(str1.substr(0, str1.size() - str2.size())));
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      id_borrower = std::stoul(str1.substr(0, str1.size() - str2.size()));
      str1 = str2.substr(1);

      return_date = std::stoul(str1.substr(0, str1.size() - 1));

      table.emplace(key, BookInfo{title, price, state, id_borrower, return_date});
      std::getline(stream, str1);
    }
}
void Books::insert(std::string title, float price, BookState state, uint id_borrower, std::time_t return_date)
{
  uint key;  //on va générer aléatoirement la clé avec notre générateur generator
  do
  {
    key = generator();
  } while (table.find(key) != table.end() && table.begin() != table.end() );    // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
  table.emplace(key, BookInfo{title, price, state, id_borrower, return_date});  // On insère notre nouvelle ligne
  save(); //On sauvegarde les changements apportés
}
void Books::delOne(uint id) //Définition de la fonction supprimant une ligne de la table Books
{
  table.erase(id);    //On supprime la ligne correspondant à l'id cible
  save();             //On sauvegarde le changement apporté
}
void Books::disp() const  //Définition de la fonction AFFICHER
{
  for (auto iter = table.begin(); iter != table.end(); ++iter)  //On affiche les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    std::cout << "key: " << iter->first << " / ";
    std::cout << "titre: " << iter->second.title << " / ";
    std::cout << "prix: " << iter->second.price << " / ";
    std::cout << "etat: " << interpretBookState(static_cast<std::underlying_type<BookState>::type>(iter->second.state)) << " / ";
    std::cout << "empreinteur: " << iter->second.id_borrower << " / ";
    std::cout << "date_retour: " << std::put_time(std::localtime(&iter->second.return_date), "%Y %m %d");
    std::cout << std::endl;
  }
}
uint Books::BorrowedBooksByMember(uint member_id)
{
  uint compteur = 0;
  std::unordered_map<uint, BookInfo>::iterator iter = table.begin();
  while(iter != table.end())
  {
    if(iter->second.id_borrower == member_id)
    {
      ++compteur;
    }
    ++iter;
  }
  return compteur;
}