#pragma once

//Version
const std::string VERSION = "2.3";
const int VERSION_FONT_SIZE = 16;

//Screen resolution
const int DISPLAY_WIDTH = 1600;
const int DISPLAY_HEIGHT = 900;

const std::string DISPLAY_TITLE = "Serious game DTE minor Group 1";

//Game states
enum GAMESTATE { QUIZ_ONE, QUIZ_TWO, QUIZ_THREE, QUIZ_FOUR, QUIZ_FIVE, QUIZ_SIX, MAIN_MENU, QUIZ_MENU, END_SCREEN };
enum QUIZ_INDEX { QUIZ_INDEX_ONE = 0, QUIZ_INDEX_TWO = 10, QUIZ_INDEX_THREE = 20, QUIZ_INDEX_FOUR = 30, QUIZ_INDEX_FIVE = 40, QUIZ_INDEX_SIX = 50 };

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

const int QUESTION_FONT_SIZE = 70; //Default font size
const int QUESTION_FONT_SIZE_LONG = 55; //Font size for long questions/explainations
const int QUESTION_FONT_SIZE_EXTRA_LONG = 50;
const int QUESTION_NUMBER_FONT_SIZE = 30;

const int QUESTION_LONG_FONT_TRESHOLD = 200; //Maximum length of a question to use the default font, everything above will use smaller font size
const int QUESTION_EXTRA_LONG_TRESHOLD = 250; //For even longer answers/explainations

const int QUESTION_TEXT_X = 25;
const int QUESTION_TEXT_Y = 5;
const int QUESTION_TEXT_MAX_WIDTH = DISPLAY_WIDTH - 45;
const int QUESTION_NUMBER_TEXT_X = 45;
const int QUESTION_NUMBER_TEXT_Y = 468;

const int MENU_BUTTON_FONT_SIZE = 35;
const int MENU_BUTTON_AUTHOR_FONT_SIZE = 20;
const int MENU_BUTTON_START_Y = 60;

const int ANSWER_RESIZE_LENGTH = 150; //The size at which a question gets the smaller font
const int ANSWER_FONT_SIZE = 30; 
const int ANSWER_LONG_FONT_SIZE = 25; //For long answers so it doesn't go out of boundaries

const int SCORE_FONT_SIZE = 60;

const int SOURCE_FONT_SIZE = 40;

const int SOURCE_BUTTON_X = 1060;
const int SOURCE_BUTTON_Y = 480;
const int SOURCE_BUTTON_FONT_SIZE = 30;

const int SOURCE_BOX_X = DISPLAY_WIDTH / 2;
const int SOURCE_BOX_Y = (DISPLAY_HEIGHT / 2) - 100;

const int SOUND_BUTTON_X = 35;
const int SOUND_BUTTON_Y = 780;

const int CLOSE_SOURCE_BUTTON_X = 1150;
const int CLOSE_SOURCE_BUTTON_Y = 180;

const int MAIN_MENU_BUTTON_X_QUIZ_MENU = DISPLAY_WIDTH - 250;
const int MAIN_MENU_BUTTON_Y_QUIZ_MENU = DISPLAY_HEIGHT - 70;
const int MAIN_MENU_BUTTON_X = 294;
const int MAIN_MENU_BUTTON_Y = 480;
const int MAIN_MENU_BUTTON_FONT_SIZE = 30;

//Amount of audio samples
const int AMOUNT_OF_SAMPLES = 20; //1 for background music, 1 for clicking sound and 18 for buffers (so that multiple clicking sounds can be played at once)

//Maximum amount of possible answers per question
const int MAX_ANSWERS = 4;

//Maximum amount of questions per quiz
const int MAX_QUESTIONS = 10;

//Amount of quiz subjects (1 for every individual research)
const int AMOUNT_OF_SUBJECTS = 6; //Main quiz about data quality and 5 for each individual research

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

//Vector for random questions (to check which ones have been given yet)
std::vector<int> randomQuestions;

//Score
int playerScore = 0;

//Draw condition
bool redraw = true; //Always start with 'true', otherwise nothing will be drawn in the first frame

//Windowed/fullscreen switch
bool fullScreen = false; //Game starts in windowed mode, which can be toggled to fullscreen

