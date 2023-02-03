/*************************************************************************
                           TraitementLog  -  description
                             -------------------
    début                : 16/01/2023$
    copyright            : (C) 2023$ par ${AUTHOR}$
    e-mail               : ${EMAIL}$
*************************************************************************/

//---------- Réalisation de la classe <${ TraitementLog}> (fichier TraitementLog.cpp.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <iostream>
#include <stdbool.h>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "TraitementLog.h"
#include "Traitement.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TraitementLog::addGraphe(string referer,string cible)
// Algorithme :
//
{
    if(!graphe.count(make_pair(referer,cible))) graphe[make_pair(referer,cible)]=1;
    else graphe[make_pair(referer,cible)]++;
} //Fin addGraphe

void TraitementLog::addHits( string cible)
// Algorithme :
//
{
    if(!hits.count(cible)) hits[cible]=1;
    else hits[cible]++;
} //Fin addGraphe

void TraitementLog::addNodes(string cible,int& ordre)
// Algorithme :
//
{
    if(!nodes.count(cible)) {
        nodes[cible] = ordre;
        ordre++;
    }

}//Fin addNodes

void TraitementLog::makeHitsInverse()
// Algorithme :
//
{
    map<string,int>::iterator it;
    for(it=hits.begin();it!=hits.end();it++){
        hitsInverse.insert(make_pair(it->second,it->first));
    }
}// End afficherHits

void TraitementLog::makeDot(string fileName)
// Algorithme :
//
{
    ofstream file(fileName);
    if(!file){
        cout<<"Erreur ouverture de <"<<fileName<<">"<<endl;
        return;
    }
    file<<"digraph{"<<endl;
    map<string,int>::iterator it1;
    for(it1=nodes.begin();it1!=nodes.end();it1++){
        file<<"node"<<it1->second<<" [label=\""<<it1->first<<"\"];"<<endl;
    }
    map<pair<string,string>,int>::iterator it;
    for(it=graphe.begin();it!=graphe.end();it++){
        file<<"node"<<nodes[it->first.first]<<" -> node"<< nodes[it->first.second]<<" [label=\""<<it->second<<"\"];"<<endl;
    }
    file<<"}"<<endl;
    cout<<"Dot-file "<<fileName<<" generated"<<endl;
    file.close();
}// End afficherGraphe


void TraitementLog::afficherHitsInverse()
// Algorithme :
//
{
    // affichage par ordre croissant des hits
    // si égalité de nombre de hits par ordre croissant des noms
    multimap<int,string>::iterator it;
    int nb=0;
    for(it=hitsInverse.begin();it!=hitsInverse.end();it++){
        cout<<it->second<<" ("<<it->first<<" hits)"<<endl ;
        nb++;
        if(nb==10) break;
    }
}// End afficherHitsInverse

bool TraitementLog::filetype(const string & cible) const {
    string except = "css,jpeg,jpg,png,gif,js";
    vector<string> exceptions;
    std::size_t prev = 0, pos;
    while ((pos = except.find_first_of(",", prev)) != std::string::npos) //string::npos is the end of the line
    {
        if (pos > prev)
            exceptions.push_back(except.substr(prev, pos - prev));
        prev = pos + 1;

    }
    if (prev < except.length())
        exceptions.push_back(except.substr(prev, std::string::npos));
    // Maintenant notre vector exceptions a tous les exceptions à verifier sur la cible (en paramètre)
    // nous allons réaliser une for loop qui va voir si l'une des exception existe dans la ligne ou pas

    vector <string>::iterator parcours=exceptions.begin();
    int posi;
    while(parcours!=exceptions.end()){
        if(cible.find(*parcours)!=std::string::npos)
            return true;
        parcours++;
    }
    return false;

}//---Fin--filetype

void TraitementLog::lire()
// Algorithme :
//
{
    string  offset="http://intranet-if.insa-lyon.fr";
    //cout<<"Saisissez une url de base dans la première ligne d'un fichier config.txt"<<endl;
    ifstream file, configFile;
    file.open(fileName);
    configFile.open("config.txt");
    if(!file) {
        //si erreur d'ouverture de file
        cout << "erreur ouverture du fichier "<<fileName<<endl;
        file.close();
        configFile.close();
        return;
    }
    if(!configFile){
        // si erreur d'ouverture du fichier config.txt on prend un url de base standard t on ferme le ifstream configFile
        cout << "erreur ouverture du fichier config.txt"<<endl;
        cout<<"Url de base pris par défaut : "<<endl;
        cout<<"http://intranet-if.insa-lyon.fr"<<endl;
        configFile.close();
    }else{
        // sinon l'offset est la première ligne de config.txt et on ferme le ifstream configFile
        getline(configFile,offset);
        configFile.close();
    }
    string line;
    int ordre=0 ,heureLog;
    string extension  =".html";
    while (!file.eof())
    {
        getline(file, line); // on lit le fichier .log ligne par ligne
        if(line=="") break; // si la ligne est vide on arrête la lecture
        Traitement traitementLigne=Traitement(line); // pour séparer les diférents éléments de la ligne
        if(traitementLigne.section.size()<=11) continue;
        if(traitementLigne.section[8]=="200") // si sreturn code HTTP est égal à 200 on continue sinon on passe à la ligne d'aprés
        {
            //on mettra dans referer l'adresse de la source en enlevant l'offset porposé par l'utilisateur
            string referer;
            if(traitementLigne.section[10].substr(0,offset.size()).find(offset)!= std::string::npos)
                // si le referer contient l'url de référence (au tout début d'où le substr dans la condition du if)
                referer=traitementLigne.section[10].substr(offset.size(),traitementLigne.section[10].size());
            else
                // sinon on prend le lien en entier
                referer=traitementLigne.section[10];

            string cible=traitementLigne.section[6]; // on récupère la cible
            heureLog = traitementLigne.trouveHeure(); // on récupère l'heure

            // si on va exclure les fichiers image, css et javascript et que la cible a une telle extension on passe à la ligne suivante
            if(doExclure && filetype(cible)) continue;

            // si on va pas faire une sélection par heure
            // ou si on va faire une sélection par heure et que l'heure de la ligne de log est la même qu'on veut choisir
            //on fait notre traitement
            if(heure==-1 || heureLog==heure) {
                addGraphe(referer, cible); //ajouter dans le graphe
                addHits(cible); //ajouter dans hits
                addNodes(cible, ordre); //ajouter le node dans la liste des nodes avec son ordre d'apparition
                addNodes(referer, ordre); //ajouter le node dans la liste des nodes avec son ordre d'apparition
            }
        }
    }
    file.close();
    makeHitsInverse(); // pour avoir une map ordonnée par ordre décroissant du nombre des hits
}//Fin lire


void TraitementLog::execute(){
    lire();
    if(doGraphe) makeDot(dotName);
    afficherHitsInverse();
    cout<<endl;
}

//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
TraitementLog::~TraitementLog()
// Algorithme :
//
{
#ifdef MAP
    //cout << "Appel au destructeur de <TraitementLog>" << endl;
#endif
}//----- Fin de ~TraitementLog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
