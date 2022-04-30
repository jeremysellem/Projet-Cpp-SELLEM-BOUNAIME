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

double loi_normale(double a, double b, int n){
    double somme = 0;
    float pas = (b - a)/ n;
    int x = a;
    for (int i=0; i < n ; i++){
        somme += pas * exp(-(x*x)/2)/(sqrt(2*3.14));
        x += pas;
    }
    return somme;
}

double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-10*exp(1000), calculerD1(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
}

double calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-10*exp(1000), calculerD2(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
}

double calculerLoiNormale_D1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-10*exp(1000), calculerD1(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
}

double calculerLoiNormale_D2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
    return loi_normale(-10*exp(1000), calculerD2(prixSt, ecartType, periodT, tauxR, prixStrikeK, dividende) , 10000000);
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

	cout << "---------------------" << endl;
	cout << "Prix du Call : " << getPrixCall(prixSt, ecartType, periodT, tauxR, prixStrikeK,dividende) << endl;

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

	cout << "---------------------" << endl;
	cout << "Prix du Put : " << getPrixPut(prixSt, ecartType, periodT, tauxR, prixStrikeK,dividende) << endl;
}

string menu() {
	return "\n1 getPrixCall\n2 getPrixPut\n3 exit\nVotre choix : ";
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
