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
    void save(std::string path);    //cette fonction sauvegarde la table dans un fichier externe
    void load(const std::string path, char delimiter, char end_line); //cette fonction charge la table depuis un fichier externe
    void insert(std::string title, float price, BookState state, uint id_borrower, std::time_t return_date);   //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
    void delOne(uint id); //fonction permettant de supprimer une ligne précise en fonction de l'id de la key
    void disp() const;    //fonction permettant l'affichage de la table
    uint BorrowedBooksByMember(uint member_id);
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

enum class MemberState : bool // état du membre (banni, neutre, privilégié)
{
  BANNED,
  NORMAL
};
struct MemberInfo //on stocke toute les informations relatives à un membre
{
    std::string nom;       //nom de famille
    std::string prenom;    // prénom
    MemberState state;     // état du membre (banni, neutre)
    uint book_returned;
    std::time_t joined_on; // timestamp à laquelle le membre a été ajouté
};
struct Members //contient une table de tous les membres ainsi que des fonctions pour edit/lire celle-ci
{
  protected:                                      //On crée notre générateur, il sera protégé, donc appelable seulement dans cette classe et les classe enfant
    std::mt19937 generator;
  public:                                         //On retourne au public, les éléments seront à nouveau appelables en dehors de l'instance de la classe
    std::unordered_map<uint, MemberInfo> table;   // table de tout les membres
    void save(std::string path);  //cette fonction sauvegarde la table dans un fichier externe
    void load(const std::string path, char delimiter, char end_line);  //cette fonction charge la table depuis un fichier externe
    void insert(std::string nom, std::string prenom, MemberState state, uint book_returned, time_t joined_on); //on déclare la fonction membre qui permet d'insérer une nouvelle entrée dans la table
    void delOne(uint id); //fonction permettant de supprimer une ligne précise en fonction de l'id de la key
    void disp() const;    //fonction permettant l'affichage de la table
    uint ReturnedBooksByMember(uint member_id); //définition de la fonction me permetant de savoir combiens de livres le membre à déjà rapporté sans y avoir d'incident
};

































/*system.hpp*/

//#pragma once
//#include <unordered_map>
#include <cmath>

//using uint = unsigned int;  //on poura utiliser uint pour représenter un unsigned int

struct System
{
  int ifReturnLate(Books &book_inst, uint book_id); //Cette fonction permettra de répondre à la condition: est ce que le livre à été rendu en retard ?
  void borrow(Books &book_inst, Members &member_inst, uint book_id, uint member_id, uint days_of_borrowing);  //Déclaration de la fonction permettant l'empreint d'un livre
  void return_book(Books &book_inst, Members &member_inst, uint book_id); //Déclaration de la fonction permettant de déclaré un livre comme rapporté
  void pay_taxe(Books &book_inst, Members &member_inst, uint book_id, float taxe_coef);  //Cette fonction permet de définir la taxe a payer en cas d'oublie de la part du membre
  void returned(Books &book_inst, Members &member_inst, uint book_id); //Dans le cas ou le membre rapporte un livre ou viens payer sa taxe
  void check(Books &book_inst, Members &member_inst); //Cette fonction va s'itéré une fois par jour pour actualiser l'état de l'emprein de chaque membres
};




























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
void Books::load(const std::string path = "save/books.txt", char delimiter = '/', char end_line = '\\')  //On défini la fonction permettant de charger la table de Books
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
    save_members_file << iter->second.book_returned << "/";
    save_members_file << iter->second.joined_on << "\\";
    save_members_file << std::endl;
  }
  save_members_file.close();   //On ferme le fichier
}
void Members::load(const std::string path = "save/members.txt", char delimiter = '/', char end_line = '\\')  //On défini la fonction permettant de charger la table de Members
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
void Members::insert(std::string nom, std::string prenom, MemberState state = MemberState::NORMAL, uint book_returned = 0, time_t joined_on = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) //on défini la fonction membre qui permet d'insérer une nouvelle ligne dans la table
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


































/*system.cpp*/

