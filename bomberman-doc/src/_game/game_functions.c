/** @file game_functions.c
 * 
 * @brief Plik zawiera funkcje używane już bezpośrednio w pętlach gry i menu
 * 
 * @author  Przemysław Cedro
 * @date    2020.05.29
*/

#include "../../headers/_game.h"

/**
 * @brief Aktualizuje stan zmiennej wpisu wybranego poziomu na podstawie Stanu Gry
 * 
 * @param ls_menu wskaźnik na Menu wyboru poziomu
 */
void updateSelectedLevelVar( Menu *ls_menu ) {
    updateEntryVar( ls_menu, LEVEL_VAR_INDEX, getSelectedLevel( &gs ) );
}

/**
 * @brief Aktualizuje stan zmiennej wpisu wybranych skórek dla postaci na podstawie Stanu Gry
 * 
 * @param opt_menu wskaźnik na Menu opcji
 */
void updateSelectedSkinVars( Menu *opt_menu ) {
    updateEntryVar( opt_menu, SKIN_P1_VAR_INDEX, getSelectedSkinP1( &gs ) );
    updateEntryVar( opt_menu, SKIN_P2_VAR_INDEX, getSelectedSkinP2( &gs ) );
}

/**
 * @brief Ustala jaką bitmapę powinien otrzymać dany gracz
 * 
 * Na podstawie podanego w parametrze ID gracza (1 lub 2) pobiera aktualnie  wybraną dla niego \n
 * skórkę i według tego jak się nazywa zwraca odpowiednią bitmapę.
 * 
 * @param p ID gracza (1 lub 2)
 * 
 * @return bitmapa odpowiedniej skórki 
 */
static ALLEGRO_BITMAP *resolvePlayerBitmaps( char p )
{
    char skin[10];
    if( p == 0 ) strcpy( skin, getSelectedSkinP1( &gs ) );
    else strcpy( skin, getSelectedSkinP2( &gs ) );

    ALLEGRO_BITMAP *bmp = NULL;
    if( strcmp( skin, "ORIG" ) == 0 )
        bmp = al_load_bitmap( PLAYER_SPRITES_ORIG_SRC );
    if( strcmp( skin, "ALT1" ) == 0 )
        bmp = al_load_bitmap( PLAYER_SPRITES_ALT1_SRC );
    if( strcmp( skin, "ALT2" ) == 0 )
        bmp = al_load_bitmap( PLAYER_SPRITES_ALT2_SRC );
    
    return bmp;
}

/**
 * @brief Ładuje aktualne skórki dla każdego z graczy
 * 
 * Aktualizuje zmienne globalne bitmap skórek dla graczy 1 i 2. Zwraca kod zwrotny wykonania funkcji. \n
 * Jeśli kod to 0, wszystko poszło pomyślnie. Jeśli -1, jednak ze skórek nie została załadowana \n
 * poprawnie.
 * 
 * @return kod zwrotny funkcji - 0 jeśli wszystko poszło pomyślnie
 */
int loadSelectedSkins( void )
{
    al_destroy_bitmap( player1_sprites );
    al_destroy_bitmap( player2_sprites );

    player1_sprites = resolvePlayerBitmaps( 0 );
    player2_sprites = resolvePlayerBitmaps( 1 );

    if( player1_sprites == NULL || player2_sprites == NULL ) {
        return -1;
        al_show_native_message_box( NULL, "ERROR", "Player sprites loading error!", "Failed to laod player sprites.", NULL, ALLEGRO_MESSAGEBOX_ERROR );
    }
    return 0;
}

/**
 * @brief Zmienia aktualnie uczęszczanie Menu
 * 
 * Zmienia Menu i przywraca domyślnie wybrany wpis w danym menu. Sygnalizuje koniec zmianu menu \n
 * dla Stanu Gry.
 * 
 * @param current   podwójny wskaźnik na obecne menu 
 * @param goal      wskaźnik na docelowe menu
 */
