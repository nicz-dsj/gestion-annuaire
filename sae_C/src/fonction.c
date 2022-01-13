#include "main.h"
#include "format.c"

struct personne{ // creation de structure pour le client
    char prenom[elements];
    char nom[elements];
    char ville[elements];
    char code_postal[elements];
    char telephone[elements];
    char mail[elements];
    char profession[elements];
};

typedef struct personne personne;

int fichiers();
void lecture_repertoire(char **);
int menu_selection(char **,char *,int);
int validite(char *);
void creation_fichier(char *);
int lignes(char *);
void lecture_lignes(char *, char **);
void lecture(char *,personne *);
void remplissage(int *,int);
void permuter(int *,int *);
void tri_rapide_indirect(personne *,int *,int,int,int);
int recherche_seq(personne *, char *, char *, int);
int recherche_dichotomique(char *,personne *, int *, int,int,int);
int encadrement_sup(char *, personne *, int *, int, int,int);
int encadrement_inf(char *, personne *, int *, int, int);
void filtre (personne *, int *, int*,int*);
void affichage(personne *,int*,int,int,int,int);
int ajout(char *,int *);
int modification(personne *,char *,int);
int suppression(personne *,char *,int *);

/**
 * @fn int fichiers()
 *
 * @brief fonction qui compte le nombre de fichier dans le répertoire courant
 * @return int : le nombre de fichiers contenu dans le répertoire courant
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
int fichiers(){
    int fichiers=0;
    DIR * dir;
    struct dirent * entite;

    dir = opendir("."); // ouvre le répertoire courant
    if(dir != NULL){

        entite = readdir(dir);
        while(entite != NULL){
            if(!strcmp(entite->d_name,".") || !strcmp(entite->d_name,"..")){ // passe ces fichiers
                entite = readdir(dir);
            }
            else{
                // compte le nombre de fichiers contenus dans le répertoire courant
                fichiers++;
                entite = readdir(dir);
            }

        }

        closedir(dir);
    }

    return fichiers;
}

/**
 * @fn void lecture_repertoire(char ** liste)
 *
 * @brief fonction qui lit et stocke le nom des fichiers du répertoire courant dans une liste
 * @param liste correspond au tableau à 2 dimensions contenant le nom des fichiers
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
void lecture_repertoire(char ** liste){
    int i;

    DIR * dir;
    struct dirent * entite;

    dir = opendir("."); // ouvre le répertoire courant
    if(dir != NULL){
        i=0;
        entite = readdir(dir);
        while(entite != NULL){
            if(!strcmp(entite->d_name,".") || !strcmp(entite->d_name,"..")){ // passe ces fichiers
                entite = readdir(dir);
            }
            else{
                // copie le nom des fichiers dans le tableau
                strcpy(liste[i],entite->d_name);
                i++;
                entite = readdir(dir);
            }
        }

        closedir(dir);
    }
}

/**
 * @fn menu_selection(char ** liste, char * fichier, int lignes)
 *
 * @brief fonction qui affiche un menu de sélection et définit un fichier sélectionné a ouvrir
 * @param liste correspond au tableau à 2 dimensions contenant le nom des fichiers
 * @param fichier correspond au nom du fichier
 * @param lignes correspond au nombre de fichiers
 * @return int : 1 si le fichier est selectionné, 0 si le champ est invalide
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
int menu_selection(char ** liste, char * fichier, int lignes){

    int i;
    int choix_fichier;
    int confirm;

    printf(" ---------------------------------------------------------------------------\n");
    printf("| %-73s |\n","Selectionnez un fichier");
    printf(" ---------------------------------------------------------------------------\n");
    printf("| %-20d | %-50s |\n",0,"Retour");
    printf("|---------------------------------------------------------------------------|\n");

    // affiche les fichiers existants
    for(i=0;i<lignes;i++){
        printf("| %-20d | %-50s |\n",i+1,liste[i]);
        if(i<lignes-1){
            printf("|---------------------------------------------------------------------------|\n");
        }
        else{
            printf(" ---------------------------------------------------------------------------\n");
        }
    }
    scanf("%d",&choix_fichier);

    if(choix_fichier<0 || choix_fichier>lignes){
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","/!\\ Champ invalide");
        printf(" ---------------------------------------------------------------------------\n\n");

        getch();

        confirm = 0; // quitte la fonction
    }
    else if(choix_fichier==0){
        confirm = 0;
    }
    else{
        // lorsque un fichier est selectionné
        strcpy(fichier,liste[choix_fichier-1]);
        confirm = 1;
    }

    return confirm;
}

/**
 * @fn int validite(char* filename)
 * @brief teste l'existence du fichier
 *
 * @param filename correspond au nom du fichier
 * @return int : 0 si le fichier n'existe pas, 1 si il existe
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
 * @fn void creation_fichier(char * filename)
 *
 * @brief fonction qui crée un fichier
 * @param filename correspond au nom du fichier
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
void creation_fichier(char * filename){
    FILE * pointeur;
    pointeur = fopen(filename, "a+");
    fclose(pointeur);

}

/**
 * @fn int lignes(char* filename)
 *
 * @brief fonction qui compte le nombre de lignes d'un fichier ouvert
 * @param filename correspond au nom du fichier
 * @return int : le nombre de lignes d'un fichier ouvert
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
int lignes(char* filename){
    FILE * pointeur;
    pointeur = fopen(filename,"a+");

    int nlignes = 1;
    char lignes[taille_ligne];

    // compte le nombre de lignes
    while(fgets(lignes,taille_ligne,pointeur) != NULL){
        nlignes++;
    }

    fclose(pointeur);

    return nlignes;
}

/**
 * @fn void lecture_lignes(char * filename, char ** tableau2d)
 *
 * @brief fonction qui remplit un tableau à 2 dimensions de contenu de chaque ligne d'un fichier ouvert
 * @param filename correspond au nom du fichier
 * @param tableau2d correspond au tableau à 2 dimensions
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
void lecture_lignes(char * filename, char ** tableau2d){
    FILE * pointeur;
    pointeur = fopen(filename,"a+");
    int i=0;
    char ligne[taille_ligne];

    // copie les lignes dans le tableau
    while(fgets(ligne,taille_ligne,pointeur) != NULL){
        strcpy(tableau2d[i],ligne);
        i++;
    }

    fclose(pointeur);
}

/**
 * @fn void lecture(char* filename, int taille, int mode)
 *
 * @brief fonction qui lit les caracteres d'un fichier
 * @param filename correspond au nom du fichier
 * @param client correspond au tableau de structures
 * @param taille correspond à la taille du tableau de structures
 *
 * Etudiant(s) référent(s) : James MOREL (auteur de la fonction) & Nicolas DE SAINT JEAN
 */
