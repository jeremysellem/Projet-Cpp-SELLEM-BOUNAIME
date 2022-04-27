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

using namespace std;

double genererNbreLoiNormale();
list<double> simuler_une_trajectoire(long periodT, double r, double ecartType, double nbreLoiNormal);
list<list<double>> simuler_N_trajectoire(int N, long periodT, double r, double ecartType, double nbreLoiNormal);
double calculerPayOff(list<double> l, double strikeK, bool isCall);
double calculerPayOffs(list<list<double>> l, double strikeK, bool isCall);
double calculerMoyennePayOffs(list<list<double>>, double strikeK, bool isCall);
double getPrixCall(long periodT, double r, double ecartType, double strikeK);
double getPrixPut(long periodT, double r, double ecartType, double strikeK);

#endif /* PROJET_MONTECARLO_MONTECARLO_HPP_ */
