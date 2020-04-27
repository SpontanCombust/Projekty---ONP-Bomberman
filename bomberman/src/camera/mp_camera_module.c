#include "../../headers/camera.h"

void updateCameraModule( MultiPlayerCameraModule *mpcm )
{
    mpcm->target -> x = ( mpcm->actor1->x + mpcm->actor2->x ) / 2;
    mpcm->target -> y = ( mpcm->actor1->y + mpcm->actor2->y ) / 2;
}

void applyActorsToCameraModule( MultiPlayerCameraModule *mpcm, Actor *actor1, Actor *actor2 )
{
    Actor *empty = createActor( 0, 0, 0, NULL );
    mpcm -> target  = empty;
    mpcm -> actor1 = actor1;
    mpcm -> actor2 = actor2;
    updateCameraModule( mpcm );
}
