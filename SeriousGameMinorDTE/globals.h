#pragma once

//Screen resolution
const int DISPLAY_WIDTH = 1600;
const int DISPLAY_HEIGHT = 900;

//Game states
enum GAMESTATE { MAINMENU, QUIZ_ONE, QUIZ_TWO, QUIZ_THREE, QUIZ_FOUR, QUIZ_FIVE }; //Gameover maybe?

//Coordinations and font sizes
const int BACKGROUND_X = 0;
const int BACKGROUND_Y = 0;

const int QUESTIONBOX_X = 0;
const int QUESTIONBOX_Y = 0;

const int QUESTION_FONT_SIZE = 100;
const int QUESTION_NUMBER_FONT_SIZE = 30;

const int QUESTION_TEXT_X = 100;
const int QUESTION_TEXT_Y = 100;
const int QUESTION_NUMBER_TEXT_X = 200;
const int QUESTION_NUMBER_TEXT_Y = 478;

const int ANSWER_FONT_SIZE = 30;
//const int ANSWER_X[4] = { DISPLAY_WIDTH/4, (DISPLAY_WIDTH/4)*3, DISPLAY_WIDTH/4, (DISPLAY_WIDTH/4)*3 }; --> OBSOLETE
//const int ANSWER_Y[4] = { 550, 550, DISPLAY_HEIGHT - 175, DISPLAY_HEIGHT - 175 }; --> NOT NEEDED ANYMORE

//Maximum amount of possible answers per question
const int MAX_ANSWERS = 4;

//Answer left or right --> This decides what bitmap to load
enum POSITION { LEFT, RIGHT, TOP, BOTTOM};

//Refresh rate
const int FPS = 60;

//Main loop condition
bool isGameFinished = false; //Main loop will break once this turns 'true'

//Draw condition
bool redraw = true; //Always start with 'true', otherwise nothing will be drawn in the first frame

//Windowed/fullscreen switch
bool fullScreen = false; //Game starts in windowed mode, which can be toggled to fullscreen

//Questions (CHANGE TO VECTORS)
int currentQuestion = 0; //Starts at 0 because it acts as an index to the questions array below
std::string questions[] = { "What will happen when I insert a very long question?", "Question 2", "Question 3", "Question 4" };

//Answers (CHANGE TO VECTORS)
std::string answers[][MAX_ANSWERS] = { {"Yes", "No", "Maybe", "I don't know"}, //Maximum of 4 answers for a single question
							{"AA", "BB", "CC", "DD"},
							{"AAA", "BBB", "CCC", "DDD"},
							{"AAAA", "BBBB", "CCCC", "DDDD"} };