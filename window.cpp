#include "window.h"
#include "Client.h"
#include "Compte.h"
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDialog>

Window::Window(QWidget *parent)
    : QWidget(parent),

    compte(new  Compte(5000)),
    compte1(new  Compte(8000)),
    compte2(new Compte(10000)),

    client(new Client("FR123", "KOCHBATI", "SLIM", "123", *compte)),
    client1(new Client("FR1234", "SBIAI", "AMIR", "1234", *compte1)),
    client2(new Client("FR12345", "KHELFA", "RIYAD", "12345", *compte2))


{
setWindowTitle("MAZE BANK");

// Création des widgets
idLineEdit = new QLineEdit;
idLineEdit->setPlaceholderText("Identifiant");
idLineEdit->setMaxLength(9);

passwordLineEdit = new QLineEdit;
passwordLineEdit->setPlaceholderText("Mot de passe");
passwordLineEdit->setEchoMode(QLineEdit::Password);

montreMDPCheckBox = new QCheckBox("Afficher Mot de Passe");
connect(montreMDPCheckBox, &QCheckBox::toggled, this, &Window::echoChanged);

connexionButton = new QPushButton("Connexion");
connexionButton->setEnabled(false); // Le bouton est désactivé au départ
connect(connexionButton, &QPushButton::clicked, this, &Window::connection);

statusLabel = new QLabel;

// Disposition des widgets
QVBoxLayout *mainLayout = new QVBoxLayout;
mainLayout->addWidget(idLineEdit);
mainLayout->addWidget(passwordLineEdit);
mainLayout->addWidget(montreMDPCheckBox);
mainLayout->addWidget(connexionButton);
mainLayout->addWidget(statusLabel);
setLayout(mainLayout);

// Connexion des signaux
connect(idLineEdit, &QLineEdit::textChanged, this, &Window::valide);
connect(passwordLineEdit, &QLineEdit::textChanged, this, &Window::valide);



}

