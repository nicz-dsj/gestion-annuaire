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
    int menu_test=0;
    int menu_test_recherche=0;
    int nombre_lignes = 0;
    int *tableau_indices = NULL;
    int *tableau_indices_vide = NULL;
    int format;
    int debut_ligne;
    int fin_ligne;
    int position_personne_annuaire;
    int nouv_client;
    int ind_recherche;
    int ind_deb_filtre;
    int ind_fin_filtre;
    int mode_filtre;

    char nom_fichier[taille_nom_fichier];
    char ** tableau_fichiers = NULL;
    char ** tableau_lignes = NULL;
    char choix;
    char valeur_test[elements];

    personne saisie;
    personne * client = NULL;

    clock_t debut_test;
    clock_t fin_test;
    long temps_total;

    while(1){ // boucle premettant de boucler le programme
        nombre_fichiers = fichiers(); // compte le nombre de fichiers du répertoire courant
        tableau_fichiers = malloc(nombre_fichiers*sizeof(char*)); // initialise le tableau de fichiers

        for(i=0;i<nombre_fichiers;i++){
            tableau_fichiers[i] = malloc(taille_ligne*sizeof(char)); // initialise chaque ligne du tableau de fichiers
        }
        lecture_repertoire(tableau_fichiers); // remplit le tableau de fichiers

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

            switch(menu_accueil){
                case 0:
                    system("cls");
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Fermeture");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();

                    for(i=0;i<nombre_fichiers;i++){
                        free(tableau_fichiers[i]); // libère chaque ligne du tableau de fichiers
                    }
                    free(tableau_fichiers);

                    return 0;
                    // fermeture du logiciel
                    break;
                case 1:
                    do{
                        system("cls");
                        confim_choix_fichier = 1;

                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","Ouvrir un fichier");
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-20d | %-50s |\n",0,"Retour");
                        printf("| %-20d | %-50s |\n",1,"Saisir le nom d'un fichier");
                        printf("| %-20d | %-50s |\n",2,"Selectionner un fichier");
                        printf(" ---------------------------------------------------------------------------\n");
                        scanf("%d",&menu_ouvrir);

                        // exécute l'ouverture du fichier selon le mode d'ouverture
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

                        if(strcmp(nom_fichier,"/")!=0){ // contrôle la saisie du nom du fichier
                            if(menu_ouvrir!=0 && confim_choix_fichier == 1){
                                validite_fichier=0;
                                if(validite(nom_fichier) == 1){ // contrôle l'existence du fichier
                                    if(ctrl_extension(nom_fichier)==0){ // contrôle l'extension du fichier
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

                        // exécute la création du fichier selon l'extension choisi
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

                                strcat(nom_fichier,".txt"); // concaténation du nom du fichier et de l'extension ".txt"
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

                                strcat(nom_fichier,".csv"); // concaténation du nom du fichier et de l'extension ".csv"
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

                                // contrôle l'existence du nom du fichier
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
                                    // création du fichier
                                    creation_fichier(nom_fichier);
                                    nombre_fichiers = nombre_fichiers+1;

                                    for(i=0;i<nombre_fichiers;i++){
                                        free(tableau_fichiers[i]);
                                    }
                                    tableau_fichiers = realloc(tableau_fichiers,nombre_fichiers*sizeof(char*));
                                    for(i=0;i<nombre_fichiers;i++){
                                        tableau_fichiers[i] = malloc(taille_ligne*sizeof(char));
                                    }
                                    lecture_repertoire(tableau_fichiers); // remplit le tableau de fichiers

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
                        printf("| %-20d | %-50s |\n",1,"Saisir le nom d'un fichier");
                        printf("| %-20d | %-50s |\n",2,"Selectionner un fichier");
                        printf(" ---------------------------------------------------------------------------\n");
                        scanf("%d",&menu_supprimer);

                        // exécute la suppression du fichier selon le mode d'ouverture
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

                        if(strcmp(nom_fichier,"/")!=0){ // contrôle la saisie du nom du fichier
                            if(menu_supprimer!=0 && confim_choix_fichier==1){
                                if(validite(nom_fichier) == 1){ // contrôle l'existence du fichier
                                    if(ctrl_extension(nom_fichier)==0){
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","/!\\ Ce fichier n'est pas un fichier TXT ou CSV");
                                        printf(" ---------------------------------------------------------------------------\n\n");

                                        getch();
                                    }
                                    else{
                                        do{
                                            // confirmer la suppression du fichier
                                            printf(" ---------------------------------------------------------------------------\n");
                                            printf("| %-73s |\n","Confirmer la suppression du fichier ?");
                                            printf(" ---------------------------------------------------------------------------\n");
                                            printf("| %-20c | %-50s |\n",'y',"Oui");
                                            printf("| %-20c | %-50s |\n",'n',"Non");
                                            printf(" ---------------------------------------------------------------------------\n\n");
                                            scanf(" %c",&choix);

                                            switch(choix){
                                                case 'y':
                                                    if(remove(nom_fichier)==0){ // supprime le fichier
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
            free(tableau_fichiers[i]); // libère chaque ligne du tableau de fichiers
        }
        free(tableau_fichiers);

        nombre_lignes = lignes(nom_fichier); // calcule le nombre de lignes et l'affiche

        tableau_lignes = malloc(nombre_lignes*sizeof(char*)); // initialise le tableau de lignes
        for(i=0;i<nombre_lignes;i++){
            tableau_lignes[i] = malloc(taille_ligne*sizeof(char)); // initialise chaque ligne du tableau de lignes
        }
        lecture_lignes(nom_fichier,tableau_lignes); // remplit le tableau de lignes
        format = format_fichier(tableau_lignes,nombre_lignes); // récupère le format du fichier

        if(format==0){ // contrôle le format du fichier
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Ce fichier ne correspond pas au format attendu");
            printf(" ---------------------------------------------------------------------------\n\n");

            for(i=0;i<nombre_lignes;i++){
                free(tableau_lignes[i]); // libère chaque ligne du tableau de lignes
            }
            free(tableau_lignes);
            validite_fichier = 0;

            getch();
        }
        else{
            for(i=0;i<nombre_lignes;i++){
                free(tableau_lignes[i]); // libère chaque ligne du tableau de lignes
            }
            free(tableau_lignes);

            client = malloc(nombre_lignes*sizeof(personne)); // initialise le tableau de structures dynamiquement
            lecture(nom_fichier,client); // remplit le tableau de structures

            tableau_indices = malloc(nombre_lignes*sizeof(int)); // initialise le tableau d'indices
            remplissage(tableau_indices,nombre_lignes); // remplit le tableau d'indices



            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Gestion du fichier");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20d | %-50s |\n",0,"Retour");
                printf("| %-20d | %-50s |\n",1,"Afficher le nombre de clients");
                printf("| %-20d | %-50s |\n",2,"Afficher les clients");
                printf("| %-20d | %-50s |\n",3,"Afficher les clients (ayant aucun champ vide)");
                printf("| %-20d | %-50s |\n",4,"Afficher les clients (ayant des champs vides)");
                printf("| %-20d | %-50s |\n",5,"Rechercher un client");
                printf("| %-20d | %-50s |\n",6,"Filtrer");
                printf("| %-20d | %-50s |\n",7,"Ajouter un client");
                printf("| %-20d | %-50s |\n",8,"Modifier un client");
                printf("| %-20d | %-50s |\n",9,"Supprimer un client");
                printf("| %-20d | %-50s |\n",10,"Zone de test de temps d'execution");
                printf(" ---------------------------------------------------------------------------\n");
                scanf("%d",&menu_gestion);

                // exécute les fonctions de manipulation du fichier selon le paramètre du menu de gestion
                switch (menu_gestion){
                case 0:
                    free(client);
                    free(tableau_indices);

                    validite_fichier = 0;
                    break;
                case 1:
                    system("cls");

                    // affiche le nombre de clients
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Nombres de clients :");
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73d |\n",nombre_lignes-1);
                    printf(" ---------------------------------------------------------------------------\n\n");

                    getch();
                    break;
                case 2:
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

                        // affiche les clients selon le critère demandé
                        switch (menu_afficher){
                        case 0:
                            menu_afficher=0;
                            break;
                        // trie le tableau selon le critère demandé
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

                    affichage(client,tableau_indices,debut_ligne,fin_ligne,nombre_lignes-1,3);
                    break;
                case 4:
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

                    affichage(client,tableau_indices,debut_ligne,fin_ligne,nombre_lignes-1,4);
                    break;
                case 5:
                    system("cls");

                    fflush(stdin);
                    fflush(stdout);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Prenom :");
                    printf(" ---------------------------------------------------------------------------\n");
                    gets(saisie.prenom);

                    system("cls");

                    fflush(stdin);
                    fflush(stdout);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Nom :");
                    printf(" ---------------------------------------------------------------------------\n");
                    gets(saisie.nom);

                    ind_recherche = recherche_seq(client,saisie.nom,saisie.prenom,nombre_lignes-1);

                    if(ind_recherche == -1){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Ce client ne figure pas dans ce fichier");
                        printf(" ---------------------------------------------------------------------------\n\n");

                        getch();
                    }
                    else{
                        affichage(client,tableau_indices,ind_recherche,0,nombre_lignes-1,2);
                    }
                    break;
                case 6:
                    ind_deb_filtre = 0;
                    ind_fin_filtre = nombre_lignes;
                    filtre(client,tableau_indices,&ind_deb_filtre,&ind_fin_filtre);
                    break;
                case 7:
                    nouv_client = ajout(nom_fichier,&nombre_lignes);

                    if(nouv_client>0){
                        client = realloc(client,nombre_lignes*sizeof(personne));
                        lecture(nom_fichier,client);

                        tableau_indices = realloc(tableau_indices,nombre_lignes*sizeof(int));
                        remplissage(tableau_indices,nombre_lignes);
                    }
                    break;
                case 8:
                    if(modification(client,nom_fichier,nombre_lignes-1)>0){
                        lecture(nom_fichier,client);
                    }
                    break;
                case 9:
                    if(suppression(client,nom_fichier,&nombre_lignes)>0){
                        client = realloc(client,nombre_lignes*sizeof(personne));
                        lecture(nom_fichier,client);

                        tableau_indices = realloc(tableau_indices,nombre_lignes*sizeof(int));
                        remplissage(tableau_indices,nombre_lignes);
                    }
                    break;
                case 10:
                    system("cls");

                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Test de temps d'execution");
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20d | %-50s |\n",0,"Retour");
                    printf("| %-20d | %-50s |\n",1,"Recherche sequentielle");
                    printf("| %-20d | %-50s |\n",2,"Recherche dichotomique");
                    printf("| %-20d | %-50s |\n",3,"Tri rapide indirect");
                    printf("| %-20d | %-50s |\n",4,"Filtre");
                    printf(" ---------------------------------------------------------------------------\n");
                    scanf("%d",&menu_test);
                    switch(menu_test){
                        case 1:

                            system("cls");
                            fflush(stdin);
                            fflush(stdout);
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","Prenom :");
                            printf(" ---------------------------------------------------------------------------\n");
                            gets(saisie.prenom);

                            system("cls");

                            fflush(stdin);
                            fflush(stdout);
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","Nom :");
                            printf(" ---------------------------------------------------------------------------\n");
                            gets(saisie.nom);

                            debut_test = clock();
                            ind_recherche = recherche_seq(client,saisie.nom,saisie.prenom,nombre_lignes-1);
                            fin_test = clock();

                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","Temps d'execution");
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-71dms |\n",fin_test-debut_test);
                            printf(" ---------------------------------------------------------------------------\n");
                            getch();

                            do{
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Voulez vous afficher le résultat de la recherche ? :");
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-20s | %-50s |\n","y","Oui");
                                printf("| %-20s | %-50s |\n","n","Non");
                                printf(" ---------------------------------------------------------------------------\n");
                                scanf(" %c",&choix);

                                switch(choix){
                                    case 'y':
                                        if(ind_recherche == -1){
                                            printf(" ---------------------------------------------------------------------------\n");
                                            printf("| %-73s |\n","/!\\ Ce client ne figure pas dans ce fichier");
                                            printf(" ---------------------------------------------------------------------------\n\n");

                                            getch();
                                        }
                                        else{
                                            affichage(client,tableau_indices,ind_recherche,0,nombre_lignes-1,2);
                                        }
                                        break;
                                    case 'n':
                                        break;
                                    default:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","/!\\ Champ invalide !");
                                        printf(" ---------------------------------------------------------------------------\n\n");

                                        getch();
                                        break;
                                }
                            }while(choix != 'y' && choix != 'n');
                            break;
                        case 2:
                             system("cls");

                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","Recherche dichotomique");
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-20d | %-50s |\n",0,"Retour");
                            printf("| %-20d | %-50s |\n",1,"Rechercher par prenom");
                            printf("| %-20d | %-50s |\n",2,"Rechercher par nom");
                            printf("| %-20d | %-50s |\n",3,"Rechercher par ville");
                            printf("| %-20d | %-50s |\n",4,"Rechercher par code postal");
                            printf("| %-20d | %-50s |\n",5,"Rechercher par telephone");
                            printf("| %-20d | %-50s |\n",6,"Rechercher par mail");
                            printf("| %-20d | %-50s |\n",7,"Rechercher par profession");
                            printf(" ---------------------------------------------------------------------------\n");
                            scanf("%d",&menu_test_recherche);

                            if(menu_test_recherche!=0){
                                do{
                                    fflush(stdin);
                                    fflush(stdout);
                                    system("cls");

                                    switch (menu_test_recherche)
                                    {
                                    case 1:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Prenom : ");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        gets(valeur_test);
                                        break;
                                    case 2:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Nom : ");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        gets(valeur_test);
                                        break;
                                    case 3:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Ville : ");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        gets(valeur_test);
                                        break;
                                    case 4:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Code Postal : ");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        gets(valeur_test);
                                        break;
                                    case 5:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Telephone : ");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        gets(valeur_test);
                                        break;
                                    case 6:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Mail : ");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        gets(valeur_test);
                                        break;
                                    case 7:
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Profession : ");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        gets(valeur_test);
                                        break;
                                    }
                                    }while(strlen(valeur_test)<=0);

                                    tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-1,menu_test_recherche);

                                    debut_test = clock();
                                    ind_recherche = recherche_dichotomique(valeur_test,client,tableau_indices,0,nombre_lignes-1,menu_test_recherche);
                                    fin_test = clock();

                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","Temps d'execution");
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-71dms |\n",fin_test-debut_test);
                                    printf(" ---------------------------------------------------------------------------\n");
                                    getch();

                                    do{
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-73s |\n","Voulez vous afficher le résultat de la recherche ? :");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        printf("| %-20s | %-50s |\n","y","Oui");
                                        printf("| %-20s | %-50s |\n","n","Non");
                                        printf(" ---------------------------------------------------------------------------\n");
                                        scanf(" %c",&choix);

                                        switch(choix){
                                            case 'y':
                                                if(ind_recherche == -1){
                                                    printf(" ---------------------------------------------------------------------------\n");
                                                    printf("| %-73s |\n","/!\\ Ce client ne figure pas dans ce fichier");
                                                    printf(" ---------------------------------------------------------------------------\n\n");

                                                    getch();
                                                }
                                                else{
                                                    affichage(client,tableau_indices,ind_recherche,ind_recherche,1,1);
                                                }
                                                break;
                                            case 'n':
                                                break;
                                            default:
                                                printf(" ---------------------------------------------------------------------------\n");
                                                printf("| %-73s |\n","/!\\ Champ invalide !");
                                                printf(" ---------------------------------------------------------------------------\n\n");

                                                getch();
                                                break;
                                        }
                                    }while(choix != 'y' && choix != 'n');
                            }
                            break;
                            case 3:
                                system("cls");

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Tri rapide indirect");
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-20d | %-50s |\n",0,"Retour");
                                printf("| %-20d | %-50s |\n",1,"Trier par prenom");
                                printf("| %-20d | %-50s |\n",2,"Trier par nom");
                                printf("| %-20d | %-50s |\n",3,"Trier par ville");
                                printf("| %-20d | %-50s |\n",4,"Trier par code postal");
                                printf("| %-20d | %-50s |\n",5,"Trier par telephone");
                                printf("| %-20d | %-50s |\n",6,"Trier par mail");
                                printf("| %-20d | %-50s |\n",7,"Trier par profession");
                                printf(" ---------------------------------------------------------------------------\n");
                                scanf("%d",&menu_test_recherche);

                                debut_test = clock();
                                tri_rapide_indirect(client,tableau_indices,0,nombre_lignes-2,menu_test_recherche);
                                fin_test = clock();

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Temps d'execution");
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-71dms |\n",fin_test-debut_test);
                                printf(" ---------------------------------------------------------------------------\n");
                                getch();

                                do{
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-73s |\n","Voulez vous afficher le résultat du tri ? :");
                                    printf(" ---------------------------------------------------------------------------\n");
                                    printf("| %-20s | %-50s |\n","y","Oui");
                                    printf("| %-20s | %-50s |\n","n","Non");
                                    printf(" ---------------------------------------------------------------------------\n");
                                    scanf(" %c",&choix);

                                    switch(choix){
                                        case 'y':
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
                                            break;
                                        case 'n':
                                            break;
                                        default:
                                            printf(" ---------------------------------------------------------------------------\n");
                                            printf("| %-73s |\n","/!\\ Champ invalide !");
                                            printf(" ---------------------------------------------------------------------------\n\n");

                                            getch();
                                            break;
                                    }
                                }while(choix != 'y' && choix != 'n');

                                break;
                            case 4:
                                temps_total = 0;
                                ind_deb_filtre = 0;
                                ind_fin_filtre = nombre_lignes;
                                temps_total = filtre_test(client,tableau_indices,&ind_deb_filtre,&ind_fin_filtre);

                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-73s |\n","Temps d'execution");
                                printf(" ---------------------------------------------------------------------------\n");
                                printf("| %-71ldms |\n",temps_total);
                                printf(" ---------------------------------------------------------------------------\n");
                                getch();
                                break;
                        default:
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","/!\\ Champ invalide !");
                            printf(" ---------------------------------------------------------------------------\n\n");

                            getch();
                            break;
                    }
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
