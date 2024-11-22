#ifndef CLIENT_H
#define CLIENT_H
#include "Compte.h"
#include <string>
using namespace std;

class Client {
private:
    string RIB;           // Identifiant du client (RIB)
    string nom;           // Nom du client
    string prenom;        // Prénom du client
    string MDP;           // Mot de passe
    Compte& compte;       // Référence vers un objet Compte

public:
    // Constructeur
    Client(string, string, string, string, Compte&);

    // Méthode pour accéder au compte
    Compte& getCompte();

    // Getters
    string getRIB() const;
    string getNom() const;
    string getPrenom() const;
    string getMDP() const;
};

#endif // CLIENT_H
