#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}


int main()
{

enum BOUNCER_TYPE 
{
    BT_HELLO = 0,
    BT_MYSHA,
    BT_TRIANGLE,
    BT_RECTANGLE_1,
    BT_RECTANGLE_2,
    BT_CIRCLE,
    BT_LINE1,
    BT_LINE2,
    BT_N
};

typedef struct BOUNCER
{
    float x, y;
    float dx, dy;
    int type;
} BOUNCER;

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP* mysha;

    bool done = false, redraw = true;

    // Inicia a allegro
    must_init(al_init(), "allegro");

    // Inicia a captura do teclado
    must_init(al_install_keyboard(), "keyboard");

    // Inicia o timer
    timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    // Inicia a queue
    queue = al_create_event_queue();
    must_init(queue, "queue");

    // Opcoes para fluidez de imagens
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // Inicia o display
    disp = al_create_display(640, 480);
    must_init(disp, "display");

    // Inicia as fontes
    font = al_create_builtin_font();
    must_init(font, "font");

    // Inicia a imagem da mysha
    must_init(al_init_image_addon(), "image addon");
    mysha = al_load_bitmap("mysha.png");
    must_init(mysha, "mysha");

    // Inicia os primitives
    must_init(al_init_primitives_addon(), "primitives");

    // Registra os eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    // Loop principal do Game
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 290, 200, 0, "JEWELS");
            al_draw_bitmap(mysha, 160, 240, 0);
            al_flip_display();

            redraw = false;
        }
    }

    // Destroys
    al_destroy_bitmap(mysha);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}