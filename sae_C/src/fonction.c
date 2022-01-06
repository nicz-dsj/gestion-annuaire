#include "main.h"

struct personne{ // creation de structure pour le client
    char prenom[50];
    char nom[50];
    char ville[50];
    char code_postal[50];
    char telephone[50];
    char mail[50];
    char profession[50];
};

typedef struct personne personne;



int validite(char*);
int lignes(char*);
void lecture(char*,personne*,int);
void remplissage(int*,int);
void permuter(int*,int*);
void tri_rapide_indirect(personne*,int*,int,int,int);
void afficher(personne*,int*,int);
int ajout(char*,int*);
int recherche_dichotomique(char *,personne *, int *, int,int);

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
 * @fn int lignes(char* filename)
 *
 * @brief
 *
 * @param filename chaine de caractere representant le nom du fichier où il faut calculer le nombre de lignes
 * @return int nlignes -> le nombre de lignes
 */

int lignes(char* filename){
    FILE * fichier;
    fichier = fopen(filename,"r");

    int nlignes = 0;
    char lignes[taille_ligne];

    while(fgets(lignes,taille_ligne,fichier) != NULL){
        nlignes++;
    }

    fclose(fichier);

    return nlignes;
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

void lecture(char* filename, personne * client, int taille){
    FILE * pointeur = NULL;
    pointeur = fopen(filename,"a+");
    int i=0,j=0,deb,fin;
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

void remplissage(int * tableau, int taille){
    int i, *j;
    for(i=0;i<taille;i++){
        tableau[i] = i;
    }
}

void permuter(int * a, int * b){
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void tri_rapide_indirect(personne * client, int * index, int deb, int fin, int mode){
    int pivot, i, j;
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
 * @fn void affichage(char * nom,char * prenom,char * ville,char * telephone,char * code_postal,char * mail,char * profession, int num)
 *
 *
 * @brief fonction qui affiche le contenu du tableau de structure
 *
 * @param client
 * @param taille
 */

void affichage(personne * client, int * index, int taille){
    int i,deb,fin;

    do{
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Ligne de debut (0 si vous voulez afficher du debut) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%d",&deb);

        if(deb<0 || deb>taille){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
            printf(" ---------------------------------------------------------------------------\n\n");
        }
    }while(deb<0 || deb>taille);

    do{
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Ligne de fin (0 si vous voulez afficher jusqu'a la fin) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%d",&fin);

        if(fin<0 || fin>taille){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
            printf(" ---------------------------------------------------------------------------\n\n");
        }
    }while(fin<0 || fin>taille);

    if(fin==0){
        fin = taille;
    }

    if (deb==0){
        i=0;
    }
    else{
        i=deb-1;
    }

    while(i<fin){
        printf(" ---------------------------------------------------------------------------\n");
        printf("| Ligne %-67d |\n",i+1);
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Prenom",client[index[i]].prenom);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Nom",client[index[i]].nom);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Ville",client[index[i]].ville);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Code Postal",client[index[i]].code_postal);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Telephone",client[index[i]].telephone);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Mail",client[index[i]].mail);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Profession",client[index[i]].profession);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n\n");
        i++;
    }
}

/**
 * @fn int ajout(char * filename, int * taille)
 *
 * @brief permet d'ajouter un client
 *
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de clients du fichier
 * @return 1 si la fonction s'est bien exécutée, 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur
 */

int ajout(char * filename, int * taille){
    personne client;
    FILE * fichier;
    fichier = fopen(filename,"a+");

    int i,n,choix;

    do{
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Gestion d'annuaire - Menu d'ajout de client");
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Combien de clients voulez vous ajouter ? (maximum 10 personnes) :");
        printf(" ---------------------------------------------------------------------------\n\n");
        scanf("%d",&n);

        if(n<0){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
            printf(" ---------------------------------------------------------------------------\n\n");
        }
        if(n>10){
            printf(" ---------------------------------------------------------------------------\n");
            printf("| %-73s |\n","/!\\ Maximum 10 personnes !");
            printf(" ---------------------------------------------------------------------------\n\n");
        }
    }while(n<0 || n>10);

    *taille = *taille+n;

    for(i=0;i<n && n!=0;i++){
        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Prenom : (\"/\" pour passer) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%s",client.prenom);

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Nom (\"/\" pour passer) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%s",client.nom);
        

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Ville (\"/\" pour passer) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%s",client.ville);

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Code Postal (\"/\" pour passer) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%s",client.code_postal);

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Telephone (\"/\" pour passer) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%s",client.telephone);

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Mail (\"/\" pour passer) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%s",client.mail);


        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Profession (\"/\" pour passer) :");
        printf(" ---------------------------------------------------------------------------\n");
        scanf("%s",client.profession);

        printf(" ---------------------------------------------------------------------------\n");
        printf("| %-73s |\n","Nouveau client");
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.prenom, "/") != 0){
            printf("| %-20s | %-50s |\n","Prenom",client.prenom);
        }
        else{
            printf("| %-20s |                                                    |\n","Prenom");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.nom, "/") != 0){
            printf("| %-20s | %-50s |\n","Nom",client.nom);
        }
        else{
            printf("| %-20s |                                                    |\n","Nom");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.ville, "/") != 0){
            printf("| %-20s | %-50s |\n","Ville",client.ville);
        }
        else{
            printf("| %-20s |                                                    |\n","Ville");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.code_postal, "/") != 0){
            printf("| %-20s | %-50s |\n","Code Postal",client.code_postal);
        }
        else{
            printf("| %-20s |                                                    |\n","Code Postal");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.telephone, "/") != 0){
            printf("| %-20s | %-50s |\n","Telephone",client.telephone);
        }
        else{
            printf("| %-20s |                                                    |\n","Telephone");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.mail, "/") != 0){
            printf("| %-20s | %-50s |\n","Mail",client.mail);
        }
        else{
            printf("| %-20s |                                                    |\n","Mail");
        }
        printf(" ---------------------------------------------------------------------------\n");
        if(strcmp(client.profession, "/") != 0){
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
            printf("| %-20d | %-50s |\n",0,"Oui");
            printf("| %-20d | %-50s |\n",1,"Non");
            printf(" ---------------------------------------------------------------------------\n");
            scanf("%d",&choix);

            switch (choix){
                case 0:
                    if(strcmp(client.prenom, "/") != 0){
                        fprintf(fichier,"%s",client.prenom);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.nom, "/") != 0){
                        fprintf(fichier,"%s",client.nom);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.ville, "/") != 0){
                        fprintf(fichier,"%s",client.ville);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.code_postal, "/") != 0){
                        fprintf(fichier,"%s",client.code_postal);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.telephone, "/") != 0){
                        fprintf(fichier,"%s",client.telephone);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.mail, "/") != 0){
                        fprintf(fichier,"%s",client.mail);
                    }
                    fprintf(fichier,",");

                    if(strcmp(client.profession, "/") != 0){
                        fprintf(fichier,"%s",client.profession);
                    }
                    fprintf(fichier,"\n");
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Client ajoute");
                    printf(" ---------------------------------------------------------------------------\n\n");
                    break;
                case 1:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","Annulation du processus");
                    printf(" ---------------------------------------------------------------------------\n\n");
                    n=0;
                    break;
                default:
                    printf(" ---------------------------------------------------------------------------\n");
                    printf("| %-73s |\n","/!\\ Veuillez saisir un champ valide !");
                    printf(" ---------------------------------------------------------------------------\n\n");
                    break;
            }
        }while(choix != 0 && choix != 1);
    }

    fclose(fichier);

    return n;
}


