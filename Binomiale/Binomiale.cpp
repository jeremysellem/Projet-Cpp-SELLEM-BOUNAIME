/*
 * Binomiale.cpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#include "Binomiale.hpp"

//
double getU(double ecartType, long periodT) {
	return exp(ecartType * sqrt(periodT));
}

//
double getD(double ecartType, long periodT) {
	return exp(-ecartType * sqrt(periodT));
}

// ecarType : volatilité (sigma) | periodT : échénace en années
// Cette fonction retourne p la probabilité de hausse telle que :
// // p = (e^(-rT) - d) / (u - d) = (e^(-rT) - e^(-sigma * T)) / (e^(sigma * T) - e^(-sigma * T))
double calculerProbabiliteHausseU(double ecartType, long periodT, double tauxR) {
	double pu, u, d;
	u = getU(ecartType, periodT);
	d = getD(ecartType, periodT);
	pu = (exp(-tauxR * periodT) - d) / (u - d);
	return pu;
}

double calculerProbabiliteBaisseD(double ecartType, long periodT, double tauxR) {
	return 1 - calculerProbabiliteHausseU(ecartType, periodT, tauxR);
}

double calculerPayOffCallHausseU(double prixSO, double ecartType, long periodT, double prixStrikeK) {
	double u = getU(ecartType, periodT);
	return max(prixSO * u - prixStrikeK, 0.0);
}

double calculerPayOffCallBaisseD(double prixSO, double ecartType, long periodT, double prixStrikeK) {
	double d = getD(ecartType, periodT);
	return max(prixSO * d - prixStrikeK, 0.0);
}

double calculerPayOffPutHausseU(double prixSO, double ecartType, long periodT, double prixStrikeK) {
	double u = getU(ecartType, periodT);
	return max(prixStrikeK - prixSO * u, 0.0);
}

double calculerPayOffPutBaisseD(double prixSO, double ecartType, long periodT, double prixStrikeK) {
	double d = getD(ecartType, periodT);
	return max(prixStrikeK - prixSO * d, 0.0);
}

double getPrixCall(double prixSO, double ecartType, long periodT, double tauxR, double prixStrikeK) {
	double pu, pd, Cu, Cd;
	pu = calculerProbabiliteHausseU(ecartType, periodT, tauxR);
	pd = calculerProbabiliteBaisseD(ecartType, periodT, tauxR);
	Cu = calculerPayOffCallHausseU(prixSO, ecartType, periodT, prixStrikeK);
	Cd = calculerPayOffCallBaisseD(prixSO, ecartType, periodT, prixStrikeK);
	return exp(-tauxR * periodT) * (pu * Cu + pd * Cd);
}

double getPrixPut(double prixSO, double ecartType, long periodT, double tauxR, double prixStrikeK) {
	double pu, pd, Cu, Cd;
	pu = calculerProbabiliteHausseU(ecartType, periodT, tauxR);
	pd = calculerProbabiliteBaisseD(ecartType, periodT, tauxR);
	Cu = calculerPayOffPutHausseU(prixSO, ecartType, periodT, prixStrikeK);
	Cd = calculerPayOffPutBaisseD(prixSO, ecartType, periodT, prixStrikeK);
	return exp(-tauxR * periodT) * (pu * Cu + pd * Cd);
}

string menu() {
	return "\n1 getPrixCall\n2 getPrixPut\n3 exit\nVotre choix : ";
}

void user_getPrixCall() {

	string answer = "";
	cout << "Paramètres du Call :" << endl;
	cout << "Volatilité : ";
	cin >> answer;
	double ecartType = atof(answer.c_str());

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
	double prixS0 = atof(answer.c_str());

	cout << "K : ";
	cin >> answer;
	double prixStrikeK = atof(answer.c_str());

	cout << "R : ";
	cin >> answer;
	double tauxR = atof(answer.c_str());

	cout << "---------------------" << endl;
	cout << "Prix du Call : " << getPrixCall(prixS0, ecartType, periodT, tauxR, prixStrikeK) << endl;
}

void user_getPrixPut() {
	string answer = "";
	cout << "Paramètres du Put :" << endl;
	cout << "Volatilité : ";
	cin >> answer;
	double ecartType = atof(answer.c_str());

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
	double prixS0 = atof(answer.c_str());

	cout << "K : ";
	cin >> answer;
	double prixStrikeK = atof(answer.c_str());

	cout << "R : ";
	cin >> answer;
	double tauxR = atof(answer.c_str());

	cout << "---------------------" << endl;
	cout << "Prix du Put : " << getPrixPut(prixS0, ecartType, periodT, tauxR, prixStrikeK) << endl;
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
					user_getPrixCall();
					break;
				case 2:
					user_getPrixPut();
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
