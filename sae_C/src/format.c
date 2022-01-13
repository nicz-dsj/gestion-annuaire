#include "main.h"

int ctrl_extension(char*);
int format_fichier(char**,int);
int ctrl_virgule(char*,int);
int format_code_postal(char*,int);
int format_telephone(char*,int);
int format_mail(char*,int);

/**
 * @fn int ctrl_extension(char * filename)
 * 
 * @brief fonction qui contrôle l'extension du fichier
 * @param filename correspond au nom du fichier
 * @return int : 1 si l'extension est valide, 0 si il n'est pas valide
 * 
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN - James MOREL
 */
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

/**
 * @fn int format_fichier(char ** liste, int lignes)
 * 
 * @brief fonction qui contrôle le format du fichier
 * @param liste correspond au tableau de lignes
 * @param lignes correspond au nombre de lignes du tableau de lignes
 * @return int : 1 si le format est valide, 0 si il n'est pas valide
 * 
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN - James MOREL
 */
int format_fichier(char ** liste, int lignes){
    int i;
    int j;
    int virgules=0; // nombre de virgules rencontrées sur la ligne
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

/**
 * @fn int ctrl_virgule(char * chaine, int longueur)
 * 
 * @brief fonction qui contrôle la présence de virgules dans la chaine
 * @param chaine correspond à la chaine à vérifier
 * @param longueur correspond à la longueur de la chaine
 * @return int : 1 si il n'y a pas de virgules, 0 si il y en a
 * 
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN - James MOREL
 */
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


/**
 * @fn int format_code_postal(char * chaine, int longueur)
 * 
 * @brief fonction qui contrôle le format du code postal
 * @param chaine correspond à la chaine à vérifier
 * @param longueur correspond à la longueur de la chaine
 * @return int : 1 si le format est valide, 0 si il n'est pas valide, -1 si la chaine contient des virgules
 * 
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN - James MOREL
 */
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

/**
 * @fn int format_telephone(char * chaine, int longueur)
 * 
 * @brief fonction qui contrôle le format du téléphone
 * @param chaine correspond à la chaine à vérifier
 * @param longueur correspond à la longueur de la chaine
 * @return int : 1 si le format est valide, 0 si il n'est pas valide, -1 si la chaine contient des virgules
 * 
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN - James MOREL
 */
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

/**
 * @fn int format_mail(char * chaine, int longueur)
 * 
 * @brief fonction qui contrôle le format du mail
 * @param chaine correspond à la chaine à vérifier
 * @param longueur correspond à la longueur de la chaine
 * @return int : 1 si le format est valide, 0 si il n'est pas valide, -1 si la chaine contient des virgules
 * 
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN - James MOREL
 */
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
            if(chaine[0]=='@'){ // contrôle la présence d'un arobase sur le premier caractère
                arobase_ind_0++;
            }
            if(i>0 && chaine[i]=='@'){ // contrôle la présence d'un arobase dans la chaine
                arobase++;
            }
            if(arobase>0 && chaine[i]=='.'){ // contrôle la présence d'un point après un arobase dans la chaine
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