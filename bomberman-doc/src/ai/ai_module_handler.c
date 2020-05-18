#include "../../headers/ai.h"

bool reachedDestination( AIModule *module )
{
    if( abs( module->actor->x - module->current_step.dest_x ) < 1 && abs( module->actor->y - module->current_step.dest_y ) <  1 )
        return true;
    return false;
}

void doNextStep( AIModule *module )
{
    PathStep prev_step = module->current_step;

    if( module->reversed_path == false )
        module -> step_index++;
    else
        module -> step_index--;

    PathStep next_step = module->path.steps[ module->step_index ];

    resetVelocity( module->actor );

    if( next_step.dest_x - prev_step.dest_x < 0 )
        updateVelocityX( module->actor, true, false );
    else if( next_step.dest_x - prev_step.dest_x > 0 )
        updateVelocityX( module->actor, false, true );

    if( next_step.dest_y - prev_step.dest_y < 0 )
        updateVelocityY( module->actor, true, false );
    else if( next_step.dest_y - prev_step.dest_y > 0 )
        updateVelocityY( module->actor, false, true );

    if( module->step_index == 0 )
        module -> reversed_path = false;
    else if( module->step_index == module->path.step_num - 1 )
        module -> reversed_path = true;

    module -> current_step = next_step;
}