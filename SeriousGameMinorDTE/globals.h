#pragma once

//Screen resolution
const int DISPLAY_WIDTH = 1920;
const int DISPLAY_HEIGHT = 1080;

//Refresh rate
const int FPS = 60;

//Main loop condition
bool isGameFinished = false; //Main loop will break once this turns 'true'

//Draw condition
bool redraw = true; //Always start with 'true', otherwise nothing will be drawn in the first frame

//Questions
const char* questions[] = { "Question 1", "Question 2", "Question 3", "Question 4" };

//Answers
const char* answers[][4] = { {"A", "B", "C", "D"}, //Maximum of 4 answers for a single question
							{"AA", "BB", "CC", "DD"},
							{"AAA", "BBB", "CCC", "DDD"},
							{"AAAA", "BBBB", "CCCC", "DDDD"} };