#include "books.hpp"
#include "classic_content.hpp"

std::time_t addDaysToDate(uint nb_of_days, std::time_t start_date)
{
    std::tm* tm = std::localtime(&start_date);
    tm->tm_mday += nb_of_days;
    return std::mktime(tm);
}
std::string interpretMemberState(bool state)
{
  if(state == 0)  
  { 
    return "BANNED";
  }
std::string interpretBookState(uint state)
{
  return book_states[state];
}