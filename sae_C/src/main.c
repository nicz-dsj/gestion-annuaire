/**
 * @file main.c
 * @author morel james | De Saint Jean Nicolas
 * @brief un programe de gestion de liste de client
 * @version 0.1
 * @date 2021-11-18
 */

#include "main.h"
#include "fonction.c"

    
/**
 * @fn int main()
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
        personne * client = malloc((nombre_lignes+1)*sizeof(personne));
        lecture(nom_fichier,client,nombre_lignes);

        do{
            printf("Que souhaitez vous faire ? \n");
            printf("1 - Afficher le nombre de lignes \n");
            printf("2 - Afficher \n");
            printf("3 - Ajouter une ligne \n");
            printf("0 - Revenir au debut \n");
            scanf("%d",&mode);

            switch (mode){ // condition sur le mode de manipulation du fichier entree par l'utilisateur
            case 0:
                free(client);
                validite_fichier = 0;
                break;
            case 1:
                printf("Ce fichier contient %d lignes \n", nombre_lignes); // affiche le nombre de lignes
                break;
            case 2: // lit et affiche le contenu du fichier
                affichage(client,nombre_lignes);
                break;
            case 3:
                if(ajout(nom_fichier,&nombre_lignes)==1){ // ajoute une ligne de client dans le fichier
                    client = realloc(client,(nombre_lignes+1)*sizeof(personne));
                    lecture(nom_fichier,client,nombre_lignes); 
                    printf("Ligne ajoutee");
                }
                else{
                    printf("Erreur \n");
                }
            default:
                printf("Veuillez saisir un champ valide");
                break;
            }
        }while(validite_fichier == 1); // tant que la validite ne change pas de valeur

    }while(ouverture != 0); // boucle permettant de boucler le menu 

    return 0;
}