#include <iostream>
#include <fstream>
#include <vector>
#include <string>
struct book
{
    std::string Author;
    std::string Title;
    int Year;
};

void saveToFile(const std::string& filename, const std::vector<book>& data) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const book& book : data) {
            file << book.Author << ", " << book.Title << ", " << book.Year << std::endl;
        }
        std::cout << "Book successfully saved to file: " << filename << std::endl;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}
void loadFromFile(const std::string& filename, std::vector<book>& outData) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t zapyataya1 = line.find(", ");
            size_t zapyataya2 = line.find(", ", zapyataya1 + 1);
            std::string author = line.substr(0, zapyataya1);
            std::string title = line.substr(zapyataya1 + 1, zapyataya2 - zapyataya1 - 1);
            int year = std::stoi(line.substr(zapyataya2 + 1));
            outData.push_back({author, title, year});
        }
        std::cout << "Book successfully loaded from file: " << filename << std::endl;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}

int main() {
    std::vector<book> books = {{"Egor", "Kakogo zhit s bolshim rostom?", 2013}, {"Mikhail", "Kakogo zhit s bochonkom?", 2023}, {"Konstantin", "Kakogo zhit so Skodoi?", 2020}};
    saveToFile("books.txt", books);
    std::vector<book> loadedBooks;
    loadFromFile("books.txt", loadedBooks);
    std::cout << "Loaded books:" << std::endl;
    for (const book& book : loadedBooks) {
        std::cout << "Author: " << book.Author << ", Title: " << book.Title << ", Year: " << book.Year << std::endl;
    }
    return 0;
}