void lecture(char* filename, personne * client){
    FILE * fichier = NULL;
    fichier = fopen(filename,"a+");
    int i=0; // indice des caratères d'une chaine
    int j=0; // indice de la ligne
    int virgule = 0; // nombre de virgules rencontrées dans la ligne

    char caractere_lu;

    do{
        caractere_lu = fgetc(fichier);

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
                client[j].prenom[i] = caractere_lu;
                i++;
                client[j].prenom[i] = '\0';
                break;
            case 1:
                client[j].nom[i] = caractere_lu;
                i++;
                client[j].nom[i] = '\0';
                break;
            case 2:
                client[j].ville[i] = caractere_lu;
                i++;
                client[j].ville[i] = '\0';
                break;
            case 3:
                client[j].code_postal[i] = caractere_lu;
                i++;
                client[j].code_postal[i] = '\0';
                break;
            case 4:
                client[j].telephone[i] = caractere_lu;
                i++;
                client[j].telephone[i] = '\0';
                break;
            case 5:
                client[j].mail[i] = caractere_lu;
                i++;
                client[j].mail[i] = '\0';
                break;
            case 6:
                client[j].profession[i] = caractere_lu;
                i++;
                client[j].profession[i] = '\0';
                break;
            default:
                break;
            }
        break;
        }
    }while(caractere_lu != EOF);

    fclose(fichier);
}

/**
 * @fn remplissage(int * tableau, int taille)
 *
 * @brief fonction qui remplit le tableau d'indices
 * @param tableau correspond au tableau d'indices
 * @param taille correspond à la taille du tableau de structures
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN & James MOREL
 */
void remplissage(int * tableau, int taille){
    int i;
    for(i=0;i<taille;i++){
        tableau[i] = i;
    }
}

/**
 * @fn permuter(int * a, int * b)
 *
 * @brief fonction qui permutent 2 valeurs
 * @param a correspond à l'adresse de la première valeur
 * @param b correspond à l'adresse de la deuxième valeur
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN & James MOREL
 */
void permuter(int * a, int * b){
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @fn tri_rapide_indirect(personne * client, int * index, int deb, int fin, int mode)
 *
 * @brief fonction de tri rapide de manière indirecte pour éviter de déplacer tout le tableau de structure
 * @param client correspond au tableau de structures
 * @param index correspond au tableau d'indices à trier
 * @param deb correspond au début de la zone a trier
 * @param fin correspond à la fin de la zone à trier
 * @param mode correspond au paramètre avec lequel on triera le tableau
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN & James MOREL
 */
void tri_rapide_indirect(personne * client, int * index, int deb, int fin, int mode){
    int pivot;
    int i;
    int j;
    if(deb < fin){
        pivot = deb;
        i = deb;
        j = fin;

        while(i<j){
            switch (mode){
            case 1:
                while(strcmp(client[index[i]].prenom, client[index[pivot]].prenom) <= 0 && i <= j){ // compare la valeur du pivot à celle du tableau
                    i++;
                }
                while(strcmp(client[index[j]].prenom, client[index[pivot]].prenom) > 0 && i <= j){
                    j--;
                }
                break;
            case 2:
                while(strcmp(client[index[i]].nom, client[index[pivot]].nom) <= 0 && i <= j){
                    i++;
                }
                while(strcmp(client[index[j]].nom, client[index[pivot]].nom) > 0 && i <= j){
                    j--;
                }
                break;
            case 3:
                while(strcmp(client[index[i]].ville, client[index[pivot]].ville) <= 0 && i <= j){
                    i++;
                }
                while(strcmp(client[index[j]].ville, client[index[pivot]].ville) > 0 && i <= j){
                    j--;
                }
                break;
            case 4:
                while(strcmp(client[index[i]].code_postal, client[index[pivot]].code_postal) <= 0 && i <= j){
                    i++;
                }
                while(strcmp(client[index[j]].code_postal, client[index[pivot]].code_postal) > 0 && i <= j){
                    j--;
                }
                break;
            case 5:
                while(strcmp(client[index[i]].telephone, client[index[pivot]].telephone) <= 0 && i <= j){
                    i++;
                }
                while(strcmp(client[index[j]].telephone, client[index[pivot]].telephone) > 0 && i <= j){
                    j--;
                }
                break;
            case 6:
                while(strcmp(client[index[i]].mail, client[index[pivot]].mail) <= 0 && i <= j){
                    i++;
                }
                while(strcmp(client[index[j]].mail, client[index[pivot]].mail) > 0 && i <= j){
                    j--;
                }
                break;
            case 7:
                while(strcmp(client[index[i]].profession, client[index[pivot]].profession) <= 0 && i <= j){
                    i++;
                }
                while(strcmp(client[index[j]].profession, client[index[pivot]].profession) > 0 && i <= j){
                    j--;
                }
                break;
            }

            if(i<j){
                permuter(&index[i],&index[j]); // permute les valeurs du tableau d'indices
                i++;
                j--;
            }
        }
        permuter(&index[pivot],&index[j]); // permute le pivot avec la dernière valeur plus petite qu'elle même
        // appels récursifs de la fonction sur les 2 parties du tableau
        tri_rapide_indirect(client,index,deb,j-1,mode);
        tri_rapide_indirect(client,index,j+1,fin,mode);
    }
}

/**
 * @fn recherche_seq(personne * client, char * saisie_nom, char * saisie_prenom, int taille)
 *
 * @brief fonction de recherche séquentielle dans le tableau de structures de l'annuaire
 * @param client correspond au tableau de structures
 * @param saisie_nom correspond au nom recherché
 * @param saisie_prenom correspond au prénom recherché
 * @param taille correspond à la taille du tableau de structures
 * @return int : retourne l'indice de la valeur recherchée, -1 si elle n'est pas trouvée
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
int recherche_seq(personne * client, char * saisie_nom, char * saisie_prenom, int taille){
    int i, ind=-1;

    for(i=0;i<taille && ind == -1;i++){ // cherche dans le tableau tant que ne trouve pas la valeur ou qu'on n'est pas à la fin
        if (strcmp(client[i].nom,saisie_nom)==0){ // contrôle si le nom recherché correspond à celui du tableau de structures
            if(strcmp(client[i].prenom,saisie_prenom)==0){ // contrôle si le prénom recherché correspond à celui du tableau de structures
                ind = i;
            }
        }
    }

    return ind;
}

/**
 * @fn recherche_dichotomique(char * valeur_recherche,personne * client, int * index, int debut, int fin, int mode)
 *
 * @brief fonction de recherche dichotomique dans le tableau de structures de l'annuaire (s'utilise dans tableau trié au préalable)
 * @param valeur_recherche correspond à la valeur à rechercher
 * @param client correspond au tableau de structures
 * @param index correspond au tableau d'indices
 * @param debut correspond au début de la zone de recherche
 * @param fin correspond à la fin de la zone de recherche
 * @param mode correspond au paramètre avec lequel le tableau est trié
 * @return int : retourne l'indice de la valeur recherchée, -1 si elle n'est pas trouvée
 *
 * Etudiant(s) référent(s) : James MOREL (auteur de la fonction) & Nicolas DE SAINT JEAN
 */
int recherche_dichotomique(char * valeur_recherche,personne * client, int * index, int debut, int fin, int mode){
    int ind =-1, pos, trouve = 0;

    switch (mode)
    {
    case 1:
        while (trouve == 0 && debut <= fin) // les conditions de sortie de boucle sont de trouver la valeur ou que la zone de recherche soit <= 1
        {
            pos = (debut + fin)/2; // correspond au milieu de la zone de recherche

            // vérification de la valeur au milieu de la zone de recherche
            if(strcmp(valeur_recherche, client[index[pos]].prenom) == 0){ // si c'est la valeur recherchée, on quitte la boucle
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].prenom) > 0){ // si la valeur est plus petite que la valeur recherchée, on réduit la zone de recherche en déplacant le début
                    debut = pos + 1;
                }
                else{ // si la valeur est plus grande que la valeur recherchée, on réduit la zone de recherche en déplacant la fin
                    fin = pos -1;
                }
            }
        }
        break;
    case 2:
        while (trouve == 0 && debut <= fin)
        {
            pos = (debut + fin)/2;

            if(strcmp(valeur_recherche, client[index[pos]].nom) == 0){
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].nom) > 0){
                    debut = pos + 1;
                }
                else{
                    fin = pos -1;
                }
            }
        }
        break;
    case 3:
        while (trouve == 0 && debut <= fin)
        {
            pos = (debut + fin)/2;

            if(strcmp(valeur_recherche, client[index[pos]].ville) == 0){
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].ville) > 0){
                    debut = pos + 1;
                }
                else{
                    fin = pos -1;
                }
            }
        }
        break;
    case 4:
        while (trouve == 0 && debut <= fin)
        {
            pos = (debut + fin)/2;

            if(strcmp(valeur_recherche, client[index[pos]].code_postal) == 0){
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].code_postal) > 0){
                    debut = pos + 1;
                }
                else{
                    fin = pos -1;
                }
            }
        }
        break;
    case 5:
        while (trouve == 0 && debut <= fin)
        {
            pos = (debut + fin)/2;

            if(strcmp(valeur_recherche, client[index[pos]].telephone) == 0){
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].telephone) > 0){
                    debut = pos + 1;
                }
                else{
                    fin = pos -1;
                }
            }
        }
        break;
    case 6:
        while (trouve == 0 && debut <= fin)
        {
            pos = (debut + fin)/2;

            if(strcmp(valeur_recherche, client[index[pos]].mail) == 0){
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].mail) > 0){
                    debut = pos + 1;
                }
                else{
                    fin = pos -1;
                }
            }
        }
        break;
    case 7:
        while (trouve == 0 && debut <= fin)
        {
            pos = (debut + fin)/2;

            if(strcmp(valeur_recherche, client[index[pos]].profession) == 0){
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].profession) > 0){
                    debut = pos + 1;
                }
                else{
                    fin = pos -1;
                }
            }
        }
        break;

    default:
        break;
    }

    return ind+1;
}

