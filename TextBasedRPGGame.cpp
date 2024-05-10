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
		name(name), description(description), dialogue(dialogue), x(startX), y(startY), health(health), strength(strength), dex(dex), magic(magic), isDefeated(false) {}

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
	std::string charClass;
	int health;
	int strength;
	int dex;
	int magic;
	int level = 1;
	double exp = 0;
	double neededEXP = 100;
	int maxhealth = health;
	// New WIP 
	int mana;
	int stamina;
	int maxStamina = stamina;
	int maxMana = mana;
	std::vector<std::string> spells;
	std::vector<std::string> inventory;

	int x; // Player's x coordinates
	int y; // Player's y coordinates

	Character(std::string name, int health, int strength, int dex, int magic, int startX, int startY, int startlvl, std::string charClass, int startMana, int startStamina) :
		name(name), health(health), strength(strength), dex(dex), magic(magic), x(startX), y(startY), level(startlvl),
		charClass(charClass), mana(startMana), stamina(startStamina) {}

	//display

	std::string heroAttack =

		"     ==\n"
		"     ||__________________________\n"
		"OOOOO||_________________________/\n"
			"     ||\n"
			"     ==\n";


	void displayCharacter() {
		std::cout << "Name: " << name << "\n"
			<< "Level: " << level << "\n"
			<< "Class: " << charClass << "\n"
			<< "Health: " << health << "\n"
			<< "Strength: " << strength << "\n"
			<< "Agility: " << dex << "\n"
			<< "Magic: " << magic << "\n"
			<< "EXP: " << exp << " / " << neededEXP << "\n"
			<< "Mana: " << mana <<  " / " << maxMana << "\n"
			<< "Stamina: " << stamina << " / " << maxStamina << "\n"

			<< std::endl;
	}

	void basicAttack(NPC& target) {

		int damage = strength;

		target.health -= damage;
		std::cout << name << " attacks " << target.name << " for " << damage << " damage." << "\n" << heroAttack << std::endl;


	}

	void heavyAttack(NPC& target) {

		int damage = (strength * 2);

		target.health -= damage;
		std::cout << name << " attacks " << target.name << " for " << damage << " damage." << std::endl;


	}


	void performAction(const std::string& actionType, NPC& target) {
		if (actionType == "Basic Attack") {
			basicAttack(target);
		}
		else if (actionType == "Defend") {
		}
		else if (actionType == "Use Item") {
			// useItem("Health Potion");  // Example item
		}
		else if (actionType == "Magic Spell") {
			// castSpell("Fireball", target);  // Example spell
		}
	}


	// XP Function



	void levelUp() {
		level += 1;
		exp = exp - neededEXP;
		neededEXP = neededEXP * (1.2); // 20% exp needed for next

		if (charClass == "Barbarian")
		{
			strength += 8;
			dex += 2;
			magic += 2;
			maxhealth += 20;
		}
		else if (charClass == "Warrior")
		{
			strength += 8;
			dex += 4;
			magic += 2;
			maxhealth += 15;
		}
		else if (charClass == "Mage")
		{
			strength += 2;
			dex += 2;
			magic += 10;
			maxhealth += 5;
		}
		else if (charClass == "Thief")
		{
			strength += 4;
			dex += 8;
			magic += 2;
			maxhealth += 10;
		}
		else if (charClass == "Wanderer")
		{
			strength += 5;
			dex += 5;
			magic += 5;
			maxhealth += 10;
		}
		else
		{
			strength += 5;
			dex += 5;
			magic += 5;
			maxhealth += 10;
		}

		health = maxhealth;
		std::cout << "Congratulations! You have leveled up to level " << level << " !! \n";
		std::cout << "Type 'stats' to view details";

	}


	void addEXP(int amt) {
		exp += amt;
		if (exp == neededEXP)
		{
			levelUp();
		}
	}

	// XP above



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

	while (true)
	{
		if (std::cin >> classChoice)
		{
			break;
		}
		else
		{
			// clear any error states
			std::cin.clear();
			// ignore the input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid class choice, try again using just a number.\n";
		}

	}





	// health low = 75, med = 100, high = 125
	// stats low = 5, med = 10, high 15 

	switch (classChoice)
	{
	case 1: // Barb (High Strength / High Health / Low Agility / Low Magic)
		std::cout << "You chose a Barbarian \n";
		return Character(name, 125, 15, 5, 5, 0, 0, 1, "Barbarian", 10, 50);

	case 2: // Warrior (High Strength / Medium Health / Medium Agility / Low Magic)
		std::cout << "You chose a Warrior \n";
		return Character(name, 100, 15, 10, 5, 0, 0, 1, "Warrior", 10, 65);

	case 3: // Light Mage (Low Strength / Low Health / Medium Agility / High Magic)
		std::cout << "You chose a Light Mage \n";
		return Character(name, 75, 5, 10, 15, 0, 0, 1, "Mage", 50, 10);

	case 4: // Thief (Medium Strength / Low Health / High Agility / Low Magic)
		std::cout << "You chose a Thief \n";
		return Character(name, 75, 10, 15, 5, 0, 0, 1, "Thief", 10, 80);

	case 5: // Wanderer (Medium Strength / Medium Health / Medium Agility / Medium Magic)
		std::cout << "You chose a Wanderer \n";
		return Character(name, 100, 10, 10, 10, 0, 0, 1, "Wanderer", 35, 35);

	default:
		std::cout << "Invalid, starting as a Wanderer";
		// Wanderer (Medium Strength / Medium Health / Medium Agility / Medium Magic)
		return Character(name, 100, 10, 10, 10, 0, 0, 1, "Wanderer", 35, 35);
	}
}