void switchMenu( Menu **current, Menu *goal ) {
    *current = goal;
    resetToDefaultHighlighted( *current );
    signalStopMenuSwitch( &gs );
}

/**
 * @brief Aktualizuje stan tablic na Bomby i SFX
 * 
 * Iteruje po każdej z tych tablic. \n
 * \n
 * Dla tablicy Bomb, dla każdej obecnej bomby aktualizuje klatkę animacji, zmniejsza czas do wybuchu, \n
 * a jeśli ten wynosi już 0, eksploduje tę bombę, zwalnia z niej pamięć i sygnalizuje zmianę wyglądu mapy. \n
 * \n
 * Dla tablicy SFX, dla każdego obecnego SFX zmniejsza czas życia SFX, a jeśli ten wynosi 0, zwalnia \n
 * pamięć z SFX.
 * 
 * @param bomb_container    tablica wskaźników na Bomby
 * @param sfx_container     tablica wskaźników na SFX
 * @param level_map         Mapa Poziomu
 * @param enemies           tablica wskaźników na aktorów wrogów /nieużywane/
 * @param enemy_num         ilość wrogów /nieużywane/
 * @param explosion_bmp     wskaźnik na bitmapę eksplozji
 * @param map_update        wskaźnik na bool sygnalizacji zmiany wyglądu mapy
 */
void updateContainers( Bomb *bomb_container[], SFX *sfx_container[], LevelMap *level_map, Actor **enemies, int enemy_num, ALLEGRO_BITMAP *explosion_bmp, bool *map_update )
{
    for (int i = 0; i < BOMB_BUDGET; i++)
    {
        if( bomb_container[i] != NULL )
        {
            updateAnimFrameForBomb( bomb_container[i] );
            bomb_container[i] -> fuse--;
            if( bomb_container[i]->fuse == 0 )
            {
                explodeBomb( bomb_container[i], level_map, sfx_container, explosion_bmp );
                destroyBomb( &bomb_container[i] );
                *map_update = true;
            }
        }
    }        

    for (int i = 0; i < SFX_BUDGET; i++)
    {
        if( sfx_container[i] != NULL )
        {   
            sfx_container[i] -> lifespan--;
            if( sfx_container[i]->lifespan == 0)
                destroySFX( &sfx_container[i] );
        }
    }    
}

/**
 * @brief Sprawdza, czy tablice Bomb i SFX są puste
 * 
 * @param bomb_container    tablica wskaźników na Bomby
 * @param sfx_container     tablica wskaxników na SFX
 * 
 * @return true jeśli obie są puste, false w przeciwnym wypadku
 */
bool areContainersEmpty( Bomb *bomb_container[], SFX *sfx_container[] ) {
    return  isBombContainerEmpty( bomb_container ) &&  isSFXContainerEmpty( sfx_container );
}

/**
 * @brief Tworzy SFX zwłok dla danego aktora i dodaje je do tablicy SFX 
 * 
 * @param actor         wskaźnik na aktora
 * @param sfx_container tablica wskaźników na SFX
 */
static void killActor( Actor *actor, SFX *sfx_container[] ) {
    SFX *corpse = createSFX( actor->x, actor->y, CORPSE_LIFESPAN, CORPSE, 0, actor->bmp );
    addSFXToContainer( &corpse, sfx_container );
}

/**
 * @brief Aktualizuje pozycję i kierunek, w którym patrzy się dany gracz
 * 
 * Aktualizuje pozycję dla gracza dla obu osi współrzędnych i w obu przypadkach jeśli ten ma włączoną \n
 * kolizję, obsługuje jej logikę. Na końcu aktualizuje kierunek, w którym powinien patrzyć się Aktor gracza.
 * 
 * @param player    wskaźnik na Aktora gracza
 * @param level_map wskaźnik na Mapę Poziomu
 */
