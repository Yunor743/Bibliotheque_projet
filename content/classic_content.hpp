
#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>

using uint = unsigned int;  //on pourra utiliser uint pour représenter un unsigned int

std::time_t addDaysToDate(uint nb_of_days = 30, std::time_t start_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) );  //Cette fonction permet d'ajouter des jours à une date
std::string interpretMemberState(bool state);   //Ceci permet de traduire la valeur représentant l'état du membre en string
std::string interpretBookState(uint state);     //Ceci permet de traduire la valeur représentant l'état du livre en string