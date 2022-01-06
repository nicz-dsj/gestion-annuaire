#include "main.h"

int ctrl_extension(char * filename, int longueur){
    int ext=strrchr(filename,'.csv'), valide=1;

    if(ext==NULL){
        valide=0;
    }

    return valide;
}

int format_fichier(char ** liste, int lignes, int taille){
    int i,j,virgules,valide=1;

    for(i=0;i<lignes;i++){
        virgules=0;
        for(j=0;j<taille;j++){
            if(liste[i][j]==','){
                virgules=virgules+1;
            }
        }
        if(virgules!=6){
            valide=0;
        }
    }

    return valide;
}

int ctrl_virgule(char * chaine, int longueur){
    int i, valide=1;

    for(i=0;i<longueur;i++){
        if(chaine[i]==','){
            valide=0;
        }
    }

    return valide;
}

int format_code_postal(char * chaine, int longueur){
    int i,valide=1;

    int controle_virgule = ctrl_virgule(chaine,longueur);

    if(controle_virgule==0){
        valide=-1;
    }
    else{
        if(longueur!=5){
            valide=0;
        }
        else{
            for(i=0;i<longueur;i++){
                if(isdigit(chaine[i])==0){
                    valide=0;
                }
            }
        }
    }

    return valide;
}

int format_telephone(char * chaine, int longueur){
    int i, valide=1;

    int controle_virgule = ctrl_virgule(chaine,longueur);

    if(controle_virgule==0){
        valide=-1;
    }
    else{
        if(longueur!=14){
            valide=0;
        }
        else{
            for(i=0;i<longueur;i++){
                if(i==2 || i==5 || i==8 || i==11){
                    if(chaine[i]!='.'){
                        valide=0;
                    }
                }
                else{
                    if(isdigit(chaine[i])==0){
                        valide=0;
                    }
                }
            }
        }
    }

    return valide;
}

int format_mail(char * chaine, int longueur){
    int i, valide=0,arobase_ind_0=0,arobase=0,point=0,resultat;

    int controle_virgule = ctrl_virgule(chaine,longueur);

    if(controle_virgule==0){
        valide=-1;
    }
    else{
        for(i=0;i<longueur;i++){
            if(chaine[0]=='@'){
                arobase_ind_0++;
            }
            if(i>0 && chaine[i]=='@'){
                arobase++;
            }
            if(arobase>0 && chaine[i]=='.'){
                point++;
            }
        }

        if(arobase>0 && point >0){
            resultat = arobase+point+arobase_ind_0;
        }

        if(resultat==2){
            valide=1;
        }
    }

    return valide;
}