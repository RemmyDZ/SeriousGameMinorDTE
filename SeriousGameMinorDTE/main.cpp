//Libraries
#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include"globals.h"
#include"objects.h"

//Main function
int main()
{
	if (!al_init()) //Initialize Allegro and throw an error message if it fails
	{
		al_show_native_message_box(0, "Error", "Error", "Could not initialize Allegro", 0, 0);
	}

	//Create display
	ALLEGRO_DISPLAY* display;
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) //Throw an error message if the display has not been created
	{
		al_show_native_message_box(0, "Error", "Error", "Could not create display", 0, 0);
	}
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST); //Run game in V-sync if available

	//Define standard colors
	ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR RED = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR GREEN = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR BLUE = al_map_rgb(0, 0, 255);

	//Initialize addons
	al_init_primitives_addon();
	al_install_keyboard();

	//Create timer
	ALLEGRO_TIMER* timer = NULL;
	timer = al_create_timer(1.0 / FPS);

	//Create event queue and event listeners
	ALLEGRO_EVENT_QUEUE* event_queue;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//Create objects


	//Start timer
	al_start_timer(timer);

	//Main loop
	while (!isGameFinished)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true; //Redraw everything only after every timer tick. This prevents unnecessary drawing
		}

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			isGameFinished = true;
		}

		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				isGameFinished = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) //Only redraw when variable is 'true' and there are no events being handled
		{
			redraw = false;
			al_clear_to_color(BLACK); //Set background to black
			//Draw objects here
			al_flip_display(); //Everything is drawn to a buffer. Once you flip the display, the buffer replaces the current screen composition
		}
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();
	al_uninstall_keyboard();
}