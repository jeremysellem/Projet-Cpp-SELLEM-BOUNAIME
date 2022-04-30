/*
 * BlackAndSholes.hpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#ifndef PROJET_BLACKANDSHOLES_BLACKANDSHOLES_HPP_
#define PROJET_BLACKANDSHOLES_BLACKANDSHOLES_HPP_

// Fonctions mathématiques
#include <cmath>

// Fonctions usuelles d'affichage
#include <iostream>

// Fonction max()
#include <algorithm>

using namespace std;

int simulation_trajectoire_mvt_brownien();
double calculerD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double getPrixCall(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double getPrixPut(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double getSensibiliteDelta();
double getSensibiliteGamma();
double getSensibiliteVega();
double getSensibiliteRho();
double getSensibiliteThega();

#endif /* PROJET_BLACKANDSHOLES_BLACKANDSHOLES_HPP_ */