int System::ifReturnLate(Books &book_inst, uint book_id)
{
  BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;            //On obtient le BookInfo
  return static_cast<int>(std::round((difftime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), one_bookinfo.return_date) / 3600)/24));
}
void System::borrow(Books &book_inst, Members &member_inst, uint book_id, uint member_id, uint days_of_borrowing = 30) //function permettant l'emprunt d'un livre
{
  if(book_inst.table.find(book_id) != book_inst.table.end())            //On s'assure que le livre demandé existe
  {
    BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;            //On obtient le BookInfo
    if(one_bookinfo.state == BookState::AVAILABLE)                     //On s'arrure que le livre demandé est disponible
    {
      if(member_inst.ReturnedBooksByMember(member_id) >= 20)    //Si le membre à déja empreinter plus de 20 livres sans accroc
      {     //alors le membre peut empreinter jusqu'à 7 livre en même temps
        if(book_inst.BorrowedBooksByMember(member_id) < 7)
        {
          one_bookinfo.state = BookState::BORROWED;                     //On déclare le livre comme empreinté
          one_bookinfo.id_borrower = member_id;                         //On garde en mémoire le membre ayant empreinté le livre
          one_bookinfo.return_date = addDaysToDate(days_of_borrowing);  //On définie la date limite où le membre devra rapporter le livre
        }
        else
        {
          //Erreur: le maximum de livres pouvant êtres empreintés par cet utilisateur à été atteind
        }
      }
      else  //Si le membre n'à pas empreinter plus de 20 livres sans accroc
      { //alors le membre ne peut empreinter que 2 livres
        if(book_inst.BorrowedBooksByMember(member_id) < 2)
        {
          one_bookinfo.state = BookState::BORROWED; //On déclare le livre comme empreinté
          one_bookinfo.id_borrower = member_id; //On garde en mémoire le membre ayant empreinté le livre
          one_bookinfo.return_date = addDaysToDate(days_of_borrowing);  //On définie la date limite où le membre devra rapporter le livre
        }
        else
        {
        //Erreur: le maximum de livres pouvant êtres empreintés par cet utilisateur à été atteind
        }
      }
      book_inst.save();//On sauvegarde les potentiels changements apporté
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
void System::return_book(Books &book_inst, Members &member_inst, uint book_id)  //Définition de la fonction permettant de déclaré un livre comme rapporté
{
    if(book_inst.table.find(book_id)->second.state == BookState::BORROWED)  //On vérifie que le livre à été empreinté
    {
      BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;            //On obtient le BookInfo
      MemberInfo &one_memberinfo = (&(*member_inst.table.find(one_bookinfo.id_borrower)))->second;
      ++one_memberinfo.book_returned;
      one_bookinfo.id_borrower = 0;
      one_bookinfo.return_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      one_bookinfo.state = BookState::AVAILABLE;
    }
    else
    {
      //Erreur: Ce livre est soit perdu, disponible ou en commande mais il n'a pas été empreinté
    }
}
void System::pay_taxe(Books &book_inst, Members &member_inst, uint book_id, float taxe_coef = 0.5)
{
  BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;
  MemberInfo &one_memberinfo = (&(*member_inst.table.find(one_bookinfo.id_borrower)))->second;
  int days = ifReturnLate(book_inst, book_id);
  std::cout << "taxe + livre: " << one_bookinfo.price + days * taxe_coef << std::endl;
  std::cout << "taxe seulement: " << days * taxe_coef << std::endl;
  std::cout << "Le membre est à présent considéré comme débité du montant dette" << std::endl;
  std::cout << "le livre est déclaré comme perdu" << std::endl;
  one_bookinfo.state = BookState::LOST;
  one_memberinfo.book_returned = 0;
}
void System::returned(Books &book_inst, Members &member_inst, uint book_id)
{
  if(book_inst.table.find(book_id) != book_inst.table.end()) //on vérifie que le livre existe
  {
      if(ifReturnLate(book_inst, book_id) > 0) //Si le membre rapporte le livre en retard ou perdu
      {
        pay_taxe(book_inst, member_inst, book_id);
      }
      else    //Si le membre rapporte le livre dans les temps
      {
        return_book(book_inst, member_inst, book_id);
      }
  }
  else
  {
    //Erreur: le livre n'est pas dans le registre
  }
}
void System::check(Books &book_inst, Members &member_inst)
{
  auto &iter_booktable = book_inst.table.begin();
  while(iter_booktable != book_inst.table.end() )
  {
    if(ifReturnLate(book_inst, iter_booktable->first) > 60) //Si ça fait 60 jour que le livre aurait du etre ramené
    {
      std::unordered_map<uint, MemberInfo>::iterator &iter_membertable = member_inst.table.find(iter_booktable->second.id_borrower);
      iter_booktable->second.state = BookState::LOST;
      iter_membertable->second.state = MemberState::BANNED;
    }
    ++iter_booktable;
  }
}

































/*main.cpp*/
//#include <iostream> // For debug purposes


int main(int, char**)
{
    /*On créé nos objets*/
    Members members;
    Books books;
    System lib_system;

    /*On charge les fichiers de sauvegarde*/
    books.load();
    members.load();

    /*On insère dans nos tables*/
    //members.insert("PERINAZZO", "Christine");
    //books.insert("L'homme bicentnaire",20.0);

    /*On supprime une ligne de nos table se trouvant à l'id cible*/
    //books.delOne(581869302);
    //members.delOne(581869302);

    /*On sauvegarde nos tables*/
    //books.save();
    //members.save();

    /*Opération system*/
    lib_system.borrow(books, members, 545404204, 3499211612, 90);
    //lib_system.return_book(books, members, 545404204);
    //lib_system.ifReturnLate(books, members, 3586334585);
    lib_system.returned(books, members, 545404204);
    //lib_system.check(books, members);

    /*On affiche nos tables*/
    books.disp();
    members.disp();
    system("pause");
    return 0;
}
