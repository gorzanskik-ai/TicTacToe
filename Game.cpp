#include <iostream>
#include <Windows.h>
#include "Game.h"

using namespace std;

int Game::Evaluate() { //funkcja heurystyczna X - maksymalizator, O - minimalizator

	if (Win('X') == 'X') //jeœli wygra X dajemy mu wartoœæ +10
		return 10;

	if (Win('O') == 'O') //jesli wygra O dajemy mu wartoœæ -10
		return -10;

	return 0; //gra koñczy siê remisem -> 0
}

void Game::BestMove() { //funkcja która wyznacza najlepsze pole do wstawienia O dla komputera

	int bestVal = -1000;
	int bestMove_i;
	int bestMove_j;
	
	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			if (area[i][j] != 'X' && area[i][j] != 'O') { //sprawdzenie czy pole jest puste

				area[i][j] = 'X'; //wykonanie ruchu

				int moveVal = MinMax(0, false); //obliczanie funkcji heurystycznej dla ruchu

				area[i][j] = '='; //cofanie ruchu

				if (moveVal > bestVal) {	//jesli wartoœc ruchu jest wiêksza ni¿ najlepszego, to uaktualnij wartoœæ

					bestMove_i = i;	//optymalne pole
					bestMove_j = j;
					bestVal = moveVal;
				}
			}
		}
	}

	cout << "Komputer wstawil liczbe w pole: " << "[" << bestMove_i + 1 << "," << bestMove_j + 1 << "]" << endl;
	area[bestMove_i][bestMove_j] = 'O'; //Wstawienie najlepszego ruchu dla komputera
	Sleep(1000);

}

int Game::MinMax(int depth, bool isMax) {

	int score = Evaluate();

	if (score == 10)    // X wygra³
		return score;

	if (score == -10)   // O wygra³
		return score;

	if (IsFull() == false)  // remis
		return 0;

	if (isMax) {        //ruch maksymalizatora

		int best = -1000;

		for (int i = 0; i < size; i++) { //przejœcie po wszystkich komórkach

			for (int j = 0; j < size; j++) {

				if (area[i][j] != 'X' && area[i][j] != 'O') { //sprawdzenie czy komórka jest pusta

					area[i][j] = 'X';   //wykonanie ruchu

					best = max(best, MinMax(depth + 1, !isMax));    //wywo³anie rekurencyjne MinMax i wybranie maksymalnej wartoœci

					area[i][j] = '=';   //cofanie ruchu
				}
			}
		}
		return best;
	}

	else {      //ruch minimalizatora

		int best = 1000;

		for (int i = 0; i < size; i++) {    //przejœcie po wszystkich komórkach

			for (int j = 0; j < size; j++) {

				if (area[i][j] != 'X' && area[i][j] != 'O') {   //sprawdzenie czy komórka jest pusta

					area[i][j] = 'O';   //wykonanie ruchu

					best = min(best, MinMax(depth + 1, !isMax));  //rekurencyjne wywo³anie MinMax i wybranie minimalnej wartoœci

					area[i][j] = '=';   //cofniecie ruchu
				}
			}
		}
		return best;
	}
}
