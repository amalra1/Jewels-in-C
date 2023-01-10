#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

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

    bool done = false;
    float x, y, speed = 5;

    // Inicia a allegro
    must_init(al_init(), "allegro");

    // Inicia a captura do teclado
    must_init(al_install_keyboard(), "keyboard");

    // Inicia o timer
    timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    // Inicia a queue de eventos
    queue = al_create_event_queue();
    must_init(queue, "queue");

    // Opcoes para fluidez de imagens
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // Inicia o display
    disp = al_create_display(ScreenWidth, ScreenHeight);
    must_init(disp, "display");

    // Inicia as fontes
    font = al_create_builtin_font();
    must_init(font, "font");

    // Inicia os primitives
    must_init(al_init_primitives_addon(), "primitives");

    // Registra os eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    x = 100;
    y = 100;
    al_start_timer(timer);

    // Loop principal do Game
    while(!done)
    {
        al_wait_for_event(queue, &event);

        if (events.type = ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (events.keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN
                    y += speed;
                    break;
                case ALLEGRO_KEY_UP
                    y -= speed;
                    break;
                case ALLEGRO_KEY_LEFT
                    x -= speed;
                    break;
                case ALLEGRO_KEY_RIGHT
                    x += speed;
                    break;
                case ALLEGRO_KEY_ESCAPE
                    done = true;
                    break;
            }            
        }

        al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X:%.1f Y:%.1f", x, y);
        al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }

    // Destroys
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
