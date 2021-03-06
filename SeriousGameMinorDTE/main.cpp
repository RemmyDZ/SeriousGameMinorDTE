//Libraries
#include<iostream>
#include<Windows.h>
#include<shellapi.h>
#include<string>
#include<vector>
#include<iterator>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
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

	//Set display title
	al_set_window_title(display, DISPLAY_TITLE.c_str());

	//Define standard colors
	ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);

	//Initialize addons
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	//Set display icon (after image addon loaded)
	ALLEGRO_BITMAP* icon;
	icon = al_load_bitmap("Resources/Icons/icon2.png");
	al_set_display_icon(display, icon);

	//Create timer
	ALLEGRO_TIMER* timer = NULL;
	timer = al_create_timer(1.0 / FPS);

	//Create audio samples
	ALLEGRO_SAMPLE* backgroundMusic = NULL;
	ALLEGRO_SAMPLE* clickSound = NULL;
	ALLEGRO_SAMPLE_ID backgroundMusicID;

	//Reserve audio samples
	al_reserve_samples(AMOUNT_OF_SAMPLES);

	//Load audio samples
	backgroundMusic = al_load_sample("Resources/Audio/bg_music.wav"); 
	clickSound = al_load_sample("Resources/Audio/button_click.wav"); 

	//Create event queue and event listeners
	ALLEGRO_EVENT_QUEUE* event_queue;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//Create objects
	Background background(BACKGROUND_X, BACKGROUND_Y);
	NextQuestionButton nextQuestionButton;
	MenuBox menuBox("Test");
	MenuButton startQuiz(0, "Start quizzing!", menuBox, 0, "", ""); //Quiznumber doesn't matter here, any number will do 
	MenuButton quitGame(1, "Quit", menuBox, 0, "", ""); //Quiznumber doesn't matter here, any number will do
	MenuButton quizButton[AMOUNT_OF_SUBJECTS] = { MenuButton(0, "Data quality", menuBox, 0, "", "Main Quiz"),
										MenuButton(1, "Collecting LiDAR data", menuBox, 5, "Remco de Zeeuw", "Individual Research"), MenuButton(2, "Data noise", menuBox, 2, "Hicham Agzanay", "Individual Research"),
										MenuButton(3, "Modelling LiDAR data", menuBox, 1, "Danny Zoetmulder", "Individual Research"), MenuButton(4, "Creating and maintaining databases", menuBox, 3, "Ivo Kalverboer", "Individual Research"),
										MenuButton(5, "What to do with modeled data", menuBox, 4, "Valtteri Rauhala", "Individual Research") };
	Question question(""); //Start with empty question
	Answer answer[MAX_ANSWERS] = { Answer(LEFT, TOP, question), Answer(RIGHT, TOP, question),
									Answer(LEFT, BOTTOM, question), Answer(RIGHT, BOTTOM, question) }; //Change text once text coordinates are implemented and update draw()
	//Source source;
	MainMenuButton mainMenuButton[2] = { MainMenuButton(MAIN_MENU_BUTTON_X, MAIN_MENU_BUTTON_Y), MainMenuButton(MAIN_MENU_BUTTON_X_QUIZ_MENU, MAIN_MENU_BUTTON_Y_QUIZ_MENU) };
	SourceButton sourceButton;
	SourceBox sourceBox("", ""); //Start with empty source and url
	CloseSourceButton closeSourceButton;
	Fadeout fadeout;
	TextBox credits(1430, 750, 20, "Danny Zoetmulder\nIvo Kalverboer\nHicham Agzanay\nValtteri Rauhala\nRemco de Zeeuw", true, 200, 30);
	TextBox mainMenuInfo(850, 10, 53, "Welcome to our serious game. This game is comprised of quizes pertaining to our research into LiDAR data. We hope you have fun and maybe learn something new.", true, 750, 55);
	TextBox quizMenuInfo(850, 10, 60, "Please select the quiz you would like to play.", true, 750, 65);
	SoundButton soundButton;

	//Load version font
	ALLEGRO_FONT* versionFont;
	versionFont = al_load_font("Resources/Fonts/GILLUBCD.ttf", VERSION_FONT_SIZE, NULL);

	//Initialize random seed
	srand(time(NULL));

	//Start timer
	al_start_timer(timer);

	//Play background music on loop
	al_play_sample(backgroundMusic, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &backgroundMusicID);

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

		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			if (gameState == MAIN_MENU)
			{
				if (startQuiz.onHover())
					startQuiz.setBitmap(1); //HOVER doesn't work here, as its value is '3'
				else
					startQuiz.setBitmap(DEFAULT);

				if (quitGame.onHover())
					quitGame.setBitmap(1);
				else
					quitGame.setBitmap(DEFAULT);
			}

			else if (gameState == QUIZ_MENU)
			{
				for (int i = 0; i < AMOUNT_OF_SUBJECTS; i++)
				{
					if (quizButton[i].onHover())
						quizButton[i].setBitmap(1); //Hover bitmap
					else
						quizButton[i].setBitmap(DEFAULT);
				}
				for (int i = 0; i < 2; i++)
				{
					if (mainMenuButton[i].onHover())
						mainMenuButton[i].setBitmap(1); //Hover bitmap
					else
						mainMenuButton[i].setBitmap(DEFAULT);
				}
			}

			else if (gameState == QUIZ_ONE || gameState == QUIZ_TWO || gameState == QUIZ_THREE || gameState == QUIZ_FOUR || gameState == QUIZ_FIVE || gameState == QUIZ_SIX)
			{
				if (!fadeout.isVisible) //Don't bother with hover animations while the fadeout is being drawn
				{
					for (int i = 0; i < 2; i++)
					{
						if (mainMenuButton[i].onHover())
							mainMenuButton[i].setBitmap(1); //Hover bitmap
						else
							mainMenuButton[i].setBitmap(DEFAULT);
					}
				}

				if (!isAnswerGiven) //Only change bitmaps when the answer hasn't been given yet (if answer hasn't been given yet, fadeout cannot possibly be visible, so no need to check for that)
				{
					for (int i = 0; i < MAX_ANSWERS; i++)
					{
						if (answer[i].onHover())
							answer[i].setBitmap(HOVER); //Set the bitmap to the hover bitmap when the mouse is hovering over the answer box
						else
							answer[i].setBitmap(DEFAULT); //Set bitmap back to default when the mouse is no longer hovering over the answer box
					}
				}
				else if (isAnswerGiven && !fadeout.isVisible) //Don't bother with hover animations while the fadeout is being drawn
				{
					if (nextQuestionButton.onHover())
						nextQuestionButton.setBitmap(1);
					else
						nextQuestionButton.setBitmap(DEFAULT);

					if (sourceButton.onHover())
						sourceButton.setBitmap(1);
					else
						sourceButton.setBitmap(DEFAULT);
					
				}
				else if (isAnswerGiven && fadeout.isVisible)
				{
					if (closeSourceButton.onHover())
						closeSourceButton.setBitmap(1);
					else
						closeSourceButton.setBitmap(DEFAULT);

					if (sourceBox.onHover())
						sourceBox.setHover(true);
					else
						sourceBox.setHover(false);
				}
			}

			else if (gameState == END_SCREEN)
			{
				for (int i = 0; i < 2; i++)
				{
					if (mainMenuButton[i].onHover())
						mainMenuButton[i].setBitmap(1); //Hover bitmap
					else
						mainMenuButton[i].setBitmap(DEFAULT);
				}
			}
		}
		

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (gameState == MAIN_MENU)
			{
				if (event.mouse.button == 1)
				{
					if (startQuiz.onClick())
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						setGameState(QUIZ_MENU);
					}

					else if (quitGame.onClick())
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						isGameFinished = true;
					}

					else if (soundButton.onClick())
					{
						if (soundButton.getMuteStatus()) //Sound is muted and will be un-muted
						{
							soundButton.setBitmap(0);
							soundButton.setMuteStatus(false);
							al_play_sample(backgroundMusic, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &backgroundMusicID);
							
						}
						else if (!soundButton.getMuteStatus()) //Sound is un-muted and will be muted
						{
							soundButton.setBitmap(1);
							soundButton.setMuteStatus(true);
							al_stop_sample(&backgroundMusicID);
						}
					}
				}
			}
			else if (gameState == QUIZ_MENU)
			{
				if (event.mouse.button == 1) //Left click
				{
					if (mainMenuButton[1].onClick())
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						background.setBitmap(DEFAULT);
						setGameState(MAIN_MENU);
					}
					for (int i = 0; i < AMOUNT_OF_SUBJECTS; i++)
					{
						if (quizButton[i].onClick()) //Check if button is clicked
						{
							al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							switch (quizButton[i].quizNumber)
							{
							case 0:
								setGameState(QUIZ_ONE);
								break;
							case 1:
								setGameState(QUIZ_TWO);
								break;
							case 2:
								setGameState(QUIZ_THREE);
								break;
							case 3:
								setGameState(QUIZ_FOUR);
								break;
							case 4:
								setGameState(QUIZ_FIVE);
								break;
							case 5:
								setGameState(QUIZ_SIX);
								break;
							default:
								break;
							}
							currentQuestion = 0;
							playerScore = 0; //Reset player score
							randomQuestions.clear(); //Reset the vector with random question numbers
							resetAnswers(answer);
							goToNextQuestion(question, answer, sourceBox, gameState, -1); //Random question
						}
					}
				}
			}
			else if (gameState == QUIZ_ONE || gameState == QUIZ_TWO || gameState == QUIZ_THREE || gameState == QUIZ_FOUR || gameState == QUIZ_FIVE || gameState == QUIZ_SIX)
			{
				if (event.mouse.button == 1) //Left click
				{
					if (checkForAnswers(question, answer, true))
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					if (isAnswerGiven && nextQuestionButton.onClick() && !fadeout.isVisible) //Only go to the next question when an answer has been given and the button has been pressed
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						if (currentQuestion < 9)
						{
							currentQuestion++;
							resetAnswers(answer);
							goToNextQuestion(question, answer, sourceBox, gameState, -1); //Random question
							nextQuestionButton.setBitmap(DEFAULT);
						}
						else if (currentQuestion == 9)
						{
							background.setBitmap(1); //Set background to score screen
							setGameState(END_SCREEN);
						}
					}
					if (mainMenuButton[0].onClick() && !fadeout.isVisible)
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						background.setBitmap(DEFAULT);
						setGameState(MAIN_MENU);
					}
					if (isAnswerGiven && sourceButton.onClick() && !fadeout.isVisible)
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						fadeout.setVisibility(true);
					}
					if (isAnswerGiven && fadeout.isVisible && closeSourceButton.onClick())
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						fadeout.setVisibility(false);
					}
					if (isAnswerGiven && fadeout.isVisible && sourceBox.onClick())
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						std::string url = sourceBox.getURL();
						ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL); //Only works on Windows!
						
					}
				}
			}

			else if (gameState == END_SCREEN)
			{
				if (event.mouse.button == 1) //Left click
				{
					if (mainMenuButton[1].onClick())
					{
						al_play_sample(clickSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						background.setBitmap(DEFAULT);
						setGameState(MAIN_MENU);
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
				quitGame.draw();
				credits.draw();
				mainMenuInfo.draw();
				soundButton.draw();
				al_draw_textf(versionFont, BLACK, 800, 870, NULL, "Version: %s", VERSION.c_str());
			}

			else if (gameState == QUIZ_MENU)
			{
				menuBox.draw();
				for (int i = 0; i < AMOUNT_OF_SUBJECTS; i++)
				{
					quizButton[i].draw();
				}
				mainMenuButton[1].draw();
				quizMenuInfo.draw();
			}

			else if (gameState == END_SCREEN)
			{
				mainMenuButton[1].draw();
			}

			else if (gameState == QUIZ_ONE || gameState == QUIZ_TWO || gameState == QUIZ_THREE || gameState == QUIZ_FOUR || gameState == QUIZ_FIVE || gameState == QUIZ_SIX)
			{
				question.draw();
				if (isAnswerGiven)
				{
					nextQuestionButton.draw(); //Only shows when answer has been given
					sourceButton.draw(); 
				}
				for (size_t i = 0; i < std::size(answer); i++)
				{
						answer[i].draw();
				}
				mainMenuButton[0].draw();
				fadeout.draw();
				if (fadeout.isVisible) //Only show the source box  and 'close source'-button when fadeout is active
				{
					sourceBox.draw();
					closeSourceButton.draw();
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
	nextQuestionButton.clear();
	quitGame.clear();
	for (int i = 0; i < AMOUNT_OF_SUBJECTS; i++)
	{
		quizButton[i].clear();
	}
	for (int i = 0; i < 2; i++)
	{
		mainMenuButton[i].clear();
	}
	sourceButton.clear();
	sourceBox.clear();
	closeSourceButton.clear();
	fadeout.clear();
	credits.clear();
	mainMenuInfo.clear();
	quizMenuInfo.clear();
	soundButton.clear();
	al_destroy_display(display);
	al_destroy_sample(backgroundMusic);
	al_destroy_sample(clickSound);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_primitives_addon();
	al_shutdown_font_addon();
	al_shutdown_native_dialog_addon();
	al_shutdown_image_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_audio();
	al_uninstall_system();
}