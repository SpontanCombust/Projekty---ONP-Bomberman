#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

// definicje stalej wysokosci okna
#define SCREEN_HEIGHT 480
// definicje stalej szderokosci okna
#define SCREEN_WIDTH 640
// definicje stalej czestotliwosci wyswietlania
// tu rowniez dotychczas jak czesto bedzie odswiezana sama logika gry - mniej FPS, bardziej tnie 
#define FPS 60.0

struct SEntity {
    int x, y;
    ALLEGRO_BITMAP *bmp;
};
typedef struct SEntity Entity; 

void setEntity(Entity *entity, int x, int y, ALLEGRO_BITMAP *bmp)
{
    entity -> x = x;
    entity -> y = y;
    entity -> bmp = bmp;
}

int main(void)
{
    // enum dla kierunku, w ktorym ma byc zwrocona postac
    enum Direction { DOWN, UP, LEFT, RIGHT };

    // inicjalizacja biblioteki i sprawdzenie, czy zostala ta procedura wykonana pomyslnie
    if (!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }

    // deklaracja i inicjalizacja zmiennej wskaznikowej display odpowiadajacej za wyswietlacz
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    // sprawdzenie, czy "display" zostal stworzony pomyslnie 
    if (!display)
    {
        // wyswietlenie komunikatu o bledzie
        fprintf(stderr, "Failed to create display!\n");
        // zwrocenie wartosci odpowiadajacej odpowiedniemu bledowi
        return -1;
    }

    // ustawienie flagi dla wyswietlacza, tutaj: praca w trybie okna
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    // ustawienie tytulu dla okna
    al_set_window_title(display, "BOMBERMAN");
    // ustawienie pozycji okna
    al_set_window_position(display, 600, 300);

    // zainstalowanie klawiatury - pozwolenie na uzycie funkcji przechwytywania wejsc z klawiatury
    al_install_keyboard();
    // zainicjowanie modulu odpowiedzialnego za obsluge obrazow
    al_init_image_addon();

    // deklaracja i inicjalizacja kolejki zdarzen
    ALLEGRO_EVENT_QUEUE *eq = al_create_event_queue();
    // deklaracja i inicjalizacja czasomierza sluzacego do przechwytywania momentu uplyniecia danego czasu, tu: czasu odswiezania 
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    // deklaracja stanu klawiatury (obecnie wcisnietego klawisza)
    ALLEGRO_KEYBOARD_STATE keyState;

    // zarejestrowanie klawiatury jako zrodla zdarzen
    al_register_event_source( eq, al_get_keyboard_event_source() );
    // zarejestrowanie czasomierza jako zrodla zdarzen
    al_register_event_source( eq, al_get_timer_event_source( timer ) );
    // zarejestrowanie okna jako zrodla zdarzen (by mozna bylo zakonczyc program przez nacisniecie "X")
    al_register_event_source( eq, al_get_display_event_source( display ) );

    // deklaracja i inicjalizacja bitmapy "player_sprites" przechowujacej sprite'y bohatera
    ALLEGRO_BITMAP *player_sprites = al_load_bitmap("player_sheet.png");
    Entity player;
    setEntity(&player, 100, 100, player_sprites);

    int v = 5;
    int dir = DOWN;
    bool done = false, draw = false;

    // zapoczotkowanie dzialania czasomierza - za nim powinna sie znajdowac tylko petla gry
    al_start_timer( timer );

    // petla gry
    while( !done )
    {
        ALLEGRO_EVENT event;
        al_wait_for_event( eq, &event );

        if ( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
            done = true;

        else if ( event.type == ALLEGRO_EVENT_TIMER )
        {
            al_get_keyboard_state( &keyState );

            if( al_key_down( &keyState, ALLEGRO_KEY_DOWN ) ) {
                dir = DOWN;
                player.y += v;
            }
            if ( al_key_down( &keyState, ALLEGRO_KEY_UP ) ) {
                dir = UP;
                player.y -= v;
            }
            if ( al_key_down( &keyState, ALLEGRO_KEY_LEFT ) ) {
                dir = LEFT;
                player.x -= v;
            }
            if ( al_key_down( &keyState, ALLEGRO_KEY_RIGHT ) ) {
                dir = RIGHT;
                player.x += v;
            }

            if ( al_key_down( &keyState, ALLEGRO_KEY_ESCAPE ) )
                done = true;

            draw = true;
        }

        if ( draw )
        {
            al_draw_bitmap_region(player.bmp, dir * 32, 0, 32, 32, player.x, player.y, 0);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 150, 0));
            // wazne, by "draw" ustawiac na false po kazdym zwroceniu bufora, by nie marnowac zasobow na nadmierne renderowanie
            // aktualne tylko w przypadku, gdy nic nie porusza sie na ekranie 
            draw = false;
        }    
    }

    al_destroy_event_queue(eq);
    al_destroy_timer(timer);
    al_destroy_display(display);

    return 0;
}
