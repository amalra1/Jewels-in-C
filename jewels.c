#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#define ScreenWidth 640
#define ScreenHeight 480

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main()
{
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP* img;
    
    const float FPS = 60.0;

    bool done = false, draw = false;
    float x, y, speed = 5;

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

    al_start_timer(timer);

    // Loop principal do jogo
    while (true)
    {
        ///
        // Testando
        ///

        int i;

        
        
        for(i=0;i < 10;i++) 
        {
            al_clear_to_color(white);
            al_draw_bitmap(img, 0, 0, 0);
            
            al_flip_display();
            al_rest(1.0);
            al_clear_to_color(white);
            al_draw_bitmap(img, 0, 10, 0);
            
            al_flip_display();
            al_rest(1.0);
        }

        al_clear_to_color(black);
        al_flip_display();

        al_rest(1.0);

    }

    // Destroys
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(img);

    return 0;
}
