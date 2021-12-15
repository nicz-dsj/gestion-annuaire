#include <stdlib.h> // pour le scanf
#include <stdio.h> // pour le printf
#include <string.h>
#define TAILLE_MAX 50


struct Annuaire {
    char prenom[TAILLE_MAX];
    char nom[TAILLE_MAX];
    char ville[TAILLE_MAX];
    char telephone[TAILLE_MAX];
    char code_postal[TAILLE_MAX];
    char mail[TAILLE_MAX];
    char profession[TAILLE_MAX];
};
typedef struct Annuaire per;

void lire_fichier(char* fichier);

void ajout_client(per* tab_personne, int* taille);

/**
 * @fn void lire_fichier(char* fichier)
 * @brief fonction qui lit un fichier csv et qui en affiche le contenu
 * 
 * @param fichier chaine de caractère représantant un fichier à ouvrir
 * @return rien
 */
void lire_fichier(char* fichier) {
    int taille_tab = 5000;
    per* personne = malloc(taille_tab*sizeof(per));
    FILE* pointeur = NULL;
    char caractere_lu;
    int nbr_virgule =0;
    int ind;
    int ind_talbeau =0;
    pointeur = fopen(fichier,"r"); // ouverture du fichier

    if(pointeur == NULL){ //verification de la réussite de l'ouverture
        printf("Ce fichier n'existe pas \n\n");
    }
    else {
        printf("ouvert\n");
        do{
            caractere_lu = fgetc(pointeur);

            switch (caractere_lu)
            {
            case ',':
                nbr_virgule ++;
                ind = 0;
                break;
            case '\n':
                nbr_virgule =0;
                ind = 0;
                printf("prenom: %s ",personne[ind_talbeau].prenom);
                printf("nom: %s ",personne[ind_talbeau].nom);
                printf("ville: %s ",personne[ind_talbeau].ville);
                printf("code_postal: %s ",personne[ind_talbeau].code_postal);
                printf("telephone: %s ",personne[ind_talbeau].telephone);
                printf("mail: %s ",personne[ind_talbeau].mail);
                printf("profession: %s \n",personne[ind_talbeau].profession);
                ind_talbeau ++;

                break;
                        
            default:
                switch (nbr_virgule)
                {
                case 0:
                    personne[ind_talbeau].prenom[ind] = caractere_lu;
                    ind ++;
                    personne[ind_talbeau].prenom[ind] = '\0';
                    break;
                case 1:
                    personne[ind_talbeau].nom[ind] = caractere_lu;
                    ind ++;
                    personne[ind_talbeau].nom[ind] = '\0';
                    break;
                case 2:
                    personne[ind_talbeau].ville[ind] = caractere_lu;
                    ind ++;
                    personne[ind_talbeau].ville[ind] = '\0';
                    break;
                case 3:
                    personne[ind_talbeau].telephone[ind] = caractere_lu;
                    ind ++;
                    personne[ind_talbeau].telephone[ind] = '\0';
                    break;
                case 4 :
                    personne[ind_talbeau].code_postal[ind] = caractere_lu;
                    ind ++;
                    personne[ind_talbeau].code_postal[ind] = '\0';
                    break;
                case 5:
                    personne[ind_talbeau].mail[ind] = caractere_lu;
                    ind ++;
                    personne[ind_talbeau].mail[ind] = '\0';
                    break;
                case 6:
                    personne[ind_talbeau].profession[ind] = caractere_lu;
                    ind ++;
                    personne[ind_talbeau].profession[ind] = '\0';
                    break;
                
                default:
                    break;
                }
                break;
            }

            

        }while (caractere_lu != EOF);

        fclose(pointeur);

        printf("\nAppuyez sur n'importe quelle touche pour continuer");

        printf("\n\n ----------------------------- \n\n");
    }
}

void ajout_client(per* tab_personne, int*taille){
    int nb_pers =0;
    printf("combien de clients voulez vous rajouter?");
    scanf("%d",&nb_pers);
    tab_personne = realloc(tab_personne, (*taille+nb_pers)*sizeof(per));
    if (tab_personne ==NULL)
    {
        printf("Erreur de reallocation\n");
    }
    
}