#include "game.h"

//BUT init de la SDL
//ENTREE les paramètres de la fenetre
//SORTIE init de la sdl
int init(char *title, int xpos, int ypos, int width, int height, int flags, game *myGame){

    myGame->g_pRenderer=NULL;
    myGame->g_ptexture=NULL;
    myGame->g_pWindow=NULL;

    //init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0){

        //creation de la fenetre
        myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);

        //si fenetre
        if(myGame->g_pWindow!=NULL){
            myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);//creation de rendu

        }

        SDL_SetRenderDrawColor(myGame->g_pRenderer,255,255,0,255);

    }else{

        return 0;
    }

    SDL_RenderClear(myGame->g_pRenderer);
    SDL_RenderPresent(myGame->g_pRenderer);

    return 1;

}

//BUT destruction de la sdl
//ENTREE GameObject
//SORTIE sdl destroy
void destroy(game *myGame){

    //destruction texture
    if(myGame->g_ptexture!=NULL){
        SDL_DestroyTexture(myGame->g_ptexture);
    }

    //destruction du rendu
    if(myGame->g_pRenderer!=NULL){
        SDL_DestroyRenderer(myGame->g_pRenderer);
    }

    //destruction fenetre
    if(myGame->g_pWindow!=NULL){
        SDL_DestroyWindow(myGame->g_pWindow);
    }
}

//BUT gestion des events (inpur=>clavier)
//ENTREE un évènement
//SORTIE action correspondante
void handleEvents(gameState *state,coordonner *RaquetteGCoor,float speedJ){

    SDL_Event event;

    //si évènement alors réalisation de l'évènement correspondant
        if(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                state->g_bRunning=0;break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_DOWN:if(RaquetteGCoor->y+speedJ+RAQUETTE_HEIGHT<=SCREEN_HEIGHT){
                            RaquetteGCoor->y=RaquetteGCoor->y+speedJ;
                        }else{
                            RaquetteGCoor->y=SCREEN_HEIGHT-RAQUETTE_HEIGHT;
                        }break;
                    case SDLK_UP:if(RaquetteGCoor->y-speedJ>=0){
                            RaquetteGCoor->y=RaquetteGCoor->y-speedJ;
                        }else{
                            RaquetteGCoor->y=0;
                        }break;
                    case SDLK_ESCAPE: state->g_bRunning=0;break;
                }
                break;
            case SDL_KEYUP:;break;

            default:break;

            }
        }

}

