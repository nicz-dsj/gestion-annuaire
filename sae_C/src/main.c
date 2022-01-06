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
    int nombre_fichiers;
    int choix_fichier;
    int confim_choix_fichier; int existence_fichier=0; 
    int i; 
    int validite_fichier=0;
    int est_protege;
    int menu_accueil; 
    int menu_gestion; 
    int menu_ouvrir=0;
    int menu_supprimer=0;
    int menu_afficher=0; 
    int nombre_lignes = 0; 
    int *tableau_indices = NULL; 
    int format; 
    int nouv_client;

    char nom_fichier[taille_nom_fichier]; 
    char **tableau_fichiers;
    char fichiers_proteges[nombre_fichiers_proteges][taille_ligne];
    char extension[] = ".csv"; 
    char **tableau_lignes = NULL;

    personne * client = NULL;

    strcpy(fichiers_proteges[0],"main.c");
    strcpy(fichiers_proteges[1],"fonction.c");
    strcpy(fichiers_proteges[3],"format.c");
    strcpy(fichiers_proteges[4],"main.h");
    strcpy(fichiers_proteges[5],"main.exe");
    strcpy(fichiers_proteges[6],"build");

    while(1){ // boucle premettant de boucler le programme
        nombre_fichiers = fichiers();

        tableau_fichiers = malloc(nombre_fichiers*sizeof(char*));
        for(i=0;i<nombre_fichiers;i++){
            tableau_fichiers[i] = malloc(taille_ligne*sizeof(char));
        }
        lecture_repertoire(tableau_fichiers);
        
        do{
            confim_choix_fichier = 1;

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Accueil");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20d | %-50s |\n",0,"Fermer");
            printf("| %-20d | %-50s |\n",1,"Ouvrir un fichier");
            printf("| %-20d | %-50s |\n",2,"Creer un fichier");
            printf("| %-20d | %-50s |\n",3,"Supprimer un fichier");
            printf(" ---------------------------------------------------------------------------\n");
            scanf("%d",&menu_accueil);

            switch(menu_accueil){ // condition sur le mode d'menu_accueil entree par l'utilisateur
                case 0:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Fermeture");
                    printf(" ---------------------------------------------------------------------------\n");

                    return 0;
                    break;
                case 1:
                    do{
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","Ouvrir un fichier");
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-20d | %-50s |\n",0,"Retour");
                        printf("| %-20d | %-50s |\n",1,"Ouvrir un fichier par saisie");
                        printf("| %-20d | %-50s |\n",2,"Ouvrir un fichier present par selection");
                        printf(" ---------------------------------------------------------------------------\n");
                        scanf("%d",&menu_ouvrir);

                        switch (menu_ouvrir){
                            case 0:
                                menu_ouvrir=0;
                                break;
                            case 1:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Le fichier doit etre de format :");
                                printf("| %-73s |\n","prenom,nom,ville,code_postal,telephone,mail,profession)");
                                printf(" ---------------------------------------------------------------------------\n");

                                fflush(stdin);
                                fflush(stdout);
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Saisissez le nom du fichier :");
                                printf(" ---------------------------------------------------------------------------\n");
                                gets(nom_fichier);
                                break;
                            case 2:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Le fichier doit etre de format :");
                                printf("| %-73s |\n","prenom,nom,ville,code_postal,telephone,mail,profession)");
                                printf(" ---------------------------------------------------------------------------\n");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Selectionnez un fichier");
                                printf(" ---------------------------------------------------------------------------\n");
                                for(i=0;i<nombre_fichiers;i++){
                                    printf("| %-20d | %-50s |\n",i,tableau_fichiers[i]);
                                    printf(" ---------------------------------------------------------------------------\n");
                                }
                                scanf("%d",&choix_fichier);

                                if(choix_fichier<0 || choix_fichier>nombre_fichiers-1){
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide");
                                    printf(" ---------------------------------------------------------------------------\n\n");
                                    confim_choix_fichier = 0;
                                }
                                else{
                                    strcpy(nom_fichier,tableau_fichiers[choix_fichier]);
                                }
                                break;
                            default:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
                                printf(" ---------------------------------------------------------------------------\n\n");
                                break;
                            }

                        if(menu_ouvrir!=0 && confim_choix_fichier == 1){
                            if(validite(nom_fichier) == 1){ // teste l'existence du fichier grace a la fonction validite()
                            validite_fichier = 1;
                            }
                            else{
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Ce fichier n'existe pas");
                                printf(" ---------------------------------------------------------------------------\n\n");
                            }
                            menu_ouvrir=0;
                        }
                    }while(menu_ouvrir!=0);
                    break;
                case 2:
                    fflush(stdin);
                    fflush(stdout);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Creer un fichier");
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Nom du fichier a creer :");
                    printf("| %-73s |\n","/!\\ Le nom du fichier ne doit pas etre existant");
                    printf(" ---------------------------------------------------------------------------\n");
                    gets(nom_fichier);

                    strcat(nom_fichier,extension);
                    existence_fichier=0;

                    for(i=0;i<nombre_fichiers && existence_fichier==0;i++){
                        if(strcmp(nom_fichier,tableau_fichiers[i])==0){
                            existence_fichier=1;
                        }
                    }

                    if(existence_fichier==1){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Ce nom de fichier existe deja");
                        printf(" ---------------------------------------------------------------------------\n\n");
                    }
                    else{
                        creation_fichier(nom_fichier);
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","Fichier cree");
                        printf(" ---------------------------------------------------------------------------\n\n");
                    }
                    break;
                case 3:
                    do{
                        confim_choix_fichier = 1;

                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Supprimer un fichier");
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-20d | %-50s |\n",0,"Retour");
                        printf("| %-20d | %-50s |\n",1,"Supprimer un fichier par saisie");
                        printf("| %-20d | %-50s |\n",2,"Supprimer un fichier par selection");
                        printf(" ---------------------------------------------------------------------------\n");
                        scanf("%d",&menu_supprimer);

                        switch (menu_supprimer){
                            case 0:
                                menu_supprimer==0;
                                break;
                            case 1:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ L'option supprimer supprime n'importe quel fichier");
                                printf(" ---------------------------------------------------------------------------\n");

                                fflush(stdin);
                                fflush(stdout);
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Saisissez le nom du fichier : ");
                                printf(" ---------------------------------------------------------------------------\n");
                                gets(nom_fichier);
                                break;
                            case 2:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ L'option supprimer supprime n'importe quel fichier");
                                printf(" ---------------------------------------------------------------------------\n");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Selectionnez un fichier");
                                printf(" ---------------------------------------------------------------------------\n");
                                for(i=0;i<nombre_fichiers;i++){
                                    printf("| %-20d | %-50s |\n",i,tableau_fichiers[i]);
                                    printf(" ---------------------------------------------------------------------------\n");
                                }
                                scanf("%d",&choix_fichier);

                                if(choix_fichier<0 || choix_fichier>nombre_fichiers-1){
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide");
                                    printf(" ---------------------------------------------------------------------------\n\n");
                                    confim_choix_fichier = 0;
                                }
                                else{
                                    strcpy(nom_fichier,tableau_fichiers[choix_fichier]);
                                }
                                break;
                            default:
                                break;
                            }
                        if(menu_supprimer!=0 && confim_choix_fichier==1){
                            if(validite(nom_fichier) == 1){

                                est_protege=0;

                                for(i=0;i<nombre_fichiers_proteges && est_protege==0;i++){
                                    if(strcmp(nom_fichier,fichiers_proteges[i])==0){
                                        est_protege = 1;
                                    }
                                }

                                if(est_protege==1){
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Ce fichier est protege");
                                    printf(" ---------------------------------------------------------------------------\n\n");
                                }
                                else{
                                    if(remove(nom_fichier)==0){
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Fichier supprime");
                                        printf(" ---------------------------------------------------------------------------\n\n");
                                    }
                                    else{
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","/!\\ Erreur lors de la suppression du fichier");
                                        printf(" ---------------------------------------------------------------------------\n\n");
                                    }
                                }
                                menu_supprimer=0;
                            }
                            else{
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Ce fichier n'existe pas");
                                printf(" ---------------------------------------------------------------------------\n\n");
                            }
                        }
                    }while(menu_supprimer!=0);
                    break;
                default:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
                    printf(" ---------------------------------------------------------------------------\n\n");
                    break;
            }
        } while(validite_fichier == 0); // si le fichier existe alors on quitte la boucle

        for(i=0;i<nombre_fichiers;i++){
            free(tableau_fichiers[i]);
        }

        free(tableau_fichiers);

        nombre_lignes = lignes(nom_fichier); // calcule le nombre de lignes et l'affiche 

        tableau_lignes = malloc(nombre_lignes*sizeof(char*));
        for(i=0;i<nombre_lignes;i++){
            tableau_lignes[i] = malloc(taille_ligne*sizeof(char));
        }
        lecture_lignes(nom_fichier,tableau_lignes);
        format = format_fichier(tableau_lignes,nombre_lignes);

        if(format==0){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Ce fichier ne correspond pas au format attendu");
            printf(" ---------------------------------------------------------------------------\n\n");

            for(i=0;i<nombre_lignes;i++){
                free(tableau_lignes[i]);
            }
            free(tableau_lignes);
            validite_fichier = 0;
        }
        else{
            client = malloc(nombre_lignes*sizeof(personne));
            lecture(nom_fichier,client,nombre_lignes);

            tableau_indices = malloc(nombre_lignes*sizeof(int));
            remplissage(tableau_indices,nombre_lignes);

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Ouverture du fichier");
            printf(" ---------------------------------------------------------------------------\n\n");

            do{
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Gestion du fichier");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20d | %-50s |\n",0,"Retour");
                printf("| %-20d | %-50s |\n",1,"Afficher le nombre de clients");
                printf("| %-20d | %-50s |\n",2,"Afficher les clients");
                printf("| %-20d | %-50s |\n",3,"Rechercher un client");
                printf("| %-20d | %-50s |\n",4,"Ajouter un client");
                printf(" ---------------------------------------------------------------------------\n");
                scanf("%d",&menu_gestion);

                switch (menu_gestion){ // condition sur le mode de manipulation du fichier entree par l'utilisateur
                case 0:
                    free(client);

                    for(i=0;i<nombre_lignes;i++){
                        free(tableau_lignes[i]);
                    }
                    free(tableau_lignes);

                    free(tableau_indices);

                    strcpy(nom_fichier, "");

                    validite_fichier = 0;
                    break;
                case 1:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Nombres de clients :"); // affiche le nombre de lignes
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73d |\n",nombre_lignes-1);
                    printf(" ---------------------------------------------------------------------------\n\n");
                    break;
                case 2: // lit et affiche le contenu du fichier
                    do{
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","Afficher les clients");
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
                        scanf("%d",&menu_afficher);
                        switch (menu_afficher){
                        case 0:
                            menu_afficher=0;
                            break;
                        case 1:
                            tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_afficher);
                            break;
                        case 2:
                            tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_afficher);
                            break;
                        case 3:
                            tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_afficher);
                            break;
                        case 4:
                            tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_afficher);
                            break;
                        case 5:
                            tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_afficher);
                            break;
                        case 6:
                            tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_afficher);
                            break;
                        case 7:
                            tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_afficher);
                            break;
                        default:
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
                            printf(" ---------------------------------------------------------------------------\n\n");
                            break;
                        }
                        if(menu_afficher != 0){
                            affichage(client,tableau_indices,nombre_lignes-1);
                            menu_afficher=0;
                        }
                    }while(menu_afficher != 0);
                    break;
                case 3:
                    break;
                case 4:
                    nouv_client = ajout(nom_fichier,&nombre_lignes);

                    if(nouv_client>0){ // ajoute une ligne de client dans le fichier
                        for(i=0;i<nombre_lignes;i++){
                            free(tableau_lignes[i]);
                        }
                        free(tableau_lignes);

                        free(tableau_indices);

                        tableau_lignes = malloc(nombre_lignes*sizeof(char*));
                        for(i=0;i<nombre_lignes;i++){
                            tableau_lignes[i] = malloc(taille_ligne*sizeof(char));
                        }
                        lecture_lignes(nom_fichier,tableau_lignes);

                        client = realloc(client,nombre_lignes*sizeof(personne));
                        lecture(nom_fichier,client,nombre_lignes);

                        tableau_indices = malloc(nombre_lignes*sizeof(int));
                        remplissage(tableau_indices,nombre_lignes);
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
}