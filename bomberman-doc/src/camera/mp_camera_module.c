/** @file mp_camera_module.c
 * 
 * @brief Plik zawiera funkcje obsługi kamery dla wielu graczy
 * 
 * MPCM - MultiPlayer Camera Module
 * Zawiera funkcje aktualizowania stanu modułu kamery dla wielu graczy oraz aplikowania tego modułu\n
 * dla danych dwóch aktorów.
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.24
*/


#include "../../headers/camera.h"

/** @brief Aktualizuje stan modułu kamery dla wielu graczy
 * 
 * Jeśli moduł jest aktywny, aktualizuje pozycję celu tego modułu, którym jest punkt pośredni\n
 * między pozycją pierwszego i drugiego zaaplikowanego aktora.
 *
 * @param mpcm wskaźnik na moduł kamery dla wielu graczy
*/
void updateCameraModule( MultiPlayerCameraModule *mpcm )
{
    if( mpcm->target != NULL ) {
        mpcm->target -> x = ( mpcm->actor1->x + mpcm->actor2->x ) / 2;
        mpcm->target -> y = ( mpcm->actor1->y + mpcm->actor2->y ) / 2;
    }
}

/** @brief Aplikuje aktorów do modułu kamery dla wielu graczy
 * 
 * Ustawia dwóch podanych aktorów jako cele modułu i tworzy cel dla kamery będący punktem pośrednim\n
 * między pozycjami jednego i drugiego aktora.
 *
 * @param mpcm      wskaźnik na moduł kamery dla wielu graczy
 * @param actor1    wskaźnik na pierwszego aktora
 * @param actor2    wskaźnik na drugiego aktora 
*/
void applyActorsToCameraModule( MultiPlayerCameraModule *mpcm, Actor *actor1, Actor *actor2 )
{
    Actor *empty = createActor( 0, 0, 0, NULL );
    mpcm -> target  = empty;
    mpcm -> actor1 = actor1;
    mpcm -> actor2 = actor2;
    updateCameraModule( mpcm );
}
