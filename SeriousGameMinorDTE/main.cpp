//Libraries
#include<iostream>
#include<iterator>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include"globals.h"
#include"objects.h"

//Main function
int main()
{
	if (!al_init()) //Initialize Allegro and throw an error message if it fails
	{
		al_show_native_message_box(0, "Error", "Error", "Could not initialize Allegro", 0, 0);
	}

	//Set display flags (only works if doing so before creating the display)
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST); //Run game in V-sync if available
	al_set_new_display_flags(ALLEGRO_WINDOWED); //Set the game to windowed by default

	//Create display
	ALLEGRO_DISPLAY* display;
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) //Throw an error message if the display has not been created
	{
		al_show_native_message_box(0, "Error", "Error", "Could not create display", 0, 0);
	}

	//Define standard colors
	ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR RED = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR GREEN = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR BLUE = al_map_rgb(0, 0, 255);

	//Initialize addons
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
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
	Background background(BACKGROUND_X, BACKGROUND_Y);
	MenuButton menuButton(10, 10, "Test");
	Question question(questions[0]);
	Answer answer[MAX_ANSWERS] = { Answer(LEFT, TOP, question), Answer(RIGHT, TOP, question),
									Answer(LEFT, BOTTOM, question), Answer(RIGHT, BOTTOM, question) }; //Change text once text coordinates are implemented and update draw()
	//Controller controller(&question, &answer, &menuButton, &background);

	//TEST (REMOVE LATER)
	/*for (size_t i = 0; i < (std::size(questions[currentQuestion])) - 1; i++)
	{
		answer[static_cast<int>(i)].setAnswer(currentQuestion, static_cast<int>(i));
	}*/
	int answersAmount = (sizeof(answers) / sizeof(answers[0]));
	
	for (int i = 0; i < answersAmount; i++)
	{
		if(! std::empty(answers[currentQuestion][i]))
			answer[i].setAnswer(currentQuestion, i);
	}

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
			case ALLEGRO_KEY_F:
				if (fullScreen)
				{
					fullScreen = false;
					al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, false);
				}
				else if (!fullScreen)
				{
					fullScreen = true;
					al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);
				}
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) //Only redraw when variable is 'true' and there are no events being handled
		{
			redraw = false;
			al_clear_to_color(BLACK); //Set background to black

			//Draw objects here
			background.draw();
			question.draw();
			for (size_t i = 0; i < std::size(answer); i++)
			{
				if (answer[i].isVisible) //Only draw answer if visible (non-visible if question has less answers than the max amount of answers)
				{
					answer[i].draw();
				}
			}

			al_flip_display(); //Everything is drawn to a buffer. Once you flip the display, the buffer replaces the current screen composition
		}
	}

	//Garbage control
	question.clear();
	background.clear();
	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		answer[i].clear();
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();
	al_uninstall_keyboard();
}