/**
 * @fn int encadrement_sup(char * valeur_recherche, personne * client, int * index, int taille, int depart,int mode)
 *
 * @brief fonction qui se lance dans un tableau trié et permet d'avoir la dernière position où se trouve une valeur donnée à partir de la position d'une de ses occurences
 * @param valeur_recherche correspond à la valeur à borner
 * @param client correspond au tableau de structures
 * @param index correspond au tableau d'indices
 * @param taille correspond à la fin de la zone à encadrer
 * @param depart correspond à la position de la première occurence
 * @param mode corrspond au paramètre avec lequel le tableau est trié
 * @return int : la position de la dernière occurence de la valeur
 *
 * Etudiant(s) référent(s) : James MOREL (auteur de la fonction) & Nicolas DE SAINT JEAN
 */
int encadrement_sup(char * valeur_recherche, personne * client, int * index, int taille, int depart,int mode){
    int pos = depart;

    // exécute selon le paramètre de tri du tableau
    switch (mode)
    {
    case 1:
        // incrémente l'indice jusqu'à ne plus tomber sur une occurence de la valeur recherchée
        while (strcmp(valeur_recherche, client[index[pos]].prenom) == 0)
        {
            pos++;
        }
        break;
    case 2:
        while (strcmp(valeur_recherche, client[index[pos]].nom) == 0)
        {
            pos++;
        }
        break;
    case 3:
        while (strcmp(valeur_recherche, client[index[pos]].ville) == 0)
        {
            pos++;
        }
        break;
    case 4:
        while (strcmp(valeur_recherche, client[index[pos]].code_postal) == 0)
        {
            pos++;
        }
        break;
    case 5:
        while (strcmp(valeur_recherche, client[index[pos]].telephone) == 0)
        {
            pos++;
        }
        break;
    case 6:
        while (strcmp(valeur_recherche, client[index[pos]].mail) == 0)
        {
            pos++;
        }
        break;
    case 7:
        while (strcmp(valeur_recherche, client[index[pos]].profession) == 0)
        {
            pos++;
        }
        break;

    default:
        break;
    }
    return pos;
}

