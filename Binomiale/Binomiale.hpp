/*
 * Binomiale.hpp
 *
 *  Created on: 27 avr. 2022
 *      Authors: Jeremy SELLEM & Mohamed BOUNAIME
 */

#ifndef PROJET_BINOMIALE_BINOMIALE_HPP_
#define PROJET_BINOMIALE_BINOMIALE_HPP_

double calculerProbabiliteHausseU(double ecartType, long periodT);
double calculerProbabiliteBaisseD(double ecartType, long periodT);
double calculerPayOffHausseU(double prixSO, double ecartType, long periodT);
double calculerPayOffBaisseD(double prixSO, double ecartType, long periodT);
double getPrixCall(double prixSO, double ecartType, long periodT, double tauxR, double prixStrikeK);
double getPrixPut(double prixSO, double ecartType, long periodT, double tauxR, double prixStrikeK);

#endif /* PROJET_BINOMIALE_BINOMIALE_HPP_ */
