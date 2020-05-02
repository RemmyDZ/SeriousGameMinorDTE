#pragma once

//Screen resolution
const int DISPLAY_WIDTH = 1600;
const int DISPLAY_HEIGHT = 900;

//Game states
enum GAMESTATE { QUIZ_ONE, QUIZ_TWO, QUIZ_THREE, QUIZ_FOUR, QUIZ_FIVE, MAIN_MENU, QUIZ_MENU }; //Gameover maybe?
enum QUIZ_INDEX { QUIZ_INDEX_ONE = 0, QUIZ_INDEX_TWO = 10, QUIZ_INDEX_THREE = 20, QUIZ_INDEX_FOUR = 30, QUIZ_INDEX_FIVE = 40 };

int gameState = MAIN_MENU; //Start in main menu

//Coordinations and font sizes
const int BACKGROUND_X = 0;
const int BACKGROUND_Y = 0;

const int NEXT_QUESTION_BUTTON_X = 1354;
const int NEXT_QUESTION_BUTTON_Y = 480;
const int NEXT_QUESTION_FONT_SIZE = 30;

const int MENU_BOX_X = 5;
const int MENU_BOX_Y = 10;

const int QUESTIONBOX_X = 10;
const int QUESTIONBOX_Y = 5;

const int QUESTION_FONT_SIZE = 70;
const int QUESTION_NUMBER_FONT_SIZE = 30;

const int QUESTION_TEXT_X = 25;
const int QUESTION_TEXT_Y = 5;
const int QUESTION_TEXT_MAX_WIDTH = DISPLAY_WIDTH - 45;
const int QUESTION_NUMBER_TEXT_X = 45;
const int QUESTION_NUMBER_TEXT_Y = 468;

const int MENU_BUTTON_FONT_SIZE = 35;
const int MENU_BUTTON_START_Y = 60;

const int ANSWER_RESIZE_LENGTH = 150; //The size at which a question gets the smaller font
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

//Answer colors
enum COLORS { DEFAULT, GREEN, RED, HOVER }; //For Answer bitmaps

//Refresh rate
const int FPS = 60;

//Main loop condition
bool isGameFinished = false; //Main loop will break once this turns 'true'

//Go to next question condition
bool isAnswerGiven = false; //Only proceed to next question when true

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
		
																{"Which of the following parts is NOT present in a LiDAR camera?", 
																"What is the correct formula a LiDAR camera uses to measure distance?", 
																"\"When using a Class 1 laser, no safety precautions are needed\"", 
																"Does collecting LiDAR data comply with the GDPR?", 
																"Is the simulated data accurate enough to work with?", 
																"What is the maximum scanning range of the LiDAR used by NS?", 
																"If you want to see what personal data a company has stored about you, which GDPR law could you use?", 
																"At what speed does a LiDAR laser travel?", 
																"Is a laser with a wavelength of 1550nm considered 'eye-safe'?", 
																"Who wrote the Spoorwegwet (Railroad law)?" } };

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
											{"Laser(s)", "Scanners and Optics", "Antenna", "Photodetector", "2"}, 
											{"Distance = (Speed of Sound * Time of Flight) / 2", "Distance = (Speed of Light * Time of Flight) / 2", "Distance = (Speed of Sound * Time of Flight) * 2", "Distance = (Speed of Light * Time of Flight) * 2", "1"},
											{"True", "False", "", "", "1"},
											{"Yes", "No", "", "", "0"},
											{"Yes, simulations nowadays are very accurate", "Yes, every variable can be simulated", "No, but with different software it should be possible", "No, because some variables cannot be simulated", "3"},
											{"10m", "30m", "60m", "100m", "2"}, 
											{"The right to be informed", "The right to erasure", "The right to object", "The right of access", "3"},
											{"About 10.000 km/h", "About 50.000 km/h", "About 100.000 km/h", "About 300.000 km/h", "3"},
											{"Yes", "No", "", "", "0"},
											{"NS", "Dutch government", "European Union", "United Nations", "1"} };