int recherche_dichotomique(char * valeur_recherche,personne * client, int * index, int taille, int mode){
    int ind =-1, pos, trouve = 0, debut = 0, fin = taille-1;
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
                    debut = pos;
                }
                else{
                    fin = pos;
                }
            }
        }
        break;
    case 2:
    while (trouve == 0 && debut <= fin)
    {
        pos = (debut + fin)/2;
        if (strcmp(valeur_recherche, client[index[pos]].nom) == 0)
        {
            ind = pos;
            trouve =1;
        }
        else{
            if (strcmp(valeur_recherche, client[index[pos]].nom) > 0)
            {
                debut = pos;
            }
            else
                fin = pos;
        }
    }
    break;
    case 3:
    printf("mode ville");
    while (trouve == 0 && debut <= fin)
    {
        pos = (debut + fin)/2;
        if (strcmp(valeur_recherche, client[index[pos]].ville) == 0)
        {
            ind = pos;
            trouve =1;
        }
        else{
            if (strcmp(valeur_recherche, client[index[pos]].ville) > 0)
            {
                debut = pos;
            }
            else
                fin = pos;
        }
    }
    break;
    case 4:
    printf("mode code");
    while (trouve == 0 && debut <= fin)
    {
        pos = (debut + fin)/2;
        if (strcmp(valeur_recherche, client[index[pos]].code_postal) == 0)
        {
            ind = pos;
            trouve =1;
        }
        else{
            if (strcmp(valeur_recherche, client[index[pos]].code_postal) > 0)
            {
                debut = pos;
            }
            else
                fin = pos;
        }
    }
    break;
    case 5:
    printf("mode telephone");
    while (trouve == 0 && debut <= fin)
    {
        pos = (debut + fin)/2;
        if (strcmp(valeur_recherche, client[index[pos]].telephone) == 0)
        {
            ind = pos;
            trouve =1;
        }
        else{
            if (strcmp(valeur_recherche, client[index[pos]].telephone) > 0)
            {
                debut = pos;
            }
            else
                fin = pos;
        }
    }
    break;
    case 6:
    printf("mode mail");
    while (trouve == 0 && debut <= fin)
    {
        pos = (debut + fin)/2;
        if (strcmp(valeur_recherche, client[index[pos]].mail) == 0)
        {
            ind = pos;
            trouve =1;
        }
        else{
            if (strcmp(valeur_recherche, client[index[pos]].mail) > 0)
            {
                debut = pos;
            }
            else
                fin = pos;
        }
    }
    break;
    case 7:
    printf("mode prefession");
    while (trouve == 0 && debut <= fin)
    {
        pos = (debut + fin)/2;
        if (strcmp(valeur_recherche, client[index[pos]].profession) == 0)
        {
            ind = pos;
            trouve =1;
        }
        else{
            if (strcmp(valeur_recherche, client[index[pos]].profession) > 0)
            {
                debut = pos;
            }
            else
                fin = pos;
        }
    }
    break;
    
    default:
        break;
    }
    
    return ind;
}