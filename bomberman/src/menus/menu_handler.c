#include "../../headers/menus.h"

void setEntryText( Menu *menu, int entry_index, char *entry_text )
{
    strncpy( menu->entries[ entry_index ].entry_text, entry_text, MAX_ENTRY_TEXT_LENGTH - 1 );
}

void setEntrySelectOperation( Menu *menu, int entry_index, void ( *operation_select )( GameState * ) )
{
    menu -> entries[ entry_index ].operation_select = operation_select;
}

void setEntryLeftOperation( Menu *menu, int entry_index, void ( *operation_left )( GameState * ) )
{
    menu -> entries[ entry_index ].operation_left = operation_left;
}

void setEntryRightOperation( Menu *menu, int entry_index, void ( *operation_right )( GameState * ) )
{
    menu -> entries[ entry_index ].operation_right = operation_right;
}

void setMenuEscOperation( Menu *menu, void ( *operation_esc )( GameState * ) )
{
    menu -> operation_esc = operation_esc;
}

void enableEntry( Menu *menu, int entry_index )
{
    menu -> entries[ entry_index ].entry_set = true;
}

void executeSelectOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_selected ].operation_select != NULL )
        menu->entries[ menu->currently_selected ].operation_select( gs );
}

void executeLeftOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_selected ].operation_left != NULL )
        menu->entries[ menu->currently_selected ].operation_left( gs ); 
}

void executeRightOperation( Menu *menu, GameState *gs )
{
    if( menu->entries[ menu->currently_selected ].operation_right != NULL )
        menu->entries[ menu->currently_selected ].operation_right( gs );
}

void executeEscOperation( Menu *menu, GameState *gs )
{
    if( menu->operation_esc != NULL )
        menu->operation_esc( gs );
}

static int getNextSetEntryIndex( Menu *menu, int step )
{
    int to_be_selected = menu->currently_selected;
    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        to_be_selected += step;

        if( to_be_selected >= MAX_ENTRIES )
            to_be_selected = 0;
        else if( to_be_selected < 0 )
            to_be_selected = MAX_ENTRIES - 1;

        if( menu->entries[ to_be_selected ].entry_set )
            return to_be_selected;
    }
    return to_be_selected;
}

void updateCurrentlySelectedEntry( Menu *menu, int step )
{
    menu -> currently_selected = getNextSetEntryIndex( menu, step );
}
