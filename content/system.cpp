#include "system.hpp"

void System::saveSearch(std::string save_filename, std::string &save_path)
{
  std::string possibilities[2] = { //cette variable regroupe tout les potentiels chemins où trouver le fichier filename
    "save/",
    ""
    };
  std::string whole_path; //this var is use after to bind the path + filename
  for (int i = 0; std::find(std::begin(possibilities), std::end(possibilities), possibilities[i]) != std::end(possibilities); i++)
  {
    whole_path = possibilities[i].append(save_filename);  //we bind the path with the file
    std::ifstream stream(whole_path);   //we make an instance of the stream
    if(stream.is_open())        //we verify if the file can be open
    {
      save_path = whole_path;
      std::cout << save_filename << " found at: \n" << save_path << std::endl;
    }
  }
  if(save_path == "")
  {
    std::cout << "ERROR: " << save_filename << " can't be found" << std::endl; //we don't change the save_path value if we didn't find its path 
  }
}
void System::borrow(Books &book_inst, Members &member_inst, uint book_id, uint member_id, uint days_of_borrowing) //function permettant l'emprunt d'un livre
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
          std::cout << "ERROR: \n" << "this member has already reach the maximum of 7 books" << std::endl;
        }
      }
      else  //Si le membre n'à pas empreinter plus de 20 livres sans accroc
      { //alors le membre ne peut empreinter que 2 livres
        if(book_inst.BorrowedBooksByMember(member_id) < 2)
        {
          one_bookinfo.state = BookState::BORROWED; //On déclare le livre comme empreinté
          one_bookinfo.id_borrower = member_id; //On garde en mémoire le membre ayant empreinté le livre
          one_bookinfo.return_date = addDaysToDate(days_of_borrowing);  //On définie la date limite où le membre devra rapporter le livre
          std::cout << "NOTE: \n" << "a member has borrow a book" << std::endl;
        }
        else
        {
        std::cout << "ERROR: \n" << "this member has already reach the maximum of 2 books" << std::endl;
        }
      }
      book_inst.save();//On sauvegarde les potentiels changements apporté
    }
    else
    {
      std::cout << "ERROR: \n" << "The target book isn't actually available" << std::endl;
    }
  }
  else
  {
    std::cout << "ERROR: \n" << "The target book isn't exist" << std::endl;
  }
}
int System::ifReturnLate(Books &book_inst, uint book_id)
{
  BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;            //On obtient le BookInfo
  return static_cast<int>(std::round((difftime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), one_bookinfo.return_date) / 3600)/24));
}
void System::return_book(Books &book_inst, Members &member_inst, uint book_id)  //Définition de la fonction permettant de déclaré un livre comme rapporté
{
    BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;            //On obtient le BookInfo
    MemberInfo &one_memberinfo = (&(*member_inst.table.find(one_bookinfo.id_borrower)))->second;
    ++one_memberinfo.book_returned;
    one_bookinfo.id_borrower = 0;
    one_bookinfo.return_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    one_bookinfo.state = BookState::AVAILABLE;
    std::cout << "NOTE: \n" << "A book has been returned" << std::endl;
}
void System::pay_tax(Books &book_inst, Members &member_inst, uint book_id, bool is_booklost, float tax_coef)
{
  BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;
  MemberInfo &one_memberinfo = (&(*member_inst.table.find(one_bookinfo.id_borrower)))->second;
  int days = ifReturnLate(book_inst, book_id);
  if(!is_booklost)
  {
    std::cout << "tax only: " << days * tax_coef << std::endl;
    std::cout << "NOTE: \n" << "The book is declared available" << std::endl;
    one_bookinfo.state = BookState::AVAILABLE;
  }
  else
  {
    std::cout << "tax & book price: " << one_bookinfo.price + days * tax_coef << std::endl;
    std::cout << "NOTE: \n" << "The book is declared lost" << std::endl;
    one_bookinfo.state = BookState::LOST;
  }
  std::cout << "NOTE: \n" << " We consider the member have paid his debt" << std::endl;
  one_memberinfo.book_returned = 0;

}
void System::returned(Books &book_inst, Members &member_inst, uint book_id, bool is_booklost)
{
  if(book_inst.table.find(book_id) != book_inst.table.end())    //on vérifie que le livre existe
  {
    if(book_inst.table.find(book_id)->second.state == BookState::BORROWED)  //On vérifie que le livre à été empreinté
    {
      if(ifReturnLate(book_inst, book_id) > 0 || is_booklost)   //Si le membre rapporte le livre en retard ou perdu
      {
        pay_tax(book_inst, member_inst, book_id, is_booklost);
      }
      else    //Si le membre rapporte le livre dans les temps
      {
        return_book(book_inst, member_inst, book_id);
      }
    }
    else
    {
      std::cout << "ERROR: \n" << "this book is lost, available or ordered but it is not borrowed" << std::endl;
    }
  }
  else
  {
    std::cout << "ERROR: \n" << "The book isn't in the register" << std::endl;
  }
}
void System::order(Books &book_inst, uint book_id, uint days_before_arrival)
{
  BookInfo &one_bookinfo = (&(*book_inst.table.find(book_id)))->second;
  if(one_bookinfo.state == BookState::LOST)
  {
    one_bookinfo.state = BookState::ORDERED;
    one_bookinfo.return_date = addDaysToDate(days_before_arrival);
    std::cout << "NOTE: \n" << "The book have been ordered" << std::endl;
  }
  else
  {
    std::cout << "ERROR: \n" << "The target book is not lost" << std::endl;
  }
}
void System::check(Books &book_inst, Members &member_inst)
{
  /*
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
  */
}