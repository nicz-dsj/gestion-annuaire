/**
 * @file main.c
 * @author morel james | De Saint Jean Nicolas
 * @brief un programe de gestion de liste de client
 * @version 0.1
 * @date 2021-11-18
 */

#include "main.h"

    
/**
 * @fn int main(void)
 * @brief programme principale, qui sert à gerer une liste de client dans un fichier csv
 * 
 * @return 0 par convention pour confirmer la bonne execution du programme 
 */
int main(void) {
    int mode_ouverture; // un entier qui permet de naviguer dans les différents modes
    char nom_fichier[TAILLE_MAX]; // un tableau qui prendra comme valeur un nom de fichier entré au clavier

    do {
        printf("Que souhaitez-vous faire ? \n");
        printf("Guide : \n");
        printf("1 : Afficher du contenu \n");
        printf("0 : Fermer \n");
        scanf("%d",&mode_ouverture);

        switch (mode_ouverture) { // test de la saisie du clavier pour basculer entre les modes
        case 1:
            printf("Entrez le nom du fichier : ");
            scanf("%s", &nom_fichier); // saisie du nom du fichier
            lire_fichier(nom_fichier); // lecture du fichier
            break;
        case 0:
            printf("Fermeture...");
            sleep(1);
            break;
        default:
            printf(" ! Veuillez saisir une information vailde ! ");
            break;
        }
    } while(mode_ouverture != 0); // boucle acctif tant que l'option fermer n'a pas été choisi

    return 0;
}


