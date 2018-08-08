#include <iostream>
#include "classic_content.hpp"
#include "books.hpp"

void Books::save(std::string path) //On définit la fonction permettant de sauvegarder notre table de Books dans un fichier
{
  std::ofstream save_books_file(path);    //On instancie le flux
  for (auto [key, val] : table)    //On inscrit les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    save_books_file << key << "/";
    save_books_file << val.title << "/";
    save_books_file << val.price << "/";
    save_books_file << static_cast<std::underlying_type<BookState>::type>(val.state) << "/";
    save_books_file << val.id_borrower << "/";
    save_books_file << val.return_date << "\\" << std::endl;
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

  if(stream.is_open())  //we verify if the file can be open
  {
    std::getline(stream, str1);     //we get the stream
    while (str1.find(end_line) != std::string::npos)   //we read the stream
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
  else  //error message if we cant open the file
  {
    std::cout << "Error: " << path << " can't be read" << std::endl;
  }
}
void Books::insert(std::string title, float price, BookState state, uint id_borrower, std::time_t return_date)
{
  uint key;  //on va générer aléatoirement la clé avec notre générateur generator
  do
  {
    key = generator();
  } while (table.find(key) != table.end());    // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
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
  for (auto [key, val] : table)  //On affiche les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    std::cout << "key: " << key << " / ";
    std::cout << "titre: " << val.title << " / ";
    std::cout << "prix: " << val.price << " / ";
    std::cout << "etat: " << interpretState(val.state) << " / ";
    std::cout << "emprunteur: " << val.id_borrower << " / ";
    std::cout << "date_retour: " << std::put_time(std::localtime(&val.return_date), "%Y %m %d");
    std::cout << std::endl;
  }
}
uint Books::BorrowedBooksByMember(uint member_id)
{
  auto counter = 0u;
  for(auto [key, val] : table)
  {
	if(val.id_borrower == member_id)
	  ++counter;
  }
  return counter;
}