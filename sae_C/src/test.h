#include <stdlib.h> // pour le scanf
#include <stdio.h> // pour le printf
#include <string.h>
#define TAILLE_MAX 1000


struct Annuaire {
    char prenom[TAILLE_MAX];
    char nom[TAILLE_MAX];
    char ville[TAILLE_MAX];
    char telephone[TAILLE_MAX];
    char code_postal[TAILLE_MAX];
    char mail[TAILLE_MAX];
    char profession[TAILLE_MAX];
};

void lire_fichier(char* fichier);

/**
 * @fn void lire_fichier(char* fichier)
 * @brief fonction qui lit un fichier csv et qui en affiche le contenu
 * 
 * @param fichier chaine de caractère représantant un fichier à ouvrir
 * @return rien
 */
void lire_fichier(char* fichier) {
    struct Annuaire personne;
    FILE* pointeur = NULL;
    pointeur = fopen(fichier,"r"); // ouverture du fichier

    if(pointeur == NULL){ //verification de la réussite de l'ouverture
        printf("Ce fichier n'existe pas \n\n");
    }
    else {
        char caractere_lu;
        int nbr_virgule =0;
        int ind;
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
                printf("prenom: %s | nom: %s ville: %s code_postal: %s telephone: %s mail: %s profession: %s \n",personne.prenom,personne.nom,personne.ville,personne.telephone,personne.code_postal,personne.mail,personne.profession);
                personne.prenom[0] = '\0';
                personne.nom[0] = '\0';
                personne.ville[0] = '\0';
                personne.telephone[0] = '\0';
                personne.code_postal[0] = '\0';
                personne.profession[0] = '\0';
                break;
                        
            default:
                switch (nbr_virgule)
                {
                case 0:
                    personne.prenom[ind] = caractere_lu;
                    personne.prenom[ind+1] = '\0';
                    ind ++;
                    break;
                case 1:
                    personne.nom[ind] = caractere_lu;
                    personne.nom[ind+1] = '\0';
                    ind ++;
                    break;
                case 2:
                    personne.ville[ind] = caractere_lu;
                    personne.ville[ind+1] = '\0';
                    ind ++;
                    break;
                case 3:
                    personne.telephone[ind] = caractere_lu;
                    personne.telephone[ind+1] = '\0';
                    ind ++;
                    break;
                case 4 :
                    personne.code_postal[ind] = caractere_lu;
                    personne.code_postal[ind+1] = '\0';
                    ind ++;
                    break;
                case 5:
                    personne.mail[ind] = caractere_lu;
                    personne.mail[ind+1] = '\0';
                    ind ++;
                    break;
                case 6:
                    personne.profession[ind] = caractere_lu;
                    personne.profession[ind+1] = '\0';
                    ind ++;
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