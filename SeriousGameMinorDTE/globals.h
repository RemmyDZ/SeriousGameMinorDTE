#pragma once

//Screen resolution
const int DISPLAY_WIDTH = 1600;
const int DISPLAY_HEIGHT = 900;

//Game states
enum GAMESTATE { MAINMENU, QUIZ_ONE, QUIZ_TWO, QUIZ_THREE, QUIZ_FOUR, QUIZ_FIVE }; //Gameover maybe?

//Coordinations
const int BACKGROUND_X = 0;
const int BACKGROUND_Y = 0;

const int QUESTIONBOX_X = 0;
const int QUESTIONBOX_Y = 0;

const int QUESTION_FONT_SIZE = 100;
const int QUESTION_TEXT_X = 100;
const int QUESTION_TEXT_Y = 100;

const int ANSWER_X[4] = { 2, DISPLAY_WIDTH - 802, 2, DISPLAY_WIDTH - 802 };
const int ANSWER_Y[4] = { 550, 550, DISPLAY_HEIGHT - 175, DISPLAY_HEIGHT - 175 };

//Maximum amount of possible answers per question
const int MAX_ANSWERS = 4;

//Answer left or right --> This decides what bitmap to load
enum POSITION { LEFT, RIGHT};

//Refresh rate
const int FPS = 60;

//Main loop condition
bool isGameFinished = false; //Main loop will break once this turns 'true'

//Draw condition
bool redraw = true; //Always start with 'true', otherwise nothing will be drawn in the first frame

//Windowed/fullscreen switch
bool fullScreen = false; //Game starts in windowed mode, which can be toggled to fullscreen

//Questions
std::string questions[] = { "Question 1", "Question 2", "Question 3", "Question 4" };

//Answers
std::string answers[][MAX_ANSWERS] = { {"A", "B", "C", "D"}, //Maximum of 4 answers for a single question
							{"AA", "BB", "CC", "DD"},
							{"AAA", "BBB", "CCC", "DDD"},
							{"AAAA", "BBBB", "CCCC", "DDDD"} };