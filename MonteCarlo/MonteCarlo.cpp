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
	double G = genererNbreLoiNormale();
	double Si;
	list<double> single_list;
	single_list.push_back(prixS0);
    for (long i = 1; i < periodT; i++) {
    	Si = prixS0 * exp((r - (ecartType / 2)) * i + ecartType * sqrt(i) * genererNbreLoiNormale());
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
	return isCall ? max(*l.end() - strikeK, 0.0) : max(strikeK - *l.end(), 0.0);
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

double getPrixCall(double prixS0, long periodT, double r, double ecartType, double strikeK) {
	int N = 1000;
	list<list<double> > trajectoires = simuler_N_trajectoire(prixS0, N, periodT, r, ecartType);
	double moyenne_payoffs = calculerMoyennePayOffs(trajectoires, strikeK, true);
	return exp(-r * periodT) * moyenne_payoffs;
}

double getPrixPut(double prixS0, long periodT, double r, double ecartType, double strikeK) {
	int N = 1000;
	list<list<double> > trajectoires = simuler_N_trajectoire(prixS0, N, periodT, r, ecartType);
	double moyenne_payoffs = calculerMoyennePayOffs(trajectoires, strikeK, false);
	return exp(-r * periodT) * moyenne_payoffs;
}

int main() {
	int N  = 40;
	double prixS0 = 100;
	long periodT = 50;
	double r = 0.02;
	double ecartType = 0.25;
	list<list<double> > trajectoires = simuler_N_trajectoire(prixS0, N, periodT, r, ecartType);
	list<list<double> >::iterator it;
	list<double>::iterator it2;
	for (it = trajectoires.begin(); it != trajectoires.end(); it++) {
		for (it2 = (*it).begin(); it2 != (*it).end(); it2++) {
			cout << (*it2) << ",";
		}
		cout << endl;
	}
	return 0;
}
