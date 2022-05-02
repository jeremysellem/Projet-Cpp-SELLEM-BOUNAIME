/*
 * BlackAndSholes.cpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#include "BlackAndSholes.hpp"

// int simulation_trajectoire_mvt_brownien(){

// }
double calculerD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return (log(prixSt/prixStrikeK) + (tauxR - dividende + ecartType*ecartType/2) * periodT ) / (ecartType * sqrt(periodT));
}

double calculerD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return calculerD1(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) - ecartType * sqrt(periodT);
}

double loi_normale(double a, double b, double n){
    double somme = 0;
    double pas = (b - a)/ n;
    double x = a;
    for (double i=0; i < n ; i++){
        somme += pas * exp(-(x*x)/2)/(sqrt(2*M_PI));
        x += pas;
    }
    return somme;
}

double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-1000000, calculerD1(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
}

double calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-1000000, calculerD2(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
}

double calculerLoiNormale_D1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-1000000, -calculerD1(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
}

double calculerLoiNormale_D2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-1000000, -calculerD2(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
}

double getPrixCall(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return prixSt * calculerLoiNormaleD1(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) - prixStrikeK * exp(-tauxR*periodT) * calculerLoiNormaleD2(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende);
}
double getPrixPut(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return - prixSt * calculerLoiNormale_D1(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) + prixStrikeK * exp(-tauxR*periodT) * calculerLoiNormale_D2(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende);
}

// double getSensibiliteDelta();
// double getSensibiliteGamma();
// double getSensibiliteVega();
// double getSensibiliteRho();
// double getSensibiliteThega();

void user_getPrixBS(bool isCall) {

	string answer = "";
	string optionType = isCall ? "Call : " : "Put : ";

	cout << "Paramètres du " << optionType << endl;
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
	double prixSt = atof(answer.c_str());

	cout << "K : ";
	cin >> answer;
	double prixStrikeK = atof(answer.c_str());

	cout << "R : ";
	cin >> answer;
	double tauxR = atof(answer.c_str());

    cout << "dividende : ";
	cin >> answer;
	double dividende = atof(answer.c_str());

	// Calculer le prix
	double result = isCall ? getPrixCall(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) : getPrixPut(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende);
	cout << "---------------------" << endl;
	cout << "Prix du " << optionType << result << endl;
}

string BlackAndScholesMenu() {
	// Dire bonjour
	cout << "----------------------" << endl;
	cout << "BLACK & SCHOLES MODEL" << endl;
	cout << "----------------------" << endl;
	return "1 Call\n2 Put\n3 Retour menu principal\n4 Exit\n\nVotre choix : ";
}

int BlackAndScholesMain() {

	// L'utilisateur arrive sur le menu de Binomial
	// Tant que sa réponse n'est pas Exit ou Retour on continue
	string answer = "0";
	while (true) {
		cout << BlackAndScholesMenu();
		cin >> answer;
		try {
			switch (stoi(answer)) {
				case 1:
					// Pricing d'un Call
					user_getPrixBS(true);
					break;
				case 2:
					// Pricing d'un Put
					user_getPrixBS(false);
					break;
				case 3:
					// Retour au menu principal
					return 0;
				case 4:
					// Fin du programme
					exit(0);
				default:
					// Pas compris donc on reste continue
					answer = "0";
					break;
			}
		}
		catch (exception&) {
			answer = "0";
		}
	}
	return 0;
}


// int main(){
//     cout<< calculerLoiNormaleD1(100,0.25,5,0.01,100,0);
//     return 0;
// }
