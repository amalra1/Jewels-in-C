#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#define ScreenWidth 640
#define ScreenHeight 480
#define ROWS 8
#define COLS 8
#define NUM_JEWEL_TYPES 4

// Funcao que verifica as inicializacoes
void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

// Funcao que inicializa a matriz que contera as jewels
// Cada campo da matriz recebera um numero, indicando
// o tipo da joia
void board_init(int board[ROWS][COLS])
{
    int i, j;

    for (i = 0; i < ROWS; i++) 
    {
        for (j = 0; j < COLS; i++)
            board[i][j] = rand() % NUM_JEWEL_TYPES;
    }
}

void drawMainMenu() {}
void drawGameplay() {}
void drawPauseMenu() {}
void drawGameOver() {}

// Funcao que realiza a parte de 'output' da logica do game
void draw(GameState state) 
{
    int i, j;

    al_clear_to_color(black);
    for (i = 0; i < ROWS; i++) 
    {
        for (j = 0; j < COLS; i++)
            al_draw_textf(font, al_map_rgb(255, 255, 255), i, j, 0, "%d", board[i][j]);   
    }

    /*switch (state) 
    {
        case MAIN_MENU:
            drawMainMenu();
            break;
        case GAMEPLAY:
            drawGameplay();
            break;
        case PAUSE:
            drawPauseMenu();
            break;
        case GAME_OVER:
            drawGameOver();
            break;
    }*/
    al_flip_display();
}

int main()
{   
    enum GameState { MAIN_MENU, GAMEPLAY, PAUSE, GAME_OVER };
    GameState currentState;

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP* img;
    
    const float FPS = 60.0;

    bool done = false, draw = false;
    float x, y, speed = 5;
    int board[ROWS][COLS];
    int i, j;

    // Inicia a allegro
    must_init(al_init(), "allegro");

    // Inicia a captura das imagens
    must_init(al_init_image_addon(), "images");

    // Inicia a captura do teclado
    must_init(al_install_keyboard(), "keyboard");

    // Inicia a captura do mouse
    must_init(al_install_mouse(), "mouse");

    // Inicia a imagem
    img = al_load_bitmap("small_jewels.png");
    must_init(img, "imagem");

    // Inicia o timer
    timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    // Inicia a queue de eventos
    queue = al_create_event_queue();
    must_init(queue, "queue");

    // Inicia o display
    disp = al_create_display(ScreenWidth, ScreenHeight);
    must_init(disp, "display");

    // Inicia as fontes
    font = al_create_builtin_font();
    must_init(font, "font");

    // Registra os eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_hide_mouse_cursor(disp); 

    // Alguns 'defines' para cores
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

    // Define a posicao do display na tela
    al_set_window_position(disp, 400, 250);

    // Estado inicial = menu
    currentState = MAIN_MENU;

    // Iniciando a matriz
    board_init(board);

    //al_start_timer(timer);

    // Loop principal do jogo
    while (!done) 
    {
        switch (currentState) 
        {
            case MAIN_MENU:
                updateMainMenu();
                break;
            case GAMEPLAY:
                updateGameplay();
                break;
            case PAUSE:
                updatePauseMenu();
                break;
            case GAME_OVER:
                updateGameOver();
                break;
        }
        draw(currentState);
    }

    // Destroys
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(img);

    return 0;
}
