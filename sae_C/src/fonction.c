#include "main.h"

struct personne{ // creation de structure pour le client
    char prenom[50];
    char nom[50];
    char ville[50];
    char telephone[50];
    char code_postal[50];
    char mail[50];
    char profession[50];
};

typedef struct personne personne;


int validite(char*);
int lignes(char*);
void lecture(char*,personne*,int);
void remplissage(int*,int);
void permuter(int*,int*);
void tri_rapide_indirect(personne*,int*,int,int);
void afficher(personne*,int*,int);
int ajout(char*,int*);

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
                client[j].telephone[i] = caractere_lu;
                i++;
                client[j].telephone[i] = '\0';
                break;
            case 4:
                client[j].code_postal[i] = caractere_lu;
                i++;
                client[j].code_postal[i] = '\0';
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

void tri_rapide_indirect(personne * client, int * index, int deb, int fin){
    int pivot, i, j;
    if(deb < fin){
        pivot = deb;
        i = deb;
        j = fin;

        while(i<j){
            while(strcmp(client[index[i]].nom, client[index[pivot]].nom) <= 0 && i <= j){
                i++;
            }
            while(strcmp(client[index[j]].nom, client[index[pivot]].nom) > 0 && i <= j){
                j--;
            }
            if(i<j){
                permuter(&index[i],&index[j]);
            }
        }
        permuter(&index[pivot],&index[j]);
        tri_rapide_indirect(client,index,deb,j-1);
        tri_rapide_indirect(client,index,j+1,fin);
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
        printf("client du debut (0 si vous voulez afficher du debut): ");
        scanf("%d",&deb);
    }while(deb<0);

    do{
        printf("client de fin (0 si vous voulez afficher jusqu'a la fin) : ");
        scanf("%d",&fin);
    }while(fin<0);

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
        printf("| %-73d |\n",i+1);
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
        printf("| %-20s | %-50s |\n","Telephone",client[index[i]].telephone);
        printf("|                      |                                                    |\n");
        printf(" ---------------------------------------------------------------------------\n");
        printf("|                      |                                                    |\n");
        printf("| %-20s | %-50s |\n","Code Postal",client[index[i]].code_postal);
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
        printf("Combien de personnes voulez vous ajouter ? : ");
        scanf("%d",&n);
    }while(n<0);

    *taille = *taille+n;

    for(i=0;i<n && n!=0;i++){
        printf("Prenom : (\"/\" pour passer) : ");
        scanf("%s",client.prenom);
        if(strcmp(client.prenom, "/") != 0){
            fprintf(fichier,"%s",client.prenom);
        }
        fprintf(fichier,",");

        printf("Nom (\"/\" pour passer) : ");
        scanf("%s",client.nom);
        if(strcmp(client.nom, "/") != 0){
            fprintf(fichier,"%s",client.nom);
        }
        fprintf(fichier,",");

        printf("Ville (\"/\" pour passer) : ");
        scanf("%s",client.ville);
        if(strcmp(client.ville, "/") != 0){
            fprintf(fichier,"%s",client.ville);
        }
        fprintf(fichier,",");

        printf("Telephone (\"/\" pour passer) : ");
        scanf("%s",client.telephone);
        if(strcmp(client.telephone, "/") != 0){
            fprintf(fichier,"%s",client.telephone);
        }
        fprintf(fichier,",");

        printf("Code Postal (\"/\" pour passer) : ");
        scanf("%s",client.code_postal);
        if(strcmp(client.code_postal, "/") != 0){
            fprintf(fichier,"%s",client.code_postal);
        }
        fprintf(fichier,",");

        printf("Mail (\"/\" pour passer) : ");
        scanf("%s",client.mail);
        if(strcmp(client.mail, "/") != 0){
            fprintf(fichier,"%s",client.mail);
        }
        fprintf(fichier,",");

        printf("Profession (\"/\" pour passer) : ");
        scanf("%s",client.profession);
        if(strcmp(client.profession, "/") != 0){
            fprintf(fichier,"%s",client.profession);
        }
        fprintf(fichier,"\n");
    }

    fclose(fichier);

    if(n==0){
        return 0;
    }

    return 1;
}
