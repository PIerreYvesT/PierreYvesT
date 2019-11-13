
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include"fonctions_fichiers.c"


#define LARGEUR_TILE 16 // hauteur et largeur des tiles.
#define HAUTEUR_TILE 16

#define NOMBRE_BLOCS_LARGEUR 8 // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 8


 
 
 
 
 
 
 
 char ** allouer_tab_2dim(int n, int m)
 {
	 char ** tab ; 
	 tab =malloc (n*sizeof(char*));
	 for (int i =0; i<n; i++)
	 {
	 tab[i]= malloc(m*sizeof(char*));
	 }
	 for(int i =0;i<n;i++){
		 for (int j=0;j<m;j++)
		 {
			 tab[i][j]='0';
		 }
	 }
	 return tab;
 }
 
 
 
 
 
 
 
 
 
 
 void affichage(SDL_Surface *tileset,SDL_Window *ecran, SDL_Renderer *afficheur,SDL_Texture *textuTil)
 {
	 if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    ecran = SDL_CreateWindow("Kill Homer !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, SDL_WINDOW_SHOWN);
    if (ecran == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    afficheur = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);
	printf("creation affichage\n");
    if (afficheur == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    tileset = SDL_LoadBMP("bloc16px.bmp");
    if (tileset == NULL)
    {
        fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
        goto Quit;
    }

    textuTil = SDL_CreateTextureFromSurface(afficheur, tileset);
    if (textuTil == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
        goto Quit;
    }
	
    SDL_FreeSurface(tileset);
	
	int f=0;
	if (f==3)
	{
	Quit:
    if (NULL != textuTil)
        SDL_DestroyTexture(textuTil);
    if (NULL != afficheur)
        SDL_DestroyRenderer(afficheur);
    if (NULL != ecran)
        SDL_DestroyWindow(ecran);
    SDL_Quit();
	}
 }
 
 struct joueur_s{

	double posx;
	double posy;
	
};typedef struct joueur_s joueur_t;

void init_joueur(joueur_t *jou)

{
	jou[0].posx=200;
	jou[0].posy=200;
}
 
 
 void change_posdx(joueur_t *jou)
 {
	 jou[0].posx=jou[0].posx+50;
 }
 
 
 
 void fichiertxt(char** table)
{
	printf("fonctionft\n");
    FILE * fichier = fopen("texteb.txt", "r");
 
    int c;
    int i = 0;
	//printf("valeur du premier%u\n",(unsigned char)fscanf(fichier, "%u", &c));
    /*while(!feof(fichier)){
        unsigned int id = 0;
        fscanf(fichier, "%u", &id);
        table[i] = (unsigned char)id;
        i++;
    }*/
	//while(fgetc(fichier)!=EOF)
	while(!feof(fichier))
		
	{
		//unsigned int id=0;
		//printf("valeur dans boucle en 0 0 :%u \n", (unsigned char)table[0][0]);
		printf("fonctionft2\n");
		char ch;
		for (i=0; i<NOMBRE_BLOCS_LARGEUR;i++)
		{
			for (int j=0; j<NOMBRE_BLOCS_HAUTEUR;j++)
			{
				/*printf("testboucle\n");
				table[i][j]=fgetc(fichier);*/
				fscanf(fichier, "%u", &c);
				//c=fgetc(fichier);
				table[i][j] = (char)c;
				
			}
		}
			
    
	}
	printf("valeur dans boucle en 0 0 :%u \n", (unsigned char)table[0][0]);
	fclose(fichier);
}
 
void afficher_tableau(char** tab, int nombre_blocs_largeur, int nombre_blocs_hauteur)
{
	printf("testaft1\n");
    for (int i = 0; i < nombre_blocs_hauteur; i++) 
	{
        for (int j = 0; j < nombre_blocs_largeur; j++) 
		{
            //printf("%u ", tab[i][j]);//, i * nombre_blocs_largeur + j
			printf("valeur: %u indice:[%d][%d]\n",tab[i][j],i,j);
			//printf("testaft2\n");
        }
        //printf("\n");
    }
	printf("valeur en 0 0 :%u \n", tab[0][0]);
}



	

	
	
	

	

void Afficher(SDL_Renderer* afficheur, SDL_Texture* textuTil,
     char** table, int nombre_blocs_largeur, int nombre_blocs_hauteur)
{
    int i, j,stock;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = LARGEUR_TILE;
    Rect_dest.w   = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    Rect_dest.h   = HAUTEUR_TILE;
	//init
	Rect_source.y=0;
	Rect_dest.x=0;
	Rect_dest.y=0;
    for(i = 0 ; i < NOMBRE_BLOCS_HAUTEUR; i++)
    {
        for(j = 0 ; j < NOMBRE_BLOCS_LARGEUR; j++)
        {
            stock=(int)table[i][j];
			printf("valeur de stock:%d\n",stock);
            Rect_source.x = stock*LARGEUR_TILE;//(table[i*NOMBRE_BLOCS_HAUTEUR+j] )* LARGEUR_TILE;//- '0'
            /*Rect_source.y = 0;
			Rect_dest.x = i * LARGEUR_TILE;
            Rect_dest.y = j * HAUTEUR_TILE;*/
            SDL_RenderCopy(afficheur, textuTil, &Rect_source, &Rect_dest);
			Rect_source.x=0;
			Rect_dest.x+=LARGEUR_TILE;
        }
		Rect_source.y=0;
		Rect_dest.x=0;
		Rect_dest.y+=LARGEUR_TILE;
		
		
    }
}

void spriteim(SDL_Renderer *pRenderer, joueur_t *joueur)
{
		if ( pRenderer )
	{
		SDL_Surface* pSprite = SDL_LoadBMP("perso.bmp");
		if ( pSprite )
		{
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Préparation du sprite
			if ( pTexture )
			{
				SDL_Rect dest = { /*2000/2 - pSprite->w/2*/joueur[0].posx,/*480/2 - pSprite->h/2*/joueur[0].posy, 100, 200};
				SDL_RenderCopy(pRenderer,pTexture,NULL,&dest); // Copie du sprite grâce au SDL_Renderer
				
				SDL_RenderPresent(pRenderer); // Affichage
				SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */
				
				SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
			}
			else
			{
				fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
			}
			
			SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
		}
		else
		{
			fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
		}
		
		//SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer
	}
	else
	{
		fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
	}
}
	
	
	
	
	
int main(int argc, char *argv[])
{
    SDL_Window *ecran = NULL;
    SDL_Renderer *afficheur = NULL;

    SDL_Surface *tileset = NULL;
    SDL_Texture *textuTil = NULL;
    SDL_Event event;
    int continuer = 1, tempsPrecedent = 0, tempsActuel = 0;
    int statut = EXIT_FAILURE;
	
	//unsigned char* table = (unsigned char*)malloc(NOMBRE_BLOCS_HAUTEUR*NOMBRE_BLOCS_LARGEUR * sizeof(unsigned char));
	char** table2=allouer_tab_2dim(NOMBRE_BLOCS_HAUTEUR,NOMBRE_BLOCS_LARGEUR);
	joueur_t jou[1];
	init_joueur(jou);
	
	fichiertxt(table2);
	printf("testmain\n");
	//table2=lire_fichier("texteb.txt");
	afficher_tableau(table2,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);
	//Afficher(afficheur, textuTil, table, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR);
	//return 0;
	//char table[16*16];
	//spriteim(afficheur);
	printf("testmain2\n");
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    ecran = SDL_CreateWindow("Kill Homer !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, SDL_WINDOW_SHOWN);
    if (ecran == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    afficheur = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);
    if (afficheur == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    tileset = SDL_LoadBMP("bloc16px.bmp");
    if (tileset == NULL)
    {
        fprintf(stderr, "Erreur chargement image droite : %s", SDL_GetError());
        goto Quit;
    }

    textuTil = SDL_CreateTextureFromSurface(afficheur, tileset);
    if (textuTil == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateTexturetil : %s", SDL_GetError());
        goto Quit;
    }
	
    SDL_FreeSurface(tileset);
	
    //fichiertxt(table);
	//affichage(tileset,ecran,afficheur,textuTil);
	Afficher(afficheur, textuTil, table2, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR);
	int h=0;
	while(h<4)
	{
	//spriteim(afficheur,jou);
	printf("testbouclesprite");
	h++;
	}
    while(continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
					case SDLK_d:
					change_posdx(jou);
					printf("avance");
                }
                break;
        }
		//Afficher(afficheur, textuTil, table, NOMBRE_BLOCS_LARGEUR, NOMBRE_BLOCS_HAUTEUR);
		//spriteim(afficheur,jou);
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30) /* si 30ms se sont écoulé depuis le dernier tour de la boucle
                                                  plus le temps est petit plus il se deplace vite */
        {
            tempsPrecedent = tempsActuel; // le temps actuel devient le temps présent
        }
        else
        {
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));
        }

        SDL_RenderPresent(afficheur);
		
    }

Quit:
    if (NULL != textuTil)
        SDL_DestroyTexture(textuTil);
    if (NULL != afficheur)
        SDL_DestroyRenderer(afficheur);
    if (NULL != ecran)
        SDL_DestroyWindow(ecran);
    SDL_Quit();

    return statut;
}