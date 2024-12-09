#include <iostream>
#include <vector>
#include <fstream>

struct Player {
    std::string name;
    int points;
};

void LoadWords(std::vector<std::string>& words) {
    std::ifstream file("words.txt");
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
}

void SaveResults(const std::vector<Player>& players) {
    std::ofstream file("highscores.txt");
    for (const auto& player : players) {
        file << player.name << " " << player.points << std::endl;
    }
    file.close();
}

void LoadResults(std::vector<Player>& players) {
    std::ifstream file("highscores.txt");
    Player player;
    while (file >> player.name >> player.points) {
        players.push_back(player);
    }
    file.close();
}

void ShowResults(const std::vector<Player>& players) {
    std::cout << "Best results" << std::endl;
    for (const auto& player : players) {
        std::cout << player.name << " " << player.points << " points" << std::endl;
    }
    std::cout << std::endl;
}


int main()
{
    std::vector<std::string> words;
    std::vector<Player> players;

    LoadWords(words);
    if (words.empty()) {
        std::cerr << "No words in file" << std::endl;
        return 1;
    }

    LoadResults(players);
    ShowResults(players);

    char option;
    do {
        std::cin >> option;
    } while (tolower(option) == '/');

    std::cout << "Game has ended" << std::endl;
    return 0;
}
