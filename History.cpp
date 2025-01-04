#include "History.h"
#include <filesystem> // W�a�ciwe nag��wki dla C++17
#include <fstream>
#include <iostream>

namespace fs = std::filesystem; // Przestrze� nazw

History::History(const std::string& userId) {
    std::string folder = "users_info";
    if (!fs::exists(folder)) {
        fs::create_directory(folder);
    }

    fileName = folder + "/" + userId + "_info.txt";

    // Tworzenie pliku (je�li nie istnieje)
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to create or open file: " << fileName << std::endl;
    }
}

void History::addEntry(const std::string& entry) {
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        file << entry << std::endl; // Zapisuje wpis do pliku
        file.close();
    }
    else {
        std::cerr << "Error: Unable to write to file: " << fileName << std::endl;
    }
}

std::vector<std::string> History::getHistory() const {
    std::vector<std::string> entries;
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            entries.push_back(line); // Dodaje linie z pliku do wektora
        }
        file.close();
    }
    else {
        std::cerr << "Error: Unable to read file: " << fileName << std::endl;
    }
    return entries;
}
