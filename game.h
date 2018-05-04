#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "rectangle.h"
#include "bool.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 750
#define RAQUETTE_WIDTH 20
#define RAQUETTE_HEIGHT 200
#define TAILLEBALLE 50
#define TAILLEBALLE2 40
#define SEPARATION_WIDTH 10
#define SEPARATION_HEIGHT 30
#define WINSCORE 10

//déclaration du type structuré game
    typedef struct game{

        SDL_Window *g_pWindow;
        SDL_Renderer *g_pRenderer;
        SDL_Texture *g_ptexture;

    }game;

//déclaration du type structuré gameState
    typedef struct gameState{

        int g_bRunning;

    }gameState;

//prototypes
    extern int init(char *title, int xpos, int ypos, int width, int height, int flags, game *myGame);
    extern void destroy(game *myGame);
    extern void handleEvents(gameState *state,coordonner *RaquetteGCoor,float speedJ);
    extern void delay(unsigned int frameLimit);
    extern void InitJeu(game *myGame,coordonner *RaquetteGCoor,coordonner *RaquetteDCoor,coordonner *BallCoor1,coordonner *BallCoor2,
                 enum BOOL *isMouvLeft,enum BOOL *isMouvRight,enum BOOL *isMouvUp,enum BOOL *isMouvDown,float *speed,float *speedJ);
    extern void MouvBall(gameState *state, game *myGame,coordonner *BallCoor1,coordonner *BallCoor2,coordonner *RaquetteGCoor,
                  coordonner *RaquetteDCoor, enum BOOL *isMouvLeft,enum BOOL *isMouvRight,enum BOOL *isMouvUp,enum BOOL *isMouvDown,
                  int *scoreJ1, int *scoreIA,float *speed,float *speedJ);

#endif // CERCLE_H_INCLUDED
