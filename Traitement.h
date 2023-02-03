/*************************************************************************
                           Traitement  -  description
                             -------------------
    début                : 16/01/23
    copyright            : (C) 2023$ par ${AUTHOR}$
    e-mail               : ${EMAIL}$
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#ifndef Traitement_H
#define  Traitement_H

//--------------------------------------------------- Interfaces utilisées
#include <vector>
using namespace std;


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Traitement>
//
//
//------------------------------------------------------------------------

class Traitement {
//----------------------------------------------------------------- PUBLIC

public:
    vector <string> section;

//----------------------------------------------------- Méthodes publiques
    void afficherVecteur();
    // Mode d'emploi :
    //
    // Contrat :
    //

    int trouveHeure()const;
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //cette méthode va renvoyer l'heure de l'éxecution de la requête qui
    // fait appel à la méthode
    // Contrat :
    //


    void Decomposition(const string & line);
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //cette méthode va déocrtiquer la ligne afin de sticker chaque attribut dans un string et ainsi
    // remplir l'attribut vector <string> section
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Traitement &operator=(const Traitement &unTraitement);
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Traitement(const Traitement &unTraitement);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Traitement(const string & line);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Traitement();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // Traitement_H
