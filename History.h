#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>

class History {
private:
    std::string fileName; // Œcie¿ka pliku informacji u¿ytkownika
public:
    explicit History(const std::string& userId);

    void addEntry(const std::string& entry); // Dodaj nowy wpis do pliku
    std::vector<std::string> getHistory() const; // Pobierz ca³¹ zawartoœæ pliku
};

#endif
