#include "classic_content.hpp"
#include "system.hpp"

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