/**
 * @fn int encadrement_inf(char * valeur_recherche, personne * client, int * index, int depart,int mode)
 *
 * @brief fonction qui se lance dans un tableau trié et permet d'avoir la dernière position où se trouve une valeur donnée à partir de la position d'une de ses occurences
 * @param valeur_recherche correspond à la valeur à borner
 * @param client correspond au tableau de structures
 * @param index correspond au tableau d'indices
 * @param depart correspond à la position de la première occurence
 * @param mode corrspond au paramètre avec lequel le tableau est trié
 * @return int : la position de la dernière occurence de la valeur
 *
 * Etudiant(s) référent(s) : James MOREL (auteur de la fonction) - Nicolas DE SAINT JEAN
 */
int encadrement_inf(char * valeur_recherche, personne * client, int * index, int depart,int mode){
    int pos = depart;

    // exécute selon le paramètre de tri du tableau
    switch (mode)
    {
    case 1:
        // décrémente l'indice jusqu'à ne plus tomber sur une occurence de la valeur recherchée
        while (strcmp(valeur_recherche, client[index[pos-2]].prenom) == 0)
        {
            pos--;
        }
        break;
    case 2:
        while (strcmp(valeur_recherche, client[index[pos-2]].nom) == 0)
        {
            pos--;
        }
        break;
    case 3:
        while (strcmp(valeur_recherche, client[index[pos-2]].ville) == 0)
        {
            pos--;
        }
        break;
    case 4:
        while (strcmp(valeur_recherche, client[index[pos-2]].code_postal) == 0)
        {
            pos--;
        }
        break;
    case 5:
        while (strcmp(valeur_recherche, client[index[pos-2]].telephone) == 0)
        {
            pos--;
        }
        break;
    case 6:
        while (strcmp(valeur_recherche, client[index[pos-2]].mail) == 0)
        {
            pos--;
        }
        break;
    case 7:
        while (strcmp(valeur_recherche, client[index[pos-2]].profession) == 0)
        {
            pos--;
        }
        break;

    default:
        break;
    }
    return pos;
}

/**
 * @fn filtre(personne * client,int * tab_ind_filtre, int * deb,int * fin)
 *
 * @brief fonction qui permet de filtrer l'annuaire selon des paramètres qui peuvent être superposés
 * @param client correspond au tableau de structures
 * @param tab_ind_filtre correspond au tableau d'indices
 * @param deb correspond au début de la zone à filtrer
 * @param fin correspond à la fin de la zone a filtrer
 *
 * Etudiant(s) référent(s) : James MOREL (auteur de la fonction)
 */
void filtre (personne * client,int * tab_ind_filtre, int * deb,int * fin){
    char valeur[50];
    int mode,pos_valeur; // "mode" correspond au parametre avec lequel on filtre l'annuaire et "pos_valeur" correspond à la position d'une ligne de l'annuaire qui répond au critère donné
    do{
        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Filtrer");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20d | %-50s |\n",0,"Retour");
            printf("| %-20d | %-50s |\n",1,"Filtrer par prenom");
            printf("| %-20d | %-50s |\n",2,"Filtrer par nom");
            printf("| %-20d | %-50s |\n",3,"Filtrer par ville");
            printf("| %-20d | %-50s |\n",4,"Filtrer par code postal");
            printf("| %-20d | %-50s |\n",5,"Filtrer par telephone");
            printf("| %-20d | %-50s |\n",6,"Filtrer par mail");
            printf("| %-20d | %-50s |\n",7,"Filtrer par profession");
            printf(" ---------------------------------------------------------------------------\n");
            scanf("%d", &mode);

            if(mode < 0 || mode > 7){
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","/!\\ Champ invalide !");
                printf(" ---------------------------------------------------------------------------\n\n");

                getch();
            }
        }while(mode < 0 || mode > 7);

        if (mode>0)
        {
          do{
            fflush(stdin);
            fflush(stdout);
            system("cls");

             // saisie de la valeur selon le critère
            switch (mode)
            {
            case 1:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Prenom : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 2:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Nom : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 3:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Ville : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 4:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Code Postal : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 5:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Telephone : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 6:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Mail : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 7:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Profession : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            }
            }while(strlen(valeur)<=0);

            tri_rapide_indirect(client,tab_ind_filtre,*deb,*fin-1,mode); // trie la partie du tableau a filtrer
            pos_valeur = recherche_dichotomique(valeur,client,tab_ind_filtre,*deb,*fin,mode); // trouve une occurence de la valeur à filtrer

            if (pos_valeur>0)
            {
                // encadre les valeurs qui répondent au critère
                *deb=encadrement_inf(valeur,client,tab_ind_filtre,pos_valeur,mode);
                *fin=encadrement_sup(valeur,client,tab_ind_filtre,*fin,pos_valeur,mode);

                affichage(client,tab_ind_filtre,*deb,*fin,(*fin)-(*deb),1); // affiche le résultat du filtre
            }
            else{
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","/!\\ Aucun client ne répond a ce critere");
                printf(" ---------------------------------------------------------------------------\n\n");

                getch();
            }
        }
    }while(mode != 0);
}

