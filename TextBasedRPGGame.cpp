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

    int x; // Player's x coordinates
    int y; // Player's y coordinates

    Character(std::string name, int health, int strength, int dex, int magic, int startX, int startY) :
        name(name), health(health), strength(strength), dex(dex), magic(magic), x(startX), y(startY) {}


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
            return Character(name, 125, 15, 5, 5, 0, 0);

        case 2: // Warrior (High Strength / Medium Health / Medium Agility / Low Magic)
            std::cout << "You chose a Warrior \n";
            return Character(name, 100, 15, 10, 5, 0, 0);

        case 3: // Light Mage (Low Strength / Low Health / Medium Agility / High Magic)
            std::cout << "You chose a Light Mage \n";
            return Character(name, 75, 5, 10, 15, 0, 0);

        case 4: // Thief (Medium Strength / Low Health / High Agility / Low Magic)
            std::cout << "You chose a Thief \n";
            return Character(name, 75, 10, 15, 5, 0, 0);

        case 5: // Wanderer (Medium Strength / Medium Health / Medium Agility / Medium Magic)
            std::cout << "You chose a Wanderer \n";
            return Character(name, 100, 10, 10, 10, 0, 0);

        default:
            std::cout << "Invalid, starting as a Wanderer";
            // Wanderer (Medium Strength / Medium Health / Medium Agility / Medium Magic)
            return Character(name, 100, 10, 10, 10, 0, 0);
        }
}

class GameState {
public:

    Character player;
    std::vector<std::vector<std::string>> map;

    GameState() : player(createCharacter()) {  // Initialize the player using the createCharacter function
        initializeMap();
        setInitialPlayerPosition();
    }

    void initializeMap() {
        map = {
            {"Fort", "Plains", "River"},
            {"Forest", "Town", "Plains"},
            {"Mountains", "Plains", "Cave"}
        };
    }

    void setInitialPlayerPosition() {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] == "Town") {
                    player.x = j;
                    player.y = i;
                    return;
                }
            }
        }
    }

    void showMap() {
        std::cout << "You view the map \n";
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (i == player.y && j == player.x) {
                    std::cout << " |" << "*" << std::setw(9) << map[i][j];
                }
                else {
                    std::cout << " |" << std::setw(10) << map[i][j];
                }
            }
            std::cout << "|\n";
        }
    }


    void moveNorth() {
        std::cout << "Moving North...\n";
        if (player.y > 0)
        {
            player.y--;
        }
        else
        {
            std::cout << "Cannot move further North. \n";
        }
        
        

    }

    void moveEast() {
        std::cout << "Moving East...\n";
        if (player.x < map.size()-1)
        {
            player.x++;
        }
        else
        {
            std::cout << "Cannot move further East. \n";
        }



    }

    void moveSouth() {
        std::cout << "Moving South...\n";

        if (player.y < map.size() -1) // locks it to a perfect grid square if not gonna be issues later
        {
            player.y++;
        }
        else {
            std::cout << "Cannot move further South. \n";
        }


    }

    void moveWest() {
        std::cout << "Moving West...\n";
        if (player.x > 0)
        {
            player.x--;
        }
        else
        {
            std::cout << "Cannot move further West. \n";
        }



    }
};






void displayWelcome() {
    std::cout << "Welcome to Text Based Medieval Fantasy RPG!" << std::endl;
}

int main() {
    displayWelcome();
    GameState world;

    world.player.displayCharacter();

    std::cout << "Hello, " << world.player.name << ", your adventure begins!" << std::endl;

    std::string input;
    while (world.player.health > 0) {
        std::cout << "> ";
        std::getline(std::cin, input);

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
            world.showMap();
        }

        if (input == "move north")
        {
            world.moveNorth();
        }

        if (input == "move south")
        {
            world.moveSouth();
        }

        if (input == "move east")
        {
            world.moveEast();
        }

        if (input == "move west")
        {
            world.moveWest();
        }


        std::cout << "You typed: " << input << std::endl;
    }

    return 0;
}
