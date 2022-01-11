/**
 * @file main.c
 * @author morel james | De Saint Jean Nicolas
 * @brief un programe de gestion de liste de client
 * @version 0.1
 * @date 2021-11-18
 */

#include "main.h"
#include "fonction.c"
#include "format.c"
#include "couleur.c"

/**
 * @fn int main()
 * @brief Programme principal
 *
 * @return 0 par convention si le progromme s'est bien exécuté
 */

int main(){
    int nombre_fichiers=0;
    int choix_fichier;
    int confim_choix_fichier;
    int existence_nom_fichier;
    int i;
    int validite_fichier=0;
    int est_protege;
    int menu_accueil;
    int menu_gestion;
    int menu_ouvrir=0;
    int menu_creer=0;
    int menu_supprimer=0;
    int menu_afficher=0;
    int nombre_lignes = 0;
    int *tableau_indices = NULL;
    int format;
    int debut_ligne;
    int fin_ligne;
    int position_personne_annuaire;
    int nouv_client;

    char nom_fichier[taille_nom_fichier];
    char ** tableau_fichiers = NULL;
    char ** tableau_lignes = NULL;
    char choix;

    personne * client = NULL;

    while(1){ // boucle premettant de boucler le programme
        nombre_fichiers = fichiers();
        tableau_fichiers = malloc(nombre_fichiers*sizeof(char*));

        for(i=0;i<nombre_fichiers;i++){
            tableau_fichiers[i] = malloc(taille_ligne*sizeof(char));
        }
        lecture_repertoire(tableau_fichiers);

        do{
            system("cls");
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
                    system("cls");
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Fermeture");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();

                    for(i=0;i<nombre_fichiers;i++){
                        free(tableau_fichiers[i]);
                    }
                    free(tableau_fichiers);

                    return 0;
                    break;
                case 1:
                    do{
                        system("cls");

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
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","(i) Le fichier doit etre de format :");
                                printf("| %-73s |\n","prenom,nom,ville,code_postal,telephone,mail,profession)");
                                printf("| %-73s |\n","et doit etre d'extension .csv ou .txt");
                                printf(" ---------------------------------------------------------------------------\n");

                                getch();

                                system("cls");

                                fflush(stdin);
                                fflush(stdout);
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Saisissez le nom du fichier :");
                                printf(" ---------------------------------------------------------------------------\n");
                                gets(nom_fichier);
                                break;
                            case 2:
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","(i) Le fichier doit etre de format :");
                                printf("| %-73s |\n","prenom,nom,ville,code_postal,telephone,mail,profession)");
                                printf("| %-73s |\n","et doit etre de type TXT ou CSV");
                                printf(" ---------------------------------------------------------------------------\n");

                                getch();

                                system("cls");

                                confim_choix_fichier = menu_selection(tableau_fichiers,nom_fichier,nombre_fichiers);
                                break;
                            default:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Champ invalide !");
                                printf(" ---------------------------------------------------------------------------\n\n");
                                break;
                            }

                        if(strcmp(nom_fichier,"/")!=0){
                            if(menu_ouvrir!=0 && confim_choix_fichier == 1){
                                validite_fichier=0;
                                if(validite(nom_fichier) == 1){ // teste l'existence du fichier grace a la fonction validite()
                                    if(ctrl_extension(nom_fichier)==0){
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","/!\\ Ce fichier n'est pas un fichier CSV ou TXT");
                                        printf(" ---------------------------------------------------------------------------\n\n");

                                        getch();
                                    }
                                    else{
                                        validite_fichier=1;
                                    }
                                }
                                else{
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Ce fichier n'existe pas");
                                    printf(" ---------------------------------------------------------------------------\n\n");

                                    getch();
                                }
                            }
                                menu_ouvrir=0;
                        }
                    }while(menu_ouvrir!=0);
                    break;
                case 2:
                    system("cls");

                    do{
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","Creer un fichier");
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-20d | %-50s |\n",0,"Retour");
                        printf("| %-20d | %-50s |\n",1,"Creer un fichier .txt");
                        printf("| %-20d | %-50s |\n",2,"Creer un fichier .csv");
                        printf(" ---------------------------------------------------------------------------\n");
                        scanf("%d",&menu_creer);

                        switch (menu_creer){
                            case 0:
                                menu_creer=0;
                                break;
                            case 1:
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","(i) Le nom du fichier ne doit pas etre existant");
                                printf(" ---------------------------------------------------------------------------\n\n");

                                getch();

                                system("cls");

                                fflush(stdin);
                                fflush(stdout);
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Nom du fichier a creer :");
                                printf(" ---------------------------------------------------------------------------\n");
                                gets(nom_fichier);

                                strcat(nom_fichier,".txt");
                                break;
                            case 2:
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","(i) Le nom du fichier ne doit pas etre existant");
                                printf(" ---------------------------------------------------------------------------\n\n");

                                getch();

                                system("cls");

                                fflush(stdin);
                                fflush(stdout);
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Nom du fichier a creer :");
                                printf(" ---------------------------------------------------------------------------\n");
                                gets(nom_fichier);

                                strcat(nom_fichier,".csv");
                                break;
                            default:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Champ invalide");
                                printf(" ---------------------------------------------------------------------------\n\n");

                                getch();
                                break;
                        }

                        if(strcmp(nom_fichier,"/")!=0){
                            if(menu_creer!=0){
                                existence_nom_fichier=0;

                                for(i=0;i<nombre_fichiers && existence_nom_fichier==0;i++){
                                    if(strcmp(nom_fichier,tableau_fichiers[i])==0){
                                        existence_nom_fichier=1;
                                    }
                                }

                                if(existence_nom_fichier==1){
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Ce nom de fichier existe deja");
                                    printf(" ---------------------------------------------------------------------------\n\n");

                                    getch();
                                }
                                else{
                                    creation_fichier(nom_fichier);
                                    nombre_fichiers = nombre_fichiers+1;

                                    for(i=0;i<nombre_fichiers;i++){
                                        free(tableau_fichiers[i]);
                                    }
                                    tableau_fichiers = realloc(tableau_fichiers,nombre_fichiers*sizeof(char*));
                                    for(i=0;i<nombre_fichiers;i++){
                                        tableau_fichiers[i] = malloc(taille_ligne*sizeof(char));
                                    }
                                    lecture_repertoire(tableau_fichiers);

                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","Fichier cree");
                                    printf(" ---------------------------------------------------------------------------\n\n");

                                    getch();
                                }
                                menu_creer=0;
                            }
                        }
                    }while(menu_creer != 0);

                    break;
                case 3:
                    do{
                        system("cls");
                        confim_choix_fichier = 1;

                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","Supprimer un fichier");
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
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","(i) L'option supprimer ne peut supprimer que des fichiers TXT ou CSV");
                                printf(" ---------------------------------------------------------------------------\n");

                                getch();

                                system("cls");

                                fflush(stdin);
                                fflush(stdout);
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Saisissez le nom du fichier : ");
                                printf(" ---------------------------------------------------------------------------\n");
                                gets(nom_fichier);
                                break;
                            case 2:
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","(i) L'option supprimer ne peut supprimer que des fichiers TXT ou CSV");
                                printf(" ---------------------------------------------------------------------------\n");

                                getch();

                                system("cls");

                                confim_choix_fichier = menu_selection(tableau_fichiers,nom_fichier,nombre_fichiers);
                                break;
                            default:
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","/!\\ Champ invalide");
                                printf(" ---------------------------------------------------------------------------\n\n");
                                break;
                            }

                        if(strcmp(nom_fichier,"/")!=0){
                            if(menu_supprimer!=0 && confim_choix_fichier==1){
                                if(validite(nom_fichier) == 1){
                                    if(ctrl_extension(nom_fichier)==0){
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","/!\\ Ce fichier n'est pas un fichier TXT ou CSV");
                                        printf(" ---------------------------------------------------------------------------\n\n");

                                        getch();
                                    }
                                    else{
                                        do{
                                            printf(" ---------------------------------------------------------------------------\n");
                                            printf("| %-73s |\n","Confirmer la suppression du fichier ?");
                                            printf(" ---------------------------------------------------------------------------\n");
                                            printf("| %-20c | %-50s |\n",'y',"Oui");
                                            printf("| %-20c | %-50s |\n",'n',"Non");
                                            printf(" ---------------------------------------------------------------------------\n\n");
                                            scanf(" %c",&choix);

                                            switch(choix){
                                                case 'y':
                                                    if(remove(nom_fichier)==0){
                                                        nombre_fichiers = nombre_fichiers-1;

                                                        for(i=0;i<nombre_fichiers;i++){
                                                            free(tableau_fichiers[i]);
                                                        }
                                                        tableau_fichiers = realloc(tableau_fichiers,nombre_fichiers*sizeof(char*));
                                                        for(i=0;i<nombre_fichiers;i++){
                                                            tableau_fichiers[i] = malloc(taille_ligne*sizeof(char));
                                                        }
                                                        lecture_repertoire(tableau_fichiers);

                                                        printf(" ---------------------------------------------------------------------------\n");
                                                        printf("| %-73s |\n","Fichier supprime");
                                                        printf(" ---------------------------------------------------------------------------\n\n");

                                                        getch();
                                                    }
                                                    else{
                                                        printf(" ---------------------------------------------------------------------------\n");
                                                        printf("| %-73s |\n","/!\\ Erreur lors de la suppression du fichier");
                                                        printf(" ---------------------------------------------------------------------------\n\n");

                                                        getch();
                                                    }
                                                    break;
                                                case 'n':
                                                    printf(" ---------------------------------------------------------------------------\n");
                                                    printf("| %-73s |\n","Annulation du processus");
                                                    printf(" ---------------------------------------------------------------------------\n\n");

                                                    getch();
                                                    break;
                                                default:
                                                    printf(" ---------------------------------------------------------------------------\n");
                                                    printf("| %-73s |\n","/!\\ Champ invalide !");
                                                    printf(" ---------------------------------------------------------------------------\n\n");
                                            }
                                        }while(choix!='y' && choix!='n');
                                    }
                                    menu_supprimer=0;
                                }
                                else{

                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Ce fichier n'existe pas");
                                    printf(" ---------------------------------------------------------------------------\n\n");

                                    getch();
                                }
                            }
                        }
                    }while(menu_supprimer!=0);
                    break;
                default:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Champ invalide !");
                    printf(" ---------------------------------------------------------------------------\n\n");

                    getch();
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

            getch();
        }
        else{
            system("cls");

            for(i=0;i<nombre_lignes;i++){
                free(tableau_lignes[i]);
            }
            free(tableau_lignes);

            client = malloc(nombre_lignes*sizeof(personne));
            lecture(nom_fichier,client);

            tableau_indices = malloc(nombre_lignes*sizeof(int));
            remplissage(tableau_indices,nombre_lignes);



            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Gestion du fichier");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20d | %-50s |\n",0,"Retour");
                printf("| %-20d | %-50s |\n",1,"Afficher le nombre de clients");
                printf("| %-20d | %-50s |\n",2,"Afficher les clients");
                printf("| %-20d | %-50s |\n",3,"Rechercher un client");
                printf("| %-20d | %-50s |\n",4,"Ajouter un client");
                printf("| %-20d | %-50s |\n",5,"Modifier un client");
                printf("| %-20d | %-50s |\n",6,"Supprimer un client");
                printf("| %-20d | %-50s |\n",7,"filtrer les clients");
                printf(" ---------------------------------------------------------------------------\n");
                scanf("%d",&menu_gestion);

                switch (menu_gestion){ // condition sur le mode de manipulation du fichier entree par l'utilisateur
                case 0:
                    free(client);

                    free(tableau_indices);



                    validite_fichier = 0;
                    break;
                case 1:
                    system("cls");

                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Nombres de clients :"); // affiche le nombre de clients
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73d |\n",nombre_lignes-1);
                    printf(" ---------------------------------------------------------------------------\n\n");

                    getch();
                    break;
                case 2: // lit et affiche le contenu du fichier
                    do{
                        system("cls");

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
                            printf("| %-73s |\n","/!\\ Champ invalide !");
                            printf(" ---------------------------------------------------------------------------\n\n");

                            getch();
                            break;
                        }
                        if(menu_afficher != 0){
                            do{
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Ligne de debut (0 si vous voulez afficher du debut) :");
                                printf(" ---------------------------------------------------------------------------\n");
                                scanf("%d",&debut_ligne);

                                if(debut_ligne<0 || debut_ligne>nombre_lignes){
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Champ invalide !");
                                    printf(" ---------------------------------------------------------------------------\n\n");

                                    getch();
                                }
                            }while(debut_ligne<0 || debut_ligne>nombre_lignes);

                            do{
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Ligne de fin (0 si vous voulez afficher jusqu'a la fin) :");
                                printf(" ---------------------------------------------------------------------------\n");
                                scanf("%d",&fin_ligne);

                                if(fin_ligne<0 || fin_ligne>nombre_lignes){
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","/!\\ Champ invalide !");
                                    printf(" ---------------------------------------------------------------------------\n\n");

                                    getch();
                                }
                            }while(fin_ligne<0 || fin_ligne>nombre_lignes);

                            affichage(client,tableau_indices,debut_ligne,fin_ligne,nombre_lignes-1,1);
                            menu_afficher=0;
                        }
                    }while(menu_afficher != 0);
                    break;
                case 3:
                    break;
                case 4:
                    nouv_client = ajout(nom_fichier,&nombre_lignes);

                    if(nouv_client>0){ // ajoute une ligne de client dans le fichier
                        client = realloc(client,nombre_lignes*sizeof(personne));
                        lecture(nom_fichier,client);

                        tableau_indices = realloc(tableau_indices,nombre_lignes*sizeof(int));
                        remplissage(tableau_indices,nombre_lignes);
                    }
                    break;
                case 5:
                    modification(client,nom_fichier,"Thauvin",4976,nombre_lignes-1);
                    break;
                case 6:
                    suppression(client,nom_fichier,5000,&nombre_lignes);
                    break;
                case 7:
                    filtre(client,tableau_indices,0,nombre_lignes);
                    break;
                default:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Champ invalide !");
                    printf(" ---------------------------------------------------------------------------\n\n");

                    getch();
                    break;
                }
            }while(validite_fichier == 1); // tant que la validite ne change pas de valeur
        }
    }
}
