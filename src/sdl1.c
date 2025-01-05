#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>


// ps 
//2341 ....sdl1
//kill -9 2341
// compilation clang sdl1.c -lSDL -o sdl
int main() {
    srand(time(NULL));
    SDL_Surface *ecran = NULL;
    SDL_Surface* fleur = NULL;
    SDL_Rect rect_fleur;
    int i = 1;

    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Error: Initialisation Failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    ecran = SDL_SetVideoMode(1000, 720, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);

    if(ecran == NULL) {
        fprintf(stderr, "Error: Unable to set video mode: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("My first window !!", NULL);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 50, 110, 0));

    SDL_Flip(ecran); // Utilisez SDL_Flip pour mettre à jour l'écran

    // Display an image
   /*sudo apt update
sudo apt install libsdl-ttf2.0-dev

    fleur = SDL_LoadBMP("../tp9_images_fleurs/fleur8a.bmp");
    if(fleur == NULL){
        fprintf(stderr, "Can't load the bmp: %s\n",SDL_GetError());
    }
    SDL_BlitSurface(fleur, NULL, ecran, NULL); // Display
    */
    SDL_Flip(ecran);

    char nomfic[200];

    SDL_Event event;
    int continuer = 1;

    while(continuer) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;

                // Display with mouse
                case  SDL_MOUSEBUTTONDOWN:
                //loading of one of image
                i = rand() %8 +1;
                //sprintf(nomfic,"fleur1a.bmp");
                sprintf(nomfic,"../tp9_images_fleurs/fleur%da.bmp",i);
                fleur = SDL_LoadBMP(nomfic);
                
                if(fleur == NULL){
                    fprintf(stderr, "Can't load the bmp: %s\n",SDL_GetError());
                    return -1;
                }
                
                // transparence handling
                SDL_SetColorKey(fleur, SDL_SRCCOLORKEY, 0x000000);
                SDL_SetColorKey(fleur, SDL_SRCCOLORKEY, SDL_MapRGB(fleur->format,0,0,0));
                rect_fleur.x = event.button.x - (fleur->w/2);
                rect_fleur.y = event.button.y - (fleur->h);
                //printf("event.x:%d rect.x:%d\n", event.button.x, rect_fleur.x);
                SDL_BlitSurface(fleur, NULL, ecran, &rect_fleur);
                SDL_Flip(ecran);
                SDL_FreeSurface(fleur);
            
                
                
               
                break;
               

                default:
                    break;
            }
        }
    }

   


    SDL_Quit();
    return EXIT_SUCCESS;
}
