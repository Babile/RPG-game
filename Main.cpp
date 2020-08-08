#include <iostream>
#include <thread>
#include "GameManager.h"

int number = 1;
char input;

bool playGame = false;

void welcomeScreen();
void resetGame(GameManager*);

int main() {
	while (!playGame) {
		welcomeScreen();
		GameManager* game = new GameManager(number);
		system("cls");
		thread printInterface(&GameManager::threadPrintInterface, game);
		thread muveHero(&GameManager::threadMuveHero, game);
		printInterface.join();
		muveHero.join();
		resetGame(game);
	} 
	system("pause");
	return 0;
}

void welcomeScreen() {
	cout << "............................................................................." << endl;
	cout << "............................. Welcome to ...................................." << endl;
	cout << "............................................................................." << endl;
	cout << ".########..########...######............######......###....##.....##.########" << endl;
	cout << ".##.....##.##.....##.##....##..........##....##....##.##...###...###.##......" << endl;
	cout << ".##.....##.##.....##.##................##.........##...##..####.####.##......" << endl;
	cout << ".########..########..##...####.#######.##...####.##.....##.##.###.##.######.." << endl;
	cout << ".##...##...##........##....##..........##....##..#########.##.....##.##......" << endl;
	cout << ".##....##..##........##....##..........##....##..##.....##.##.....##.##......" << endl;
	cout << ".##.....##.##.........######............######...##.....##.##.....##.########" << endl;
	cout << "............................................................................." << endl;
	cout << "............................. Instructions .................................." << endl;
	cout << "..... W - top, S - down, A - left, D - right, SPACE - attack, ESC - exit ...." << endl;
	cout << "............................................................................." << endl;
	cout << "Heroes:" << endl;
	cout << "1. Hunter" << endl;
	cout << "2. Mage" << endl;
	cout << "3. Warrior" << endl;
	do {
		cout << "Enter number to choose a hero: ";
		cin >> number;
		if (!(cin)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You didn't enter number. " << endl;
			continue;
		}
		if (number >= 1 && number <= 3) {
			break;
		}
		cout << "Choose again" << endl;
		continue;
	} while (1);
}

void resetGame(GameManager* game) {
	do {
		cout << "Do you want to play game again? Press y or n" << endl;
		cout << "input: ";
		cin >> input;
		if (input == 'n' || input == 'N') {
			playGame = true;
			cout << "Thank you for playing" << endl;
			break;
		}
		else if (input == 'y' || input == 'Y') {
			delete game;
			system("cls");
			break;
		}
	} while (1);
}