static void updatePlayerPosition( Actor *player, LevelMap *level_map )
{
    Direction cdir;

    updatePositionX( player );
    
    if( player->enabled_collision && isOutOfBounds( player, level_map, &cdir ) )
        handleOutOfBounds( player, level_map, cdir );
    else if( player->enabled_collision && isTerrainCollisionX( player, level_map, &cdir ) )
        handleTerrainCollision( player, cdir );
    

    updatePositionY( player );
    
    if( player->enabled_collision && isOutOfBounds( player, level_map, &cdir ) )
        handleOutOfBounds( player, level_map, cdir );
    else if( player->enabled_collision && isTerrainCollisionY( player, level_map, &cdir ) )
        handleTerrainCollision( player, cdir );
    
    resolveDirection( player );
}

/**
 * @brief Sprawdza, czy gracz kolizuje z wrogami
 * 
 * Jeśli gracz ma włączoną kolizję, sprawdza czy któryś z Aktorów wrogów kolizuje z jego Aktorem.
 * 
 * @param player    wskaźnik na Aktora gracza
 * @param enemies   tablica wskaźników na Aktorów wrogów
 * @param enemy_num liczba wrogów
 * 
 * @return true jeśli gracz kolizuje z którymś z wrogów, false w przeciwnym wypadku
 */
static bool isCollisionWithEnemies( Actor *player, Actor * *enemies, int enemy_num )
{
    if( player -> enabled_collision )
    {
        for (int i = 0; i < enemy_num; i++)
        {
            if( isActorCollision( player, enemies[i] ) )
                return true;
        }
    }
    return false;
}

/**
 * @brief Sprawdza, czy dany aktor dotknął eksplozji
 * 
 * Sprawdza, czy na tym samym polu, na którym znajduje się środek bitmapy Aktora znajduje się też \n
 * SFX eksplozji.
 * 
 * @param actor         wskaźnik na Aktora
 * @param sfx_container tablica wskaźników na SFX
 * 
 * @return true jeśli Aktor dotknął eksplozji, false w przeciwnym wypadku
 */
static bool touchedExplosion( Actor *actor, SFX * sfx_container[] ) {
    return isSFXAtTile( tileFromPixel( actor->x + TILE_SIZE/2 ), tileFromPixel( actor->y + TILE_SIZE/2 ), sfx_container, EXPLOSION );
}

/**
 * @brief Aktualizuje ogólny stan Aktora danego gracza
 * 
 * Jeśl aktor istnieje i jest żywy, aktualizuje jego pozycję, a następnie jeśli ten dotknął wroga \n
 * lub eksplozji i jednocześnie ma włączoną kolizję, zadaje mu obrażenia i jeśli nie jest już żywy, \n
 * tworzy jego zwłoki i synalizuje do Stany Gry śmierć gracza.
 * 
 * @param player 
 * @param level_map 
 * @param enemies 
 * @param enemy_num 
 * @param sfx_container 
 */
void updatePlayer( Actor *player, LevelMap *level_map, Actor * *enemies, int enemy_num, SFX *sfx_container[] )
{
    if( player != NULL && isActorAlive( player ) )
    {
        updatePlayerPosition( player, level_map );

        if( player->enabled_collision && ( touchedExplosion( player, sfx_container ) || isCollisionWithEnemies( player, enemies, enemy_num ) ) ) 
        {
            damageActor( player );

            if( !isActorAlive( player ) ) {
                killActor( player, sfx_container );
                signalPlayerDied( &gs );
            }
        }
    }
}

/**
 * @brief Aktualizuje pozycję dla Modułu AI
 * 
 * Jeśli Aktor zaaplikowany do Modułu osiągnął swój cel, przydzielany mu jest kolejny. Aktualizowana \n
 * jest pozycja Aktora Modułu i kierunek, w którym powinien być skierowany.
 * 
 * @param enemy_module wskaźnik na Moduł AI wrogga
 */
static void updateEnemyPosition( AIModule *enemy_module )
{
    if( reachedDestination( enemy_module ) )
        doNextStep( enemy_module );
    
    updatePositionX( enemy_module -> actor );
    updatePositionY( enemy_module -> actor );

    resolveDirection( enemy_module -> actor );
}