std::string explainations[AMOUNT_OF_SUBJECTS][MAX_QUESTIONS] = { {"LiDAR data contains large amounts of numbers and therefore needs to be able to handle large amounts of data. Making it easier to produce new queries also makes this handling easier. However being widely used and easy to understand is not necessary, but could improve readability and the depth of the modelling tool.",
																"All of these modelling tools are possible candidates, because they can all handle large amounts of data.", 
																"Entity relationship modelling leads to databases that have an intricate and efficient pathing with a lot of foreign keys. This construction leads to a database (almost) no repeating values and therefore no redundancy.", 
																"Entity relationship modelling creates intricate joins and has a lot of foreign keys. These need to be incorporated during the production of new queries and makes this a lot harder.", 
																"A fact table is a table that connects the entire data warehouse with the other dimensions, so this is correct.", 
																"A snowflake schema is more expansive, because of hierarchies and not the other way around.", 
																"This is correct and makes the model made with this modelling method very easy to understand.", 
																"Fact-Oriented Modelling models and queries business domains in terms of underlying facts of interest, which makes them very easy to read. The other 2 modelling tools do not do this and rely on often not logical names.", 
																"Multidimensional Modelling has a short implementation compared to the other 2 modelling tools, because it only takes a couple of short steps.", 
																"The STAR schema is the best method for modelling LiDAR data, because it can handle large amounts of data and encompasses the easy production of new queries. While the Object Role schema is clearer, it is harder to implement as the STAR schema. The same can be said for the Snowflake schema."},

																{"Rain droplets may reflect the LiDAR waves and cause the reading to be a shorter distance than what you actually want to measure.", 
																"When a rolling shutter camera tries to capture an object that is moving at very high speeds, the object may turn out malformed in the end result.", 
																"NO EXPLAINATION HERE (FIX?)", 
																"Harsh sunlight may cause more reflection than normal on already reflective surfaces. Rain may cause distances to be measured incorrectly. Fog may impede the waves of the LiDAR camera.", 
																"The doppler effect does not affect measurements regarding stationary objects, but rather objects that are approaching or receding from the camera.", 
																"Noisy data is data that does not provide useful information to a research.", 
																"Removing noise with an algorithmic approach means to use algorithms to remove data points based on classifiers for what is and isn’t data noise. Removing data noise on a data level means to apply filters to a dataset to limit the insertion of data that does not fit the filter’s criteria.", 
																"Outliers may be considered data noise in a certain context, but they are actually two separate things. noise can be defined as mislabeled examples or errors in the values of attributes, whereas outliers are defined as abnormalities or anomalies.", 
																"INFFC is a noise removal method that is based on a fusion of multiple classifiers to detect noise. The use of multiple classifiers in an iterative way makes this a very accurate way of removing data noise, but also a very time consuming one.", 
																"While atmospheric noise can be a source of data noise in certain specific contexts it isn’t applicable to our context."},

																{"Batch processing presupposes a stored dataset and performs large queries on it.", 
																"Stream processing takes an incoming flow of data and performs operations on it.", 
																"Protocol buffer is a protocol for binary encoding, which greatly reduces the size of the data.", 
																"NO EXPLAINATION HERE (FIX?)", 
																"Partitioning data means you split up your data over different machines. This helps reduce the load for a frequently queried dataset.", 
																"A key range is easily queryable because there is a logical order to the keys.", 
																"NO EXPLAINATION HERE (FIX?)", 
																"Data is stored as a self contained sequence of bytes. Memory is only used when performing operations on the data.", 
																"JSON is the most widely used encoding format on the web.", 
																"Replication of data means keeping the same dataset available on multiple machines. When one machine goes down, the dataset will still be available on the other machine."}, 

																{"This is because raw LiDAR-data is only a distance calculation which can be really abstract", 
																"Those three subjects commonly utilize LiDAR.", 
																"This information is according to statista digital economy compass 2019", 
																"Companies can utilize data much better when they begin to think it as an asset", 
																"This is not a own category but it's part of the strategic asset of companies", 
																"When a company wants to utilize data better the first thing they need to do is build a data strategy and communicate it through whole company", 
																"The benefit of data strategy is that it consolidates the data handling, and produces an integrated process.", 
																"There are two paths internal and external path", 
																"This is correct according to MIT-Sloan article \"demystifying data monetization\"", 
																"This is due the fact that it's the most simplest out of the three and also has lowest revenue potential"},

																{"There are no LiDAR cameras with antennas on the market.", 
																"Speed of light is used because LiDAR uses a laser, which is a lightsource. It has to be divided by 2, because the laser goes towards the object and then back to the source.", 
																"A Class 1 laser is the safest class. However, it should not be placed on eye level of people, which is the only safety precaution needed.", 
																"It does fully comply. The GDPR only talks about personal data, and LiDAR data is not personal data.", 
																"Things like environmental variables (rain, snow, sunlight, etc) cannot be simulated. Also the Doppler effect cannot be simulated.", 
																"The maximum scanning range of the LiDAR (UTM-30LX-EW) is specified as 60 meters.", 
																"The right to be informed only tells you if a company has data stored about you. If you want to see the actual data, you need the right of access.", 
																"The laser moves as the speed of light, which is roughly 300.000 km/h.", 
																"Yes, 1550nm falls within the bandwidth of ‘eye-safe’ wavelengths.", 
																"The Dutch government created the Spoorwegwet on April 23th of 2003."} };