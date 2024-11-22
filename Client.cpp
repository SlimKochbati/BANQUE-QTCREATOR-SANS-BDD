#include "Client.h"
#include "Compte.h"
Client::Client(string id, string Nom, string Prenom, string monMDP , Compte& sonCompte ) : compte (sonCompte) {


    RIB = id;
    nom = Nom;
    prenom = Prenom;
    MDP = monMDP;
    // compte = sonCompte;


}

string Client::getNom() const {
    return nom;
}

string Client::getRIB() const {
    return RIB;
}

string Client::getPrenom() const {
    return prenom;
}


string Client::getMDP() const {
    return MDP;
}

// Client.cpp
Compte& Client::getCompte() {
    return compte;  // Retourne l'objet Compte
}

