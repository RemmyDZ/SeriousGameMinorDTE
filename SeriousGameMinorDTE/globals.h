#pragma once

//Screen resolution
const int DISPLAY_WIDTH = 1600;
const int DISPLAY_HEIGHT = 900;

//Coordinations
const int BACKGROUND_X = 0;
const int BACKGROUND_Y = 0;

const int QUESTIONBOX_X = 0;
const int QUESTIONBOX_Y = 0;

const int ANSWER_X[4] = { 20, 20, DISPLAY_WIDTH - 20, DISPLAY_WIDTH - 20 };
const int ANSWER_Y[4] = { 650, 650, DISPLAY_HEIGHT - 20, DISPLAY_HEIGHT - 20 };

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
std::string answers[][4] = { {"A", "B", "C", "D"}, //Maximum of 4 answers for a single question
							{"AA", "BB", "CC", "DD"},
							{"AAA", "BBB", "CCC", "DDD"},
							{"AAAA", "BBBB", "CCCC", "DDDD"} };