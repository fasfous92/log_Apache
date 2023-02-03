#include <iostream>
#include "Traitement.h"
#include "TraitementLog.h"
#include <fstream>
#include <regex>

int main(int argc,char* argv[]) {


    bool nomLogPresent = false;
    string nomLog=argv[argc-1];  //on vérifie si le fichier source existe par la suite
    if(nomLog.find(".log")==std::string::npos){ //if he doesn't find a .log extension there's an error
        cerr<<"Paramètre non valide pour le nom du fichier src ";
        return 1;
    }

    bool faireGraphe = false; //implique l'éxistance du -g suivi du nom de fichier destination
    string nomGraphe;

    bool selectionpar_heure = false;
    int heure=-1;

    bool exclusions=false;
    //tout d'abords on commence par vérifier si le fichier log (source) est présent et de format log


    // parcourt le tableau des arguments
    for ( int i = 1 ; i < argc-1; i++ ) // on commence à 1 car ./analog est négligé
    {
        string argCourant = argv[ i ] ;
        if( strlen( argv[i] ) < 1 ) //si l'argument est inférieur à 1 déjà nous remarquons une erreur dans les args
        {
            cerr<< "parametre"<< argCourant <<" non valide "<<endl;
            return 1;
        }
        if( argCourant == "-g" )
        {
            if( i == argc -1 )
            {
                cerr << "Paramètre non valide pour l'option -g : aucun paramètre" << endl;
                return 1;
            }
            else
            {
                if(i+1 == argc-1) {
                    cerr<<"Paramètre non valide pour l'option -g :aucun paramètre ou confondu avec le fichier.log source"<<endl;
                    return 1;
                }

                nomGraphe = argv [ i+1 ];
                faireGraphe = true;
                i++;
            }
        }
        else if( argCourant == "-t" )
        {
            if( i == argc -1 )
            {
                cerr << "Paramètre non valide pour l'option -t : aucun paramètre" << endl;
                return 1 ;
            }
            else
            {

                try{
                    heure = stoi(argv[i+1]);

                }
                catch(exception &err)
                {
                    cerr<<"Paramètre non valide pour l'option -t "<<endl;
                    return 1;
                }
                if( heure < 0)
                {
                    cerr << "Paramètre non valide pour l'option -t " << endl;
                    return 1;
                }else {
                    selectionpar_heure=true;
                    i++;
                }
            }
        }
        else if( argCourant == "-e" ){
            exclusions= true;
        }
    }

    TraitementLog t(nomLog,faireGraphe,nomGraphe,exclusions,heure);
    t.execute();

    return 0;
}