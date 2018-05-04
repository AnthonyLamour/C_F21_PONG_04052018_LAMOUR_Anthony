#include "define.h"

int main(int argc, char *argv[])
{
    //déclaration des variables
        //variables relatives à l'état de la balle
            enum BOOL isMouvLeft=False;
            enum BOOL isMouvRight=False;
            enum BOOL isMouvUp=False;
            enum BOOL isMouvDown=False;
        //variables relaives au jeu
            game myGame;
            gameState state;
        //variables de coordonnées des objets
            coordonner RaquetteGCoor;
            coordonner RaquetteDCoor;
            coordonner BallCoor1;
            coordonner BallCoor2;
        //variables de scores
            int scoreJ1=0;
            int scoreIA=0;
        //variables de vitesses
            float speed=0.2;
            float speedJ=2;
        //variable de choix du menu
            int choix=0;

    //boucle permettant de rejouer
        do{
            //menu
                do{
                    //clear screen
                        system("@cls||clear");
                    //affichage du menu
                        printf("1:lancer le jeu\n2:regles du jeu\n3:quitter\n");
                        scanf("%d",&choix);
                }while(choix<1 || choix>3);

            //résultat du choix du joueur
                switch (choix) {
                    case 1: //initialisation de la sdl
                                if(init ("Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame)){

                                    state.g_bRunning=1;

                                }else{

                                    return EXIT_FAILURE; //si impossible d'init sdl erreur

                                }

                            //initialisation du jeu
                                InitJeu(&myGame,&RaquetteGCoor,&RaquetteDCoor,&BallCoor1,&BallCoor2,&isMouvLeft,&isMouvRight,&isMouvUp,&isMouvDown,&speed,&speedJ);

                            //boucle de jeu
                                while(state.g_bRunning){

                                    handleEvents(&state, &RaquetteGCoor,speedJ);
                                    MouvBall(&state,&myGame,&BallCoor1,&BallCoor2,&RaquetteGCoor,&RaquetteDCoor,&isMouvLeft,&isMouvRight,&isMouvUp,&isMouvDown,
                                             &scoreJ1,&scoreIA,&speed,&speedJ);

                                }

                            //destuction du jeu
                                destroy(&myGame);

                            //affichage du score
                                printf("Ordi : %d\nJoueur : %d\n",scoreIA,scoreJ1);
                                system("pause");

                            break;
                    case 2: //affichage des règles du jeu
                                printf("But du jeu :\nMarquer %d points.\n\nCommandes :\nFleche du haut et du bas pour bouger la raquette de haut en bas.(Vous controler la raquette de gauche)\n",WINSCORE);
                                system("pause");
                            break;
                    case 3:break;
                    default:break;
                }
        }while(choix!=3);

    return 0;
}
