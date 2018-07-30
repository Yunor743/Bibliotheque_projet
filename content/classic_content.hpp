
#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>

using uint = unsigned int; //on pourra utiliser uint pour représenter un unsigned int

std::time_t addDaysToDate(uint nb_of_days, std::time_t start_date);
std::string interpretMemberState(uint state);
std::string interpretBookState(uint state);