class GameState {
public:

	Character player;
	std::vector<std::vector<std::string>> map;
	std::vector<NPC> npcs;
	std::string heroArt =
		"   Hero:\n"
		"    O\n"
		"   /|\\\n"
		"   / \\\n";

	std::string monsterArt =

		"														\n"
		"                          +######                      \n"
		"                        +#+----++++                    \n"
		"                        ++--++-+-+++#                  \n"
		"                       ++--+------+++#                 \n"
		"                       ++++-+#+--+####                 \n"
		"                      ##+++-+##+-++++#                 \n"
		"                     #++++---+++######                 \n"
		"                    ###+------+#######                 \n"
		"                   #++-+++++-+#####                    \n"
		"                  #+++------+#####+#                   \n"
		"                 #++-++----+########+++#               \n"
		"              #+#++--+-----+++#######+-+#              \n"
		"             +++-+---+#++-++-----++-----+#             \n"
		"          #++++-+--------------------++++--++          \n"
		"          ++-----+------------++----++-------##        \n"
		"          #++----+#++--++------+#++#+-------+#         \n"
		"              ####++-------------------++###           \n"
		"                    ###++--------++++##                \n"
		"                        #########                      \n";
																

	GameState() : player(createCharacter()) {  // Initialize the player using the createCharacter function
		initializeMap();
		setInitialPlayerPosition();
	}

	int highestNPCStat(NPC& npc) {
		return std::max(npc.strength, npc.magic);
	}

	// Combat System //////////
	bool playerAttacksFirst(Character& player, NPC& enemy) {
		int totalDex = player.dex + enemy.dex;
		if (totalDex == 0) return rand() % 2 == 0;  // Avoid division by zero, fallback to 50-50 chance

		// Calculate the probability of the player attacking first
		double playerProbability = static_cast<double>(player.dex) / totalDex;

		// Generate a random number between 0 and 1
		double randValue = static_cast<double>(rand()) / RAND_MAX;

		// Determine if the player attacks first based on the calculated probability
		return randValue < playerProbability;
	}

	void combat(Character& player, NPC& enemy) {
		bool playerTurn = playerAttacksFirst(player, enemy);
		std::cout << (playerTurn ? "You attack first!\n" : "Monster attacks first!\n");
		std::cout << monsterArt << "\n";


		while (player.health > 0 && enemy.health > 0) {
			if (playerTurn) {
				std::cout << "Choose your action:\n";
				std::cout << "1. Basic Attack (10 stamina)\n";
				std::cout << "2. Heavy Attack (30 stamina)\n";
				/*std::cout << "3. Use Item\n";
				std::cout << "4. Defend\n";
				std::cout << "Enter choice: ";*/
				int choice;
				while (true)
				{
					if (std::cin >> choice)
					{
						break;
					}
					else
					{
						// clear any error states
						std::cin.clear();
						// ignore the input
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "Invalid class choice, try again using just a number.\n";
					}

				}

				switch (choice) {
				case 1:
					if (player.stamina < 10)
					{
						std::cout << "Not enough stamina! Resting!" << "\n";
						player.stamina += 5;
						std::cout << "Stamina: " << player.stamina << " / " << player.maxStamina << "\n";
					}
					else {
						player.basicAttack(enemy);
						player.stamina -= 10;
						std::cout << "Stamina: " << player.stamina << " / " << player.maxStamina << "\n";
					}
					break;
				case 2:
					if (player.stamina < 30)
					{
						std::cout << "Not enough stamina! Resting!" << "\n";
						player.stamina += 5;
						std::cout << "Stamina: " << player.stamina << " / " << player.maxStamina << "\n";
					}
					else {
						player.heavyAttack(enemy);
						player.stamina -= 30;
						std::cout << "Heavy Attack!\n";
						std::cout << "Stamina: " << player.stamina << " / " << player.maxStamina << "\n";
					}
					break;
				case 3:
					//player.useItem("HealthPotion");
					break;
				case 4:
					//player.defend();
					break;
				default:
					player.basicAttack(enemy);
					break;
				}
			}
			else {
				std::cout << enemy.name << " hits you for " << highestNPCStat(enemy) << " Damage! \n";
				player.health -= enemy.strength;
			}

			if (enemy.health <= 0) {
				std::cout << enemy.name << " defeated!\n";
				enemy.isDefeated = true;  // Mark the enemy as defeated
				player.stamina = player.maxStamina; // refresh stam
				player.mana = player.maxMana; // refresh mana
				player.addEXP(50);  // Award experience points
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
		npcs.push_back(NPC("Zombie", "Spooky ", "RAAAAUUUUGHHHH!", 1, 2, 20, 10, 5, 5));
		npcs.push_back(NPC("Zombie", "Spooky ", "RAAAAUUUUGHHHH!", 3, 2, 20, 10, 5, 5));
		npcs.push_back(NPC("Zombie", "Spooky ", "RAAAAUUUUGHHHH!", 4, 2, 20, 10, 5, 5));
		npcs.push_back(NPC("Zombie", "Spooky ", "RAAAAUUUUGHHHH!", 3, 3, 20, 10, 5, 5));
	}
	void showMapWithNPCs() {
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				bool npcFound = false;
				for (const auto& npc : npcs) {
					if (npc.x == j && npc.y == i && !npc.isDefeated) {
						std::cout << "?->";
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
					std::cout << " ||" << "*" << std::setw(9) << map[i][j];
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

	//world.showMapWithNPCs(); // uncomment to see npcs

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
