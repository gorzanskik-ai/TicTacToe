#include <iostream>
#include "Game.h"

using namespace std;

int main() {

	int size, choice, choice2, amount;

	cout << "Menu" << endl;				//Menu rozgrywki
	cout << "----------------------" << endl;
	cout << "1. Gra dwuosobowa" << endl;	//Tryby gry do wyboru
	cout << "2. Zagraj z komputerem" << endl;
	cout << "3. Zamknij gre" << endl;
	cout << "----------------------" << endl;

	do {
		cout << "Wybor: ";
		cin >> choice;

		switch (choice) {

		case 1: {	//gra dwuosobowa

			cout << "Rozmiar planszy: ";
			cin >> size;
			cout << "Ilosc znakow w linii: ";
			cin >> amount;

			Game g1(size, amount); //stworzenie gry o określonym rozmiarze (size x size)

			while (1) {

				g1.Output();
				g1.CurrentPlayer();
				g1.Input();

				//sprawdzenie czy któryś z graczy wygrał lub po wypełnieniu wszystkich pól bez wygranej -> remis
				if (g1.Win('X') == 'X') {
					g1.Output();
					cout << "Wygral gracz X" << endl;
					break;
				}

				if (g1.Win('O') == 'O') {
					g1.Output();
					cout << "Wygral gracz O" << endl;
					break;
				}

				if (g1.IsFull() == true) {
					g1.Output();
					cout << "Remis" << endl;
					break;
				}

				g1.TogglePlayer(); //zmiana gracza
			}
		}
			  break;

		case 2: {		//gra z komputerem

			cout << "Rozmiar planszy: ";
			cin >> size;
			cout << "Ilosc znakow w rzedzie: ";
			cin >> amount;

			Game g2(size, amount); //stworzenie gry o określonym rozmiarze (size x size)

			system("cls");

			do {
				cout << "-------------------" << endl;
				cout << "1. Zaczyna gracz" << endl;		//kto pierwszy zaczyna
				cout << "2. Zaczyna komputer" << endl;
				cout << "-------------------" << endl;
				cout << "Wybor: ";
				cin >> choice2;

				switch (choice2) {

				case 1: {		//zaczyna gracz

					while (1) {

						g2.Output();
						g2.CurrentPlayer();
						g2.Input();

						if (g2.Win('X') == 'X') {
							g2.Output();
							cout << "Wygral gracz X" << endl;
							break;
						}

						if (g2.IsFull() == true) {
							g2.Output();
							cout << "Remis" << endl;
							break;
						}

						g2.BestMove();

						if (g2.Win('O') == 'O') {
							g2.Output();
							cout << "Wygral komputer O" << endl;
							break;
						}

						if (g2.IsFull() == true) {
							g2.Output();
							cout << "Remis" << endl;
							break;
						}

					}
					break;
				}
				case 2: {		//zaczyna komputer

					while (1) {

						g2.Output();

						g2.BestMove();

						if (g2.Win('O') == 'O') {
							g2.Output();
							cout << "Wygral komputer O" << endl;
							break;
						}

						if (g2.IsFull() == true) {
							g2.Output();
							cout << "Remis" << endl;
							break;
						}

						g2.Output();

						g2.CurrentPlayer();

						g2.Input();

						if (g2.Win('X') == 'X') {
							g2.Output();
							cout << "Wygral gracz X" << endl;
							break;
						}

						if (g2.IsFull() == true) {
							g2.Output();
							cout << "Remis" << endl;
							break;
						}
					}
				}
					  break;

				default:
					cout << "Niepoprawny numer wyboru!" << endl;
					break;
				}

			} while (choice2 > 2);
		}
			  break;

		case 3:
			exit(0);
			break;

		default:
			cout << "Niepoprawny numer wyboru!" << endl;
		}
	} while (choice > 3);

	return 0;
}


