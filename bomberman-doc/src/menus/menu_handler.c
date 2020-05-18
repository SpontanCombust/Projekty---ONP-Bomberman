#include "../../headers/menus.h"

void executeSelectOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_highlighted ].operation_select != NULL )
        menu->entries[ menu->currently_highlighted ].operation_select( gs );
}

void executeLeftOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_highlighted ].operation_left != NULL )
        menu->entries[ menu->currently_highlighted ].operation_left( gs ); 
}

void executeRightOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_highlighted ].operation_right != NULL )
        menu->entries[ menu->currently_highlighted ].operation_right( gs );
}

void executeEscOperation( Menu *menu, GameState *gs )
{
    if( menu->operation_esc != NULL )
        menu->operation_esc( gs );
}

static int getNextHighlightableEntryIndex( Menu *menu, int step )
{
    int to_be_highlighted = menu->currently_highlighted;
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        to_be_highlighted += step;

        if( to_be_highlighted >= MAX_ENTRIES )
            to_be_highlighted = 0;
        else if( to_be_highlighted < 0 )
            to_be_highlighted = MAX_ENTRIES - 1;

        if( menu->entries[ to_be_highlighted ].entry_set && menu->entries[ to_be_highlighted ].highlightable )
            return to_be_highlighted;
    }
    return to_be_highlighted;
}

void switchEntry( Menu *menu, int step ) {
    menu -> currently_highlighted = getNextHighlightableEntryIndex( menu, step );
}

void updateEntryVar( Menu *menu, int var_index, char *entry_var ) {
    strncpy( menu->entries[ var_index ].entry_var, entry_var, MAX_ENTRY_VAR_LENGTH );
}