/**
 * @brief Aktualizuje ogólny stan Aktorów i Modułów wrogów
 * 
 * Dla każdego z Modułów wrogów, jeśli jego Aktor jest żywy, aktualizuje jego pozycję, a jeśli ten \n
 * dotyka eksplozji, odejmuje mu punkty życia i zostawia jego zwłoki jeśli ten jest już nieżywy. 
 * 
 * @param enemy_modules tablica wskaźników na Moduły AI wrogów
 * @param enemy_num     ilość wrogów
 * @param sfx_container tablica wskaźników na SFX
 */
void updateEnemies( AIModule * *enemy_modules, int enemy_num, SFX *sfx_container[] )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( isActorAlive( enemy_modules[i]->actor ) )
        {
            updateEnemyPosition( enemy_modules[i] );

            if( touchedExplosion( enemy_modules[i]->actor, sfx_container ) ) 
            {
                damageActor( enemy_modules[i]->actor );

                if( !isActorAlive( enemy_modules[i]->actor ) )
                    killActor( enemy_modules[i]->actor, sfx_container );
            }
        }
    }
}

/**
 * @brief Zajmuje się rysowaniem wszystkiego w czasie rozgrywki
 * 
 * Rysuje Mapę Poziomu, Bomby, SFX i wszystkich żywych Aktorów na obecną docelową bitmapę Allegro, \n
 * Następnie zmienia docelową bitmapę na tylny bufor i rysuje na samej górze panel tytułowy poziomu. \n
 * Na koniec zamienia bufory i wyświetla obecnie narysowaną klatkę gry.
 * 
 * @param camera            wskaźnik na Kamerę
 * @param player1           wskaźnik na Aktora pierwszego gracza
 * @param player2           wskaźnik na Aktora drugiego gracza
 * @param enemies           tablica wskaźników na Aktrów wrogów
 * @param enemy_num         ilość wrogów
 * @param level_map         wskaźnik na Mapę Poziomu
 * @param bomb_container    tablica wskaźników na Bomby
 * @param sfx_container     tablica wskaźników na SFX
 */
void updateGFX( Camera *camera, Actor *player1, Actor *player2, Actor * *enemies, int enemy_num, LevelMap *level_map, Bomb *bomb_container[], SFX *sfx_container[] )
{
    drawLevelMap( level_map );
    drawBombs( bomb_container );
    drawSFX( sfx_container );
    if( isActorAlive( player1 ) )
        drawActor( player1 );
    if( player2 != NULL && isActorAlive( player2) )
        drawActor( player2 );
    for (int i = 0; i < enemy_num; i++)
        if( isActorAlive( enemies[i] ) )   
            drawActor( enemies[i] );

    disableCamera( camera );
    al_set_target_backbuffer( display );
    al_clear_to_color( COLOR_GRAY );
    al_draw_bitmap( game_window, 0, GAME_WINDOW_Y_OFFSET, 0 );
    al_draw_textf( font_small, COLOR_BLACK, SCREEN_WIDTH/2, -1, ALLEGRO_ALIGN_CENTER, "LEVEL %s", getSelectedLevel( &gs ) );

    al_flip_display();
}

/**
 * @brief Zajmuje się rysowaniem wszystkiego w czasie pauzy w grze
 * 
 * Najpierw rysuje stopklatkę gry, z kiedy ta została zatrzymana, a następnie rysuje menu pauzy.
 * 
 * @param game_stop_frame   wskaźnik na bitmapę stopklatki gry
 * @param pause_menu        wskaźnik na Menu pauzy
 */
void updateGFXOnPause( ALLEGRO_BITMAP *game_stop_frame, Menu *pause_menu )
{
    al_draw_bitmap( game_stop_frame, 0, 0, 0 );
    drawMenu( pause_menu );
    al_flip_display();
}

