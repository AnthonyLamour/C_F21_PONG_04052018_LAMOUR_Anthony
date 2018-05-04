#include "rectangle.h"

//BUT set les valeurs d'un rectangle
//ENTREE le rectangle et ses futures valeurs
//SORTIE rectangle set
    void setRectangle(SDL_Rect *Rect,float x,float y,float width,float height){

        Rect->x=x;
        Rect->y=y;
        Rect->w=width;
        Rect->h=height;

    }
