#pragma once

//Screen resolution
const int DISPLAY_WIDTH = 1600;
const int DISPLAY_HEIGHT = 900;

//Game states
enum GAMESTATE { MAIN_MENU, QUIZ_MENU, QUIZ_ONE, QUIZ_TWO, QUIZ_THREE, QUIZ_FOUR, QUIZ_FIVE, SCORE_MENU }; //Gameover maybe?
enum QUIZ_INDEX { QUIZ_INDEX_ONE = 0, QUIZ_INDEX_TWO = 10, QUIZ_INDEX_THREE = 20, QUIZ_INDEX_FOUR = 30, QUIZ_INDEX_FIVE = 40 };

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

const int ANSWER_RESIZE_LENGTH = 60; //The size at which a question gets the smaller font
const int ANSWER_FONT_SIZE = 30; 
const int ANSWER_LONG_FONT_SIZE = 25; //For long answers so it doesn't go out of boundaries
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
int currentQuiz = QUIZ_ONE; //Change this later to be dynamic
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
																"True or false: \"The doppler effect causes inaccuracy in the measurement of the distance between the camera and a stationary object?\"", 
																"True or false: \"Noisy data is data that doesn\'t fit your beliefs\".", 
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
																"According to MIT-Sloan research \"what\'s your data worth\" data can be divided into three different categories, which category doesn\'t belong here? (1)?", 
																"The data strategy is not important when a company wants to utilize data better.", 
																"What benefits the data strategy provides? ( choose the INCORRECT option) ", 
																"There are usually three different paths to data monetizations.", 
																"Externally there are 3 different paths of data monetization. Choose the correct paths", 
																"Data as a service is the simplest of the three paths and has the lowest business potential." },
		
																{"", "", "", "", "", "", "", "", "", "" } };

//Answers (CHANGE TO VECTORS)
std::string answers[MAX_QUESTIONS * AMOUNT_OF_SUBJECTS][MAX_ANSWERS + 1] = { {"Able to handle large amounts of data and easy to produce new queries.", "Widely used and easy to understand", "", "", "0"}, //Maximum of 4 answers for a single question + 1 string to determine the correct answer (which will be converted to an int)
											{"Entity Relationship Modelling.", "Multidimensional Modelling.", "Fact-Oriented Modelling.", "All of the above.", "3"},
											{"Correct", "Incorrect", "", "", "0"}, 
											{"Correct", "Incorrect", "", "", "1"}, 
											{"Correct", "Incorrect", "", "", "0"},
											{"Correct", "Incorrect", "", "", "1"},
											{"Correct", "Incorrect", "", "", "0"},
											{"Entity Relationship Modelling.", "Multidimensional Modelling.", "Fact-Oriented Modelling.", "All of the above.", "2"},
											{"Entity Relationship Modelling.", "Multidimensional Modelling.", "Fact-Oriented Modelling.", "All of the above.", "1"},
											{"Entity Relationship Diagram.", "STAR schema (Multidimensional Modelling).", "Snowflake schema (Multidimensional Modelling).", "Object Role schema.", "1"},
											{"The recorded distance may be larger than the actual distance.", "The data becomes corrupted.", "The rain may break the camera.", "The recorded distance may be shorter than the actual distance.", "3"}, 
											{"Wrong colours.", "Malformed objects.", "Blurriness.", "Corrupted image files.", "1"},
											{"The Doppler effect is the change in frequency of a wave in relation to an observer who is moving relative to the wave source", "The Doppler effect is the change in wavelength of a wave in relation to an observer who is moving relative to the wave source", "The doppler effect is a malformation of fast moving objects caused by the mechanics of a rolling shutter camera.", "The doppler effect doesn\'t exist.", "0"},
											{"Harsh sunlight", "Rain", "Fog", "All of the above", "3"},
											{"True", "False", "", "", "1"},
											{"True", "False", "", "", "1"}, 
											{"Algorithmic and Data based.", "Algorithmic and physical removal.", "Only algorithmic.", "Only data based.", "0"},
											{"Yes", "No", "", "", "1"},
											{"Iterative Nose Filter based on the Fusion of Classifiers.", "International Noise Filter based on the Fusion of Classifications.", "I don\'t know", "Internal Nighttime Final Finger Classroom.", "0"},
											{"The rolling shutter effect.", "The doppler effect", "The weather", "Atmospheric noise.", "3"},
											{"Web processing", "Chunk processing", "Stream processing", "Batch processing", "3"}, 
											{"Batch processing", "Service processing", "Stream processing", "Web processing", "2"},
											{"Binary JSON", "XML", "Protocol Buffer", "CSV", "2"},
											{"Availability, Compatibility and Security", "Availability, Reliability and Scalability", "Security, Performance Efficiency and Portability", "Performance Efficiency, Reliability and Functional Stability", "1"},
											{"Dividing parts of a data collection over multiple machines", "Keeping a backup of your data on an external hard drive", "Keeping the same dataset available on multiple machines", "Copying your files", "0"},
											{"Hash partitioning, because each hash uniquely identifies each record", "Key range partitioning, because each record is easily found by its key", "", "", "1"}, 
											{"Increase the performance by acquiring more potent hardware", "Increase the performance by acquiring more machines", "", "", "0"},
											{"An object, accessible by pointers stored in memory", "A sequence of bytes", "", "", "1"},
											{"Language specific, so that it matches the language used to build the web application", "JSON, because it\'s supported by most web browsers", "CSV, because there is little markup", "Apache thrift, because it\'s very compact", "1"},
											{"Replication", "Partitioning", "Operability", "Binary Encoding", "0"},
											{"Yes", "No", "", "", "0"},
											{"Self-driving vehicles", "Terrain scan", "Atmosphere research", "All above", "3"},
											{"200", "500", "1000", "600", "3"},
											{"Correct", "Incorrect", "", "", "0"},
											{"Data as a strategic asset.", "The value of data in use.", "Selling the data", "The expected future value of data.", "2"},
											{"True", "False", "", "", "1"}, 
											{"It helps company to use the resources more efficiently", "It helps to unlock the power of data", "It creates unique patterns and models for each department", "The volume of data is increasing fast.", "2"},
											{"True", "False", "", "", "1"},
											{"Data as a service", "Insight as a service", "Analytics-enabled platform as a service", "All above", "3"},
											{"True", "False", "", "", "0"},
											{"", "", "", "", ""}, 
											{"", "", "", "", ""},
											{"", "", "", "", ""},
											{"", "", "", "", ""},
											{"", "", "", "", ""},
											{"", "", "", "", ""}, 
											{"", "", "", "", ""},
											{"", "", "", "", ""},
											{"", "", "", "", ""},
											{"", "", "", "", ""} };