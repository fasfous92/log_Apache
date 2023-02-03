/*************************************************************************
                           TraitementLog  -  description
                             -------------------
    début                : 16/01/2023
    copyright            : (C) 2023$ par FAYALA Mohamed
    e-mail               : fayalla.mohamed@gmail.com
*************************************************************************/

//---------- Interface de la classe <TraitementLog> (fichier TraitementLog.h) ----------------
#ifndef TraitementLog_H
#define  TraitementLog_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <cstring>
#include <stdbool.h>
#include <fstream>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class TraitementLog  {
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void addGraphe(string referer,string cible);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void addHits(string cible);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void addNodes(string cible,int& ordre);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void lire();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void makeDot(string fileName);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void makeHitsInverse();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void afficherHitsInverse();
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool filetype(const string & cible) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void execute();
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
    TraitementLog(string name,bool graphe=false,string dot="",bool exclure=false,int h=-1):fileName(name),doGraphe(graphe),dotName(dot),doExclure(exclure),heure(h){};
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TraitementLog();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
map<pair<string,string>,int> graphe; //key=(referer,cible) , val = nb de fois on a accédé à la cible à partir de ce referer
map<string,int> hits; //key=noeud val=nb de hits
multimap<int,string,greater<int>> hitsInverse;
map<string,int> nodes ; // contient les nodes comme clés et les valeurs sont l'ordre d'ajout (commence de 0)
bool doGraphe,doExclure;
int heure;
string fileName,dotName;

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // TraitementLog_H
