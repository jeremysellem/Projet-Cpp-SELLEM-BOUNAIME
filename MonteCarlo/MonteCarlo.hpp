/*
 * MonteCarlo.hpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#ifndef PROJET_MONTECARLO_MONTECARLO_HPP_
#define PROJET_MONTECARLO_MONTECARLO_HPP_

#include <iostream>
#include <list>

// Loi normale
#include <random>

using namespace std;

double genererNbreLoiNormale();

list<double> simuler_une_trajectoire(double prixS0, long periodT, double r, double ecartType);

list<list<double> > simuler_N_trajectoire(double prixS0, int N, long periodT, double r, double ecartType);

// Retourne le payoff d'une trajectoire
double calculerPayOff(list<double> l, double strikeK, bool isCall);

// Retourne la somme des payoffs d'une liste de trajectoires
double calculerPayOffs(list<list<double> > l, double strikeK, bool isCall);

// Retourne la moyenne des payoffs d'une liste de trajectoires
double calculerMoyennePayOffs(list<list<double> > l, double strikeK, bool isCall);

double getPrix(double prixS0, long N, long periodT, double r, double ecartType, double strikeK, bool isCall);

string menu();

void user_getPrixOption(bool isCall);

int main();

#endif /* PROJET_MONTECARLO_MONTECARLO_HPP_ */
