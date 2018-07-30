/*classic_content.hpp*/

//#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>

using uint = unsigned int; //on pourra utiliser uint pour représenter un unsigned int

std::time_t addDaysToDate(uint nb_of_days, std::time_t start_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
std::string interpretMemberState(uint state);
std::string interpretBookState(uint state);