//BUT initialisation du jeu
//ENTREE variables relatives au jeu
//SORTIE jeu initié
    void InitJeu(game *myGame,coordonner *RaquetteGCoor,coordonner *RaquetteDCoor, coordonner *BallCoor1,coordonner *BallCoor2,
                  enum BOOL *isMouvLeft,enum BOOL *isMouvRight,enum BOOL *isMouvUp,enum BOOL *isMouvDown,float *speed,float *speedJ){

            //i sert pour dessiner les séparations
                int i=0;
            //speed=vitesse de la balle
                *speed=0.4;
            //speedJ=vitesse de la raquette du joueur
                *speedJ=4;
            //variables d'états de la balle
                *isMouvRight=True;
                *isMouvLeft=False;
                *isMouvUp=True;
                *isMouvDown=False;

           //Définition des raquettes
                SDL_Rect raquetteG;
                SDL_Rect raquetteD;

            //Définition de la séparation
                SDL_Rect separation;

            //Définition de la balle
                SDL_Rect BalleH;
                SDL_Rect BalleL;


            //remplissage de la fenêtre en noir
                SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(myGame->g_pRenderer);

            //set de la couleur en blanc
                SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

            //set de la raquette de gauche et de ses corrdonnées
                setRectangle(&raquetteG,0,(SCREEN_HEIGHT/2)-(RAQUETTE_HEIGHT/2),RAQUETTE_WIDTH,RAQUETTE_HEIGHT);
                RaquetteGCoor->x=raquetteG.x;
                RaquetteGCoor->y=raquetteG.y;

            //set de la raquette de droite et de ses corrdonnées
                setRectangle(&raquetteD,(SCREEN_WIDTH-RAQUETTE_WIDTH),(SCREEN_HEIGHT/2)-(RAQUETTE_HEIGHT/2),RAQUETTE_WIDTH,RAQUETTE_HEIGHT);
                RaquetteDCoor->x=raquetteD.x;
                RaquetteDCoor->y=raquetteD.y;

            //set de la balle et de ses coordonnées
                setRectangle(&BalleH,(SCREEN_WIDTH/2)-(TAILLEBALLE2/2),0,TAILLEBALLE2,TAILLEBALLE);
                BallCoor1->x=BalleH.x;
                BallCoor1->y=BalleH.y;

                setRectangle(&BalleL,(SCREEN_WIDTH/2)-(TAILLEBALLE/2),5,TAILLEBALLE,TAILLEBALLE2);
                BallCoor2->x=BalleL.x;
                BallCoor2->y=BalleL.y;

            //set et dessin des séparations
                separation.x=(SCREEN_WIDTH/2)-(SEPARATION_WIDTH/2);
                separation.w=SEPARATION_WIDTH;
                separation.h=SEPARATION_HEIGHT;

                do{
                    separation.y=i;
                    SDL_RenderFillRect(myGame->g_pRenderer,&separation);
                    i=i+SEPARATION_HEIGHT*2;
                }while (i<SCREEN_HEIGHT-SEPARATION_HEIGHT);

                separation.h=SCREEN_HEIGHT-i;
                separation.y=i;

                SDL_RenderFillRect(myGame->g_pRenderer,&separation);

            //dessins des raquettes et de la balle
                SDL_RenderFillRect(myGame->g_pRenderer,&raquetteG);
                SDL_RenderFillRect(myGame->g_pRenderer,&raquetteD);
                SDL_RenderFillRect(myGame->g_pRenderer,&BalleH);
                SDL_RenderFillRect(myGame->g_pRenderer,&BalleL);

            //Affichage dans fenêtre
                SDL_RenderPresent(myGame->g_pRenderer);

    }

