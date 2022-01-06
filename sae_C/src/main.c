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
    int validite_fichier=0, ouverture, mode, mode2=0, nombre_lignes = 0, *tableau_indices, nouv_client;
    char nom_fichier[taille_nom_fichier];
    int ind;
    char mot[] = "Adelaide";

    while(1){ // boucle premettant de boucler le programme
        do{
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Gestion d'annuaire - Accueil");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20d | %-50s |\n",0,"Fermer");
            printf("| %-20d | %-50s |\n",1,"Ouvrir un fichier");
            printf(" ---------------------------------------------------------------------------\n");
            scanf("%d",&ouverture);

            switch(ouverture){ // condition sur le mode d'ouverture entree par l'utilisateur
                case 0:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Fermeture");
                    printf(" ---------------------------------------------------------------------------\n");
                    return 0;
                    break;
                case 1:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Entrez le nom du fichier :");
                    printf(" ---------------------------------------------------------------------------\n");
                    scanf("%s",&nom_fichier);

                    if(validite(nom_fichier) == 1){ // teste l'existence du fichier grace a la fonction validite()
                        validite_fichier = 1;
                    }
                    else{
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Ce fichier n'existe pas");
                        printf(" ---------------------------------------------------------------------------\n\n");
                    }
                    break;
                default:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
                    printf(" ---------------------------------------------------------------------------\n\n");
                    break;
            }
        } while(validite_fichier == 0); // si le fichier existe alors on quitte la boucle

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Ouverture du fichier");
        printf(" ---------------------------------------------------------------------------\n\n");
        nombre_lignes = lignes(nom_fichier); // calcule le nombre de lignes et l'affiche 

        personne * client = malloc((nombre_lignes+1)*sizeof(personne));
        lecture(nom_fichier,client,nombre_lignes);

        tableau_indices = malloc((nombre_lignes+1)*sizeof(int));
        remplissage(tableau_indices,nombre_lignes);

        do{
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Gestion d'annuaire - Gestion du fichier");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20d | %-50s |\n",0,"Retour");
            printf("| %-20d | %-50s |\n",1,"Afficher le nombre de clients");
            printf("| %-20d | %-50s |\n",2,"Afficher les clients");
            printf("| %-20d | %-50s |\n",3,"Rechercher un client");
            printf("| %-20d | %-50s |\n",4,"Ajouter un client");
            printf("| %-20d | %-50s |\n",5,"Cherhcer un client");
            printf(" ---------------------------------------------------------------------------\n");
            scanf("%d",&mode);

            switch (mode){ // condition sur le mode de manipulation du fichier entree par l'utilisateur
            case 0:
                free(client);
                free(tableau_indices);
                validite_fichier = 0;
                break;
            case 1:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Nombres de clients :"); // affiche le nombre de lignes
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73d |\n",nombre_lignes);
                printf(" ---------------------------------------------------------------------------\n\n");
                break;
            case 2: // lit et affiche le contenu du fichier
            do{
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Gestion d'annuaire - Menu d'affichage");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20d | %-50s |\n",0,"Retour");
                printf("| %-20d | %-50s |\n",1,"Afficher par prenom");
                printf("| %-20d | %-50s |\n",2,"Afficher par nom");
                printf("| %-20d | %-50s |\n",3,"Afficher par ville");
                printf("| %-20d | %-50s |\n",4,"Afficher par code postal");
                printf("| %-20d | %-50s |\n",5,"Afficher par telephone");
                printf("| %-20d | %-50s |\n",6,"Afficher par mail");
                printf("| %-20d | %-50s |\n",7,"Afficher par profession");
                printf(" ---------------------------------------------------------------------------\n");
                scanf("%d",&mode2);
                switch (mode2){
                    case 0:
                        mode2=0;
                        break;
                    case 1:
                        tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                        mode2=0;
                        break;
                    case 2:
                        tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                        mode2=0;
                        break;
                    case 3:
                        tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                        mode2=0;
                        break;
                    case 4:
                        tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                        mode2=0;
                        break;
                    case 5:
                        tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                        mode2=0;
                        break;
                    case 6:
                        tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                        mode2=0;
                        break;
                    case 7:
                        tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                        mode2=0;
                        break;
                    default:
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
                        printf(" ---------------------------------------------------------------------------\n\n");
                        break;
                    }
                    affichage(client,tableau_indices,nombre_lignes);
            }while(mode2 != 0);
                break;
            case 3:
                break;
            case 4:
                nouv_client = ajout(nom_fichier,&nombre_lignes);

                if(nouv_client>0){ // ajoute une ligne de client dans le fichier
                    free(tableau_indices);

                    client = realloc(client,(nombre_lignes+1)*sizeof(personne));
                    lecture(nom_fichier,client,nombre_lignes);

                    tableau_indices = malloc((nombre_lignes+1)*sizeof(int));
                    remplissage(tableau_indices,nombre_lignes);
                }
                break;
            case 5:
                printf("avec quel parametre voulez vous chercher\n");
                scanf("%d",&mode2);
                tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,mode2);
                printf("\nle nom a chercher est %s",mot);
                ind = recherche_dichotomique(mot,client,tableau_indices,nombre_lignes,mode2);
                if (ind>=0)
                {
                printf("recherche effectué");
                printf(" ---------------------------------------------------------------------------\n");
                printf(" ---------------------------------------------------------------------------\n");
                printf("|                      |                                                    |\n");
                printf("| %-20s | %-50s |\n","Prenom",client[tableau_indices[ind]].prenom);
                printf("|                      |                                                    |\n");
                printf(" ---------------------------------------------------------------------------\n");
                printf("|                      |                                                    |\n");
                printf("| %-20s | %-50s |\n","Nom",client[tableau_indices[ind]].nom);
                printf("|                      |                                                    |\n");
                printf(" ---------------------------------------------------------------------------\n");
                printf("|                      |                                                    |\n");
                printf("| %-20s | %-50s |\n","Ville",client[tableau_indices[ind]].ville);
                printf("|                      |                                                    |\n");
                printf(" ---------------------------------------------------------------------------\n");
                printf("|                      |                                                    |\n");
                printf("| %-20s | %-50s |\n","Code Postal",client[tableau_indices[ind]].code_postal);
                printf("|                      |                                                    |\n");
                printf(" ---------------------------------------------------------------------------\n");
                printf("|                      |                                                    |\n");
                printf("| %-20s | %-50s |\n","Telephone",client[tableau_indices[ind]].telephone);
                printf("|                      |                                                    |\n");
                printf(" ---------------------------------------------------------------------------\n");
                printf("|                      |                                                    |\n");
                printf("| %-20s | %-50s |\n","Mail",client[tableau_indices[ind]].mail);
                printf("|                      |                                                    |\n");
                printf(" ---------------------------------------------------------------------------\n");
                printf("|                      |                                                    |\n");
                printf("| %-20s | %-50s |\n","Profession",client[tableau_indices[ind]].profession);
                printf("|                      |                                                    |\n");
                printf(" ---------------------------------------------------------------------------\n\n"); 
                }
                    break;
            default:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
                printf(" ---------------------------------------------------------------------------\n\n");
                break;
            }
        }while(validite_fichier == 1); // tant que la validite ne change pas de valeur
    }
}