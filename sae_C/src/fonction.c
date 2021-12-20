#include "main.h"

struct personne{ // creation de structure pour le client
    char nom[50];
    char prenom[50];
    char ville[50];
    char telephone[50];
    char code_postal[50];
    char mail[50];
    char profession[50];
};

typedef struct personne personne;


int validite(char*);
int lignes(char*);
void lecture(char*, personne *,int);
void afficher(personne *,int);
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
 * @param ligne
 * @param taille taille du tableau de structures
 * @return /
 */

void lecture(char* filename, personne * ligne, int taille){
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
                ligne[j].nom[i] = caractere_lu;
                i++;
                ligne[j].nom[i] = '\0';
                break;
            case 1:
                ligne[j].prenom[i] = caractere_lu;
                i++;
                ligne[j].prenom[i] = '\0';
                break;
            case 2:
                ligne[j].ville[i] = caractere_lu;
                i++;
                ligne[j].ville[i] = '\0';
                break;
            case 3:
                ligne[j].telephone[i] = caractere_lu;
                i++;
                ligne[j].telephone[i] = '\0';
                break;
            case 4:
                ligne[j].code_postal[i] = caractere_lu;
                i++;
                ligne[j].code_postal[i] = '\0';
                break;
            case 5:
                ligne[j].mail[i] = caractere_lu;
                i++;
                ligne[j].mail[i] = '\0';
                break;
            case 6:
                ligne[j].profession[i] = caractere_lu;
                i++;
                ligne[j].profession[i] = '\0';
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
 * @fn void affichage(char * nom,char * prenom,char * ville,char * telephone,char * code_postal,char * mail,char * profession, int num)
 * 
 *
 * @brief fonction qui affiche le contenu du tableau de structure
 * 
 * @param ligne 
 * @param taille 
 */

void affichage(personne * ligne, int taille){
    int i,deb,fin;

    printf("Ligne du debut (0 si vous voulez afficher du debut): ");
    scanf("%d",&deb);

    printf("Ligne de fin (0 si vous voulez afficher jusqu'a la fin) : ");
    scanf("%d",&fin);

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
        printf("================================================ \n");
        printf("Personne n %d \n", i+1);
        printf("================================================ \n");
        printf("Nom : %s \n",ligne[i].nom);
        printf("Prenom : %s \n",ligne[i].prenom);
        printf("Ville : %s \n",ligne[i].ville);
        printf("Telephone : %s \n",ligne[i].telephone);
        printf("Code postal : %s \n",ligne[i].code_postal);
        printf("Mail : %s \n",ligne[i].mail);
        printf("Profession : %s \n",ligne[i].profession);
        printf("================================================ \n");
        printf("\n");
        i++;
    }

}

/**
 * @fn int ajout(char * filename, int * taille)
 *
 * @brief permet d'ajouter un client
 * 
 * @param filename correspond au nom du fichier
 * @param taille correspond au nombre de lignes du fichier
 * @return 1 si la fonction s'est bien exécutée, 0 si l'utilisateur souhaite quitter la fonction ou si il y a erreur
 */

int ajout(char * filename, int * taille){
    personne ligne;
    FILE * fichier;
    fichier = fopen(filename,"a+");

    int i,n,choix;

    printf("Combien de personnes voulez vous ajouter ? : ");
    scanf("%d",&n);

    *taille = *taille+n;

    for(i=0;i<n && n!=0;i++){
        printf("Nom : ");
        scanf("%s",ligne.nom);

        printf("Prenom : ");
        scanf("%s",ligne.prenom);

        printf("Ville : ");
        scanf("%s",ligne.ville);

        printf("Telephone : ");
        scanf("%s",ligne.telephone);

        printf("Code Postal : ");
        scanf("%s",ligne.code_postal);

        printf("Mail : ");
        scanf("%s",ligne.mail);

        printf("Profession : ");
        scanf("%s",ligne.profession);

        fprintf(fichier,"%s,%s,%s,%s,%s,%s,%s\n",ligne.nom,ligne.prenom,ligne.ville,ligne.telephone,ligne.code_postal,ligne.mail,ligne.profession);
    }

    fclose(fichier);

    if(n==0){
        return 0;
    }

    return 1;
}