#include "main.h"

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
void lecture_repertoire(char**);
int validite(char*);
void creation_fichier(char*);
int lignes(char*);
void lecture(char*,personne*);
void remplissage(int*,int);
void permuter(int*,int*);
void tri_rapide_indirect(personne*,int*,int,int,int);
int recherche_dichotomique(char *,personne *, int *, int,int,int);
int encadrement_sup(char *, personne *, int *, int, int,int);
int encadrement_inf(char *, personne *, int *, int, int);
void filtre (personne *, int *, int*,int*);
void ligne_avec_vide(personne *,int *, int);
void afficher(personne*,int*,int);
int ajout(char*,int*);
int modification(personne*,char*,int);
int suppression(personne*,char*,int*);

/**
 * @brief 
 * 
 * @return int 
 */
int fichiers(){
    int fichiers=0;
    DIR * dir;
    struct dirent * entite;

    dir = opendir(".");
    if(dir != NULL){

        entite = readdir(dir);
        while(entite != NULL){
            if(!strcmp(entite->d_name,".") || !strcmp(entite->d_name,"..")){
                entite = readdir(dir);
            }
            else{
                fichiers++;
                entite = readdir(dir);
            }

        }

        closedir(dir);
    }

    return fichiers;
}

/**
 * @brief 
 * 
 * @param liste 
 */
void lecture_repertoire(char ** liste){
    int i;

    DIR * dir;
    struct dirent * entite;

    dir = opendir(".");
    if(dir != NULL){
        i=0;
        entite = readdir(dir);
        while(entite != NULL){
            if(!strcmp(entite->d_name,".") || !strcmp(entite->d_name,"..")){
                entite = readdir(dir);
            }
            else{
                strcpy(liste[i],entite->d_name);
                i++;
                entite = readdir(dir);
            }
        }

        closedir(dir);
    }
}

/**
 * @brief 
 * 
 * @param liste 
 * @param fichier 
 * @param lignes 
 * @return int 
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

        confirm = 0;
    }
    else if(choix_fichier==0){
        confirm = 0;
    }
    else{
        strcpy(fichier,liste[choix_fichier-1]);
        confirm = 1;
    }

    return confirm;
}

/**
 * @fn int validite(char* filename)
 * @brief teste l'existence du fichier
 *
 * @param filename chaine de caractere representant le nom du fichier à vérifier
 * @return 0 si le fichier n'existe pas, 1 si le fichier existe
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
 * @brief 
 * 
 * @param filename 
 */
void creation_fichier(char * filename){
    FILE * pointeur;
    pointeur = fopen(filename, "a+");
    fclose(pointeur);

}

/**
 * @fn int lignes(char* filename)
 *
 * @brief
 *
 * @param filename chaine de caractere representant le nom du fichier où il faut calculer le nombre de lignes
 * @return int nlignes -> le nombre de lignes
 */

int lignes(char* filename){
    FILE * pointeur;
    pointeur = fopen(filename,"a+");

    int nlignes = 1;
    char lignes[taille_ligne];

    while(fgets(lignes,taille_ligne,pointeur) != NULL){
        nlignes++;
    }

    fclose(pointeur);

    return nlignes;
}

/**
 * @brief 
 * 
 * @param filename 
 * @param tableau2d 
 */
void lecture_lignes(char * filename, char ** tableau2d){
    FILE * pointeur;
    pointeur = fopen(filename,"a+");
    int i=0;
    char ligne[taille_ligne];

    while(fgets(ligne,taille_ligne,pointeur) != NULL){
        strcpy(tableau2d[i],ligne);
        i++;
    }

    fclose(pointeur);
}

/**
 * @fn void lecture(char* filename, int taille, int mode)
 *
 * @brief fonction qui lit les caracteres du fichier
 *
 * @param filename correspondant au nom du fichier
 * @param client
 * @param taille taille du tableau de structures
 * @return /
 */

void lecture(char* filename, personne * client){
    FILE * pointeur = NULL;
    pointeur = fopen(filename,"a+");
    int i=0;
    int j=0;
    int virgule = 0;

    char caractere_lu;

    do{
        caractere_lu = fgetc(pointeur);

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

    fclose(pointeur);
}

/**
 * @brief 
 * 
 * @param tableau 
 * @param taille 
 */
void remplissage(int * tableau, int taille){
    int i;
    for(i=0;i<taille;i++){
        tableau[i] = i;
    }
}

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 */
void permuter(int * a, int * b){
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief 
 * 
 * @param client 
 * @param index 
 * @param deb 
 * @param fin 
 * @param mode 
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
                while(strcmp(client[index[i]].prenom, client[index[pivot]].prenom) <= 0 && i <= j){
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
                permuter(&index[i],&index[j]);
                i++;
                j--;
            }
        }
        permuter(&index[pivot],&index[j]);
        tri_rapide_indirect(client,index,deb,j-1,mode);
        tri_rapide_indirect(client,index,j+1,fin,mode);
    }
}

