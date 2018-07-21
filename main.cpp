#include "headers/books.hpp"
#include "headers/members.hpp"
#include <iostream> // For debug purposes


struct MemberInfo //on stock toute les informations relatives à un membre
{
    std::string nom;    //nom de famille
    std::string prenom; // prénom
    bool state;         // état (banni, neutre)
};
struct BookInfo // on stock toute les informations relatives à un livre
{
    std::string title;          //titre du livre
    int state;                  //état du livre (empreinté, perdu, en achat, dispo)
    int id_member;              //id du membre qui à empreinté le livre
    float price;                //prix théorique du livre si il doit y avoir un remboursement
    std::time_t return_date;    //Date où le livre doit être returner à la bibliothèque
};
struct Members //contien une table de tous les membres ainsi que des fonctions pour edit/lire celle-ci
{
    private:          //On créé notre générateur, il sera privé, donc inapellable en dehors de cette classe
    std::mt19937 gen; //On instencie notre générateur de type mt19937 sous le nom gen
    public:           //On retourne au public, les éléments sont à nouveau appelables
    std::unordered_map<unsigned int, MemberInfo> table;   // table de tout les membres
    void insert(std::string nom, std::string prenom, bool state = 0) //cette fonction membre permet d'insérer une nouvelle ligne dans la table
    {
        unsigned int key; //on va générer aléatoirement la clé avec notre générateur gen
        do 
        {
            key = gen();
        } 
        while (table.end == table.find(key)); // Si table.find(key) est égale à table.end (donc la fin de table) alors c'est que cette clé n'éxiste pas encore et on peut passer à la suite, sinon on recommence
        table.emplace(key, MemberInfo{nom, prenom, state}); //
    }
    void disp()
    {

    }
};
struct Books //contien une table de tous les livres ainsi que des fonctions pour edit/lire celle-ci
{
    std::unordered_map<int, BookInfo> table;    // table de tout les livres
    void insert()
    {

    }
    void disp()
    {

    }
};




int main(int, char**)
{
    Members mesmembres;
    return 0;
}
