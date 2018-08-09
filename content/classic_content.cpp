#include "classic_content.hpp"

std::time_t addDaysToDate(uint nb_of_days, std::time_t start_date)
{
    std::tm* tm = std::localtime(&start_date);
    tm->tm_mday += nb_of_days;
    return std::mktime(tm);
}
std::string interpretState(MemberState state)
{
  return (static_cast<bool>(state)) ? "NORMAL" : "BANNED";
}
std::string interpretState(BookState state)
{
  return book_states[static_cast<std::underlying_type_t<BookState>>(state)];
}