/**
 * @fn void affichage(personne * client, int * index, int deb, int fin, int taille, int mode)
 *
 * @brief affiche la liste client ou un seul client recherché selon le mode d'affichage
 * @param client correspond au tableau de structures
 * @param index correspond au tableau d'indices
 * @param deb correspond a la ligne du début que l'on souhaite afficher
 * @param fin correspond a la ligne de fin jusqu'où l'on souhaite afficher
 * @param taille correspond au nombre de lignes
 * @param mode correspond au mode d'affichage
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
void affichage(personne * client, int * index, int deb, int fin, int taille, int mode){
    int i;
    int champ_vide;
    switch (mode){
        case 1: // affiche tous ou une partie des clients
            if(fin==0){
                fin = taille;
            }

            if (deb==0){
                i=0;
            }
            else{
                i=deb-1;
            }

            system("cls");

            while(i<fin){
                // affiche les informations des clients
                printf(" ---------------------------------------------------------------------------\n");
                printf("| Ligne %-67d |\n",i+1);
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","Prenom",client[index[i]].prenom);
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","Nom",client[index[i]].nom);
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","Ville",client[index[i]].ville);
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","Code Postal",client[index[i]].code_postal);
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","Telephone",client[index[i]].telephone);
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","Mail",client[index[i]].mail);
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","Profession",client[index[i]].profession);
                printf(" ---------------------------------------------------------------------------\n\n");
                i++;
            }

            getch();
            break;
        case 2: // affiche un seul client
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","*");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Prenom",client[deb].prenom);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Nom",client[deb].nom);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Ville",client[deb].ville);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Code Postal",client[deb].code_postal);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Telephone",client[deb].telephone);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Mail",client[deb].mail);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Profession",client[deb].profession);
            printf(" ---------------------------------------------------------------------------\n\n");

            getch();
            break;
        case 3: // affiche les clients qui possèdent aucune information manquante
            if(fin==0){
                fin = taille;
            }

            if (deb==0){
                i=0;
            }
            else{
                i=deb-1;
            }

            system("cls");

            while(i<fin){
                champ_vide = 1;

                if(strcmp(client[i].prenom,"")!=0){ // vérifie si le champ n'est pas vide
                    if(strcmp(client[i].nom,"")!=0){
                        if(strcmp(client[i].ville,"")!=0){
                            if(strcmp(client[i].code_postal,"")!=0){
                                if(strcmp(client[i].telephone,"")!=0){
                                    if(strcmp(client[i].mail,"")!=0){
                                        if(strcmp(client[i].profession,"")!=0){
                                            champ_vide = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if(champ_vide==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| Ligne %-67d |\n",i+1);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Prenom",client[i].prenom);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Nom",client[i].nom);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Ville",client[i].ville);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Code Postal",client[i].code_postal);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Telephone",client[i].telephone);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Mail",client[i].mail);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Profession",client[i].profession);
                    printf(" ---------------------------------------------------------------------------\n\n");
                }

                i++;
            }
            getch();
            break;
        case 4: // affiche les clients dont il manque une ou plusieurs informations
            if(fin==0){
                fin = taille;
            }

            if (deb==0){
                i=0;
            }
            else{
                i=deb-1;
            }

            system("cls");

            while(i<fin){
                champ_vide = 0;

                if(strcmp(client[i].prenom,"")==0){ // vérifie si le champ est vide
                    champ_vide = 1;
                }
                if(strcmp(client[i].nom,"")==0){
                    champ_vide = 1;
                }
                if(strcmp(client[i].ville,"")==0){
                    champ_vide = 1;
                }
                if(strcmp(client[i].code_postal,"")==0){
                    champ_vide = 1;
                }
                if(strcmp(client[i].telephone,"")==0){
                    champ_vide = 1;
                }
                if(strcmp(client[i].mail,"")==0){
                    champ_vide = 1;
                }
                if(strcmp(client[i].profession,"")==0){
                    champ_vide = 1;
                }

                if(champ_vide==1){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| Ligne %-67d |\n",i+1);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Prenom",client[i].prenom);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Nom",client[i].nom);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Ville",client[i].ville);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Code Postal",client[i].code_postal);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Telephone",client[i].telephone);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Mail",client[i].mail);
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-20s | %-50s |\n","Profession",client[i].profession);
                    printf(" ---------------------------------------------------------------------------\n\n");
                }

                i++;
            }
            getch();
            break;
    }
}

/**
 * @fn int ajout(char * filename, int * taille)
 *
 * @brief fonction qui permet d'ajouter un client dans le fichier ouvert
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de clients du fichier
 * @return int : 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur, supérieur à 0 si la fonction s'est bien exécutée
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
int ajout(char * filename, int * taille){
    personne client;
    FILE * fichier;
    fichier = fopen(filename,"a+");

    int i;
    int n;
    int confirmation=0;

    char choix;

    do{
        system("cls");

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Ajouter un client");
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Combien de clients voulez vous ajouter ? (0 pour quitter) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%d",&n);

        if(n<0){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Champ invalide !");
            printf(" ---------------------------------------------------------------------------\n\n");

            getch();
        }
    }while(n<0);

    system("cls");

    printf(" ---------------------------------------------------------------------------\n");
    printf("| %-73s |\n","(i) Lors de votre saisie veuillez ne pas mettre de virgule");
    printf(" ---------------------------------------------------------------------------\n\n");

    getch();

    for(i=0;i<n && n!=0;i++){
        fflush(stdin);
        fflush(stdout);

        // saisie des informations du nouveau client, pour ne pas remplir un ou plusieurs champs, on presse la touche entrée
        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Prenom : (touche entree pour passer) :");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.prenom);

            confirmation = ctrl_virgule(client.prenom,strlen(client.prenom)); // controle si la saisie contient des virgules

            if (strcmp(client.prenom,"\0") !=0 ){ // contrôle si la saisie est la touche entrée
                if(confirmation==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
            }
            else{
                confirmation = 1;
            }
        }while(confirmation!=1);

        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Nom (touche entree pour passer) :");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.nom);

            confirmation = ctrl_virgule(client.nom,strlen(client.nom));

            if (strcmp(client.nom,"\0") !=0 ){
                if(confirmation==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
            }
            else{
                confirmation = 1;
            }
        }while(confirmation!=1);

        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Ville (touche entree pour passer) :");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.ville);

            confirmation = ctrl_virgule(client.ville,strlen(client.ville));

            if (strcmp(client.ville,"\0") !=0 ){
                if(confirmation==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
            }
            else{
                confirmation = 1;
            }
        }while(confirmation!=1);

        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Code Postal (touche entree pour passer) :");
            printf("| %-73s |\n","(format : \"00000\")");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.code_postal);

            confirmation = format_code_postal(client.code_postal,strlen(client.code_postal)); // contrôle si le format est respecté

            if(strcmp(client.code_postal,"\0") != 0){
                if(confirmation==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez respecter le format \"000000\"");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
                else if(confirmation==-1){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
            }
            else{
                confirmation = 1;
            }
        }while(confirmation!=1);

        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Telephone (touche entree pour passer) :");
            printf("| %-73s |\n","(format : \"00.00.00.00.00\")");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.telephone);

            confirmation = format_telephone(client.telephone,strlen(client.telephone));

            if(strcmp(client.telephone,"\0")!=0){
                if(confirmation==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez respecter le format \"00.00.00.00.00\"");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
                else if(confirmation==-1){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
            }
            else{
                confirmation=1;
            }
        }while(confirmation!=1);


        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Mail (touche entree pour passer) :");
            printf("| %-73s |\n","(format : \"texte@texte.domaine\")");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.mail);

            confirmation = format_mail(client.mail,strlen(client.mail));

            if(strcmp(client.mail,"\0")!=0){
                if(confirmation==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez respecter le format \"texte@texte.domaine\"");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
                else if(confirmation==-1){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
            }
            else{
                confirmation=1;
            }
        }while(confirmation!=1);

        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Profession (touche entree pour passer) :");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.profession);

            confirmation = ctrl_virgule(client.profession,strlen(client.profession));

            if (strcmp(client.profession,"\0") !=0 ){
                if(confirmation==0){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                    printf(" ---------------------------------------------------------------------------\n");

                    getch();
                }
            }
            else{
                confirmation = 1;
            }
        }while(confirmation!=1);

        system("cls");

        // affiche les informations du nouveau client

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Nouveau client");
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.prenom, "\0") != 0){
            printf("| %-20s | %-50s |\n","Prenom",client.prenom);
        }
        else{
            printf("| %-20s |                                                    |\n","Prenom");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.nom, "\0") != 0){
            printf("| %-20s | %-50s |\n","Nom",client.nom);
        }
        else{
            printf("| %-20s |                                                    |\n","Nom");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.ville, "\0") != 0){
            printf("| %-20s | %-50s |\n","Ville",client.ville);
        }
        else{
            printf("| %-20s |                                                    |\n","Ville");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.code_postal, "\0") != 0){
            printf("| %-20s | %-50s |\n","Code Postal",client.code_postal);
        }
        else{
            printf("| %-20s |                                                    |\n","Code Postal");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.telephone, "\0") != 0){
            printf("| %-20s | %-50s |\n","Telephone",client.telephone);
        }
        else{
            printf("| %-20s |                                                    |\n","Telephone");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.mail, "\0") != 0){
            printf("| %-20s | %-50s |\n","Mail",client.mail);
        }
        else{
            printf("| %-20s |                                                    |\n","Mail");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.profession, "\0") != 0){
            printf("| %-20s | %-50s |\n","Profession",client.profession);
        }
        else{
            printf("| %-20s |                                                    |\n","Profession");
        }
        printf(" ---------------------------------------------------------------------------\n\n");

        do{
            // confirmation de l'ajout du nouveau client
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Confirmer l'ajout de ce nouveau client ? :");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","y","Oui");
            printf("| %-20s | %-50s |\n","n","Non");
            printf(" ---------------------------------------------------------------------------\n");

            scanf(" %c",&choix);

            switch (choix){
                case 'y':
                    // écrit dans le fichier les informations du nouveau client
                    if(strcmp(client.prenom, "\0") != 0){
                        fprintf(fichier,"%s",client.prenom);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.nom, "\0") != 0){
                        fprintf(fichier,"%s",client.nom);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.ville, "\0") != 0){
                        fprintf(fichier,"%s",client.ville);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.code_postal, "\0") != 0){
                        fprintf(fichier,"%s",client.code_postal);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.telephone, "\0") != 0){
                        fprintf(fichier,"%s",client.telephone);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.mail, "\0") != 0){
                        fprintf(fichier,"%s",client.mail);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.profession, "\0") != 0){
                        fprintf(fichier,"%s",client.profession);
                    }
                    fprintf(fichier,"\n");

                    *taille = *taille + 1;

                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Client ajoute");
                    printf(" ---------------------------------------------------------------------------\n\n");

                    getch();
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

                    getch();
                    break;
            }
        }while(choix != 'y' && choix != 'n');
    }

    fclose(fichier);

    return n;
}

/**
 * @fn int modification(personne * client, char * filename, int taille)
 *
 * @brief fonction qui permet de modification des informations d'un client
 * @param client correspond au tableau de structures
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de lignes du fichier
 * @return int : 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur, supérieur à 0 si la fonction s'est bien exécutée
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
int modification(personne * client, char * filename, int taille){
    int i,j,ind_recherche,n,confirmation,confirmation_recherche;
    char choix;
    personne saisie;
    FILE * fichier;

    do{
        system("cls");

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Modifier des clients");
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Combien de clients voulez vous supprimer ? (0 pour quitter) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%d",&n);

        if(n<0){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Champ invalide !");
            printf(" ---------------------------------------------------------------------------\n\n");

            getch();
        }
    }while(n<0);

    for(i=0;i<n && n != 0;i++){
        do{
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

            ind_recherche = recherche_seq(client,saisie.nom,saisie.prenom,taille-1); // réalise la recherche séquentielle et retourne l'indice du client

            confirmation_recherche = 1; // confirme la recherche, si la variable est à zéro alors on quitte la boucle, sinon on execute le reste de la fonction
            if(strcmp(saisie.nom,"\0") != 0 || strcmp(saisie.prenom, "\0")!=0){ // controle ce qu'il y a dans les 2 champs
                if(ind_recherche == -1){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez rechercher un client");
                    printf(" ---------------------------------------------------------------------------\n\n");

                    getch();
                }
            }
            else{
                confirmation_recherche = 0;
            }
        }while(ind_recherche==-1);

        if(ind_recherche != -1 && confirmation_recherche == 1){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Client a modifier");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Prenom",client[ind_recherche].prenom);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Nom",client[ind_recherche].nom);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Ville",client[ind_recherche].ville);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Code Postal",client[ind_recherche].code_postal);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Telephone",client[ind_recherche].telephone);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Mail",client[ind_recherche].mail);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Profession",client[ind_recherche].profession);
            printf(" ---------------------------------------------------------------------------\n\n");

            getch();

            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","(i) Lors de votre saisie veuillez ne pas mettre de virgule");
            printf(" ---------------------------------------------------------------------------\n\n");

            getch();

            fflush(stdin);
            fflush(stdout);
            // saisie des informations a modifier, pour ne pas modifier le champ, on presse la touche entrée
            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Prenom : (touche entree pour passer) :");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.prenom);

                confirmation = ctrl_virgule(saisie.prenom,strlen(saisie.prenom)); // confirme si la saisie ne contient pas de virgule

                if (strcmp(saisie.prenom,"\0") !=0 ){ // contrôle si la saisie est la touche entree
                    if(confirmation==0){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                }
                else{
                    confirmation = 1;
                }
            }while(confirmation!=1);

            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Nom (touche entree pour passer) :");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.nom);

                confirmation = ctrl_virgule(saisie.nom,strlen(saisie.nom));

                if (strcmp(saisie.nom,"\0") !=0 ){
                    if(confirmation==0){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                }
                else{
                    confirmation = 1;
                }
            }while(confirmation!=1);

            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Ville (touche entree pour passer) :");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.ville);

                confirmation = ctrl_virgule(saisie.ville,strlen(saisie.ville));

                if (strcmp(saisie.ville,"\0") !=0 ){
                    if(confirmation==0){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                }
                else{
                    confirmation = 1;
                }
            }while(confirmation!=1);

            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Code Postal (touche entree pour passer) :");
                printf("| %-73s |\n","(format : \"00000\")");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.code_postal);

                confirmation = format_code_postal(saisie.code_postal,strlen(saisie.code_postal)); // confirme si le format est respecté

                if(strcmp(saisie.code_postal,"\0") != 0){
                    if(confirmation==0){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez respecter le format \"000000\"");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                    else if(confirmation==-1){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                }
                else{
                    confirmation = 1;
                }
            }while(confirmation!=1);

            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Telephone (touche entree pour passer) :");
                printf("| %-73s |\n","(format : \"00.00.00.00.00\")");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.telephone);

                confirmation = format_telephone(saisie.telephone,strlen(saisie.telephone));

                if(strcmp(saisie.telephone,"\0")!=0){
                    if(confirmation==0){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez respecter le format \"00.00.00.00.00\"");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                    else if(confirmation==-1){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                }
                else{
                    confirmation=1;
                }
            }while(confirmation!=1);


            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Mail (touche entree pour passer) :");
                printf("| %-73s |\n","(format : \"texte@texte.domaine\")");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.mail);

                confirmation = format_mail(saisie.mail,strlen(saisie.mail));

                if(strcmp(saisie.mail,"\0")!=0){
                    if(confirmation==0){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez respecter le format \"texte@texte.domaine\"");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                    else if(confirmation==-1){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                }
                else{
                    confirmation=1;
                }
            }while(confirmation!=1);

            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Profession (touche entree pour passer) :");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.profession);

                confirmation = ctrl_virgule(saisie.profession,strlen(saisie.profession));

                if (strcmp(saisie.profession,"\0") !=0 ){
                    if(confirmation==0){
                        printf(" ---------------------------------------------------------------------------\n");
                        printf("| %-73s |\n","/!\\ Veuillez ne pas mettre de virgule");
                        printf(" ---------------------------------------------------------------------------\n");

                        getch();
                    }
                }
                else{
                    confirmation = 1;
                }
            }while(confirmation!=1);

            system("cls");

            // affiche les champs mis à jour

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Champs mis a jour");
            printf(" ---------------------------------------------------------------------------\n");
            if(strcmp(saisie.nom,"\0")!=0){
                printf("| %-20s | %-50s |\n","Prenom",saisie.prenom);
                printf(" ---------------------------------------------------------------------------\n");
            }
            if(strcmp(saisie.prenom,"\0")!=0){
                printf("| %-20s | %-50s |\n","Nom",saisie.nom);
                printf(" ---------------------------------------------------------------------------\n");
            }
            if(strcmp(saisie.ville,"\0")!=0){
                printf("| %-20s | %-50s |\n","Ville",saisie.ville);
                printf(" ---------------------------------------------------------------------------\n");
            }
            if(strcmp(saisie.code_postal,"\0")!=0){
                printf("| %-20s | %-50s |\n","Code Postal",saisie.code_postal);
                printf(" ---------------------------------------------------------------------------\n");
            }
            if(strcmp(saisie.telephone,"\0")!=0){
                printf("| %-20s | %-50s |\n","Telephone",saisie.telephone);
                printf(" ---------------------------------------------------------------------------\n");
            }
            if(strcmp(saisie.mail,"\0")!=0){
                printf("| %-20s | %-50s |\n","Mail",saisie.mail);
                printf(" ---------------------------------------------------------------------------\n");
            }
            if(strcmp(saisie.profession,"\0")!=0){
                printf("| %-20s | %-50s |\n","Profession",saisie.profession);
                printf(" ---------------------------------------------------------------------------\n\n");
            }

            do{
                // confirme la modification des information du client
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Confirmer la modification du client ? :");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","y","Oui");
                printf("| %-20s | %-50s |\n","n","Non");
                printf(" ---------------------------------------------------------------------------\n");
                scanf(" %c",&choix);

                switch(choix){
                    case 'y':
                        if(remove(filename)==0){ // supprime le fichier
                            // remplace les éventuelles informations saisies sur les variables du tableau de structures
                            if(strcmp(saisie.nom,"\0")!=0){
                                strcpy(client[ind_recherche].nom,saisie.nom);
                            }

                            if(strcmp(saisie.prenom,"\0")!=0){
                                strcpy(client[ind_recherche].prenom,saisie.prenom);
                            }

                            if(strcmp(saisie.ville,"\0")!=0){
                                strcpy(client[ind_recherche].ville,saisie.ville);
                            }

                            if(strcmp(saisie.code_postal,"\0")!=0){
                                strcpy(client[ind_recherche].code_postal,saisie.code_postal);
                            }

                            if(strcmp(saisie.telephone,"\0")!=0){
                                strcpy(client[ind_recherche].telephone,saisie.telephone);
                            }

                            if(strcmp(saisie.mail,"\0")!=0){
                                strcpy(client[ind_recherche].mail,saisie.mail);
                            }

                            if(strcmp(saisie.profession,"\0")!=0){
                                strcpy(client[ind_recherche].profession,saisie.profession);
                            }

                            fichier = fopen(filename, "a+"); // recrée le fichier

                            for(j=0;j<taille;j++){
                                // écrit dans le fichier
                                fprintf(fichier,"%s,%s,%s,%s,%s,%s,%s\n",client[j].prenom,client[j].nom,client[j].ville,client[j].code_postal,client[j].telephone,client[j].mail,client[j].profession);
                            }
                            fclose(fichier);

                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","Client modifie");
                            printf(" ---------------------------------------------------------------------------\n\n");

                            getch();
                        }
                        else{
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","/!\\ Erreur lors de la modification du client");
                            printf(" ---------------------------------------------------------------------------\n\n");
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

                        getch();
                        break;
                }
            }while(choix != 'y' && choix != 'n');
        }

    }

    return n;
}

/**
 * @fn suppression(personne * client, char * filename, int * taille)
 *
 * @brief fonction qui permet de supprimer un client dans le fichier ouvert
 * @param client correspond au tableau de structures
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de lignes du fichier
 * @return int : 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur, supérieur à 0 si la fonction s'est bien exécutée
 *
 * Etudiant(s) référent(s) : Nicolas DE SAINT JEAN (auteur de la fonction) & James MOREL
 */
