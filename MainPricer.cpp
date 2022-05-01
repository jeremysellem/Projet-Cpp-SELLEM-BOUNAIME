/*
 * MainPricer.cpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#include <iostream>
#include "Binomiale/Binomiale.cpp"
#include "BlackAndSholes/BlackAndSholes.cpp"
#include "MonteCarlo/MonteCarlo.cpp"

using namespace std;

string MainMenu() {
	// Dire bonjour
	cout << "---------" << endl;
	cout << "MAIN MENU" << endl;
	cout << "---------" << endl;
	return "    1 Binomial Model\n    2 Black & Scholes\n    3 Monte Carlo\n    4 Futures/Forward\n    5 Exit\n\nVotre choix : ";
}

int main() {

	// L'utilisateur arrive sur le menu principal
	// Tant que sa réponse n'est pas exit on continue
	string answer = "0";
	while (true) {
		cout << MainMenu();
		cin >> answer;
		try {
			switch (stoi(answer)) {
				case 1:
					// Lancer le menu principal du Binomial Model
					BinomialeMain();
					break;
				case 2:
					// Lancer le menu principal de Black & Scholes
					BlackAndScholesMain();
					break;
				case 3:
					// Lancer le menu principal de Black & Scholes
					MonteCarloMain();
					break;
				case 4:
					// Lancer le menu principal des contrats à terme
					cout << "Futures/Forward not imlplemented yet" << endl;
					break;
				case 5:
					// Exit
					return 0;
				default:
					answer = "0";
					break;
			}
		}
		catch (exception&) {
			answer = "0";
		}
	};


}
