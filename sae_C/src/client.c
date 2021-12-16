/**
 * @file client.c
 * @author MOREL - DSJ
 * @brief Gestion d'un annuaire de client
 * @version 0.1
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#define taille_tableau 50
#define taille_ligne 256
#define taille_nom_fichier 50

struct personne{ // creation de structure pour le client
    char nom[50];
    char prenom[50];
    char ville[50];
    char telephone[50];
    char code_postal[50];
    char mail[50];
    char profession[50];
};

typedef struct personne personne;

int validite(char*);
int lignes(char*);
void lecture(char*,int);
void afficher(char*,char*,char*,char*,char*,char*,char*,int);
int ajout(char*,int*);

/**
 * @brief Programme principal
 * 
 * @return 0 par convention si le progromme s'est bien exécuté
 */

int main(){
    int validite_fichier=0;
    int ouverture, mode;
    int nombre_lignes = 0;
    char nom_fichier[taille_nom_fichier];

    do{
        do{
            printf("Que souhaitez vous faire ? \n");
            printf("1 - Ouvrir un fichier \n");
            printf("0 - Quitter \n");
            scanf("%d",&ouverture);

            switch(ouverture){ // condition sur le mode d'ouverture entree par l'utilisateur
                case 0:
                    printf("Fermeture...");
                    return 0;
                    break;
                case 1:
                    printf("Entrez le nom du fichier : ");
                    scanf("%s",&nom_fichier);

                    if(validite(nom_fichier) == 1){ // teste l'existence du fichier grace a la fonction validite()
                        validite_fichier = 1;
                    }
                    else{
                        printf("Ce fichier n'existe pas \n");
                    }
                    break;
                default:
                    printf("Veuillez saisir un champ valide");
                    break;
            }
        } while(validite_fichier == 0); // si le fichier existe alors on quitte la boucle

        nombre_lignes = lignes(nom_fichier); // calcule le nombre de lignes et l'affiche 
        printf("Ce fichier contient %d lignes \n", nombre_lignes);

        do{
            printf("Que souhaitez vous faire ? \n");
            printf("1 - Afficher le nombre de lignes \n");
            printf("2 - Afficher \n");
            printf("3 - Ajouter une ligne \n");
            printf("0 - Revenir au debut \n");
            scanf("%d",&mode);

            switch (mode){ // condition sur le mode de manipulation du fichier entree par l'utilisateur
            case 0:
                validite_fichier = 0;
                break;
            case 1:
                printf("Ce fichier contient %d lignes \n", nombre_lignes); // affiche le nombre de lignes
                break;
            case 2:
                lecture(nom_fichier,nombre_lignes); // lit et affiche le contenu du fichier
                break;
            case 3:
                if(ajout(nom_fichier,&nombre_lignes)==1){ // ajoute une ligne de client dans le fichier
                    printf("Ligne ajoutee");
                }
                else{
                    printf("Erreur");
                }
            default:
                printf("Veuillez saisir un champ valide");
                break;
            }
        }while(validite_fichier == 1); // tant que la validite ne change pas de valeur

    }while(ouverture != 0); // boucle permettant de boucler le menu 

    return 0;
}

/**
 * @fn int validite(char* filename) 
 * @brief teste l'existence du fichier
 * 
 * @param filename chaine de caractere representant le nom du fichier à vérifier
 * @return 0 si le fichier n'existe pas, 1 si le fichier existe
 */

int validite(char* filename){
    FILE * fichier = NULL;
    fichier = fopen(filename,"r");

    if(fichier == NULL){ // test l'existence du fichier
        return 0;
    }
    else{
        fclose(fichier);
        return 1;
    }
}

/**
 * @fn int lignes(char* filename)
 * 
 * @brief 
 * 
 * @param filename chaine de caractere representant le nom du fichier où il faut calculer le nombre de lignes
 * @return int nlignes -> le nombre de lignes
 */

int lignes(char* filename){
    FILE * fichier;
    fichier = fopen(filename,"r");

    int nlignes = 0;
    char lignes[taille_ligne];

    while(fgets(lignes,taille_ligne,fichier) != NULL){
        nlignes++;
    }

    fclose(fichier);

    return nlignes;
}

/**
 * @fn void lecture(char* filename, int taille, int mode)
 * 
 * @brief fonction qui lit les caracteres du fichier
 * 
 * @param filename correspondant au nom du fichier 
 * @param taille taille du tableau de structures
 * @return /
 */

