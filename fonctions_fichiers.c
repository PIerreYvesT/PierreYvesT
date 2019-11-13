#include "fonctions_fichiers.h" 

char** allouer_tab_2D(int n, int m){
    char** tab = NULL;
    tab = malloc(n*m*sizeof(*tab));
    
    for (int i=0;i<n;i++){
        tab[i] = (char*) malloc(sizeof(char));
    }
    
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            tab[i][j]='a';
        }
    }
    
    return tab;
}

void desallouer_tab_2D(char** tab, int n){
    for (int i=0;i<n;i++){
        free(tab[i]);
    }
    free(tab);
    tab = NULL;
}

void afficher_tab_2D(char** tab, int n, int m){
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%c",tab[i][j]);
        }
        printf("\n");
    }
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
    
    FILE* fichier = NULL;
    
    fichier = fopen(nomFichier, "r");
    char ligne[100] = "\0";
    
    int nbColMax=0;
    int nbColTmp=0;
    int nbLigMax=0;
    
    while (fgets(ligne,100,fichier)!=NULL){
        nbColTmp=0;
        nbLigMax++;
        for(int i=0;ligne[i]!='\0';i++){
            nbColTmp++;
        }
        nbColTmp-=2;
        if (nbColMax<nbColTmp){
            nbColMax=nbColTmp;
        }
    }
    
    *nbLig=nbLigMax;
    *nbCol=nbColMax;
    
    fclose(fichier);
}

char** lire_fichier(const char* nomFichier){
    FILE* fichier = NULL;
    
    fichier = fopen(nomFichier, "r");
    
    char** tab = NULL;
    int lig,col;
    taille_fichier(nomFichier,&lig,&col);
    tab = allouer_tab_2D(lig,col);
    
    for (int i=0;i<lig;i++){
        for(int j=0;j<col;j++){
            tab[i][j]=fgetc(fichier);
        }
    }
    
    fclose(fichier);
    
    return tab;
}

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            if (tab[i][j]==ancien){
                tab[i][j]=nouveau;
            }
        }
    }
    return tab;
}

void ecrire_fichier(const char* nomFichier, char** tab, int n, int m){
    FILE* fichier = NULL;
    
    fichier = fopen(nomFichier, "w");

    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            fputc(tab[i][j],fichier);
        }
    }
    
    fclose(fichier);
}
