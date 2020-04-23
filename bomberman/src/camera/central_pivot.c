#include "../../headers/camera.h"

void updatePivot( CentralPivotModule *cpm )
{
    cpm->pivot -> x = ( cpm->actor1->x + cpm->actor2->x ) / 2;
    cpm->pivot -> y = ( cpm->actor1->y + cpm->actor2->y ) / 2;
}

void applyActorsToPivot( CentralPivotModule *cpm, Actor *actor1, Actor *actor2 )
{
    Actor *empty = createActor( 0, 0, 0, NULL );
    cpm -> pivot  = empty;
    cpm -> actor1 = actor1;
    cpm -> actor2 = actor2;
    updatePivot( cpm );
}
