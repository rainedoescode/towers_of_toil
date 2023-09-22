//Raine Adams, rainedoescode@gmail.com, 2021-7-25
//Text based adventure game

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "Location.h"

enum difficulty { hard = 30, normal = 45, easy = 60}; // time given to the player
//TODO: test time limits and difficulty

//struct for items in game
struct Item {
	int itemX, itemY; //item location, set to -1,-1 if in inventory
	std::string name; //item name
	std::string itemDesc; //item description
	int counter = 0; //counter for special cases
	bool inInventory = false; //flag for inventory
	bool found = false; //flag to set as found, used if dropped later?
	bool specialFlag = false; //flag for special item interactions
};

std::string mood(int lvl); // function to return emoji for current mood

int main() {
	
	//data for locations

	const int LOCATIONS = 17;

	std::string locationNames[LOCATIONS] = {
		"Cloister of Cleansing", "Spire of Slumber", "Palace of Provisions",
		"Armory of Attire", "Hall of Many Ways", "Room of Renewal",
		"The Bastion of Knowledge","The World's Threshold","The Dank Underground",
		"The Flowering Labyrinth","The Iron Stable","The Green Expanse",
		"House of Caffeine","Rivers of Stone","Espresso Express",
		"Towers of Toil","The Swirling Void"
	};

	std::string shortDescriptions[LOCATIONS] = {
		"A religious building has spring up around your bathroom. So much for privacy...",
		"Once a second-story bedroom, now at the top of a spire reaching into the sky...",
		"The kitchen has transformed into a palace fit for a king. Probably a Henry VIII portrait around here somewhere...",
		"There used to be a closet here. Now every one of your outfits is on its own mannequin...",
		"More doorways than you know what to do with. Luckily four of them are glowing and labeled... how convenient...",
		"These names are getting ridiculous. This is just your living room. It looks the same...",
		"Books everywhere. On shelves. Piled on the floor. Half blocking the door...",
		"The front door got much bigger. A gateway into the great unknown. You could fit a trojan horse through this thing...",
		"Dank. Dark. Deep. Dungeon-like. Dozens of dryers...",
		"You don't recall having Hedges. Did you even have a garden before?\nYou're not sure at this point. Wait, the entrance was right there behind you...",
		"Ah yes, your trusty iron steed. Maybe you should've called your car something else...",
		"The yard seems much bigger than before. And the tree. And the treehou... \nWait you didn't have a treehouse...",
		"Well-worn wooden floors. The smell of freshly roasted coffee beans. Friendly faces. \nThe best place to feed your addiction...",
		"The wide-open road. Miles of concrete. It's looking a bit flowy today...",
		"Stale pastries. The screaming of steamed milk. Automation.\n At least you can get your fix...",
		"Downtown looks more uninviting than usual. \nAs you gallop your way into the concrete jungle, the sun is hidden from view...",
		"You don't know how you got here. Nothing makes sense. Maybe you should just quit..."
	};

	std::string longDescriptions[LOCATIONS] = {
		"That's your bathroom... or at least the contents. Surrounded by glass walls.",
		"Spire? Is that the right word? More of a tower. The tallest tower around it seems. \nAnd you're locked in like some damsel in distress or deposed prince. \nThere must be a key in here somewhere, otherwise how will this story progess...",
		"At one end is a kitchen big enough to feed dozens. Three refriderators, four ovens, a stovetop long enough to lay on.\nAt the other end, a dining table with more seats then you have friends. And of course.\nHanging on the wall about the head of the table is a portrait of Henry VIII... with your face...",
		"How are you even going to get these clothes off the mannequins to get dressed?\nRows upon rows of outfits. You really hope you didn't leave anything in your pockets yesterday.",
		"You don't quite understand the geometry of this place. If you think about it too long you get dizzy.",
		"Couch. TV. Coffee table. Yep. Same stuff.",
		"The smell of old paper permeates the air.\nYou're surrounded by the type of organized chaos only a genius could produce...\nA genius, or a psychopath...",
		"So many coat hooks and mirrors. Tiny shelves covered in knicknacks. Front door. Lock it on the way out - key needed",
		"This is like some surrealist rendition of a modern catacomb. Perhaps this is where dead dryers go for their final resting place.",
		"In front of you there is a ledge with a little blue cattipillar sitting on it.\n\"Hello there. You look lost. If you take a right here, you'll get straight to the exit.\"",
		"Your trusty iron steed sits in the driveway. Passage to the rivers of stone to the south.",
		"There would probably be something in the treehouse, but who has time to write all that out.\nJust pretend there is nothing important here.",
		"Delicious coffee.",
		"Surrealism solidified in concrete.",
		"Crappy coffee.",
		"Workworkworkworkwork.",
		"Hello darkness, my old friend."
	};

	std::string examineDescriptions[LOCATIONS] = {
		"Maybe there is a more private bathroom somewhere around here...",
		"You rummage around for a moment before opening the nightstand drawer.",
		"Somehow there's no coffee anywhere. Blasphemy. Perhaps in the refidgerator?",
		"You walk up to one of your work outfits...",
		"",
		"Huh. It was sitting right there on the coffee table.",
		"A stack of your favorite books catches your eye. They're a bit off-kilter. You lift them up.",
		"After looking around you see it on one of the little shelves.",
		"You do a doubletake and notice a passageway without a dryer. There is a glint of light at the end.",
		"You can't see any difference no matter what direction you look. Which way to go...",
		"",
		"",
		"",
		"",
		"",
		"",
		"The dark abyss of depression. You really should just give up. You don't see a way out of this.\n\n\t(really though, the author ran out of time to code an exit)",
	};

	//initialize locations
	Location bathroom(locationNames[0], shortDescriptions[0], longDescriptions[0], examineDescriptions[0]);
	Location bedroom(locationNames[1], shortDescriptions[1], longDescriptions[1], examineDescriptions[1]);
	Location kitchen(locationNames[2], shortDescriptions[2], longDescriptions[2], examineDescriptions[2]);
	Location wardrobe(locationNames[3], shortDescriptions[3], longDescriptions[3], examineDescriptions[3]);
	Location hall(locationNames[4], shortDescriptions[4], longDescriptions[4], examineDescriptions[4]);
	Location livingroom(locationNames[5], shortDescriptions[5], longDescriptions[5], examineDescriptions[5]);
	Location library(locationNames[6], shortDescriptions[6], longDescriptions[6], examineDescriptions[6]);
	Location frontdoor(locationNames[7], shortDescriptions[7], longDescriptions[7], examineDescriptions[7]);
	Location basement(locationNames[8], shortDescriptions[8], longDescriptions[8], examineDescriptions[8]);
	Location garden(locationNames[9], shortDescriptions[9], longDescriptions[9], examineDescriptions[9]);
	Location driveway(locationNames[10], shortDescriptions[10], longDescriptions[10], examineDescriptions[10]);
	Location yard(locationNames[11], shortDescriptions[11], longDescriptions[11], examineDescriptions[11]);
	Location goodcoffee(locationNames[12], shortDescriptions[12], longDescriptions[12], examineDescriptions[12]);
	Location road(locationNames[13], shortDescriptions[13], longDescriptions[13], examineDescriptions[13]);
	Location badcoffee(locationNames[14], shortDescriptions[14], longDescriptions[14], examineDescriptions[14]);
	Location office(locationNames[15], shortDescriptions[15], longDescriptions[15], examineDescriptions[15]);
	Location thevoid(locationNames[16], shortDescriptions[16], longDescriptions[16], examineDescriptions[16]);

	// 2d array to hold location map
	Location map[6][3] = {
		bathroom, bedroom, kitchen,
		wardrobe, hall, livingroom,
		library, frontdoor, basement,
		garden, driveway, yard,
		goodcoffee, road, badcoffee,
		thevoid, office //no 18th location, empty
	}; 

	//flags and variable declaration
	bool quit = false;
	bool gameStart = true;

	bool showered, caffeinated, break_fast, portraitTrigger, inCar, gameOver;

	int timeRemaining, happinessLevel, playerX, playerY, r;


	Item tower_key, keys, wallet, phone, badge, work_clothes, coin;

	//main game loop
	while (!quit) {

		//set values on game start, print story
		if (gameStart) {

			showered = false;
			caffeinated = false;
			break_fast = false;
			portraitTrigger = false;
			inCar = false;
			gameOver = false;

			playerY = 0;
			playerX = 1;

			for (int y = 0; y < 6; y++) {
				for (int x = 0; x < 3; x++) {
					if (y == 5 && x == 2) {
						break;
					}
					map[y][x].setExamined(false);
					map[y][x].setVisited(false);
				}
			}

			timeRemaining = normal; //difficulty currently hard coded for testing
			happinessLevel = 1;// 3; //happiness level hard coded for testing

			//initialize items
			tower_key = { 0,1, "Spire Key", "\tIt's even styled like a spire. Very Pointy." };
			keys = { 1,2, "Keys", "\tCar key, front door, office desk. \n\tA couple others you can't remember the use for. \n\t\"You won't get far without these.\"" };
			wallet = { 2,0, "Wallet", "\tContents: Identification, money, expired coupons, random business cards." };
			phone = { 2,2, "Phone", "\tA tiny computer, capable of accessing the knowledge of the world.\n\tYou use it mostly for playing games..."};
			badge = { 1,2, "Work Badge", "\tA near-field communication device the size of a credit card.\n\tThis give you access to the Office.\n\tIt has a very \"Professional\" photo of you on the front." };
			work_clothes = { 1, 0, "Work Clothes", "Business Casual. What an oxymoron. You certainly feel like an oxymoron in these.", 5 }; //5 sets of work clothes, probably too many
			coin = { 3,0, "A Coin", "Nothing fancy here. Just a quarter. Heads. Tails. Worth $0.25..." };

			//story time
			std::cout << std::endl << std::endl;
			std::cout << "\tA story of a day just like any other... You wake up, but something's not quite right." << std::endl;
			std::cout << "\tYour house has turned into some sort of fantastic medieval castle, and your alarm never went off." << std::endl;
			std::cout << "\tYou must hurry to get ready for work, but you can't remember where you left anything." << std::endl;
			std::cout << "\tKeys, wallet, phone, work badge... they must be here somewhere." << std::endl;
			std::cout << "\tWho knows that The Boss will do if you're late again." << std::endl << std::endl;
			std::cout << "\tYou look out the window and see the Towers of Toil far off in the distance." << std::endl; 
			std::cout << "\tThis is going to be a long day, try to keep your head up." << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(2500));

			gameStart = false;

			std::cout << std::endl << "\t\t Enter any key to continue: ";
			std::cin.get();
			std::cin.clear();

			std::cout << "\t The day begins.";
			for (int i = 0; i < 4; i++) {
				std::cout << ".";

				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			//clear screen
			system("CLS");
		}
		

		//location and time display
		std::cout << "\n-=-=-=-=-=-=-=-=- Current Location -=-=-=-=-=-=-=-=-\n\n";
		std::cout << "\t " << map[playerY][playerX].getName() << std::endl;
		std::cout << "\t Time until shift starts: ";
		if (phone.inInventory) { std::wcout << timeRemaining; } //only display time if phone in inventory
		else { std::cout << "???"; }
		std::cout << " minutes" << std::endl;
		std::cout << "\t Mood: " << mood(happinessLevel) << std::endl;
		std::cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
		std::cout << std::endl;

		std::cout << map[playerY][playerX].getShortDesc() << std::endl;

		//movement flags
		bool canMove = true;

		bool validMove = false;
		bool north = false;
		bool south = false;
		bool east = false;
		bool west = false;

		//move menu
		std::string moveNorth, moveSouth, moveEast, moveWest;

		// turn \ location loop
		// loop through actions possible in location
		while (!validMove) {

			canMove = true;
			validMove = false;
			north = false;
			south = false;
			east = false;
			west = false;

			//check if player is in bedroom, door is locked?
			if ((map[playerY][playerX].getName().std::string::compare(bedroom.getName()) == 0) && !(tower_key.inInventory)) {

				canMove = false;
			}
			else if (playerY == 5 && playerX == 0) {

				canMove = false;
			}
			else {
				if (!(playerY == 0 || (playerY == 4 && (playerX == 0 || playerX == 2)))) {
					//north movement ok
					north = true;
					moveNorth = "\t[N] for north";
				}

				if (!(playerY == 5 || (playerY == 3 && (playerX == 0 || playerX == 2)) || (playerY == 4 && (playerX == 0 || playerX == 2)))) {
					//south movement ok
					//test for car keys
					if (!(playerX == 1 && playerY == 3)) {

						south = true;
						moveSouth = "\t[S] for south";
					}
					else {
						if (keys.inInventory) {
							south = true;
							moveSouth = "\t[S] to drive south";
						}
						else {
							moveSouth = "\t[ ] You need your keys to drive south";
						}
					}
				}

				if (!(playerX == 2 || (playerY == 5 && playerX == 1))) {
					//east movement ok
					east = true;
					moveEast = "\t[E] for east";
				}
				if (!(playerX == 0 || (playerY == 5 && playerX == 1))) {
					//west movement ok
					west = true;
					moveWest = "\t[W] for west";
				}

			}

			if ((map[playerY][playerX].getName().std::string::compare(hall.getName()) == 0)) {
				moveNorth = "\t[N] " + map[playerY - 1][playerX].getName();
				moveSouth = "\t[S] " + map[playerY + 1][playerX].getName();
				moveEast = "\t[E] " + map[playerY][playerX + 1].getName();
				moveWest = "\t[W] " + map[playerY][playerX - 1].getName();
			}

			std::cout << std::endl;


			std::cout << "\t[L] to look around";
			if (map[playerY][playerX].isExamined()) {
				std::cout << "\t[X] to examine location";
			}
			std::cout << std::endl;

			if (canMove) {
				std::cout << moveNorth << moveSouth << moveEast << moveWest;
			}
			

			char input = '0';
			std::cout << std::endl << std::endl;
			std::cout << "Enter command, [Q] to quit: ";
			std::cin >> input;

			std::cout << std::endl;

			char choice = '0';
			bool validChoice = false;

			switch (input) {
			case 'L':
			case 'l':
				//print long description
				std::cout << map[playerY][playerX].getLongDesc();
				map[playerY][playerX].setExamined(true);
				std::cout << std::endl;

				//reduce time by 1 when looking over location
				timeRemaining--;

				//check for one-time portrait trigger
				if ((map[playerY][playerX].getName().std::string::compare(kitchen.getName()) == 0) && !portraitTrigger) {
					std::cout << "\n\t\tHow depressing..." << std::endl;
					happinessLevel--;
					portraitTrigger = true;
				}

				break;
			case 'X':
			case 'x':
				//print examination description
				std::cout << map[playerY][playerX].getExamineDesc();
				//check for items, if here put in inventory
				if (tower_key.itemX == playerX && tower_key.itemY == playerY) {
					std::cout << "\tYou found the " << tower_key.name << "!" << std::endl << std::endl;
					std::cout << tower_key.itemDesc << std::endl;
					tower_key.inInventory = true;
					tower_key.found = true;
					tower_key.itemX = -1;
					tower_key.itemY = -1;
				}
				else if (keys.itemX == playerX && keys.itemY == playerY) {
					std::cout << "\tYou found your " << keys.name << "!" << std::endl << std::endl;
					std::cout << keys.itemDesc << std::endl;
					keys.inInventory = true;
					keys.found = true;
					keys.itemX = -1;
					keys.itemY = -1;
				}
				else if (wallet.itemX == playerX && wallet.itemY == playerY) {
					std::cout << "\tYou found your " << wallet.name << "!" << std::endl << std::endl;
					std::cout << wallet.itemDesc << std::endl;
					wallet.inInventory = true;
					wallet.found = true;
					wallet.itemX = -1;
					wallet.itemY = -1;
				}
				else if (phone.itemX == playerX && phone.itemY == playerY) {
					std::cout << "\tYou found your " << phone.name << "!" << std::endl << std::endl;
					std::cout << phone.itemDesc << std::endl;
					phone.inInventory = true;
					if (phone.found == false) {
						phone.found = true;

						std::cout << std::endl << "\tFinally you can check the time.\n\tYou have " << timeRemaining;
						std::cout << " minutes until your shift starts!" << std::endl;
					}
					phone.itemX = -1;
					phone.itemY = -1;
				}
				else if (badge.itemX == playerX && badge.itemY == playerY) {
					std::cout << "\tYou found your " << badge.name << "!" << std::endl << std::endl;
					std::cout << badge.itemDesc << std::endl;
					badge.inInventory = true;
					badge.itemX = -1;
					badge.itemY = -1;
				}
				else if ((map[playerY][playerX].getName().std::string::compare(kitchen.getName()) == 0) && break_fast == false) {
					std::cout << "\nIt takes all your might to open the refridgerator door. \nA holy light shines upon you as you behold the Breakfast of Champions." << std::endl;
					std::cout << "As if on queue, your stomach growls, reminding you that you haven't had breakfast.\nWill you pause to eat this bless'd feast?" << std::endl << std::endl;
					while (!validChoice) {
						std::wcout << "\tEat? [Y] yes or [N] no: ";
						choice = 0;
						std::cin >> choice;
						switch (choice) {
						case 'Y':
						case 'y':
							std::cout << "You consume one of the best morning meals you've had in some time.\nYour mood has improved." << std::endl;
							
							//increase happiness but decrease time for eating
							happinessLevel += 1;
							timeRemaining -= 3;

							break_fast = true;
							validChoice = true;

							break;
						case 'N':
						case 'n':
							std::cout << "No time to eat right now. You'll survive." << std::endl;

							//decrease happiness by one for hunger, no extra time decrease
							happinessLevel -= 1;

							validChoice = true;

							break;
						default:
							std::cout << std::endl << "-Invalid Command-" << std::endl;
						}
					}
				}
				else if ((map[playerY][playerX].getName().std::string::compare(wardrobe.getName()) == 0) && (work_clothes.found == false)) {
					
					while (!validChoice) {
						choice = 0;
						std::cout << "Do you try to take the clothes? [Y] yes or [N] no: ";
						std::cin >> choice;

						switch (choice) {
						case 'Y':
						case 'y':
							r = rand() % 6;
							if (r < 2) {
								std::cout << "\tYou touch the hem of the shirt";
							}
							else if (r < 4) {
								std::cout << "\tYour hand brushes the jacket";
							}
							else {
								std::cout << "\tYou place your hand on the mannequin";
							}

							r = rand() % 6;
							if (r < 2) {
								std::cout << " and suddenly you're wearing the clothes..." << std::endl;
							}
							else if (r < 4) {
								std::cout << " and the clothes jump onto your body..." << std::endl;
							}
							else {
								std::cout << " and *poof* you're all dressed up..." << std::endl;
							}
							if (!showered) {
								std::cout << "\tToo bad you haven't showered yet. Now you're wearing dirty clothes..." << std::endl;

								happinessLevel -= 1;
								work_clothes.specialFlag = true; //dirty clothes
								work_clothes.found = true; //alter later to see if you put a second set of clothes on before showering
								work_clothes.inInventory = true;
								work_clothes.counter -= 1;
							}
							else {
								std::cout << "\tAt least you look ready to work." << std::endl;
								work_clothes.found = true;
								work_clothes.inInventory = true;
								work_clothes.specialFlag = false; //clean clothes
								work_clothes.counter -= 1;
							}


							validChoice = true;

							break;
						case 'N':
						case 'n':
							std::cout << "No time dress up right now. Maybe later." << std::endl;

							//TODO: add case for visited and unshowered

							validChoice = true;

							break;
						default:
							std::cout << std::endl << "-Invalid Command-" << std::endl;
							break;
						}
					}
				}
				//no key items found
				else {
					std::cout << "You spend a couple minutes searching but find nothing of interest." << std::endl;
				}

				std::cout << std::endl;

				//reduce time by 2 after examining/searching location
				timeRemaining -= 2;

				break;

			//movement options
			case 'N':
			case 'n':
				if (north) {
					playerY -= 1;
					std::cout << "Moving North" << std::endl;
					validMove = true;

					//reduce time by 1 when moving
					timeRemaining--;
				}
				else {
					std::cout << "You can't go that way" << std::endl;
				}
				break;
			case 'S':
			case 's':
				if (south) {
					playerY += 1;
					std::cout << "Moving South" << std::endl;
					validMove = true;

					//reduce time by 1 when moving
					timeRemaining--;
				}
				else {
					std::cout << "You can't go that way" << std::endl;
				}
				break;
			case 'E':
			case 'e':
				if (east) {
					playerX += 1;
					std::cout << "Moving East" << std::endl;
					validMove = true;

					//reduce time by 1 when moving
					timeRemaining--;
				}
				else {
					std::cout << "You can't go that way" << std::endl;
				}
				break;
			case 'W':
			case 'w':
				if (west) {
					playerX -= 1;
					std::cout << "Moving West" << std::endl;
					validMove = true;

					//reduce time by 1 when moving
					timeRemaining--;
				}
				else {
					std::cout << "You can't go that way" << std::endl;
				}
				break;
			case 'Q':
			case 'q':
				std::cout << "Quitting Game.";
				quit = true;
				validMove = true;
				break;
			default:
				std::cout << "-Invalid Command-" << std::endl;
			}

			//delay before next location \ event
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			if ((happinessLevel <= 0) && !(map[playerY][playerX].getName().std::string::compare(thevoid.getName()) == 0)) {
				//set location to the void
				playerX = 0;
				playerY = 5;
				validMove = true;
				for (int i = 0; i < 5; i++) {
					std::cout << ".";

					std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
				system("CLS");
				std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			}

			//TODO: add real way out of the void.


			//out of time, game over
			if ( timeRemaining <= 0) {

				for (int i = 0; i < 8; i++) {
					std::cout << ".";

					std::this_thread::sleep_for(std::chrono::milliseconds(400));
				}

				system("CLS");

				std::cout << "\n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

				if (phone.inInventory) {
					std::cout << std::endl << "\tSuddenly a chill runs down your spine. Instinctively you reach into your pocket.\n\tYou pull out your phone and look at the time... your shift is supposed to start right now." << std::endl;
				}
				else {
					std::cout << std::endl << "\tA sound like a church bell tolling rings through your mind.\n\tA chill enters the air and goosebumps form on your arms.\n\tYou suddenly feel as if you should be at work right at this moment..." << std::endl;
				}

				std::cout << "\tThe ground starts rumbling as a booming voice echoes \"YOU'RE LATE\"\n\tThe Boss is coming for you, there's nowhere to hide." << std::endl;
				
				if (playerY < 3 || (playerY == 4 && (playerX == 0 || playerX == 2))) {
					
					std::cout << "\tThe building shakes as the roof is torn off. A giant hand reaches down and engulfs you.\n\n\t\t\"TIME TO WORK\"";
				}
				else {
					std::cout << "\tThe sky darkens as a giant hand looms over you. \"TIME TO WORK\"\n\tYou're scooped up and carried away...";
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(3000));

				choice = '0';
				std::cout << "\n\n\t\tGAME OVER" << std::endl;
				validChoice = false;
				while (!validChoice) {
					std::cout << "\t Do you want to try again?\n\t [Y] yes or [N] no: ";
					std::cin >> choice;
					switch (choice)
					{
					case 'Y':
					case 'y':
						std::cout << "\n\t Good luck, you're gonna need it.";
						for (int i = 0; i < 4; i++) {
							std::cout << ".";

							std::this_thread::sleep_for(std::chrono::milliseconds(500));
						}
						gameStart = true;
						validChoice = true;
						validMove = true;
						system("CLS");
						break;
					case 'N':
					case 'n':
						std::cout << "Farewell.";
						for (int i = 0; i < 4; i++) {
							std::cout << ".";

							std::this_thread::sleep_for(std::chrono::milliseconds(500));
						}
						quit = true;
						validChoice = true;
						validMove = true;
						system("CLS");
						break;
					default:
						std::cout << "\t-Invalid Command-" << std::endl;
						break;
					}
				}
				//clear input buffer
				std::cin.ignore();
				std::cin.clear();
			}// end gameover section

			if ((map[playerY][playerX].getName().std::string::compare(office.getName()) == 0)) {

				if (badge.inInventory) {

					std::cout << "You win...\n\n\tReally? How anticlimactic.\n\nIt's like the author ran out of time or something..." << std::endl;

					std::cout << "Farewell.";
					for (int i = 0; i < 4; i++) {
						std::cout << ".";

						std::this_thread::sleep_for(std::chrono::milliseconds(500));
					}
					quit = true;
					validChoice = true;
					validMove = true;
					system("CLS");
				}
			}
			
			
		}// end turn \ location loop
		system("CLS");
	
	}// end game loop

	return 0;
}

std::string mood(int lvl) {
	std::string face;
	
	if (lvl >= 5) {
		face = ":-D";
	}
	else if (lvl == 4) {
		face = ":-)";
	}
	else if (lvl == 3) {
		face = ":-|";
	}
	else if (lvl == 2) {
		face = ":-\\";
	}
	else if (lvl == 1) {
		face = ":-(";
	}
	else {
		face = "X-[";
	}
	return face;
}