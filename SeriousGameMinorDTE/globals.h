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

const int QUESTION_FONT_SIZE = 70;
const int QUESTION_NUMBER_FONT_SIZE = 30;

const int QUESTION_TEXT_X = 30;
const int QUESTION_TEXT_Y = 30;
const int QUESTION_TEXT_MAX_WIDTH = DISPLAY_WIDTH - 30;
const int QUESTION_NUMBER_TEXT_X = 200;
const int QUESTION_NUMBER_TEXT_Y = 478;

const int ANSWER_FONT_SIZE = 30;
//const int ANSWER_X[4] = { DISPLAY_WIDTH/4, (DISPLAY_WIDTH/4)*3, DISPLAY_WIDTH/4, (DISPLAY_WIDTH/4)*3 }; --> OBSOLETE
//const int ANSWER_Y[4] = { 550, 550, DISPLAY_HEIGHT - 175, DISPLAY_HEIGHT - 175 }; --> NOT NEEDED ANYMORE

//Maximum amount of possible answers per question
const int MAX_ANSWERS = 4;

//Maximum amount of questions per quiz
const int MAX_QUESTIONS = 10;

//Amount of quiz subjects (1 for every individual research)
const int AMOUNT_OF_SUBJECTS = 5;

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
std::string questions[AMOUNT_OF_SUBJECTS][MAX_QUESTIONS] = {	{"What characteristics does a modelling tool need for modelling LiDAR data?", 
																"What are possible candidates for modelling LiDAR data?", 
																"Entity Relationship Modelling produces databases with as less redundancy (double values) as possible.", 
																"Entity Relationship Modelling has a structure that makes producing new queries very simple.", 
																"With Multidimensional Modelling every model is composed of 1 table with a multipart key, which is called a fact table.", 
																"The difference between a STAR schema and a Snowflake schema is that a STAR schema contains more hierarchies, which make the schema more expansive.", 
																"Fact-Oriented Modelling treats all facts as relationships.", 
																"Which modelling method is the most readable for users?", 
																"Which modelling method is most easy to perform?", 
																"What is the best diagram for modelling LiDAR data (choose from the following answers)?" },

																{"What is a direct consequence of rain on LiDAR measurements?", 
																"What visual distortion is characteristic of the rolling shutter effect?", 
																"Which of these is the correct definition of the doppler effect?", 
																"What type of weather can cause inaccurate readings?", 
																"True or false: “The doppler effect causes inaccuracy in the measurement of the distance between the camera and a stationary object?”", 
																"True or false: “Noisy data is data that doesn’t fit your beliefs”.", 
																"Which two schools of thought are the most common for the removal of data noise?", 
																"Are outlying data points considered data noise?", 
																"What does the acronym INFFC stand for?", 
																"Which of these is not a type of data noise within the context of a LiDAR?" }, 

																{"What method of processing data is most suitable for large, existing datasets?", 
																"What method of processing data is most suitable for processing an incoming data flow?", 
																"Which of these encoding formats reduce data to the smallest format?", 
																"Which are the three most important requirements for data intensive applications?", 
																"Partitioning of a data collection means:", 
																"If you want to be able to retrieve your data as fast as possible you should opt for:", 
																"When scaling vertically you:", 
																"When stored on a machine, data is represented as:", 
																"Which way of encoding is the most practical when you are sending data to/from a web application?", 
																"Which measure helps improve data availability most?" },

																{"Does raw LiDAR data need some kind of modifications to be user friendly?", 
																"Which of the following subjects are utilizing LiDAR either in product or research?", 
																"How much is expected data creation in 2030 ( in zettabytes, approx)?", 
																"Companies should think of data as an asset.", 
																"According to MIT-Sloan research “what’s your data worth” data can be divided into three different categories, which category doesn’t belong here? (1)?", 
																"The data strategy is not important when a company wants to utilize data better.", 
																"What benefits the data strategy provides? ( choose the INCORRECT option) ", 
																"There are usually three different paths to data monetizations.", 
																"Externally there are 3 different paths of data monetization. Choose the correct paths", 
																"Data as a service is the simplest of the three paths and has the lowest business potential." },
		
																{"", "", "", "", "", "", "", "", "", "" } };

//Answers (CHANGE TO VECTORS)
std::string answers[][MAX_ANSWERS + 1] = { {"Yes", "No", "", "", "0"}, //Maximum of 4 answers for a single question + 1 string to determine the correct answer (which will be converted to an int)
											{"AA", "BB", "CC", "DD"},
											{"AAA", "BBB", "CCC", "DDD"},
											{"AAAA", "BBBB", "CCCC", "DDDD"} };