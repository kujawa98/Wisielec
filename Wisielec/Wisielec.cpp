#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
//#include <algorithm>

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

std::string RandomWord(const std::vector<std::string>& words) {
    srand(time(nullptr));
    return words[rand() % words.size()];
}

int CalculatePoints(int chances, int time) {
    return chances * 100 - time;
}

void Play(const std::vector<std::string>& words, std::vector<Player>& players) {
    std::string word = RandomWord(words);
    std::string discovered(word.length(), '_');
    int chances = 7;
    std::map<char, bool> guessed;
    time_t start = time(nullptr);

    std::cout << "Game started" << std::endl;

    while (chances > 0 && discovered != word) {
        std::cout << "Word " << discovered << std::endl<< "Chances left: " << chances << std::endl<< "Letter: ";
        char letter;
        std::cin >> letter;

        if (guessed[letter]) {
            std::cout << "Already guessed" << std::endl;
            continue;
        }

        guessed[letter] = true;

        if (word.find(letter) != std::string::npos) {
            for (size_t i = 0; i < word.length(); i++) {
                if (word[i] == letter) {
                    discovered[i] = letter;
                }
            }
            std::cout << "You guessed" << std::endl;
        }
        else {
            chances--;
            std::cout << "Wrong guess" << std::endl;
        }
    }

    time_t end = time(nullptr);
    int gameTime = static_cast<int>(end - start);
    int points = (discovered == word) ? CalculatePoints(chances, gameTime) : 0;

    if (points > 0) {
        std::cout << "You guessed \"" << word << "\". You've got " << points << " points" << std::endl;
        std::cout << "Your name is: ";
        std::string name;
        std::cin >> name;
        players.push_back({ name, points});
        std::sort(players.begin(), players.end(), [](const Player& first, const Player& second) {
            return first.points > second.points;
            });
        SaveResults(players);
    }
    else {
        std::cout << "You lost, word is: " << word << std::endl;
    }
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
        Play(words, players);
        std::cout << "Would you like to play again? [y/n]" << std::endl;
        std::cin >> option;
    } while (tolower(option) == 'y');

    std::cout << "Game has ended" << std::endl;
    return 0;
}
