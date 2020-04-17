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

	}
}