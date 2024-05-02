#include <iostream>
#include <fstream>
#include <unordered_map>

struct Player {
    std::string name;
    int score;
};

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the input file." << std::endl;
        return 1;
    }

    int numPlayers;
    inputFile >> numPlayers;
    inputFile.ignore();

    std::unordered_map<std::string, Player> playerMap;


    for (int i = 0; i < numPlayers; ++i) {
        std::string playerName;
        std::getline(inputFile, playerName);
        playerMap[playerName] = {playerName, 0};
    }

    int numRounds;
    inputFile >> numRounds;

    
    for (int i = 0; i < numRounds; ++i) {
        std::string winner, loser;
        int score;
        inputFile >> winner >> loser >> score;
        playerMap[winner].score += score;
        playerMap[loser].score -= score;
    }

    inputFile.close();

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the output file." << std::endl;
        return 1;
    }

    for (const auto& pair : playerMap) {
        outputFile << pair.second.name << " " << pair.second.score << std::endl;
    }

    outputFile.close();

    return 0;
}