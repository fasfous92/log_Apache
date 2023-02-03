/*************************************************************************
                           Traitement  -  description
                             -------------------
    début                : 16/01/23$
    copyright            : (C) 2023$ par ${AUTHOR}$
    e-mail               : ${EMAIL}$
*************************************************************************/

//---------- Réalisation de la classe <${ Traitement}> (fichier Traitement.cpp.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//------------------------------------------------------ Include personnel
#include "Traitement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Traitement::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Traitement::afficherVecteur()
// Algorithme :
{
    vector<string>::iterator it;
    int i=0;
    for(it=section.begin();it!=section.end();it++){
        cout<<"section ["<<i<<"] = "<<*it<<endl;
        i++;
    }
}


int Traitement::trouveHeure()const
// Algorithme :
{
    std::string word;
    std::stringstream stringStream(section[3]); //elle va récuperer la date comme stream
    int i = 0;
    int res;
    while (stringStream) {
        std::size_t prev = 0, pos;
        while ((pos = section[3].find_first_of("/:", prev)) != std::string::npos) {
            if (pos > prev)
                if(i==3) {
                    res=stoi(section[3].substr(prev,pos-prev));
                    return res;
                }else {
                    word.append(section[3].substr(prev, pos - prev));
                }
            prev = pos+1;
            i++;
        }
        if (prev < section[3].length())
            word.append(section[3].substr(prev, std::string::npos));
    }
}//----- Fin de Trouveheure

void Traitement::Decomposition(const string & line)
// Algorithme :
//
{
    std::stringstream stringStream(line);
    std::string word;
    int i=0;
    string regroup;
        std::size_t prev = 0, pos;
        /*Nous avons décidé de séparer selon les séparateurs présents si dessus
         * qui nous permettent d'avoir des données correctement renseigner
         * sauf pour les dernières instances qui devrait être regroupées par
         * la suite d'où la nécessité de travailler avec un indice i.
         * En ce qui concerne la date nous la récupérons entièrement et après
         * au besoin nous pouvons récupérer le nécessaire
         */
        while ((pos = line.find_first_of("[] \"", prev)) != std::string::npos) //string::npos is the end of the line
        //line.find_first trouve le début d'un mot en prenant en compte l'ancienne position prev et les delimiteurs
        {
            if (pos > prev)
               if(i>15) {
                   regroup.append(line.substr(prev, pos - prev));
               }else {
                   section.push_back(line.substr(prev, pos - prev));
               }
            prev = pos+1;
            i++;
        }
        if (prev < line.length())
            section.push_back(line.substr(prev, std::string::npos));

            section.push_back(regroup);

} //----- Fin de Decomposition


//------------------------------------------------- Surcharge d'opérateurs
Traitement &Traitement::operator=(const Traitement &unTraitement)
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Traitement::Traitement(const Traitement &unTraitement)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Traitement>" << endl;
#endif
} //----- Fin de Traitement (constructeur de copie)


Traitement::Traitement(const string & line)
// Algorithme :
//
{
#ifdef MAP
    //cout << "Appel au constructeur de <Traitement>" << endl;
#endif
    Decomposition(line);
} //----- Fin de Traitement


Traitement::~Traitement()
// Algorithme :
//
{
#ifdef MAP
    //cout << "Appel au destructeur de <Traitement>" << endl;
#endif
} //----- Fin de ~Traitement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