int suppression(personne * client, char * filename, int * taille){
    int i,j,ind_recherche,n,confirmation_recherche;
    char choix;
    personne saisie;
    FILE * fichier;

    do{
        system("cls");

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Supprimer des clients");
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Combien de clients voulez vous supprimer ? :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%d",&n);

        if(n<0){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Champ invalide !");
            printf(" ---------------------------------------------------------------------------\n\n");

            getch();
        }
    }while(n<0);

    for(i=0;i<n && n!=0;i++){
        do{
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

            ind_recherche = recherche_seq(client,saisie.nom,saisie.prenom,*taille-1); // réalise la recherche sequentielle et retourne l'indice de la personne recherchée

            confirmation_recherche = 1; // confirme la recherche, si la variable est à zéro alors on quitte la boucle, sinon on execute le reste de la fonction

            if(strcmp(saisie.nom,"\0") != 0 || strcmp(saisie.prenom, "\0")!=0){ // verification de ce qu'il y'a dans les deux champs
                if(ind_recherche == -1){
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez rechercher un client");
                    printf(" ---------------------------------------------------------------------------\n\n");

                    getch();
                }
            }
            else{
                confirmation_recherche = 0;
            }
        }while(ind_recherche==-1);

        if(ind_recherche != -1 && confirmation_recherche == 1){

            // affichage des informations du client a supprimer
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Client a supprimer");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Prenom",client[ind_recherche].prenom);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Nom",client[ind_recherche].nom);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Ville",client[ind_recherche].ville);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Code Postal",client[ind_recherche].code_postal);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Telephone",client[ind_recherche].telephone);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Mail",client[ind_recherche].mail);
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","Profession",client[ind_recherche].profession);
            printf(" ---------------------------------------------------------------------------\n\n");

            do{
                // confirmation de la suppression
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Confirmer la suppression du client ? :");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","y","Oui");
                printf("| %-20s | %-50s |\n","n","Non");
                printf(" ---------------------------------------------------------------------------\n");
                scanf(" %c",&choix);

                switch(choix){
                    case 'y':
                        if(remove(filename)==0){ // supprime le fichier
                            fichier = fopen(filename, "a+"); // recrée le fichier
                            for(j=0;j<*taille-1;j++){
                                // écrit sur le fichier toutes les lignes sauf celui supprimé
                                if(j != ind_recherche){
                                    fprintf(fichier,"%s,%s,%s,%s,%s,%s,%s\n",client[j].prenom,client[j].nom,client[j].ville,client[j].code_postal,client[j].telephone,client[j].mail,client[j].profession);
                                }
                            }
                            fclose(fichier);

                            *taille = *taille-1;

                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","Client supprime");
                            printf(" ---------------------------------------------------------------------------\n\n");

                            getch();
                        }
                        else{
                            printf(" ---------------------------------------------------------------------------\n");
                            printf("| %-73s |\n","/!\\ Erreur lors de la suppression du client");
                            printf(" ---------------------------------------------------------------------------\n\n");
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

                        getch();
                        break;
                }
            }while(choix != 'y' && choix != 'n');
        }
    }

    return n;
}



