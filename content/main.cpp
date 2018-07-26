/*classic_content.hpp*/

//#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>

using uint = unsigned int; //on pourra utiliser uint pour représenter un unsigned int

std::time_t addDaysToDate(uint nb_of_days, std::time_t start_date);
std::string interpretMemberState(uint state);
std::string interpretBookState(uint state);






































/*books.hpp*/

//#pragma once
#include <unordered_map>
//#include <string>
//#include <ctime>
#include <random>
//#include <chrono>
#include <fstream>

//using uint = unsigned int; //on pourra utiliser uint pour représenter un unsigned int

enum class BookState : int //état du livre (empreinté, perdu, en achat, dispo)
{
  AVAILABLE,
  BORROWED,
  LOST,
  ORDERED
};
struct BookInfo // on stock toute les informations relatives à un livre
{
    std::string title;          //titre du livre
    float price;                //prix théorique du livre si il doit y avoir un remboursement
    BookState state;            //état du livre (empreinté, perdu, en achat, dispo)
    uint id_borrower;           //id du membre qui à empreinté le livre
    std::time_t return_date;    //Date où le livre doit être retourner à la bibliothèque
};
struct Books
{
  protected:                                      //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
    std::mt19937 generator; 
  public:                                         //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
    std::unordered_map<uint, BookInfo> table;     // table de tout les livres
    void save(std::string path);
    void load(const std::string file_name, char delimiter, char end_line);
    void insert(std::string title, float price, BookState state, uint id_borrower, std::time_t return_date);                                //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
    void delOne(uint id);
    void disp() const;
};







































/*members.hpp*/

//#pragma once
//#include <unordered_map>
//#include <string>
//#include <ctime>
//#include <random>
//#include <chrono>
//#include <fstream>

//using uint = unsigned int;  //on poura utiliser uint pour représenter un unsigned int

enum class MemberState : int // état du membre (banni, neutre, privilégié)
{
  BANNED,
  NORMAL,
  PRIVILEGED
};
struct MemberInfo //on stocke toute les informations relatives à un membre
{
    std::string nom;       //nom de famille
    std::string prenom;    // prénom
    MemberState state;     // état du membre (banni, neutre)
    std::time_t joined_on; // timestamp à laquelle le membre a été ajouté
};
struct Members //contient une table de tous les membres ainsi que des fonctions pour edit/lire celle-ci
{
  protected:                                      //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
    std::mt19937 generator;
  public:                                         //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
    std::unordered_map<uint, MemberInfo> table;   // table de tout les membres
    void save(std::string path);
    void load(const std::string file_name, char delimiter, char end_line);
    void insert(std::string nom, std::string prenom, MemberState state, time_t joined_on); //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
    void delOne(uint id);
    void disp() const;
};

































/*system.hpp*/

//using uint = unsigned int;  //on poura utiliser uint pour représenter un unsigned int

struct System
{
  void borrow(Books book_inst, uint book_id, uint member_id, uint days_of_borrowing);
  void return_book();
};





































