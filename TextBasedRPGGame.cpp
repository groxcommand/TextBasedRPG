#include <iostream>
#include <string>
#include <vector>

class Character {
public:
    std::string name;
    int health;
    int strength;

    Character(std::string name, int health, int strength) :
        name(name), health(health), strength(strength) {}
};

void displayWelcome() {
    std::cout << "Welcome to the Adventure RPG!" << std::endl;
    std::cout << "Enter your character's name: ";
}

int main() {
    displayWelcome();

    std::string playerName;
    std::cin >> playerName;
    Character player(playerName, 100, 10);

    std::cout << "Hello, " << player.name << ", your adventure begins!" << std::endl;

    std::string input;
    while (player.health > 0) {
        std::cout << "> ";
        std::cin >> input;

        // Process input
        if (input == "quit") {
            break;
        }
        // Add more commands and interactions here

        std::cout << "You typed: " << input << std::endl;
    }

    return 0;
}