/**
 * @brief 
 * 
 * @param client 
 * @param saisie_nom 
 * @param saisie_prenom 
 * @param taille 
 * @return int 
 */
int recherche_seq(personne * client, char * saisie_nom, char * saisie_prenom, int taille){
    int i, ind=-1;

    for(i=0;i<taille && ind == -1;i++){
        if (strcmp(client[i].nom,saisie_nom)==0){
            if(strcmp(client[i].prenom,saisie_prenom)==0){
                ind = i;
            }
        }
    }

    return ind;
}

/**
 * @brief 
 * 
 * @param valeur_recherche 
 * @param client 
 * @param index 
 * @param debut 
 * @param fin 
 * @param mode 
 * @return int 
 */
int recherche_dichotomique(char * valeur_recherche,personne * client, int * index, int debut, int fin, int mode){
    int ind =-1, pos, trouve = 0;
    switch (mode)
    {
    case 1:
        while (trouve == 0 && debut <= fin)
        {
            pos = (debut + fin)/2;

            if(strcmp(valeur_recherche, client[index[pos]].prenom) == 0){
                ind = pos;
                trouve =1;
            }
            else{
                if(strcmp(valeur_recherche, client[index[pos]].prenom) > 0){
                    printf("\nplus grand");
                    debut = pos + 1;
                }
                else{
                    printf("\nplus petit");
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
                    printf("\nplus grand");
                    debut = pos + 1;
                }
                else{
                    printf("\nplus petit");
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
                    printf("\nplus grand");
                    debut = pos + 1;
                }
                else{
                    printf("\nplus petit");
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
                    printf("\nplus grand");
                    debut = pos + 1;
                }
                else{
                    printf("\nplus petit");
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
                    printf("\nplus grand");
                    debut = pos + 1;
                }
                else{
                    printf("\nplus petit");
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
                    printf("\nplus grand");
                    debut = pos + 1;
                }
                else{
                    printf("\nplus petit");
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
                    printf("\nplus grand");
                    debut = pos + 1;
                }
                else{
                    printf("\nplus petit");
                    fin = pos -1;
                }
            }
        }
        break;

    default:
        break;
    }
    printf("%d ind recherche dicho\n",ind);
    return ind+1;
}

/**
 * @brief 
 * 
 * @param valeur_recherche 
 * @param client 
 * @param index 
 * @param taille 
 * @param depart 
 * @param mode 
 * @return int 
 */
