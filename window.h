#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QCheckBox;
class QLabel;
QT_END_NAMESPACE

class Client;
class Compte;

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    void echoChanged(bool checked);

private:
    void MENU();
    void COMPTE();
    void VIREMENT();
    void RETRAIT();
    void VERSEMENT();
    void valide();
    void connection();
    void PAGEconnection();

    // Widgets pour les champs de texte et le pavé numérique
    QLineEdit *idLineEdit;
    QLineEdit *passwordLineEdit;
    QCheckBox *montreMDPCheckBox;
    QPushButton *connexionButton;
    QLabel *info;
    QLabel *nom;
    QLabel *prenom;
    QLabel *RIB;
    QLabel *statusLabel;  // Affiche l'état actuel (bouton cliqué, etc.)

    // Compte
    Compte *compte;
    Compte *compte1;
    Compte *compte2;
    // Clients
    Client *client;
    Client *client1;
    Client *client2;
};

#endif // WINDOW_H
