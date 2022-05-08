/*
 * Futures-forwards.cpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#include "Futures_forwards.hpp"

void user_getPrixFutures_forwards(){

	string answer = "";

	cout << "Paramètres du contrat à terme " << endl;

	long periodT;
	try {
		cout << "Périodes : ";
		cin >> answer;
		periodT = stoi(answer.c_str());
	}
	catch (invalid_argument&) {
		periodT = 1;
	}

	cout << "S0 : ";
	cin >> answer;
	double prixSt = atof(answer.c_str());


	cout << "r : ";
	cin >> answer;
	double tauxR = atof(answer.c_str());


	// Calculer le prix
	double result = prixSt * exp(tauxR*periodT);
	cout << "---------------------" << endl;
	cout << "Prix du contrat à terme : "  << result << endl;
}

void Futures_forwardsMenu() {
	// Dire bonjour
	cout << "----------------------" << endl;
	cout << "Futures Forwards MODEL" << endl;
	cout << "----------------------" << endl;
}

int Futures_forwardsMain() {

	// L'utilisateur arrive sur le menu de Futures_forwardsMenu
	// Tant que sa réponse n'est pas Exit ou Retour on continue
	string answer = "0";
	while (true) {
		Futures_forwardsMenu();
		user_getPrixFutures_forwards();
	}
	return 0;
}