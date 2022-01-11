#include "main.h"

int ctrl_extension(char*);
int format_fichier(char**,int);
int ctrl_virgule(char*,int);
int format_code_postal(char*,int);
int format_telephone(char*,int);
int format_mail(char*,int);

int ctrl_extension(char * filename){
    int valide = 0;
    char * extension = strrchr(filename,'.');

    if(strcmp(extension,".csv") == 0){
        valide = 1;
    }
    if(strcmp(extension,".txt") == 0 ){
        valide = 1;
    }
    return valide;
}

int format_fichier(char ** liste, int lignes){
    int i;
    int j;
    int virgules=0; 
    int valide=1;

    for(i=0;i<lignes-1 && valide==1;i++){
        virgules=0;
        for(j=0;liste[i][j]!='\n';j++){
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
    int i; 
    int valide=1;

    for(i=0;i<longueur;i++){
        if(chaine[i]==','){
            valide=0;
        }
    }

    return valide;
}

int format_code_postal(char * chaine, int longueur){
    int i; 
    int valide=1;
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
    int i; 
    int valide=1;
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
    int i; 
    int valide=0; 
    int arobase_ind_0=0; 
    int arobase=0; 
    int point=0; 
    int resultat;
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