void lecture(char* filename, int taille){
    FILE * pointeur = NULL;
    personne * ligne = malloc((taille+1)*sizeof(personne));
    pointeur = fopen(filename,"a+");
    int i=0,j=0,deb,fin;
    int virgule = 0;
    char caractere_lu;

    do{
        caractere_lu = fgetc(pointeur);

        switch (caractere_lu){
        case ',':
            virgule++;
            i=0;
            break;
        case '\n':
            i=0; 
            virgule=0;
            j++;
            break;
        default:
            switch (virgule){
            case 0:
                ligne[j].nom[i] = caractere_lu;
                i++;
                ligne[j].nom[i] = '\0';
                break;
            case 1:
                ligne[j].prenom[i] = caractere_lu;
                i++;
                ligne[j].prenom[i] = '\0';
                break;
            case 2:
                ligne[j].ville[i] = caractere_lu;
                i++;
                ligne[j].ville[i] = '\0';
                break;
            case 3:
                ligne[j].telephone[i] = caractere_lu;
                i++;
                ligne[j].telephone[i] = '\0';
                break;
            case 4:
                ligne[j].code_postal[i] = caractere_lu;
                i++;
                ligne[j].code_postal[i] = '\0';
                break;
            case 5:
                ligne[j].mail[i] = caractere_lu;
                i++;
                ligne[j].mail[i] = '\0';
                break;
            case 6:
                ligne[j].profession[i] = caractere_lu;
                i++;
                ligne[j].profession[i] = '\0';
                break;
            default:
                break;
            }
        break;
        }
    }while(caractere_lu != EOF);

    printf("Ligne du début : ");
    scanf("%d",&deb);

    printf("Ligne de fin (0 si vous voulez afficher jusqu'a la fin) : ");
    scanf("%d",&fin);

    if(fin==0){
        fin = taille+1;
    }

    for(j=deb;j<fin;j++){
        affichage(ligne[j].nom,ligne[j].prenom,ligne[j].ville,ligne[j].telephone,ligne[j].code_postal,ligne[j].mail,ligne[j].profession,j+1);
    }

    free(ligne);
    fclose(pointeur);
}

/**
 * @fn void affichage(char * nom,char * prenom,char * ville,char * telephone,char * code_postal,char * mail,char * profession, int num)
 * 
 *
 * @brief fonction qui affiche le contenu du tableau de structure
 * 
 * @param nom correspond à la premiere variable de la structure 
 * @param prenom correspond à la deuxieme variable de la structure 
 * @param ville correspond à la troisieme variable de la structure 
 * @param telephone correspond à la quatrieme variable de la structure 
 * @param code_postal correspond à la cinquieme variable de la structure 
 * @param mail correspond à la sixème variable de la structure 
 * @param profession correspond à la septieme variable de la structure 
 * @param num correspond au numero de la ligne
 */

void affichage(char * nom,char * prenom,char * ville,char * telephone,char * code_postal,char * mail,char * profession, int num){
    printf("================================================ \n");
    printf("Personne n %d \n", num);
    printf("================================================ \n");
    printf("Nom : %s \n",nom);
    printf("Prenom : %s \n",prenom);
    printf("Ville : %s \n",ville);
    printf("Telephone : %s \n",telephone);
    printf("Code postal : %s \n",code_postal);
    printf("Mail : %s \n",mail);
    printf("Profession : %s \n",profession);
    printf("================================================ \n");
    printf("\n");
}

/**
 * @fn int ajout(char * filename, int * taille)
 *
 * @brief permet d'ajouter un client
 * 
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de lignes du fichier
 * @return 1 si la fonction s'est bien exécutée, 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur
 */

int ajout(char * filename, int * taille){
    personne ligne;
    FILE * fichier;
    fichier = fopen(filename,"a+");

    int i,n,choix;

    printf("Combien de personnes voulez vous ajouter ? : ");
    scanf("%d",&n);

    *taille = *taille+n;

    for(i=0;i<n && n!=0;i++){
        printf("Nom : ");
        scanf("%s",ligne.nom);

        printf("Prenom : ");
        scanf("%s",ligne.prenom);

        printf("Ville : ");
        scanf("%s",ligne.ville);

        printf("Telephone : ");
        scanf("%s",ligne.telephone);

        printf("Code Postal : ");
        scanf("%s",ligne.code_postal);

        printf("Mail : ");
        scanf("%s",ligne.mail);

        printf("Profession : ");
        scanf("%s",ligne.profession);

        fprintf(fichier,"%s,%s,%s,%s,%s,%s,%s\n",ligne.nom,ligne.prenom,ligne.ville,ligne.telephone,ligne.code_postal,ligne.mail,ligne.profession);
    }

    fclose(fichier);

    if(n==0){
        return 0;
    }

    return 1;
}