void Window::echoChanged(bool checked)
{
    passwordLineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void Window::valide()
{
    connexionButton->setEnabled(!idLineEdit->text().isEmpty() && !passwordLineEdit->text().isEmpty());
}

void Window::connection()
{
    // Vérification de l'identifiant et du mot de passe
    if ((idLineEdit->text() == QString::fromStdString(client->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client->getMDP())) ||
        (idLineEdit->text() == QString::fromStdString(client1->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client1->getMDP())) ||
        (idLineEdit->text() == QString::fromStdString(client2->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client2->getMDP())))
    {
        statusLabel->setText("Connexion réussie !");
        statusLabel->setStyleSheet("color: green;");

        // Connecter le bouton "Retour" à une fonction pour fermer la fenêtre et revenir au menu
        connect(connexionButton, &QPushButton::clicked, this, [=]() {
            this->close(); // Fermer la fenêtre de connexion actuelle
            MENU();
        });

    } else {
        statusLabel->setText("Identifiant et/ou mot de passe incorrect !");
        statusLabel->setStyleSheet("color: red;");
    }
}

void Window::MENU()
{
    QDialog *Appmenu = new QDialog(this);  // Fenêtre modale ou non
    Appmenu->setWindowTitle("Menu");

    QGridLayout *menuLayout = new QGridLayout;


    QPushButton *voirCOMPTE = new QPushButton("Compte");
    connect(voirCOMPTE, &QPushButton::clicked, this, [=]() {
        Appmenu->close();  // Fermer la fenêtre Menu
        COMPTE();           // Ouvrir la fenêtre du compte
    });
    menuLayout->addWidget(voirCOMPTE, 0, 1);

    QPushButton *voirVersement = new QPushButton("Versement");
    connect(voirVersement, &QPushButton::clicked, this, [=]() {
        Appmenu->close();  // Fermer la fenêtre Menu
        VERSEMENT();           // Ouvrir la fenêtre du compte
    });
    menuLayout->addWidget(voirVersement, 1, 1);


    QPushButton *voirRetrait = new QPushButton("Retrait");
    connect(voirRetrait, &QPushButton::clicked, this, [=]() {
        Appmenu->close();  // Fermer la fenêtre Menu
        RETRAIT();           // Ouvrir la fenêtre du compte
    });
    menuLayout->addWidget(voirRetrait, 2, 1);

    QPushButton *voirVirement = new QPushButton("Virement");
    connect(voirVirement, &QPushButton::clicked, this, [=]() {
        Appmenu->close();  // Fermer la fenêtre Menu
        VIREMENT();           // Ouvrir la fenêtre du compte
    });
    menuLayout->addWidget(voirVirement, 3, 1);

    QPushButton *deco = new QPushButton("Déconnexion");
    connect(deco, &QPushButton::clicked, this, [=]() {
        Appmenu->close();  // Fermer la fenêtre Menu
        Window();           // Ouvrir la fenêtre du compte
    });
    menuLayout->addWidget(deco, 4, 1);


    Appmenu->setLayout(menuLayout);
    Appmenu->exec();
}

void Window::COMPTE()
{

    // Créer une fenêtre de dialogue pour afficher les informations du compte
    QDialog *Compte = new QDialog(this);
    Compte->setWindowTitle("Compte");

    // Créer les QLabel pour afficher les informations du compte
    QLabel *info = new QLabel("Informations du compte");

    // Vérifier quel client est connecté
    Client *clientconnecte = nullptr;
    if (idLineEdit->text() == QString::fromStdString(client->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client->getMDP())) {
        clientconnecte = client;
    } else if (idLineEdit->text() == QString::fromStdString(client2->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client2->getMDP())) {
        clientconnecte = client2;
    }    else{
        clientconnecte = client1;
    }


        // Récupérer les informations du client connecté
        QLabel *nom = new QLabel("Nom : " + QString::fromStdString(clientconnecte->getNom()));
        QLabel *prenom = new QLabel("Prénom : " + QString::fromStdString(clientconnecte->getPrenom()));
        QLabel *RIB = new QLabel("RIB : " + QString::fromStdString(clientconnecte->getRIB()));
        QLabel *solde = new QLabel("Solde : " + QString::number(clientconnecte->getCompte().getSolde(), 'f', 2));


        // Créer le bouton "Retour" pour revenir au menu principal
        QPushButton *Retour = new QPushButton("Retour");

        // Connecter le bouton "Retour" à une fonction pour fermer la fenêtre et revenir au menu
        connect(Retour, &QPushButton::clicked, this, [=]() {
            Compte->close(); // Fermer la fenêtre de dialogue
            MENU();          // Ouvrir le menu principal
        });

        // Créer un layout pour organiser les QLabel et le bouton dans la fenêtre de dialogue
        QVBoxLayout *compteLayout = new QVBoxLayout;
        compteLayout->addWidget(info);
        compteLayout->addWidget(nom);
        compteLayout->addWidget(prenom);
        compteLayout->addWidget(RIB);
        compteLayout->addWidget(solde);
        compteLayout->addWidget(Retour);

        // Appliquer le layout à la fenêtre de dialogue
        Compte->setLayout(compteLayout);

        // Afficher la fenêtre de dialogue
        Compte->exec();


}


void Window::VERSEMENT()
{
    QDialog *Versement = new QDialog(this);
    Versement->setWindowTitle("Versement");


    // Créer les QLabel pour afficher les informations du compte
    QLabel *maxmontant = new QLabel ("10000€ maximum");
    QLineEdit *montant = new QLineEdit;
    QLabel *montantLabel = new QLabel;
    QPushButton *verser = new QPushButton("Valider");

    // Créer le bouton "Retour" pour revenir au menu principal
    QPushButton *Retour = new QPushButton("Retour");

    // Connecter le bouton "Retour" à une fonction pour fermer la fenêtre et revenir au menu
    connect(Retour, &QPushButton::clicked, this, [=]() {
        Versement->close(); // Fermer la fenêtre de dialogue
        MENU();          // Ouvrir le menu principal
    });


    // Vérifier quel client est connecté
    Client *clientconnecte = nullptr;
    if (idLineEdit->text() == QString::fromStdString(client->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client->getMDP())) {
        clientconnecte = client;
    } else if (idLineEdit->text() == QString::fromStdString(client2->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client2->getMDP())) {
        clientconnecte = client2;
    }    else{
        clientconnecte = client1;
    }

    // Fonction de validation du versement
    connect(verser, &QPushButton::clicked, [this, montant, montantLabel, clientconnecte]() {
        double montantValeur = montant->text().toDouble();  // Convertir QLineEdit en double
        if (montantValeur <= 0 || montantValeur > 10001) {
            montantLabel->setText("Montant incorrect !");
            montantLabel->setStyleSheet("color: red;");
        } else {
            clientconnecte->getCompte().ajouterSolde(montantValeur);  // retirer le montant au solde du client
            montantLabel->setText("Versement effectué !");
            montantLabel->setStyleSheet("color: green;");
        }
    });

    // Créer un layout pour organiser les QLabel et le bouton dans la fenêtre de dialogue
    QVBoxLayout *versementLayout = new QVBoxLayout;
    versementLayout->addWidget(maxmontant);
    versementLayout->addWidget(montant);
    versementLayout->addWidget(montantLabel);
    versementLayout->addWidget(verser);
    versementLayout->addWidget(Retour);


    // Appliquer le layout à la fenêtre de dialogue
    Versement->setLayout(versementLayout);

    Versement->exec();

}

void Window::RETRAIT()
{
    QDialog *Retrait = new QDialog(this);
    Retrait->setWindowTitle("Retrait");

    // Créer les QLabel pour afficher les informations du compte
    QLabel *montantMessage = new QLabel ("Entrez le montant a retirer:");
    QLineEdit *montant = new QLineEdit;
     QLabel *montantLabel = new QLabel;
    QPushButton *retirer = new QPushButton("Valider");

    // Créer le bouton "Retour" pour revenir au menu principal
    QPushButton *Retour = new QPushButton("Retour");

    // Connecter le bouton "Retour" à une fonction pour fermer la fenêtre et revenir au menu
    connect(Retour, &QPushButton::clicked, this, [=]() {
        Retrait->close(); // Fermer la fenêtre de dialogue
        MENU();          // Ouvrir le menu principal
    });

    // Vérifier quel client est connecté
    Client *clientconnecte = nullptr;
    if (idLineEdit->text() == QString::fromStdString(client->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client->getMDP())) {
        clientconnecte = client;
    } else if (idLineEdit->text() == QString::fromStdString(client2->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client2->getMDP())) {
        clientconnecte = client2;
    }
    else{
        clientconnecte = client1;
    }

connect(retirer, &QPushButton::clicked, [this, montant, montantLabel, clientconnecte]() {
    double montantValeur = montant->text().toDouble();  // Convertir QLineEdit en double
    if (montantValeur <= 0 || montantValeur > 10000) {
        montantLabel->setText("Montant incorrect !");
        montantLabel->setStyleSheet("color: red;");
    } else {
        clientconnecte->getCompte().retirerSolde(montantValeur);
        montantLabel->setText("Retrait effectué !");
        montantLabel->setStyleSheet("color: green;");
    }
   });

    // Créer un layout pour organiser les QLabel et le bouton dans la fenêtre de dialogue
    QVBoxLayout *retraitLayout = new QVBoxLayout;
    retraitLayout->addWidget(montantMessage);
    retraitLayout->addWidget(montant);
    retraitLayout->addWidget(montantLabel);
    retraitLayout->addWidget(retirer);
    retraitLayout->addWidget(Retour);


    // Appliquer le layout à la fenêtre de dialogue
    Retrait->setLayout(retraitLayout);

    Retrait->exec();

}

void Window::VIREMENT()
{
    QDialog *Virement = new QDialog(this);
    Virement->setWindowTitle("Virement");

    // Créer les QLabel pour afficher les informations du compte
    QLabel *ribMessage = new QLabel("Entrez le RIB du destinataire:");
    QLineEdit *rib = new QLineEdit;
    QLabel *montantautoLabel = new QLabel("Entrez le montant du virement:");
    QLineEdit *montantvirer = new QLineEdit;
    QLabel *montantLabel = new QLabel;
    QPushButton *verser = new QPushButton("Valider");

    // Créer le bouton "Retour" pour revenir au menu principal
    QPushButton *Retour = new QPushButton("Retour");

    // Connecter le bouton "Retour" à une fonction pour fermer la fenêtre et revenir au menu
    connect(Retour, &QPushButton::clicked, this, [=]() {
        Virement->close(); // Fermer la fenêtre de dialogue
        MENU();           // Ouvrir le menu principal
    });

    // Vérifier quel client est connecté
    Client *clientconnecte = nullptr;
    if (idLineEdit->text() == QString::fromStdString(client->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client->getMDP())) {
        clientconnecte = client;
    } else if (idLineEdit->text() == QString::fromStdString(client2->getRIB()) && passwordLineEdit->text() == QString::fromStdString(client2->getMDP())) {
        clientconnecte = client2;
    } else {
        clientconnecte = client1;
    }

    // Fonction de validation du virement
    connect(verser, &QPushButton::clicked, [this, rib, montantvirer, montantLabel, clientconnecte]() {
        double montantValeur = montantvirer->text().toDouble();  // Convertir QLineEdit en double
        QString destinataireRIB = rib->text();

        if (montantValeur <= 0 || montantValeur > 10000) {
            montantLabel->setText("Montant incorrect !");
            montantLabel->setStyleSheet("color: red;");
        } else if (clientconnecte->getCompte().getSolde() < montantValeur) {
            montantLabel->setText("Solde insuffisant !");
            montantLabel->setStyleSheet("color: red;");
        } else {
            // Chercher le client destinataire par RIB
            Client *clientDestinataire = nullptr;
            if (destinataireRIB == QString::fromStdString(client->getRIB())) {
                clientDestinataire = client;
            } else if (destinataireRIB == QString::fromStdString(client1->getRIB())) {
                clientDestinataire = client1;
            } else if (destinataireRIB == QString::fromStdString(client2->getRIB())) {
                clientDestinataire = client2;
            }

            if (clientDestinataire) {
                // Effectuer le virement
                clientconnecte->getCompte().retirerSolde(montantValeur);   // Retirer du compte de l'expéditeur
                clientDestinataire->getCompte().ajouterSolde(montantValeur); // Ajouter au compte du destinataire

                montantLabel->setText("Virement effectué !");
                montantLabel->setStyleSheet("color: green;");
            } else {
                montantLabel->setText("RIB du destinataire invalide !");
                montantLabel->setStyleSheet("color: red;");
            }
        }
    });

    // Créer un layout pour organiser les QLabel et le bouton dans la fenêtre de dialogue
    QVBoxLayout *virementLayout = new QVBoxLayout;
    virementLayout->addWidget(ribMessage);
    virementLayout->addWidget(rib);
    virementLayout->addWidget(montantautoLabel);
    virementLayout->addWidget(montantvirer);
    virementLayout->addWidget(montantLabel);
    virementLayout->addWidget(verser);
    virementLayout->addWidget(Retour);

    // Appliquer le layout à la fenêtre de dialogue
    Virement->setLayout(virementLayout);

    Virement->exec();
}
