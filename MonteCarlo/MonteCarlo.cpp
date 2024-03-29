/*
 * MonteCarlo.cpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#include "MonteCarlo.hpp"

double genererNbreLoiNormale() {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution(0.0, 1.0);
    double sample = distribution(generator);
    return sample;
}

list<double> simuler_une_trajectoire(double prixS0, long periodT, double r, double ecartType) {
	double Si;
	list<double> single_list;
	single_list.push_back(prixS0);
	for (double i = 0; i < periodT; i += 0.05) {
		Si = prixS0 * exp((r - (pow(ecartType, 2) / 2)) * periodT + ecartType * sqrt(periodT) * genererNbreLoiNormale());
    	single_list.push_back(Si);
    }
    return single_list;
}

list<list<double> > simuler_N_trajectoire(double prixS0, int N, long periodT, double r, double ecartType) {
    list<list<double> > l;
    list<double> single_list;
    for (int i = 0; i < N; i++) {
    	single_list = simuler_une_trajectoire(prixS0, periodT, r, ecartType);
        l.push_back(single_list);
        single_list.erase(single_list.begin(), single_list.end());
    }
    return l;
}

// Retourne le payoff d'une trajectoire
double calculerPayOff(list<double> l, double strikeK, bool isCall) {
	return isCall ? max(l.back() - strikeK, 0.0) : max(strikeK - l.back(), 0.0);
}

// Retourne la somme des payoffs d'une liste de trajectoires
double calculerPayOffs(list<list<double> > l, double strikeK, bool isCall) {
	list<list<double> >::iterator it;
	double somme = 0.0;
	for (it = l.begin(); it != l.end(); it++)
		somme += calculerPayOff((*it), strikeK, isCall);
	return somme;
}

// Retourne la moyenne des payoffs d'une liste de trajectoires
double calculerMoyennePayOffs(list<list<double> > l, double strikeK, bool isCall) {
	return calculerPayOffs(l, strikeK, isCall) / l.size();
}

// Retourne l'écart type payoffs d'une liste de trajectoires
double calculerEcartTypePayOffs(list<list<double> > l, long N, double strikeK, bool isCall) {
	double moyenne = calculerMoyennePayOffs(l, strikeK, isCall);
	double sommeDesCarres = 0.0;
	list<list<double> >::iterator it;
	for (it = l.begin(); it != l.end(); it++)
		sommeDesCarres += pow(calculerPayOff((*it), strikeK, isCall), 2);

	double variance = sommeDesCarres / N - moyenne * moyenne;
	double ecartType = sqrt(variance);
	return ecartType;
}

tuple<double, double> getPrixMC(double prixS0, long N, long periodT, double r, double ecartType, double strikeK, bool isCall) {
	list<list<double> > trajectoires = simuler_N_trajectoire(prixS0, N, periodT, r, ecartType);
	double prixMC = exp(-r * periodT) * calculerMoyennePayOffs(trajectoires, strikeK, isCall);
	double ecartType_payoffs = calculerEcartTypePayOffs(trajectoires, N, strikeK, isCall);
	return {prixMC, ecartType_payoffs};
}

void user_getPrixOptionMC(bool isCall) {

	string answer = "";
	string optionType = isCall ? "Call : " : "Put : ";

	cout << "Paramètres du " << optionType << endl;
	cout << "Volatilité : ";
	cin >> answer;
	double ecartType = atof(answer.c_str());

	long nbSimulations, periodT;
	try {
		cout << "nbSimulations : ";
		cin >> answer;
		nbSimulations = stoi(answer.c_str());

		cout << "T : ";
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
	auto [result, ecart] = getPrixMC(prixS0, nbSimulations, periodT, tauxR, ecartType, prixStrikeK, isCall);
	cout << "Prix du " << optionType << result << endl;
	cout << "Intervalle de confiance à 95% : [" << result - 1.96 * ecart/sqrt(nbSimulations) << "," << result + 1.96 * ecart/sqrt(nbSimulations) << "]" << endl;
}

string MonteCarloMenu() {
	// Dire bonjour
	cout << "----------------------" << endl;
	cout << "MONTE CARLO MODEL" << endl;
	cout << "----------------------" << endl;
	return "1 Call\n2 Put\n3 Retour menu principal\n4 Exit\n\nVotre choix : ";
}

int MonteCarloMain() {

	// L'utilisateur arrive sur le menu de Binomial
	// Tant que sa réponse n'est pas Exit ou Retour on continue
	string answer = "0";
	while (true) {
		cout << MonteCarloMenu();
		cin >> answer;
		try {
			switch (stoi(answer)) {
				case 1:
					// Pricing d'un Call
					user_getPrixOptionMC(true);
					break;
				case 2:
					// Pricing d'un Put
					user_getPrixOptionMC(false);
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