int encadrement_sup(char * valeur_recherche, personne * client, int * index, int taille, int depart,int mode){
    int pos = depart;
    switch (mode)
    {
    case 1:
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
 * @brief 
 * 
 * @param valeur_recherche 
 * @param client 
 * @param index 
 * @param depart 
 * @param mode 
 * @return int 
 */
int encadrement_inf(char * valeur_recherche, personne * client, int * index, int depart,int mode){
    int pos = depart;
    switch (mode)
    {
    case 1:
        while (strcmp(valeur_recherche, client[index[pos-2]].prenom) == 0)
        {
            pos--;
        }
        break;
    case 2:
        while (strcmp(valeur_recherche, client[index[pos-2]].nom) == 0)
        {
            printf("\n%d",pos);
            printf("\n%f ",strcmp(valeur_recherche, client[index[pos-1]].nom));
            printf("%d", pos-1);
            pos--;
            printf("\n%d",pos);
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
 * @param client correspond au tableau de structures
 * @param tab_ind_filtre correspond au tableau d'indices
 * @param deb correspond au début de la structure
 * @param fin correspond a la fin de la structure
 */
void filtre (personne * client,int * tab_ind_filtre, int * deb,int * fin){
    char valeur[50];
    int mode,pos_valeur;
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

            tri_rapide_indirect(client,tab_ind_filtre,*deb,*fin-1,mode);
            pos_valeur = recherche_dichotomique(valeur,client,tab_ind_filtre,*deb,*fin,mode);

            if (pos_valeur>0)
            {
                *deb=encadrement_inf(valeur,client,tab_ind_filtre,pos_valeur,mode);
                *fin=encadrement_sup(valeur,client,tab_ind_filtre,*fin,pos_valeur,mode);
                affichage(client,tab_ind_filtre,*deb,*fin,(*fin)-(*deb),1);
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
 * @brief 
 * 
 * @param client correspond au tableau de structures
 * @param index correspond au tableau d'indices
 * @param deb correspond a la ligne du début que l'on souhaite afficher
 * @param fin correspond a la ligne de fin jusqu'où l'on souhaite afficher
 * @param taille correspond au nombre de lignes
 * @param mode correspond au mode d'affichage
 */
void affichage(personne * client, int * index, int deb, int fin, int taille, int mode){
    int i;
    int champ_vide;
    switch (mode){
        case 1:
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
        case 2:
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
        case 3:
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

                if(strcmp(client[i].prenom,"")!=0){
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
        case 4:
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

                if(strcmp(client[i].prenom,"")==0){
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
 * @brief permet d'ajouter un client
 *
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de clients du fichier
 * @return 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur, supérieur à 0 si la fonction s'est bien exécutée
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

        do{
            system("cls");

            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Prenom : (touche espace pour passer) :");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.prenom);

            confirmation = ctrl_virgule(client.prenom,strlen(client.prenom));

            if (strcmp(client.prenom,"\0") !=0 ){
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
            printf("| %-73s |\n","Nom (touche espace pour passer) :");
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
            printf("| %-73s |\n","Ville (touche espace pour passer) :");
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
            printf("| %-73s |\n","Code Postal (touche espace pour passer) :");
            printf("| %-73s |\n","(format : \"00000\")");
            printf(" ---------------------------------------------------------------------------\n");
            gets(client.code_postal);

            confirmation = format_code_postal(client.code_postal,strlen(client.code_postal));

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
            printf("| %-73s |\n","Telephone (touche espace pour passer) :");
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
            printf("| %-73s |\n","Mail (touche espace pour passer) :");
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
            printf("| %-73s |\n","Profession (touche espace pour passer) :");
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
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","Confirmer l'ajout de ce nouveau client ? :");
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-20s | %-50s |\n","y","Oui");
            printf("| %-20s | %-50s |\n","n","Non");
            printf(" ---------------------------------------------------------------------------\n");

            scanf(" %c",&choix);

            switch (choix){
                case 'y':
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
                    fprintf(fichier,"\0");

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
 * @param client correspond au tableau de structures
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de lignes du fichier
 * @return 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur, supérieur à 0 si la fonction s'est bien exécutée
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

            ind_recherche = recherche_seq(client,saisie.nom,saisie.prenom,taille-1);

            confirmation_recherche = 1;
            if(strcmp(saisie.nom,"\0") != 0 || strcmp(saisie.prenom, "\0")!=0){
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
            do{
                system("cls");

                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Prenom : (touche espace pour passer) :");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.prenom);

                confirmation = ctrl_virgule(saisie.prenom,strlen(saisie.prenom));

                if (strcmp(saisie.prenom,"\0") !=0 ){
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
                printf("| %-73s |\n","Nom (touche espace pour passer) :");
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
                printf("| %-73s |\n","Ville (touche espace pour passer) :");
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
                printf("| %-73s |\n","Code Postal (touche espace pour passer) :");
                printf("| %-73s |\n","(format : \"00000\")");
                printf(" ---------------------------------------------------------------------------\n");
                gets(saisie.code_postal);

                confirmation = format_code_postal(saisie.code_postal,strlen(saisie.code_postal));

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
                printf("| %-73s |\n","Telephone (touche espace pour passer) :");
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
                printf("| %-73s |\n","Mail (touche espace pour passer) :");
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
                printf("| %-73s |\n","Profession (touche espace pour passer) :");
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
            getch();

            do{
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Confirmer la modification du client ? :");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","y","Oui");
                printf("| %-20s | %-50s |\n","n","Non");
                printf(" ---------------------------------------------------------------------------\n");
                scanf(" %c",&choix);

                switch(choix){
                    case 'y':
                        if(remove(filename)==0){
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

                            fichier = fopen(filename, "a+");

                            for(j=0;j<taille;j++){
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
 * @param client correspond au tableau de structures
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de lignes du fichier
 * @return 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur, supérieur à 0 si la fonction s'est bien exécutée
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

            ind_recherche = recherche_seq(client,saisie.nom,saisie.prenom,*taille-1);

            confirmation_recherche = 1;
            if(strcmp(saisie.nom,"\0") != 0 || strcmp(saisie.prenom, "\0")!=0){
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

            getch();

            do{
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-73s |\n","Confirmer la suppression du client ? :");
                printf(" ---------------------------------------------------------------------------\n");
                printf("| %-20s | %-50s |\n","y","Oui");
                printf("| %-20s | %-50s |\n","n","Non");
                printf(" ---------------------------------------------------------------------------\n");
                scanf(" %c",&choix);

                switch(choix){
                    case 'y':
                        if(remove(filename)==0){
                            fichier = fopen(filename, "a+");
                            for(j=0;j<*taille-1;j++){
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