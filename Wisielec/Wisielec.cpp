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

int main()
{
    std::cout << "Hello World!\n";
}
