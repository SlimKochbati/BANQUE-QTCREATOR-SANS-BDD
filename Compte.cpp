#include "Compte.h"
#include "Client.h"

Compte::Compte(double solde) {
    Solde = solde;
}




double Compte::getSolde() const {
    return Solde;
}


// Ajouter un montant au solde
void Compte::ajouterSolde(double montant) {
    Solde += montant;
}

// Ajouter un montant au solde
void Compte::retirerSolde(double montant) {
    Solde -= montant;
}