//Questions (CHANGE TO VECTORS)
int currentQuestion = 0; //Starts at 0 because it acts as an index to the questions array below (except when questions are randomized)
int currentRandomQuestion = 0; //Placeholder for real question number, currentQuestion is just linear when questions are randomized


//Order: Main Quiz - Danny - Hicham - Ivo - Valtteri - Remco
std::string questions[AMOUNT_OF_SUBJECTS][MAX_QUESTIONS] = { {"Why are outlying data points not considered data noise?",
																"What does the term \'data quality\' entail?",
																"Why should companies care about the quality of their data?",
																"Does quality data mean more business potential?",
																"Which data quality analysis technique is best suited for checking data value uniqueness?",
																"What is the biggest issue with reverification events?",
																"Which of the following is not an example of a data quality best practice?",
																"Which of the following is a data quality dimension?",
																"What should be done with missing values in data entries?",
																"How can we improve the accuracy when measuring points with a LiDAR camera?" },
																				
																{"What characteristics does a modelling tool need for modelling LiDAR data?", 
																"What are possible candidates for modelling LiDAR data?", 
																"Entity Relationship Modelling produces databases with as less redundancy (double values) as possible.", 
																"Entity Relationship Modelling has a structure that makes producing new queries very simple.", 
																"With Multidimensional Modelling every model is composed of 1 table with a multipart key, which is called a fact table.", 
																"The difference between a STAR schema and a Snowflake schema is that a STAR schema contains more hierarchies, which make the schema more expansive.", 
																"Using Document Oriented Modelling to make a NoSQL database can result in a database that can flexibly handle and process new and existing data.", 
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
																"How much is expected data creation in 2030 (in zettabytes, approx)?", 
																"Companies should think of data as an asset.", 
																"According to MIT-Sloan research \"what\'s your data worth\" data can be divided into three different categories, which category doesn\'t belong here? (1)?", 
																"The data strategy is not important when a company wants to utilize data better.", 
																"What benefits the data strategy provides? (choose the INCORRECT option) ", 
																"There are usually three different paths to data monetizations.", 
																"Externally there are 3 different paths of data monetization. Choose the correct paths.", 
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
//Order: Main Quiz - Danny - Hicham - Ivo - Valtteri - Remco
std::string answers[MAX_QUESTIONS * AMOUNT_OF_SUBJECTS][MAX_ANSWERS + 1] = { {"Outliers are still valuable data points, whereas noise are points that don\'t add (or even detract) valuable/useful information", "Outliers and data noise are the same", "Outliers do not add valuable information, whereas data noise still does add viable information", "", "0"}, //Maximum of 4 answers for a single question + 1 string to determine the correct answer (which will be converted to an int)
											{"The resolution of the data", "The amount of data", "The inherent quality of the data as characterized by its accuracy, precision, bias, level of error, etc.", "It doesn\'t mean anything, it\'s just a buzzword", "2"},
											{"They will make more money with better data", "Quality data means better business decisions", " Data quality doesn\'t really matter", "More data equals better data", "1"},
											{"Yes", "No", "", "", "1"},
											{"Value correlation analysis", "Structural analysis", "Value inspection", "Aggregation correlation analysis", "1"},
											{"It is extremely time consuming", "It is a virtually impossible venture", "The GDPR forbids it", "", "0"},
											{"Ensure top-level management involvement", " Operate a data issue log", "Create transparency by making the data public", "", "2"},
											{"Completeness", "Consistency", "Integrity", "All of the above", "3"},
											{"It should be left as it is", "Missing values need to be filled in by extrapolating", "Only use database entries, which have all necessary variables for doing a certain analysis", "Remove all entries, which are not complete in every data entry", "2"},
											{"Get equipment with more sensitive sensors", "Improve the settings of your LiDAR camera", "Remove outside influences", "All of the above", "3"},
											{"Able to handle large amounts of data and easy to produce new queries", "Widely used and easy to understand", "", "", "0"}, 
											{"Entity Relationship Modelling", "Multidimensional Modelling", "Fact-Oriented Modelling", "All of the above", "3"},
											{"Correct", "Incorrect", "", "", "0"}, 
											{"Correct", "Incorrect", "", "", "1"}, 
											{"Correct", "Incorrect", "", "", "0"},
											{"Correct", "Incorrect", "", "", "1"},
											{"Correct", "Incorrect", "", "", "0"},
											{"Entity Relationship Modelling", "Multidimensional Modelling", "Fact-Oriented Modelling", "All of the above", "2"},
											{"Entity Relationship Modelling", "Multidimensional Modelling", "Fact-Oriented Modelling", "All of the above", "1"},
											{"Entity Relationship Diagram", "STAR schema (Multidimensional Modelling)", "Snowflake schema (Multidimensional Modelling)", "Object Role schema", "2"},
											{"The recorded distance may be larger than the actual distance", "The data becomes corrupted", "The rain may break the camera", "The recorded distance may be shorter than the actual distance", "3"}, 
											{"Wrong colours", "Malformed objects", "Blurriness", "Corrupted image files", "1"},
											{"The Doppler effect is the change in frequency of a wave in relation to an observer who is moving relative to the wave source", "The Doppler effect is the change in wavelength of a wave in relation to an observer who is moving relative to the wave source", "The doppler effect is a malformation of fast moving objects caused by the mechanics of a rolling shutter camera", "The doppler effect doesn\'t exist", "0"},
											{"Harsh sunlight", "Rain", "Fog", "All of the above", "3"},
											{"True", "False", "", "", "1"},
											{"True", "False", "", "", "1"}, 
											{"Algorithmic and Data based", "Algorithmic and physical removal", "Only algorithmic", "Only data based", "0"},
											{"Yes", "No", "", "", "1"},
											{"Iterative Noise Filter based on the Fusion of Classifiers", "International Noise Filter based on the Fusion of Classifications", "I don\'t know", "Internal Nighttime Final Finger Classroom", "0"},
											{"The rolling shutter effect", "The doppler effect", "The weather", "Atmospheric noise", "3"},
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
											{"Data as a strategic asset", "The value of data in use", "Selling the data", "The expected future value of data", "2"},
											{"True", "False", "", "", "1"}, 
											{"It helps company to use the resources more efficiently", "It helps to unlock the power of data", "It creates unique patterns and models for each department", "The volume of data is increasing fast", "2"},
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

//Order: Main Quiz - Danny - Hicham - Ivo - Valtteri - Remco
std::string explainations[AMOUNT_OF_SUBJECTS][MAX_QUESTIONS] = { {"Outliers may be considered data noise in a certain context, but they are actually two separate things. Noise can be defined as mislabeled examples or errors in the values of attributes, whereas outliers are defined as abnormalities or anomalies.",
																"The inherent quality of the data as characterized by its accuracy, precision, bias, level of error, etc.",
																"Companies who focus on the quality of data are more likely to make better decisions.",
																"Better data quality doesn\'t automatically mean better business decisions.",
																"Structural analysis checks a collection of values for certain constraints like uniqueness.",
																"No explaination needed.",
																"Making company data public is rarely a good idea for obvious reasons. Top-level management involvement ensures more quality control, as well as operating an issue log.",
																"Completeness, consistency and integrity are three of the many data quality dimensions. Other examples include validity, accessibility and accuracy.",
																"Just making analyses by doing nothing and extrapolating values will lead to completely wrong analyses. Also not all entries need to be removed, since they could be right with another analysis and removing them would impact these analyses.",
																"All of the above questions will improve the accuracy of all measured points when making a LiDAR recording. Better sensors will lead to more accurate readings and the wrong settings and outside influences like the weather will lead to worse readings."},

																{"LiDAR data contains large amounts of numbers and therefore needs to be able to handle large amounts of data. Making it easier to produce new queries also makes this handling easier. However being widely used and easy to understand is not necessary, but could improve readability and the depth of the modelling tool.",
																"All of these modelling tools are possible candidates, because they can all handle large amounts of data.", 
																"Entity relationship modelling leads to databases that have an intricate and efficient pathing with a lot of foreign keys. This construction leads to a database (almost) no repeating values and therefore no redundancy.", 
																"Entity relationship modelling creates intricate joins and has a lot of foreign keys. These need to be incorporated during the production of new queries and makes this a lot harder.", 
																"A fact table is a table that connects the entire data warehouse with the other dimensions, so this is correct.", 
																"A snowflake schema is more expansive, because of hierarchies and not the other way around.", 
																"In a NoSQL database attributes and documents can be omitted and added flexibly and can be used as desired. However this flexibility can also make it hard to save and use the data correctly. For instance when some attributes exist in a certain record, but not in the other record. When data from these attributes is then used, it can result in many missing values and also wrong analyses from this data.", 
																"Fact-Oriented Modelling models and queries business domains in terms of underlying facts of interest, which makes them very easy to read. The other 2 modelling tools do not do this and rely on often not logical names.", 
																"Multidimensional Modelling has a short implementation compared to the other 2 modelling tools, because it only takes a couple of short steps.", 
																"The Snowflake schema is the best method for modelling LiDAR data, because it can handle large amounts of data and encompasses the easy production of new queries. While the Object Role schema is clearer, it is harder to implement as the STAR schema. Even though the Snowflake schema is more complex, this complexity is needed. This is because LiDAR data is so large and complex that it cannot be easily saved in a STAR schema."},

																{"Rain droplets may reflect the LiDAR waves and cause the reading to be a shorter distance than what you actually want to measure.", 
																"When a rolling shutter camera tries to capture an object that is moving at very high speeds, the object may turn out malformed in the end result.", 
																"No explaination needed.", 
																"Harsh sunlight may cause more reflection than normal on already reflective surfaces. Rain may cause distances to be measured incorrectly. Fog may impede the waves of the LiDAR camera.", 
																"The doppler effect does not affect measurements regarding stationary objects, but rather objects that are approaching or receding from the camera.", 
																"Noisy data is data that does not provide useful information to a research.", 
																"Removing noise with an algorithmic approach means to use algorithms to remove data points based on classifiers for what is and isn\'t data noise. Removing data noise on a data level means to apply filters to a dataset to limit the insertion of data that does not fit the filter\'s criteria.", 
																"Outliers may be considered data noise in a certain context, but they are actually two separate things. noise can be defined as mislabeled examples or errors in the values of attributes, whereas outliers are defined as abnormalities or anomalies.", 
																"INFFC is a noise removal method that is based on a fusion of multiple classifiers to detect noise. The use of multiple classifiers in an iterative way makes this a very accurate way of removing data noise, but also a very time consuming one.", 
																"While atmospheric noise can be a source of data noise in certain specific contexts it isn\'t applicable to our context."},

																{"Batch processing presupposes a stored dataset and performs large queries on it.", 
																"Stream processing takes an incoming flow of data and performs operations on it.", 
																"Protocol buffer is a protocol for binary encoding, which greatly reduces the size of the data.", 
																"A data intensive application needs to be available, reliable and scalable.", 
																"Partitioning data means you split up your data over different machines. This helps reduce the load for a frequently queried dataset.", 
																"A key range is easily queryable because there is a logical order to the keys.", 
																"Scaling vertically means acquiring more potent hardware, scaling horizontally acquiring more hardware machines, albeit with lesser specifications.", 
																"Data is stored as a self contained sequence of bytes. Memory is only used when performing operations on the data.", 
																"JSON is the most widely used encoding format on the web.", 
																"Replication of data means keeping the same dataset available on multiple machines. When one machine goes down, the dataset will still be available on the other machine."}, 

																{"This is because raw LiDAR-data is only a distance calculation which can be really abstract.", 
																"Those three subjects commonly utilize LiDAR.", 
																"This information is according to Statista\'s Digital Economy Compass 2019.", 
																"Companies can utilize data much better when they begin to think it as an asset.", 
																"This is not a own category but it's part of the strategic asset of companies.", 
																"When a company wants to utilize data better the first thing they need to do is build a data strategy and communicate it through the whole company.", 
																"The benefit of data strategy is that it consolidates the data handling, and produces an integrated process.", 
																"There are two paths internal and external path.", 
																"This is correct according to MIT-Sloan article \"demystifying data monetization\".", 
																"This is due the fact that it's the most simplest out of the three and also has lowest revenue potential."},

																{"There are no LiDAR cameras with antennas on the market.", 
																"Speed of light is used because LiDAR uses a laser, which is a lightsource. It has to be divided by 2, because the laser goes towards the object and then back to the source.", 
																"A Class 1 laser is the safest class. However, it should not be placed on eye level of people, which is the only safety precaution needed.", 
																"It does fully comply. The GDPR only talks about personal data, and LiDAR data is not personal data.", 
																"Things like environmental variables (rain, snow, sunlight, etc) cannot be simulated. Also the Doppler effect cannot be simulated.", 
																"The maximum scanning range of the LiDAR (UTM-30LX-EW) is specified as 60 meters.", 
																"The right to be informed only tells you if a company has data stored about you. If you want to see the actual data, you need the right of access.", 
																"The laser moves as the speed of light, which is roughly 300.000 km/h.", 
																"Yes, 1550nm falls within the bandwidth of \'eye-safe\' wavelengths.", 
																"The Dutch government created the Spoorwegwet on April 23th of 2003."} };

//Order: Main Quiz - Danny - Hicham - Ivo - Valtteri - Remco
std::string sources[MAX_QUESTIONS * AMOUNT_OF_SUBJECTS][2] = { {"Rouse", "https://searchbusinessanalytics.techtarget.com/definition/noisy-data"},
																{"Redman", "https://books.google.nl/books/about/Data_Driven.html?id=Q5CJJ2wVkYAC&redir_esc=y"},
																{"Spijker", "https://books.google.nl/books?id=zY3XBgAAQBAJ&hl=nl"},
																{"Spijker", "https://books.google.nl/books?id=zY3XBgAAQBAJ&hl=nl"},
																{"Olson", "https://books.google.nl/books?id=x8ahL57VOtcC&printsec=frontcover&redir_esc=y#v=onepage&q&f=false"},
																{"Olson", "https://books.google.nl/books?id=x8ahL57VOtcC&printsec=frontcover&redir_esc=y#v=onepage&q&f=false"},
																{"Profisee", "https://profisee.com/data-quality-what-why-how-who/"},
																{"Knight", "https://www.dataversity.net/what-is-data-quality/"},
																{"Fan & Geerts", "https://www.morganclaypool.com/doi/abs/10.2200/S00439ED1V01Y201207DTM030"},
																{"Csanyi & Toth", "https://www.ingentaconnect.com/content/asprs/pers/2007/00000073/00000004/art00004"},
																{"Dubayah, R.O. & Drake, J.B.", "https://academic.oup.com/jof/article/98/6/44/4614333"},
																{"Li, Q. & Chen, Y.L.", "https://link.springer.com/chapter/10.1007/978-3-540-89556-5_6"},
																{"Li, Q. & Chen, Y.L.", "https://link.springer.com/chapter/10.1007/978-3-540-89556-5_6"},
																{"Li, Q. & Chen, Y.L.", "https://link.springer.com/chapter/10.1007/978-3-540-89556-5_6"},
																{"Corr, L. & Stagnitto, J.", "https://books.google.nl/books?hl=en&lr=&id=TRWFmnv8jP0C&oi=fnd&pg=PR23&dq=Corr,+L.,+%26+Stagnitto,+J.+(2011).+Agile+data+warehouse+design:+Collaborative+dimensional+modeling,+from+whiteboard+to+star+schema.+DecisionOne+Consulting.+&ots=SNJv5oP87z&sig=kACjJpl2sfVFemxP_kvlPbX89ts#v=onepage&q=Corr%2C%20L.%2C%20%26%20Stagnitto%2C%20J.%20(2011).%20Agile%20data%20warehouse%20design%3A%20Collaborative%20dimensional%20modeling%2C%20from%20whiteboard%20to%20star%20schema.%20DecisionOne%20Consulting.&f=false"},
																{"Garani, G. & Helmer, S.", "https://www.igi-global.com/article/content/74754"},
																{"Boehm, J. & Liu, K.", "https://discovery.ucl.ac.uk/id/eprint/1471583/"},
																{"Li, Q. & Chen, Y.L.", "https://link.springer.com/chapter/10.1007/978-3-540-89556-5_6"},
																{"Li, Q. & Chen, Y.L.", "https://link.springer.com/chapter/10.1007/978-3-540-89556-5_6"},
																{"Li, Q. & Chen, Y.L.", "https://link.springer.com/chapter/10.1007/978-3-540-89556-5_6"},
																{"Goodin, Carruth, Doude, & Hudson", "https://www.mdpi.com/2079-9292/8/1/89/htm"},
																{"Hokuyo automatic co.", "https://acroname.com/sites/default/files/assets/utm-30lx-ew_spec_en.pdf"},
																{"Jia & Wang", "https://www.elsevier.com/books/transportation-cyber-physical-systems/deka/978-0-12-814295-0"},
																{"Hokuyo automatic co.", "https://www.mdpi.com/2079-9292/8/1/89/htm"},
																{"Goodin, Carruth, Doude, & Hudson", "https://www.mdpi.com/2079-9292/8/1/89/htm"},
																{"Rouse", "https://searchbusinessanalytics.techtarget.com/definition/noisy-data"}, 
																{"Saez & Galar & Luengo & Herrera", "https://sci2s.ugr.es/INFFC"},
																{"Rouse", "https://searchbusinessanalytics.techtarget.com/definition/noisy-data"}, 
																{"Saez & Galar & Luengo & Herrera", "https://sci2s.ugr.es/INFFC"},
																{"Hokuyo automatic co.", "https://acroname.com/sites/default/files/assets/utm-30lx-ew_spec_en.pdf"},
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"}, 
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"},
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"}, 
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"},
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"}, 
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"},
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"},
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"},
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"},
																{"Kleppmann, M.", "https://books.google.nl/books?id=p1heDgAAQBAJ&lpg=PP1&dq=Kleppmann%2C%20M.%20(2017).%20Designing%20Data-Intensive%20Applications%3A%20The%20Big%20Ideas%20Behind%20Reliable%2C%20Scalable%2C%20and%20Maintainable%20Systems.%20%E2%80%9CO%E2%80%99Reilly%20Media%2C%20Inc.%2C%20p.%20151&pg=PT2#v=onepage&q&f=false"},
																{"Thompson, J.", "https://levelfivesupplies.com/100-real-world-applications-of-lidar-technology/"},
																{"Thompson, J.", "https://levelfivesupplies.com/100-real-world-applications-of-lidar-technology/"},
																{"Armstrong, M.", "https://www.statista.com/chart/17727/global-data-creation-forecasts/"},
																{"Neely, A.", "https://opendatascience.com/data-valuation-what-is-your-data-worth-and-how-do-you-value-it/"},
																{"Short, J. E., & Todd, S.", "https://sloanreview.mit.edu/article/whats-your-data-worth/"},
																{"LOTAME", "https://www.lotame.com/how-to-build-a-data-strategy/"},
																{"LOTAME", "https://www.lotame.com/how-to-build-a-data-strategy/"},
																{"Gandhi, Thota, Kuchembuck & Swartz", "https://sloanreview.mit.edu/article/demystifying-data-monetization"},
																{"Gandhi, Thota, Kuchembuck & Swartz", "https://sloanreview.mit.edu/article/demystifying-data-monetization"},
																{"Gandhi, Thota, Kuchembuck & Swartz", "https://sloanreview.mit.edu/article/demystifying-data-monetization"},
																{"LiDAR UK", "http://www.lidar-uk.com/how-lidar-works/"},
																{"LiDAR UK", "http://www.lidar-uk.com/how-lidar-works/"},
																{"ARBOpodium", "https://www.arbopodium.nl/arbo-index/arbo-in-de-praktijk/lasers/"},
																{"Wolford, B.", "https://gdpr.eu/what-is-gdpr/"},
																{"Daniela Iordan, G.P.", "https://www.researchgate.net/publication/313509734_THE_ACCURACY_OF_LiDAR_MEASUREMENTS_FOR_THE_DIFFERENT_LAND_COVER_CATEGORIES"},
																{"Hokuyo USA", "https://acroname.com/sites/default/files/assets/utm-30lx-ew_spec_en.pdf"},
																{"Intersoft Consulting", "https://gdpr-info.eu/issues/right-of-access/"},
																{"LiDAR UK", "http://www.lidar-uk.com/how-lidar-works/"},
																{"LiDAR UK", "http://www.lidar-uk.com/how-lidar-works/"},
																{"Dutch government", "https://wetten.overheid.nl/BWBR0015007/2019-06-16"} };