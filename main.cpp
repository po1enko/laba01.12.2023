#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
enum Score
{
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};
struct Student
{
    std::string Name;
    int Year;
    std::map<std::string, Score> RecordBook;
};
using Groups = std::map<std::string, std::vector<Student>>;
void saveToFile(const std::string& filename, const Groups& groups) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& group : groups) {
            file << group.first << std::endl;
            for (const auto& student : group.second) {
                file << student.Name << "," << student.Year << ",";
                for (const auto& record : student.RecordBook) {
                    file << record.first << ":" << record.second << ",";
                }
                file << std::endl;
            }
            file << std::endl;
        }
        std::cout << "Data successfully saved to file: " << filename << std::endl;
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}
void loadFromFile(const std::string& filename, Groups& outGroups) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::string groupName;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                if (groupName.empty()) {
                    groupName = line;
                } else {
                    size_t commaPos1 = line.find(",");
                    size_t commaPos2 = line.find(",", commaPos1 + 1);
                    std::string name = line.substr(0, commaPos1);
                    int year = std::stoi(line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1));
                    size_t colonPos = line.find(":", commaPos2);
                    std::string subject = line.substr(commaPos2 + 1, colonPos - commaPos2 - 1);
                    Score score = static_cast<Score>(std::stoi(line.substr(colonPos + 1)));
                    outGroups[groupName].push_back({name, year, {}});
                    outGroups[groupName].back().RecordBook[subject] = score;
                }
            } else {
                groupName.clear();
            }
        }
        std::cout << "Data successfully loaded from file: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}



int main() {
    Groups groups;
    groups["Group1"].push_back({"John", 2000, {{"Math", Score::Excellent}}});
    groups["Group1"].push_back({"Jane", 2001, {{"Math", Score::Good}}});
    groups["Group2"].push_back({"Alice", 1999, {{"Math", Score::Excellent}}});
    saveToFile("groups.txt", groups);
    Groups loadedGroups;
    loadFromFile("groups.txt", loadedGroups);
    std::cout << "Loaded groups:" << std::endl;
    for (const auto& group : loadedGroups) {
        std::cout << "Group: " << group.first << std::endl;
        for (const auto& student : group.second) {
            std::cout << "Name: " << student.Name << ", Year: " << student.Year << std::endl;
            for (const auto& record : student.RecordBook) {
                std::cout << "Subject: " << record.first << ", Score: " << record.second << std::endl;
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
