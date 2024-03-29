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

# define M_PI           3.14159265358979323846  /* pi */

using namespace std;

double calculerD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double loi_normale(double a, double b, double n);
double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerLoiNormale_D1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerLoiNormale_D2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double getPrixCall(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double getPrixPut(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);


void user_getPrixBS(bool isCall);

string BlackAndScholesMenu();

int BlackAndScholesMain();

#endif /* PROJET_BLACKANDSHOLES_BLACKANDSHOLES_HPP_ */
