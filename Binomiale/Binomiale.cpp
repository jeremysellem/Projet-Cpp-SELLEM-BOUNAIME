/*
 * Binomiale.cpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#include "Binomiale.hpp"

// Retourne la valeur de u pour une volatilité et une période donnée :
// u = e^(sigma * racine(T))
double getU(double ecartType, long maturite, long periodT) {
	return exp(ecartType * sqrt(maturite/(double)periodT));
}

// Retourne la valeur de d pour une volatilité et une période donnée :
// d = e^(-sigma * racine(T))
double getD(double ecartType, long maturite, long periodT) {
	return 1/getU(ecartType, maturite, periodT);
}

// Retourne le facteur d'actualisation entre deux périodes
double getDiscountFactor(long maturite, long periodT, double tauxR) {
	return exp(tauxR * maturite/(double)periodT);
}

// Arguments  : ecartType : volatilité (sigma) | periodT : échéance en années | taux R  : taux sans risque (%)
// Retourne pu la probabilité de hausse telle que :
// pu = (e^(-rT) - d) / (u - d)
double calculerProbabiliteHausseU(double ecartType, long maturite, long periodT, double tauxR) {
	double pu, u, d;
	u = getU(ecartType, maturite, periodT);
	d = getD(ecartType, maturite, periodT);
	pu = (getDiscountFactor(maturite, periodT, tauxR) - d) / (u - d);
	return pu;
}

// Arguments  : ecartType : volatilité (sigma) | periodT : échéance en années | taux R  : taux sans risque (%)
// Retourne pd la probabilité de baisse telle que :
// pd = 1 - pu
double calculerProbabiliteBaisseD(double ecartType, long maturite, long periodT, double tauxR) {
	return 1 - calculerProbabiliteHausseU(ecartType, maturite, periodT, tauxR);
}

// Retourne le payoff d'un Call :
// payoff = (St - K)+
double calculerPayOffCall(double prixCourant, double prixStrikeK) {
	return max(prixCourant - prixStrikeK, 0.0);
}

// Retourne le payoff d'un Put :
// payoff = (K - St)+
double calculerPayOffPut(double prixCourant, double prixStrikeK) {
	return max(prixStrikeK - prixCourant, 0.0);
}

// Retourne le nombre de noeuds de l'arbre binomiale à periodT périodes :
// nbNoeuds = n * (n + 1) / 2
int getNbNodes(long periodT) {
	return periodT < 0 ? 0 : ((periodT + 1) * (periodT + 2)) / 2;
}

// Retourne le premier noeud de la période dans le graphe (le plus en haut) :
int getFirstNodePeriod(long periodT) {
	return periodT <= 0 ? 0 : getNbNodes(periodT - 1);
}

// Retourne le prix de l'actif selon un chemin de l'arbre :
// v(T, j) = u^j * d^(T - j) * S0
double getUnderlyingPrice(double prixS0, double u, double d, int j, long periodT) {
	return pow(u, j) * pow(d, periodT - j) * prixS0;
}

// Retourne le payoff à un noeud terminal donné du graphe dans le cas d'un Call
double getCallPayoffTerminal(double prixS0, double u, double d, int j, long periodT, double prixStrikeK) {
	return calculerPayOffCall(getUnderlyingPrice(prixS0, u, d, j, periodT), prixStrikeK);
}

// Retourne le payoff à un noeud terminal donné du graphe dans le cas d'un Put
double getPutPayoffTerminal(double prixS0, double u, double d, int j, long periodT, double prixStrikeK) {
	return calculerPayOffPut(getUnderlyingPrice(prixS0, u, d, j, periodT), prixStrikeK);
}

// Retourne le prix d'une option (Call/Put selon argument) suivant les paramètres donnés
double getPrix(double prixS0, double ecartType, long maturite, long periodT, double tauxR, double prixStrikeK, bool isCall) {
	double u, d, pu, pd, Cu, Cd, first;
	int currentNode;

	// Nombre de noeuds dans le graphe, donné par le nombre de périodes
	int nbNodes = getNbNodes(periodT);

	// Calculer les valuers de u, d, pu, pd suivant les paramètres donnés
	u = getU(ecartType, maturite, periodT);
	d = getD(ecartType, maturite, periodT);
	pu = calculerProbabiliteHausseU(ecartType, maturite, periodT, tauxR);
	pd = calculerProbabiliteBaisseD(ecartType, maturite, periodT, tauxR);

	// Construire le graphe complet des prix
	double prices[nbNodes];
	prices[0] = prixS0; // En 0

	// On parcourt l'arbre vers l'avant et on remplit la valeur des noeuds suivants à partir de pu et pd
	for (int t = 0; t < periodT; t++) {

		// On se positionne sur le premier noeud de la période dans le tableau
		currentNode = getFirstNodePeriod(t);

		// Pour chaque noeud de la période
		for (int j = t; j >= 0; j--) {

			// Remplir les prix des deux noeuds suivants
			// Prix en cas de hausse
			prices[currentNode + j + t + 1] = prices[currentNode + j] * u;

			// Prix en cas de baisse
			prices[currentNode + j + t + 2] = prices[currentNode + j] * d;
		}
	}

	// Construire le graphe complet des payoffs, chaque période est une liste
	double payoffs[nbNodes];

	// Calculer les payoffs des noeuds terminaux
	int firstTerminalnode = getFirstNodePeriod(periodT);
	for (int j = periodT; j >= 0; j--) {
		payoffs[firstTerminalnode + periodT - j] = isCall ? getCallPayoffTerminal(prixS0, u, d, j, periodT, prixStrikeK) : getPutPayoffTerminal(prixS0, u, d, j, periodT, prixStrikeK);
	}

	// On parcourt l'arbre des payoffs vers l'arrière en calculant à chaque fois la valeur du noeud à partir des deux suivants
	for (int t = periodT - 1; t >= 0; t--) {

		// On se positionne sur le premier noeud de la période dans le tableau
		currentNode = getFirstNodePeriod(t);

		// Pour chaque noeud de la période, on calcule la moyenne pondérée des deux noeuds suivants
		for (int noeud = currentNode; noeud <= currentNode + t; noeud++)
			payoffs[noeud] = max(getDiscountFactor(maturite, periodT, tauxR) * (pu * payoffs[noeud + t + 1] + pd * payoffs[noeud  + t + 2]), 0.0);
	}

	// On retourne le payoff en 0, valeur de notre Call
	return payoffs[0];
}

string menu() {
	return "\n1 getPrixCall\n2 getPrixPut\n3 exit\nVotre choix : ";
}

void user_getPrixOption(bool isCall) {

	string answer = "";
	string optionType = isCall ? "Call : " : "Put : ";

	cout << "Paramètres du " << optionType << endl;
	cout << "Volatilité : ";
	cin >> answer;
	double ecartType = atof(answer.c_str());

	long maturite, periodT;
	try {
		cout << "Maturité : ";
		cin >> answer;
		maturite = stoi(answer.c_str());

		cout << "Périodes : ";
		cin >> answer;
		periodT = stoi(answer.c_str());
	}
	catch (invalid_argument&) {
		periodT = 1;
	}

	cout << "S0 : ";
	cin >> answer;
	double prixS0 = atof(answer.c_str());

	cout << "K : ";
	cin >> answer;
	double prixStrikeK = atof(answer.c_str());

	cout << "R : ";
	cin >> answer;
	double tauxR = atof(answer.c_str());

	cout << "---------------------" << endl;
	cout << "Prix du " << optionType << getPrix(prixS0, ecartType, maturite, periodT, tauxR, prixStrikeK, isCall) << endl;
}

int main() {

	// L'utilisateur arrive sur le menu principal
	// Tant que sa réponse n'est pas exit on continue
	string answer = "0";
	while (stoi(answer) != 3) {
		cout << menu();
		cin >> answer;
		try {
			switch (stoi(answer)) {
				case 1:
					user_getPrixOption(true);
					break;
				case 2:
					user_getPrixOption(false);
					break;
				case 3:
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
