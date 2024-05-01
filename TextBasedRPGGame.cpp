#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class NPC {
public:
    std::string name;
    std::string description;
    std::string dialogue;
    int health;
    int strength;
    int dex;
    int magic;
    bool isDefeated;


    int x, y; // starting coordinates of a NPC

    NPC(std::string name, std::string description, std::string dialogue, int startX, int startY, int health, int strength, int dex, int magic) :
        name(name), description(description), dialogue(dialogue), x(startX), y(startY), health(health), strength(strength), dex(dex), magic(magic), isDefeated(false){}

    void interact() {
        if (!isDefeated)
        {
            std::cout << name << " says: " << dialogue << std::endl;
        }
        else {
            std::cout << name << " is defeated and can no longer interact." << std::endl;
        }
    }
};

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
    std::vector<NPC> npcs;

    GameState() : player(createCharacter()) {  // Initialize the player using the createCharacter function
        initializeMap();
        setInitialPlayerPosition();
    }
    // Combat System //////////
    bool playerAttacksFirst() {
        // Simple random initiative for now
        return rand() % 2 == 0;  // 50-50 chance
    }

    void combat(Character& player, NPC& enemy) {
        bool playerTurn = playerAttacksFirst();

        std::cout << (playerTurn ? "You attack first!\n" : "Zombie attacks first!\n");

        while (player.health > 0 && enemy.health > 0) {
            if (playerTurn) {
                enemy.health -= player.strength;
                std::cout << "You hit the zombie for " << player.strength << " damage.\n";
            }
            else {
                player.health -= enemy.strength;
                std::cout << "Zombie hits you for " << enemy.strength << " damage.\n";
            }

            if (enemy.health <= 0) {
                std::cout << "Zombie defeated!\n";
                enemy.isDefeated = true;
                break;
            }
            else if (player.health <= 0) {
                std::cout << "You have been defeated!\n";
                break;
            }

            playerTurn = !playerTurn;  // Switch turns
        }
    }



    // Combat Above

    // NPCS //////////////////////////////////////////////////
    void initializeNPCs() {
        npcs.push_back(NPC("Zombie", "Spooky ", "RAAAAUUUUGHHHH!", 1, 1, 20, 10, 5, 5));
    }
    void showMapWithNPCs() {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                bool npcFound = false;
                for (const auto& npc : npcs) {
                    if (npc.x == j && npc.y == i && !npc.isDefeated) {
                        std::cout << "?";
                        npcFound = true;
                        break;
                    }
                }
                if (!npcFound) {
                    std::cout << " " << map[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    void interactWithNPC(int x, int y) {
        for (auto& npc : npcs) {
            if (npc.x == x && npc.y == y) {
                std::cout << "You encounter " << npc.name << ": " << npc.description;
                npc.interact();
                if (npc.name == "Zombie" && !npc.isDefeated)
                {
                    combat(player, npc);
                }
              
                return;
            }
        }
        std::cout << "There is no one here to interact with.\n";
    }

    // NPCS Above

    void initializeMap() {
        map = {
            {"Fortress", "Mountains", "Plains", "Swamp", "Lake", "Swamp"},
            {"Mountains", "Plains", "Plains", "Forest", "Village", "Forest"},
            {"Plains", "Cave", "Town", "Hills", "Cave", "Deadlands"},
            {"River", "Mountains", "Pond", "Desert", "Cave", "Desert"}
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
        std::cout << "================== MAP ============================================================\n";
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (i == player.y && j == player.x) {
                    std::cout << " ||" << "*" << std::setw(7) << map[i][j];
                }
                else {
                    std::cout << " ||" << std::setw(10) << map[i][j];
                }
            }
            std::cout << "||\n";
            std::cout << "===================================================================================\n";
        }
    }




    void moveNorth() {
        std::cout << "Moving North...\n";
        if (player.y > 0) {
            player.y--;
            std::cout << "Entering: " << map[player.y][player.x] << "\n";  // Corrected the order of indices
        }
        else {
            std::cout << "Cannot move further North. \n";
        }
    }

    void moveEast() {
        std::cout << "Moving East...\n";
        if (player.x < map[0].size() - 1) {  // Assuming all rows are the same width
            player.x++;
            std::cout << "Entering: " << map[player.y][player.x] << "\n"; 
        }
        else {
            std::cout << "Cannot move further East. \n";
        }
    }

    void moveSouth() {
        std::cout << "Moving South...\n";
        if (player.y < map.size() - 1) {  // Corrected to use map.size() for y boundary
            player.y++;
            std::cout << "Entering: " << map[player.y][player.x] << "\n";
        }
        else {
            std::cout << "Cannot move further South. \n";
        }
    }

    void moveWest() {
        std::cout << "Moving West...\n";
        if (player.x > 0) {
            player.x--;
            std::cout << "Entering: " << map[player.y][player.x] << "\n";
        }
        else {
            std::cout << "Cannot move further West. \n";
        }
    }

};

void displayHelp() {
    std::cout << "Available Commands:\n"
        << "  map - Display the game map\n"
        << "  move north - Move one tile north\n"
        << "  move south - Move one tile south\n"
        << "  move east - Move one tile east\n"
        << "  move west - Move one tile west\n"
        << "  quit - Exit the game\n"
        << "  clear - Clear the screen\n"
        << "  stats - show stats\n"
        << "  interact - interact with NPCs\n"
        << std::endl;
}

void handleCommand(const std::string& input, GameState& world) {
    if (input == "help") {
        displayHelp();
    }
    else if (input == "clear") {
        system("cls");
        std::cout << "Chat logs were cleared!\n";
    }
    else if (input == "stats")
    {
        world.player.displayCharacter();
    }
    else if (input == "interact")
    {
        world.interactWithNPC(world.player.x, world.player.y);
    }
    else if (input == "map") {
        world.showMap();
    }
    else if (input == "move north") {
        world.moveNorth();
    }
    else if (input == "move south") {
        world.moveSouth();
    }
    else if (input == "move east") {
        world.moveEast();
    }
    else if (input == "move west") {
        world.moveWest();
    }
    else {
        std::cout << "Unknown command. Type 'help' for more information.\n";
    }
}





void displayWelcome() {
    std::cout << "Welcome to Text Based Medieval Fantasy RPG!" << std::endl;
}

int main() {
    displayWelcome();
    GameState world;

    world.player.displayCharacter();
    world.initializeNPCs();

    std::cout << "Hello, " << world.player.name << ", your adventure begins!" << std::endl;

    std::string input;
    while (world.player.health > 0) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "quit") {
            break; // quits
        }
        handleCommand(input, world);


       // std::cout << "You typed: " << input << std::endl;
    }

    return 0;
}
