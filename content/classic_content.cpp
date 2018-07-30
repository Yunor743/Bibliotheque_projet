#include "classic_content.hpp"

std::time_t addDaysToDate(uint nb_of_days, std::time_t start_date)
{
    std::tm tm = *std::localtime(&start_date);
    tm.tm_mday += nb_of_days;
    return std::mktime(&tm);
}
std::string interpretMemberState(bool state)
{
  if(state == 0)  
  { 
    return "BANNED";
  }
  else
  {
    return "NORMAL";
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