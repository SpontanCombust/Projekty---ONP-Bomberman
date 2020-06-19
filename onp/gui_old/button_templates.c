#include "button.h"

void setCalculatorButtons( Button btns[ BUTTONS_NUMBER ] )
{
    setButton( &btns[0], BUTTONS_ORIGIN_X, BUTTONS_ORIGIN_Y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "<--" );
    setButton( &btns[1], btns[0].x + btns[0].w, btns[0].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "C" );
    setButton( &btns[2], btns[1].x + btns[1].w, btns[0].y, BUTTON_DEFAULT_W * 2, BUTTON_DEFAULT_H, "Enter" );

    setButton( &btns[3], btns[0].x, btns[0].y + btns[0].h, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "7" );
    setButton( &btns[4], btns[3].x + btns[3].w, btns[3].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "8" );
    setButton( &btns[5], btns[4].x + btns[4].w, btns[3].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "9" );
    setButton( &btns[6], btns[5].x + btns[5].w, btns[3].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "/" );

    setButton( &btns[7], btns[0].x, btns[3].y + btns[3].h, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "4" );
    setButton( &btns[8], btns[7].x + btns[7].w, btns[7].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "5" );
    setButton( &btns[9], btns[8].x + btns[8].w, btns[7].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "6" );
    setButton( &btns[10], btns[9].x + btns[9].w, btns[7].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "*" );

    setButton( &btns[11], btns[0].x, btns[7].y + btns[7].h, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "1" );
    setButton( &btns[12], btns[11].x + btns[11].w, btns[11].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "2" );
    setButton( &btns[13], btns[12].x + btns[12].w, btns[11].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "3" );
    setButton( &btns[14], btns[13].x + btns[13].w, btns[11].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "-" );

    setButton( &btns[15], btns[0].x, btns[11].y + btns[11].h, BUTTON_DEFAULT_W * 2, BUTTON_DEFAULT_H, "0" );
    setButton( &btns[16], btns[15].x + btns[15].w, btns[15].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "." );
    setButton( &btns[17], btns[16].x + btns[16].w, btns[15].y, BUTTON_DEFAULT_W, BUTTON_DEFAULT_H, "+" );
}