#include "main.h"

/**
 * @fn void lire_fichier(char* fichier)
 * @brief fonction qui lit un fichier csv et qui en affiche le contenu
 * 
 * @param fichier chaine de caractère représantant un fichier à ouvrir
 * @return rien
 */
void lire_fichier(char* fichier) {
    struct Annuaire personne;
    FILE* pointeur;
    pointeur = fopen(fichier,"r"); // ouverture du fichier

    if(pointeur == NULL){ //verification de la réussite de l'ouverture
        printf("Ce fichier n'existe pas \n\n");
    }
    else {
        char ligne[TAILLE_MAX];
        while(fgets(ligne,TAILLE_MAX,pointeur)!=NULL){
            sscanf(ligne,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",personne.prenom,personne.nom,personne.ville,personne.telephone,personne.code_postal,personne.mail,personne.profession);
            printf("%s %s %s %s %s %s %s",personne.prenom,personne.nom,personne.ville,personne.telephone,personne.code_postal,personne.mail,personne.profession); //affichage de la ligne lu
        }
        fclose(pointeur);
        printf("\nAppuyez sur n'importe quelle touche pour continuer");

        getch();
        printf("\n\n ----------------------------- \n\n");
    }
}
