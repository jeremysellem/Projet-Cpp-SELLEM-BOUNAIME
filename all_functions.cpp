//MonteCarlo.hpp
double genererNbreLoiNormale();
list<double> simuler_une_trajectoire(long periodT, double r, double ecartType, double nbreLoiNormal);
list<list<double>> simuler_N_trajectoire(int N, long periodT, double r, double ecartType, double nbreLoiNormal);
double calculerPayOff(list<double> l, double strikeK, boolean isCall);
double calculerPayOffs(list<list<double>> l, double strikeK, boolean isCall);
double calculerMoyennePayOffs(list<list<double>>, double strikeK, boolean isCall);
double getPrixCall(long periodT, double r, double ecartType, double strikeK);
double getPrixPut(long periodT, double r, double ecartType, double strikeK);

//Binomiale.hpp
double calculerProbabiliteHausseU(double ecartType, long periodT);
double calculerProbabiliteBaisseD(double ecartType, long periodT);
double calculerPayOffHausseU(double prixSO, double ecartType, long periodT);
double calculerPayOffBaisseD(double prixSO, double ecartType, long periodT);
double getPrixCall(double prixSO, double ecartType, long periodT, double tauxR, double prixStrikeK);
double getPrixPut(double prixSO, double ecartType, long periodT, double tauxR, double prixStrikeK);

//BlackAndSholes.cpp (avec et sans dividende)
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
