#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Character {
public:
    std::string name;
    int health;
    int strength;
    int dex;
    int magic;

    Character(std::string name, int health, int strength, int dex, int magic) :
        name(name), health(health), strength(strength), dex(dex), magic(magic) {}


    void displayCharacter() {
        std::cout << "Name: " << name << "\n"
            << "Health: " << health << "\n"
            << "Strength: " << strength << "\n"
            << "Agility: " << dex << "\n"
            << "Magic: " << magic << std::endl;
    }
};



Character createCharacter() {
    std::string name;
    int classChoice;

        std::cout << "What is thy name?: ";
        std::getline(std::cin, name);


        std::cout << "\nWhat is your origins?: \n"
            << " \n ===================="
            << "\n(High Strength/Health - Low Agility/Magic)\n1. Barbarian"
            << " \n ===================="
            << "\n(High Strength - Medium Health/Agility - Low Magic)\n2. Warrior"
            << " \n ===================="
            << "\n(Low Strength/Health - Medium Agility - High Magic)\n3. Light Mage"
            << " \n ===================="
            << "\n(Medium Strength - Low Health/Magic - High Agility)\n4. Thief"
            << " \n ===================="
            << "\n(Medium Strength/Health/Agility/Magic)\n5. Wanderer \n \n";
        std::cin >> classChoice;




        // health low = 75, med = 100, high = 125
        // stats low = 5, med = 10, high 15 

        switch (classChoice)
        {
        case 1: // Barb (High Strength / High Health / Low Agility / Low Magic)
            std::cout << "You chose a Barbarian \n";
            return Character(name, 125, 15, 5, 5);

        case 2: // Warrior (High Strength / Medium Health / Medium Agility / Low Magic)
            std::cout << "You chose a Warrior \n";
            return Character(name, 100, 15, 10, 5);

        case 3: // Light Mage (Low Strength / Low Health / Medium Agility / High Magic)
            std::cout << "You chose a Light Mage \n";
            return Character(name, 75, 5, 10, 15);

        case 4: // Thief (Medium Strength / Low Health / High Agility / Low Magic)
            std::cout << "You chose a Thief \n";
            return Character(name, 75, 10, 15, 5);

        case 5: // Wanderer (Medium Strength / Medium Health / Medium Agility / Medium Magic)
            std::cout << "You chose a Wanderer \n";
            return Character(name, 100, 10, 10, 10);

        default:
            std::cout << "Invalid, starting as a Wanderer";
            // Wanderer (Medium Strength / Medium Health / Medium Agility / Medium Magic)
            return Character(name, 100, 10, 10, 10);
        }
}


void showMap() {
    std::cout << "You view the map \n";

    std::vector<std::vector<std::string>> map{
        {"Fort", "Plains", "River"},
        {"Forest", "Town", "Plains"},
        {"Mountains", "Plains", "Cave"}
    };

    for (auto i = 0; i < map.size(); i++) {
        for (auto j = 0; j < map[i].size(); j++) {
            // Use std::setw to specify a fixed width for each cell and center the text
            std::cout << " |" << std::setw(10) << std::setfill(' ') << map[i][j];
        }
        std::cout << "|\n";  // Close the last bar of the grid and move to the new line
    }
}




void displayWelcome() {
    std::cout << "Welcome to Text Based Medieval Fantasy RPG!" << std::endl;
}

int main() {
    displayWelcome();

    Character player = createCharacter();

    player.displayCharacter();

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

        if (input == "clear") {
            
            system("cls");
            std::cout << "Chat logs were cleared!\n";
        }

        if (input == "map")
        {
            showMap();
        }

        std::cout << "You typed: " << input << std::endl;
    }

    return 0;
}
