/*
 * Binomiale.hpp
 *
 *  Created on: 27 avr. 2022
 *      Author: Jeremy SELLEM & Mohamed BOUNAIME
 */

#ifndef PROJET_BINOMIALE_BINOMIALE_HPP_
#define PROJET_BINOMIALE_BINOMIALE_HPP_

// Fonctions mathématiques
#include <cmath>

// Fonctions usuelles d'affichage
#include <iostream>

// Fonction max()
#include <algorithm>

using namespace std;

// Retourne la valeur de u pour une volatilité et une période donnée :
// u = e^(sigma * racine(T))
double getU(double ecartType, long maturite, long periodT);

// Retourne la valeur de d pour une volatilité et une période donnée :
// d = e^(-sigma * racine(T))
double getD(double ecartType, long maturite, long periodT);

// Retourne le facteur d'actualisation entre deux périodes
double getDiscountFactor(long maturite, long periodT, double tauxR);

// Arguments  : ecartType : volatilité (sigma) | periodT : échéance en années | taux R  : taux sans risque (%)
// Retourne pu la probabilité de hausse telle que :
// pu = (e^(-rT) - d) / (u - d)
double calculerProbabiliteHausseU(double ecartType, long maturite, long periodT, double tauxR);

// Arguments  : ecartType : volatilité (sigma) | periodT : échéance en années | taux R  : taux sans risque (%)
// Retourne pd la probabilité de baisse telle que :
// pd = 1 - pu
double calculerProbabiliteBaisseD(double ecartType, long maturite, long periodT, double tauxR);

// Retourne le payoff d'un Call :
// payoff = (St - K)+
double calculerPayOffCall(double prixCourant, double prixStrikeK);

// Retourne le payoff d'un Put :
// payoff = (K - St)+
double calculerPayOffPut(double prixCourant, double prixStrikeK);

// Retourne le nombre de noeuds de l'arbre binomiale à periodT périodes :
// nbNoeuds = n * (n + 1) / 2
int getNbNodes(long periodT);

// Retourne le premier noeud de la période dans le graphe (le plus en haut) :
int getFirstNodePeriod(long periodT);

// Retourne le prix de l'actif selon un chemin de l'arbre :
// v(T, j) = u^j * d^(T - j) * S0
double getUnderlyingPrice(double prixS0, double u, double d, int j, long periodT);

// Retourne le payoff à un noeud terminal donné du graphe dans le cas d'un Call
double getCallPayoffTerminal(double prixS0, double u, double d, int j, long periodT, double prixStrikeK);

// Retourne le payoff à un noeud terminal donné du graphe dans le cas d'un Put
double getPutPayoffTerminal(double prixS0, double u, double d, int j, long periodT, double prixStrikeK);

// Retourne le prix d'une option (Call/Put selon argument) suivant les paramètres donnés
double getPrixBino(double prixS0, double ecartType, long maturite, long periodT, double tauxR, double prixStrikeK, bool isCall);

// Affiche le menu principal où l'utilisateur sélectionne ses choix
string BinomialeMenu();

// Cette focntion demande à l'utilisateur les paramètres de l'option
void user_getPrixOptionBino(bool isCall);

// Lance le menu principal
int BinomialeMain();

#endif /* PROJET_BINOMIALE_BINOMIALE_HPP_ */
