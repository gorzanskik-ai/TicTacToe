#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class Game {

	char** area;
	int size;	//rozmiar tablicy
	int x, y;
	char player; //gracz X / O
	int amount;

public:
	Game(int s, int a) {

		size = s;
		area = new char* [size]; //tablica zanków
		player = 'X';	//zaczyna gracz X
		x = 0;
		y = 0;

		for (int i = 0; i < size; i++) //dalsza inicjalizacja tablicy
			area[i] = new char[size];

		amount = a;
	}

	~Game() {

		for (int i = 0; i < size; i++)	//czyszczenie pamiêci po zakoñczonej grze
			delete[] area[i];

		delete[] area;
	}

	void Output() { //Wypisanie widoku rozgrywki

		system("cls");
		cout << "Tic Tac Toe" << endl;

		cout << " -";
		for (int i = 0; i < size; i++)
			cout << "----";

		cout << endl;

		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {
				cout << " | " << area[i][j];
			}

			cout << " | ";
			cout << endl;
			cout << " -";

			for (int i = 0; i < size; i++)
				cout << "----";

			cout << endl;
		}

	}

	void Input() { //Wstawianie X lub O

		int place;

		do {
			cout << "Numer pola: ";
			cin >> place;

			//Wyznaczanie komórki w tablicy na podstawie wybranego miejsca (place) np. 1 -> [0][0]
			int tmp_x = 1;
			for (int i = 0; i < size; i++) {

				if (place >= tmp_x && place <= size * (i + 1)) {

					x = i; //znalezienie rzêdu
					break;
				}
				tmp_x += size;
			}

			int tmp_y = (size * x) + 1;
			for (int j = 0; j < size; j++) {

				if (place == tmp_y) {
					y = j;	//znalezienie kolumny
					break;
				}
				tmp_y++;
			}

			//parametry dla których wstawienie znaku w okreœlone miejsce jest niemo¿liwe
			if (place > size * size) {

				cout << "Nie ma takkiego miejsca!" << endl;
				Sleep(1000);
			}

			else if (area[x][y] == 'X' || area[x][y] == 'O') {

				cout << "Miejsce jest juz zajete" << endl;
				Sleep(1000);
			}
		} while (place > size * size || (area[x][y] == 'X' || area[x][y] == 'O'));

		area[x][y] = player; //wstawienie znaku w okreslone miejsce
	}

	char Win(char player) { //funkcja sprawdzaj¹ca czy gracz wygra³

		//poziomo
		int is = 0;
		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {

				if (area[i][j] == player)
					is++;
			}

			if (is == amount)
				return player;
			is = 0;
		}

		//pionowo
		is = 0;
		for (int j = 0; j < size; j++) {

			for (int i = 0; i < size; i++) {

				if (area[i][j] == player)
					is++;
			}

			if (is == amount)
				return player;
			is = 0;
		}

		//na ukos od lewej do prawej
		is = 0;
		int j = 0;
		for (int i = 0; i < size; i++) {

			if (area[i][j] == player)
				is++;
			j++;
		}

		if (is == amount)
			return player;

		//na ukos od prawej do lewej
		is = 0;
		j = 0;
		for (int i = size - 1; i >= 0; i--) {

			if (area[i][j] == player)
				is++;
			j++;
		}

		if (is == amount)
			return player;

		return '/';
	}

	void TogglePlayer() { //zamiana graczy na przemian

		if (player == 'X')
			player = 'O';
		else
			player = 'X';
	}

	void CurrentPlayer() { //wypisuje który gracz ma ruch

		cout << "Tura gracza: " << player << endl;
	}

	bool IsFull() { //funkcja sprawdzajaca czy wszystkie pola sa zajete, wykorzystywana przy mozliwym remisie

		bool is = true;

		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {

				if (area[i][j] != 'X' && area[i][j] != 'O')
					is = false;
			}
		}

		if (is == false)
			return false;

		else if (is == true)
			return true;
	}

	void Initialization() { //wype³nienie tablicy liczbami dla u³atwienia wyboru pola

		int number = 1;
		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {

				area[i][j] = static_cast<char>(number);
				number++;
			}
		}
	}

	int Evaluate();
	void BestMove();
	int MinMax(int depth, bool isMax);

};