/*classic_content.cpp*/
std::time_t addDaysToDate(uint nb_of_days, std::time_t start_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{
    std::tm tm = *std::localtime(&start_date);
    tm.tm_mday += nb_of_days;
    return std::mktime(&tm);
}
std::string interpretMemberState(uint state)
{
  switch ( state )  
  {
      case 0:  
        return "BANNED";
        break;
      case 1:
        return "NORMAL";
        break;
      case 2:
        return "PRIVILEGED";
        break;
      default:
        return "NORMAL";
        break;
  }
}
std::string interpretBookState(uint state)
{
  switch ( state )  
  {
      case 0:  
        return "AVAILABLE";
        break;
      case 1:
        return "BORROWED";
        break;
      case 2:
        return "LOST";
        break;
      case 3:
        return "ORDERED";
        break;
      default:
        return "AVAILABLE";
        break;
  }
}






































/*books.cpp*/
void Books::save(const std::string path = "save/books.txt") //On défini la fonction permetant de sauvegarder notre table de Books dans un fichier
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
void Books::load(const std::string file_name = "save/books.txt", char delimiter = '/', char end_line = '\\')  //On défini la fonction permettant de charger la table de Books
{
    std::string str1, str2;

    uint key, id_borrower;
    std::string title;
    float price;
    BookState state;
    std::time_t return_date;

    std::ifstream stream(file_name);

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
void Books::insert(std::string title, float price, BookState state = BookState::AVAILABLE, uint id_borrower=0, std::time_t return_date=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
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


































/*members.cpp*/
void Members::save(std::string path = "save/members.txt") //On défini la fonction permetant de sauvegarder notre table de Members dans un fichier
{
  std::ofstream save_members_file;  //On instancie le flux
  save_members_file.open (path);    //On ouvre le fichier au chemin spécifique
  for (auto iter = table.begin(); iter != table.end(); ++iter)  //On inscrit les valeurs de toute les iterations jusqu'à arriver à la dernière
  {
    save_members_file << iter->first << "/";
    save_members_file << iter->second.nom << "/";
    save_members_file << iter->second.prenom << "/";
    save_members_file << static_cast<std::underlying_type<MemberState>::type>(iter->second.state) << "/";
    save_members_file << iter->second.joined_on << "\\";
    save_members_file << std::endl;
  }
  save_members_file.close();   //On ferme le fichier
}
void Members::load(const std::string file_name = "save/members.txt", char delimiter = '/', char end_line = '\\')  //On défini la fonction permettant de charger la table de Members
{
    std::string str1, str2;

    uint key;
    std::string nom, prenom;
    MemberState state;
    std::time_t joined_on;

    std::ifstream stream(file_name);

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
      prenom = std::strtof(str1.substr(0, str1.size() - str2.size()).c_str(), 0);
      str1 = str2.substr(1);

      str2 = str1.substr(str1.find(delimiter));
      state = static_cast<MemberState>(std::stoul(str1.substr(0, str1.size() - str2.size())));
      str1 = str2.substr(1);

      joined_on = std::stoul(str1.substr(0, str1.size() - 1));

      table.emplace(key, MemberInfo{nom, prenom, state, joined_on});
      std::getline(stream, str1);
    }
}
void Members::insert(std::string nom, std::string prenom, MemberState state = MemberState::NORMAL, time_t joined_on = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) //on défini la fonction membre qui permet d'insérer une nouvelle ligne dans la table
{
  uint key; //on va générer aléatoirement la clé avec notre générateur generator
  do
  {
    key = generator();
  } while (table.find(key) != table.end() && table.begin() != table.end() ); // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
  table.emplace(key, MemberInfo{nom, prenom, state, joined_on});             // On insère notre nouvelle ligne
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
    std::cout << "date_arrivee: " << std::put_time(std::localtime(&iter->second.joined_on), "%Y %m %d");
    std::cout << std::endl;
  }
}
































/*system.cpp*/

void System::borrow(Books book_inst, uint book_id, uint member_id, uint days_of_borrowing = 30) //function permettant l'emprunt d'un livre
{
  if(book_inst.table.find(book_id) != book_inst.table.end())            //On s'assure que le livre demandé existe
  {
    BookInfo one_bookinfo = book_inst.table[book_id];                   //on instancie toute les informations sur ce livre dans one_bookinfo
    if(one_bookinfo.state == BookState::AVAILABLE)                      //on s'assure que le livre est disponible
    {
      one_bookinfo.state = BookState::BORROWED;                         //On déclare le livre comme empreinté
      one_bookinfo.id_borrower = member_id;                               //On défini qui est le dernier empreinteur
      one_bookinfo.return_date = addDaysToDate(days_of_borrowing);      //On défini la date de retour
    }
    else
    {
      //Erreur: le livre n'est actuellement pas disponible
    }
  }
  else
  {
    //Erreur: le livre à empreinter n'éxiste pas
  }
}



























/*main.cpp*/
#include <iostream> // For debug purposes


int main(int, char**)
{
  /*On crée nos objets*/
    Members members;
    Books books;
    System lib_system;

    /*On charge les dossier de sauvegarde*/
    books.load();
    members.load();

    /*On insère dans nos table*/
    //members.insert("PERINAZZO", "Christian");
    //books.insert("Le silences des agneaux",100.0);
    
    /*On supprime une ligne de nos table se trouvant à l'id correspondant*/
    //books.delOne(545404204);
    //members.delOne(581869302);
    
    /*on sauvegarde nos tables*/
    //books.save();
    //members.save();

    /*On affiche nos tables*/
    books.disp();
    members.disp();

    system("pause");
    return 0;
}