void MouvBall(gameState *state,game *myGame,coordonner *BallCoor1,coordonner *BallCoor2,coordonner *RaquetteGCoor,
              coordonner *RaquetteDCoor,enum BOOL *isMouvLeft,enum BOOL *isMouvRight,enum BOOL *isMouvUp,enum BOOL *isMouvDown,
              int *scoreJ1, int *scoreIA,float *speed,float *speedJ){

    //i sert à dessiner les séparations
        int i=0;

    //mouvement de la balle
        if (*isMouvRight==True){
            if(BallCoor1->x+0.1>=SCREEN_WIDTH){
                *scoreJ1=*scoreJ1+1;
                if(*scoreJ1==WINSCORE){
                    state->g_bRunning=0;
                    return;
                }
                InitJeu(myGame,RaquetteGCoor,RaquetteDCoor,BallCoor1,BallCoor2,isMouvLeft,isMouvRight,isMouvUp,isMouvDown,speed,speedJ);
            }else if((BallCoor1->y>=RaquetteDCoor->y && BallCoor1->y+TAILLEBALLE<=RaquetteDCoor->y+RAQUETTE_HEIGHT)&& (BallCoor2->x+TAILLEBALLE>=RaquetteDCoor->x)){
                BallCoor1->x=BallCoor1->x-*speed;
                BallCoor2->x=BallCoor2->x-*speed;
                *isMouvRight=False;
                *isMouvLeft=True;
                *speed=*speed+0.01;
                *speedJ=*speedJ+0.25;
            }else{
                BallCoor1->x=BallCoor1->x+*speed;
                BallCoor2->x=BallCoor2->x+*speed;
            }
        }else if(*isMouvLeft==True){
            if(BallCoor1->x-*speed+TAILLEBALLE<=0){
                *scoreIA=*scoreIA+1;
                if(*scoreIA==WINSCORE){
                    state->g_bRunning=0;
                    return;
                }
                InitJeu(myGame,RaquetteGCoor,RaquetteDCoor,BallCoor1,BallCoor2,isMouvLeft,isMouvRight,isMouvUp,isMouvDown,speed,speedJ);
            }else if((BallCoor1->y>=RaquetteGCoor->y && BallCoor1->y+TAILLEBALLE<=RaquetteGCoor->y+RAQUETTE_HEIGHT)&& (BallCoor2->x<=RaquetteGCoor->x+RAQUETTE_WIDTH)){
                BallCoor1->x=BallCoor1->x+*speed;
                BallCoor2->x=BallCoor2->x+*speed;
                *isMouvRight=True;
                *isMouvLeft=False;
                *speed=*speed+0.01;
                *speedJ=*speedJ+0.25;
            }else{
                BallCoor1->x=BallCoor1->x-*speed;
                BallCoor2->x=BallCoor2->x-*speed;
            }
        }

        if (*isMouvUp==True){
            if(BallCoor1->y-0.1<=0){
                BallCoor1->y=BallCoor1->y+*speed;
                BallCoor2->y=BallCoor2->y+*speed;
                *isMouvUp=False;
                *isMouvDown=True;
                *speed=*speed+0.01;
                *speedJ=*speedJ+0.25;
            }else{
                BallCoor1->y=BallCoor1->y-*speed;
                BallCoor2->y=BallCoor2->y-*speed;
            }
        }else if (*isMouvDown==True){
            if(BallCoor1->y+0.1+TAILLEBALLE>=SCREEN_HEIGHT){
                BallCoor1->y=BallCoor1->y-*speed;
                BallCoor2->y=BallCoor2->y-*speed;
                *isMouvDown=False;
                *isMouvUp=True;
                *speed=*speed+0.01;
                *speedJ=*speedJ+0.25;
            }else{
                BallCoor1->y=BallCoor1->y+*speed;
                BallCoor2->y=BallCoor2->y+*speed;
            }
        }

    //Définition des raquettes
        SDL_Rect raquetteG;
        SDL_Rect raquetteD;

    //Définition de la séparation
        SDL_Rect separation;

    //Définition de la balle
        SDL_Rect BalleH;
        SDL_Rect BalleL;

    //remplissage de la fenêtre en noir
        SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(myGame->g_pRenderer);

    //set de la couleur en blanc
        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    //set de la raquette de gauche
        setRectangle(&raquetteG,RaquetteGCoor->x,RaquetteGCoor->y,RAQUETTE_WIDTH,RAQUETTE_HEIGHT);

    //mouvement de la raqutte de droite
        if(!(BallCoor1->y>=RaquetteDCoor->y && BallCoor1->y+TAILLEBALLE<=RaquetteDCoor->y+RAQUETTE_HEIGHT)){
            if (BallCoor1->y>=RaquetteDCoor->y){
                RaquetteDCoor->y=RaquetteDCoor->y+0.75;
            }else if (BallCoor1->y<=RaquetteDCoor->y){
                RaquetteDCoor->y=RaquetteDCoor->y-0.75;
            }
        }

    //set de la raquette de droite
        setRectangle(&raquetteD,RaquetteDCoor->x,RaquetteDCoor->y,RAQUETTE_WIDTH,RAQUETTE_HEIGHT);

    //set de la balle
        setRectangle(&BalleH,BallCoor1->x,BallCoor1->y,TAILLEBALLE2,TAILLEBALLE);

        setRectangle(&BalleL,BallCoor2->x,BallCoor2->y,TAILLEBALLE,TAILLEBALLE2);

    //set et dessin des séparations
        separation.x=(SCREEN_WIDTH/2)-(SEPARATION_WIDTH/2);
        separation.w=SEPARATION_WIDTH;
        separation.h=SEPARATION_HEIGHT;

        do{
            separation.y=i;
            SDL_RenderFillRect(myGame->g_pRenderer,&separation);
            i=i+SEPARATION_HEIGHT*2;
        }while (i<SCREEN_HEIGHT-SEPARATION_HEIGHT);

        separation.h=SCREEN_HEIGHT-i;
        separation.y=i;

        SDL_RenderFillRect(myGame->g_pRenderer,&separation);

    //dessin des raquettes et de la balle
        SDL_RenderFillRect(myGame->g_pRenderer,&raquetteG);
        SDL_RenderFillRect(myGame->g_pRenderer,&raquetteD);
        SDL_RenderFillRect(myGame->g_pRenderer,&BalleH);
        SDL_RenderFillRect(myGame->g_pRenderer,&BalleL);

    //Affichage dans fenêtre
        SDL_RenderPresent(myGame->g_pRenderer);

}

