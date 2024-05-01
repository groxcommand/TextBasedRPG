#include <iostream>
#include <string>

class Character {
public:
    std::string name;
    int health;
    int strength;

    Character(std::string n, int h, int s) : name(n), health(h), strength(s) {}
};

void displayWelcome() {
    std::cout << "Welcome to the Adventure RPG!" << std::endl;
    std::cout << "Please enter your character's name: ";
}

int main() {
    displayWelcome();

    std::string playerName;
    std::cin >> playerName;

    Character player(playerName, 100, 10);
    std::cout << "Hello, " << player.name << "! Let the adventure begin." << std::endl;

    // Game loop here
    while (player.health > 0) {
        // Implement game interactions such as combat, finding items, etc.
    }

    return 0;
}
