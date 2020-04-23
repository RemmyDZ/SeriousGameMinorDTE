//Libraries
#include<iostream>
#include<string>
#include<iterator>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include"globals.h"
#include"objects.h"
#include"functions.h"

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
	al_install_mouse();

	//Create timer
	ALLEGRO_TIMER* timer = NULL;
	timer = al_create_timer(1.0 / FPS);

	//Create event queue and event listeners
	ALLEGRO_EVENT_QUEUE* event_queue;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//Create objects
	Background background(BACKGROUND_X, BACKGROUND_Y);
	MenuBox menuBox("Test");
	MenuButton startQuiz(0, "Start quizzing!", menuBox);
	MenuButton checkSource(1, "View sources", menuBox);
	MenuButton quitGame(2, "Quit", menuBox);
	MenuButton quizButton[AMOUNT_OF_SUBJECTS] = { MenuButton(0, "Quiz 1", menuBox), MenuButton(1, "Quiz 2", menuBox),
										MenuButton(2, "Quiz 3", menuBox), MenuButton(3, "Quiz 4", menuBox),
										MenuButton(4, "Quiz 5", menuBox) };
	Question question(questions[0][0]);
	Answer answer[MAX_ANSWERS] = { Answer(LEFT, TOP, question), Answer(RIGHT, TOP, question),
									Answer(LEFT, BOTTOM, question), Answer(RIGHT, BOTTOM, question) }; //Change text once text coordinates are implemented and update draw()

	//TEST (REMOVE LATER)
	/*for (size_t i = 0; i < (std::size(questions[currentQuestion])) - 1; i++)
	{
		answer[static_cast<int>(i)].setAnswer(currentQuestion, static_cast<int>(i));
	}*/
	//int answersAmount = (sizeof(answers) / sizeof(answers[0]));
	//size_t result = std::size(answers[0]);
	//int answersAmount = static_cast<int>(result);
	
	//Go to the first question
	goToNextQuestion(question, answer, gameState, currentQuestion);

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
			case ALLEGRO_KEY_T:
				currentQuestion++;
				resetAnswers(answer);
				goToNextQuestion(question, answer, gameState, currentQuestion);
				//question.setQuestion(2);
				break;
			}
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (gameState == MAIN_MENU)
			{
				if (startQuiz.onClick())
				{
					setGameState(QUIZ_MENU);
				}
				else if (checkSource.onClick())
				{
					//
				}
				else if (quitGame.onClick())
				{
					isGameFinished = true;
				}
			}
			else if (gameState == QUIZ_MENU)
			{
				for (int i = 0; i < AMOUNT_OF_SUBJECTS; i++)
				{
					if (quizButton[i].onClick()) //Check if button is clicked
					{
						switch (i)
						{
						case 0:
							setGameState(QUIZ_ONE);
							currentQuestion = QUIZ_INDEX_ONE;
							break;
						case 1:
							setGameState(QUIZ_TWO);
							currentQuestion = QUIZ_INDEX_TWO;
							break;
						case 2:
							setGameState(QUIZ_THREE);
							currentQuestion = QUIZ_INDEX_THREE;
							break;
						case 3:
							setGameState(QUIZ_FOUR);
							currentQuestion = QUIZ_INDEX_FOUR;
							break;
						case 4:
							setGameState(QUIZ_FIVE);
							currentQuestion = QUIZ_INDEX_FIVE;
							break;
						default: 
							break;
						}
						goToNextQuestion(question, answer, gameState, currentQuestion);
					}
				}
			}
			else if (gameState == QUIZ_ONE || gameState == QUIZ_TWO || gameState == QUIZ_THREE || gameState == QUIZ_FOUR || gameState == QUIZ_FIVE)
			{
				if (event.mouse.button == 1) //Left click
				{
					for (int i = 0; i < MAX_ANSWERS; i++)
					{
						answer[i].onClick();
					}
				}
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) //Only redraw when variable is 'true' and there are no events being handled
		{
			redraw = false;
			al_clear_to_color(BLACK); //Set background to black

			//Draw background
			background.draw();

			//Draw objects here
			if (gameState == MAIN_MENU)
			{
				menuBox.draw();
				startQuiz.draw();
				checkSource.draw();
				quitGame.draw();
			}
			else if (gameState == QUIZ_MENU)
			{
				menuBox.draw();
				for (int i = 0; i < AMOUNT_OF_SUBJECTS; i++)
				{
					quizButton[i].draw();
				}
			}
			else if (gameState == QUIZ_ONE || gameState == QUIZ_TWO || gameState == QUIZ_THREE || gameState == QUIZ_FOUR || gameState == QUIZ_FIVE)
			{
				question.draw();
				for (size_t i = 0; i < std::size(answer); i++)
				{
					if (answer[i].isVisible) //Only draw answer if visible (non-visible if question has less answers than the max amount of answers)
					{
						answer[i].draw();
					}
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
	menuBox.clear();
	startQuiz.clear();
	checkSource.clear();
	quitGame.clear();
	for (int i = 0; i < AMOUNT_OF_SUBJECTS; i++)
	{
		quizButton[i].clear();
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
}