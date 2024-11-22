#ifndef COMPTE_H
#define COMPTE_H

#include <string>
using namespace std;

class Compte {
private:

    double Solde;         // Solde du compte

public:
    // Constructeur
    Compte(double);

    // Getters

    double getSolde() const;
    void ajouterSolde(double montant);  // Ajouter un montant au solde
    void retirerSolde(double montant);  // Ajouter un montant au solde

};



#endif // COMPTE_H
