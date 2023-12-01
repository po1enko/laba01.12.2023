#include <iostream>
#include <fstream>
#include <vector>
#include <string>
void saveToFile(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const std::string& word : data) {
            file << word << std::endl;
        }
        std::cout << "Data successfully saved to file: " << filename << std::endl;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}
void loadFromFile(const std::string& filename, std::vector<std::string>& outData) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string word;
        while (std::getline(file, word)) {
            outData.push_back(word);
        }
        std::cout << "Data successfully loaded from file: " << filename << std::endl;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}

int main() {
    std::vector<std::string> words = {"apple", "banana", "cherry"};
    saveToFile("words.txt", words);
    std::vector<std::string> loadedWords;
    loadFromFile("words.txt", loadedWords);
    std::cout << "Loaded words: ";
    for (const std::string& word : loadedWords) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    return 0;
}