/**
 * @brief Sprawdza, czy Aktorzy wszystkich wrogów są martwi
 * 
 * @param enemies   tablica wskaźników na Aktorów wrogów
 * @param enemy_num ilość wrogów
 * 
 * @return true, jeśli wszyscy wrogowie są nieżywi, false w przeciwnym wypadku 
 */
bool areAllEnemiesDead( Actor * *enemies, int enemy_num )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( isActorAlive( enemies[i]) )
            return false;
    }
    return true;
}

/**
 * @brief Obsługuje działanie kamery przy śmierci jednego z graczy
 * 
 * Jeśli jeden z graczy w trybie, który nie jest trybem pojedynczego gracza, umrze, zamienia cel \n
 * kamery na pozostałego gracza i wyłącza moduł kamery dla wielu graczy.
 * 
 * @param camera    wskaźnik na Kamerę 
 * @param mpcm      wskaźnik na Moduł Kamery Dla Wielu Graczy
 * @param player1   wskaźnik na Aktora pierwszego gracza 
 * @param player2   wskaźnik na Aktora drugiego gracza
 */
void handleCameraOnPlayerDeath( Camera *camera, MultiPlayerCameraModule *mpcm, Actor *player1, Actor *player2 )
{
    if( player2 != NULL ) {
        if( !isActorAlive( player1 ) && isActorAlive( player2 ) )
            camera -> target = player2;
        else if( !isActorAlive( player2 ) && isActorAlive( player1 ) )
            camera -> target = player1;
        destroyActor( &mpcm->target );
    }
}

/**
 * @brief Bierze stopklatkę obecnego momentu w grze
 * 
 * @param gsf       podwójny wskaźnik na bitmapę stopklatki
 * @param camera    wskaźnik na kamerę
 * @param player1   wskaźnik na Aktora pierwszego gracza
 * @param player2   wskaźnik na Aktora drugiego gracza
 * @param eq        wskaźnik na kolejkę zdarzeń Allegro
 */
void handleTakingGameStopFrame( ALLEGRO_BITMAP **gsf, Camera *camera, Actor *player1, Actor *player2, ALLEGRO_EVENT_QUEUE *eq )
{
    *gsf = al_get_backbuffer( display );

    disableCamera( camera );
    resetVelocity( player1 );
    if( player2 != NULL ) resetVelocity( player2 );

    al_flush_event_queue( eq );
    signalStopTakingGameStopFrame( &gs );
}

/**
 * @brief Sprawdza, czy oboje Aktorów graczy jest martwych
 * 
 * @param player1   wskaźnik na Aktora pierwszego gracza
 * @param player2   wskaźnik na Aktora drugiego gracza
 * 
 * @return true jeśli obaj aktorzy nie są żywi, false w przeciwnym wypadku
 */
bool areAllPlayersDead( Actor *player1, Actor *player2 )
{
    return !isActorAlive( player1 ) && ( player2 == NULL || !isActorAlive( player2 ) );
}

/**
 * @brief Aktualizuje klatki animacji dla obu Aktorów graczy
 * 
 * @param player1   wskaźnik na Aktora pierwszego gracza
 * @param player2   wskaźnik na Aktora drugiego gracza
 */
void updateAnimFrameForPlayers( Actor *player1, Actor *player2 )
{
    if( isActorAlive( player1 ) )
        updateAnimFrameForActor( player1 );
    if( player2 != NULL && isActorAlive( player2 ) )
        updateAnimFrameForActor( player2 );
}

/**
 * @brief Aktualizuje klatki animacji dla Aktorów wrogów
 * 
 * @param enemies   tablica wskaźników na Aktorów wrogów
 * @param enemy_num ilość wrogów
 */
void updateAnimFrameForEnemies( Actor * *enemies, int enemy_num )
{
    for (int i = 0; i < enemy_num; i++)
    {
        if( isActorAlive( enemies[i] ) )
            updateAnimFrameForActor( enemies[i] );
    }
}