/**
 * @fn long filtre_test (personne * client,int * tab_ind_filtre, int * deb,int * fin)
 *
 * @brief fonction qui permet de filtrer l'annuaire selon des paramètres qui peuvent être superposés
 * @param client correspond au tableau de structures
 * @param tab_ind_filtre correspond au tableau d'indices
 * @param deb correspond au début de la zone à filtrer
 * @param fin correspond à la fin de la zone a filtrer
 * @return long correspond au temps d'execution de la fonction
 * Etudiant(s) référent(s) : James MOREL (auteur de la fonction)
 */
long filtre_test (personne * client,int * tab_ind_filtre, int * deb,int * fin){
    char valeur[50];
    clock_t debut_temps;
    clock_t fin_temps;
    long temps_total = 0;
    int mode,pos_valeur; // "mode" correspond au parametre avec lequel on filtre l'annuaire et "pos_valeur" correspond à la position d'une ligne de l'annuaire qui répond au critère donné
    do{
        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Filtrer");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20d | %-50s |\n",0,"Retour");
            printf("| %-20d | %-50s |\n",1,"Filtrer par prenom");
            printf("| %-20d | %-50s |\n",2,"Filtrer par nom");
            printf("| %-20d | %-50s |\n",3,"Filtrer par ville");
            printf("| %-20d | %-50s |\n",4,"Filtrer par code postal");
            printf("| %-20d | %-50s |\n",5,"Filtrer par telephone");
            printf("| %-20d | %-50s |\n",6,"Filtrer par mail");
            printf("| %-20d | %-50s |\n",7,"Filtrer par profession");
            printf(" ---------------------------------------------------------------------------\n");
            scanf("%d", &mode);

            if(mode < 0 || mode > 7){
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","/!\\ Champ invalide !");
                printf(" ---------------------------------------------------------------------------\n\n");

                getch();
            }
        }while(mode < 0 || mode > 7);

        if (mode>0)
        {
          do{
            fflush(stdin);
            fflush(stdout);
            system("cls");

             // saisie de la valeur selon le critère
            switch (mode)
            {
            case 1:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Prenom : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 2:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Nom : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 3:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Ville : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 4:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Code Postal : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 5:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Telephone : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 6:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Mail : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            case 7:
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Profession : ");
                printf(" ---------------------------------------------------------------------------\n");
                gets(valeur);
                break;
            }
            }while(strlen(valeur)<=0);

            debut_temps = clock(); // debut du compteur
            tri_rapide_indirect(client,tab_ind_filtre,*deb,*fin-1,mode);
            pos_valeur = recherche_dichotomique(valeur,client,tab_ind_filtre,*deb,*fin,mode);

            if (pos_valeur>0)
            {
                *deb=encadrement_inf(valeur,client,tab_ind_filtre,pos_valeur,mode);
                *fin=encadrement_sup(valeur,client,tab_ind_filtre,*fin,pos_valeur,mode);
                fin_temps = clock(); // fin du compteur
                affichage(client,tab_ind_filtre,*deb,*fin,(*fin)-(*deb),1);
            }
            else{
                fin_temps = clock(); // fin du compteur
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","/!\\ Aucun client ne répond a ce critere");
                printf(" ---------------------------------------------------------------------------\n\n");

                getch();
            }
            temps_total = temps_total + (fin_temps - debut_temps); // calcul du temps au des différents filtres appliqués

        }
    }while(mode != 0);
    return temps_total;
}
