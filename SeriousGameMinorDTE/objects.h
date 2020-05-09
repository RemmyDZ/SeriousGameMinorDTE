#pragma once

//Question object
struct Question {
	int x, y;
	int textX, textY; //TextX won't be needed as the text is being drawn in the center, so 'x' can be used for that
	int textMaxWidth;
	int nrTextX, nrTextY; //Coordinations for the question number
	int fontSize;
	int nrFontSize; //Font size for the question number
	std::string question;
	ALLEGRO_COLOR fontColor;
	ALLEGRO_BITMAP* bitmap = NULL;
	ALLEGRO_BITMAP* bitmapCounter = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_FONT* nrFont = NULL; //Font for the question number

	Question(std::string question) //Constructor
	{
		this->question = question;
		x = QUESTIONBOX_X;
		y = QUESTIONBOX_Y;
		textX = QUESTION_TEXT_X;
		textY = QUESTION_TEXT_Y;
		textMaxWidth = QUESTION_TEXT_MAX_WIDTH;
		nrTextX = QUESTION_NUMBER_TEXT_X;
		nrTextY = QUESTION_NUMBER_TEXT_Y;
		fontColor = al_map_rgb(0, 0, 0);
		fontSize = QUESTION_FONT_SIZE;
		nrFontSize = QUESTION_NUMBER_FONT_SIZE;
		bitmap = al_load_bitmap("Resources/Textures/Question_box.bmp");
		bitmapCounter = al_load_bitmap("Resources/Textures/Question_counter.bmp");
		//al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 220));
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", fontSize, NULL);
		nrFont = al_load_font("Resources/Fonts/GILLUBCD.ttf", nrFontSize, NULL); //CHANGE FONT, THIS ONE IS NOT SUITABLE FOR NUMBERS
	}

	void setQuestion(int quizNumber, int questionNumber)
	{
		fontColor = al_map_rgb(0, 0, 0);
		this->question = questions[quizNumber][questionNumber];
	}

	void setExplaination(int quizNumber, int questionNumber)
	{
		fontColor = al_map_rgb(0, 255, 0);
		this->question = explainations[quizNumber][questionNumber];
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
		al_draw_bitmap(bitmapCounter, x, 456, NULL);
		//al_draw_text(font, al_map_rgb(0, 0, 0), textX, textY, NULL, question.c_str());
		al_draw_multiline_text(font, fontColor, textX, textY, textMaxWidth, 0, NULL, question.c_str());
		al_draw_textf(nrFont, al_map_rgb(0, 0, 0), nrTextX, nrTextY, NULL, "Question: %i/%zu", currentQuestion+1, std::size(questions[0])); //Plus 1, because currentQuestion is an index number, and we want to display a correct number
		//FIX TOTAL QUESTIONS NOT SHOWING
	}

	void clear() //Garbage control
	{
		al_destroy_bitmap(bitmap);
		al_destroy_font(font);
		al_destroy_font(nrFont);
	}
};

struct Answer {
	int x, y;
	int offsetX, offsetY; //Make the 0,0 point in the middle of the texture instead of the top left
	int textOffset;
	int answersAmount; //The amount of answers to the current question
	std::string answer;
	bool isAnswer; //True if it's the correct answer, false if not
	bool isVisible;
	int positionH, positionV;
	ALLEGRO_BITMAP* bitmap = NULL;
	ALLEGRO_BITMAP* bitmapNormal = NULL;
	ALLEGRO_BITMAP* bitmapGreen = NULL; //For correct answers
	ALLEGRO_BITMAP* bitmapRed = NULL; //For wrong answers
	ALLEGRO_BITMAP* bitmapHover = NULL; //For mouse hovering
	ALLEGRO_FONT* fontSmall = NULL;
	ALLEGRO_FONT* fontLarge = NULL;
	ALLEGRO_FONT* font = NULL;
	//Question &question;

	Answer(int positionV, int positionH, Question question) //Constructor
	{ //FIX 'Answer::y is unitialized' WARNING
		textOffset = ANSWER_FONT_SIZE * 2;
		answersAmount = std::size(questions[currentQuestion]);
		//this->positionV = positionV;
		this->positionH = positionH;
		this->positionV = positionV;
		isAnswer = false;
		isVisible = false; 
		bitmapNormal = al_load_bitmap("Resources/Textures/Answer.bmp");
		bitmapGreen = al_load_bitmap("Resources/Textures/Answer_right.bmp");
		bitmapRed = al_load_bitmap("Resources/Textures/Answer_wrong.bmp");
		bitmapHover = al_load_bitmap("Resources/Textures/Answer_hover.bmp");
		if (positionV == LEFT)
		{
			x = DISPLAY_WIDTH / 4;
		//	bitmapNormal = al_load_bitmap("Resources/Textures/Answer1.bmp"); //Load Answer1 bitmap for answers on the left
		//	bitmapGreen = al_load_bitmap("Resources/Textures/Answer1_right.bmp");
		//	bitmapRed = al_load_bitmap("Resources/Textures/Answer1_wrong.bmp");
		}
		else if (positionV == RIGHT)
		{
			x = (DISPLAY_WIDTH / 4) * 3;
		//	bitmapNormal = al_load_bitmap("Resources/Textures/Answer2.bmp"); //Load Answer2 bitmap for answers on the right
		//	bitmapGreen = al_load_bitmap("Resources/Textures/Answer2_right.bmp");
		//	bitmapRed = al_load_bitmap("Resources/Textures/Answer2_wrong.bmp");
		}
		bitmap = bitmapNormal; //Start with the normal bitmap
		//al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 220));
		offsetX = al_get_bitmap_width(bitmap) / 2;
		offsetY = al_get_bitmap_height(bitmap) / 2;
		if (positionH == TOP) 
			y = (((DISPLAY_HEIGHT - al_get_bitmap_height(question.bitmap)) / 5) * 2) + al_get_bitmap_height(question.bitmap);
		else if (positionH == BOTTOM)
			y = (((DISPLAY_HEIGHT - al_get_bitmap_height(question.bitmap)) / 4) * 3) + al_get_bitmap_height(question.bitmap);
		fontLarge = al_load_font("Resources/Fonts/GILLUBCD.ttf", ANSWER_FONT_SIZE, NULL);
		fontSmall = al_load_font("Resources/Fonts/GILLUBCD.ttf", ANSWER_LONG_FONT_SIZE, NULL);
		font = fontLarge;
	}

	bool onHover() //Same code as "onClick()", but better to have both for code readability
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		if (state.x > (x - offsetX) && state.x < (x + offsetX)
			&& state.y >(y - offsetY) && state.y < (y + offsetY)
			&& isVisible) //If this is true, the mouse cursor is within the bitmap. Also, the answer has to be visible
		{
			return true;
			//al_show_native_message_box(NULL, "False!", "False!", "False!", NULL, NULL);
		}
		return false;
	}

	bool onClick()
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		if (state.x > (x - offsetX) && state.x < (x + offsetX)
			&& state.y >(y - offsetY) && state.y < (y + offsetY)
			&& isVisible) //If this is true, the mouse cursor is within the bitmap. Also, the answer has to be visible
		{
			return true;
			//al_show_native_message_box(NULL, "False!", "False!", "False!", NULL, NULL);
		}
		return false;
	}

	void setAnswer(int questionNumber, int answerIndex) //Set the answers corresponding to the current question
	{
		answer = answers[questionNumber][answerIndex];
		setVisibility(true);
	}

	void setCorrectAnswer(bool correct)
	{
		isAnswer = correct;
	}

	void setVisibility(bool visible)
	{
		isVisible = visible;
	}

	void setFont(bool large)
	{
		if (large)
			font = fontLarge;
		else
			font = fontSmall;
	}

	void setBitmap(int bitmap) //0 = default, 1 = green, 2 = red, 3 = hover
	{
		switch (bitmap)
		{
		case 0:
			this->bitmap = bitmapNormal;
			break;
		case 1:
			this->bitmap = bitmapGreen;
			break;
		case 2:
			this->bitmap = bitmapRed;
			break;
		case 3:
			this->bitmap = bitmapHover;
			break;
		default:
			break;
		}
	}

	void draw()
	{
		if (isVisible) //Only draw bitmap when visible
		{
			al_draw_bitmap(bitmap, x - offsetX, y - offsetY, NULL);
			//al_draw_text(font, al_map_rgb(0, 0, 0), x, y - textOffset, ALLEGRO_ALIGN_CENTER, answer.c_str());
			al_draw_multiline_text(font, al_map_rgb(0, 0, 0), x, y-textOffset, al_get_bitmap_width(bitmap) - 50, 0, ALLEGRO_ALIGN_CENTER, answer.c_str());
			//al_draw_textf(NULL, al_map_rgb(0, 0, 0), 10, 10, NULL, "y: %i", y);
		}
	}

	void clear() //Garbage control
	{
		//al_destroy_bitmap(bitmap);
		al_destroy_bitmap(bitmapNormal);
		al_destroy_bitmap(bitmapGreen);
		al_destroy_bitmap(bitmapRed);
		al_destroy_font(fontSmall);
		al_destroy_font(fontLarge);
	}
};

struct MenuBox {
	int x, y;
	std::string text;
	ALLEGRO_BITMAP* bitmap;

	MenuBox(std::string text)
	{
		x = MENU_BOX_X;
		y = MENU_BOX_Y;
		this->text = text;
		bitmap = al_load_bitmap("Resources/Textures/menu_box.bmp");
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
	}

	void clear()
	{
		al_destroy_bitmap(bitmap);
	}
};

struct MenuButton {
	int x, y;
	std::string text;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapHover;
	ALLEGRO_FONT* font;

	MenuButton(int index, std::string text, MenuBox menuBox) //Index acts as a multiplier for the y position
	{
		this->text = text;
		bitmapNormal = al_load_bitmap("Resources/Textures/menu_option.bmp");
		bitmapHover = al_load_bitmap("Resources/Textures/menu_option_hover.bmp");
		bitmap = bitmapNormal; //Start with the default bitmap
		x = (al_get_bitmap_width(menuBox.bitmap) - al_get_bitmap_width(bitmap)) / 2;
		y = (al_get_bitmap_height(bitmap) * index) + MENU_BUTTON_START_Y;
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", MENU_BUTTON_FONT_SIZE, NULL);
	}

	bool onHover() //Same code as "onClick()", but better for readability
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		int width, height;
		width = al_get_bitmap_width(bitmap);
		height = al_get_bitmap_height(bitmap);
		if (state.x > x&& state.x < (x + width)
			&& state.y > y&& state.y < (y + height))//If this is true, the mouse cursor is within the bitmap. 
		{
			return true;
		}
		return false;
	}

	bool onClick() //Returns true if clicked
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		int width, height;
		width = al_get_bitmap_width(bitmap);
		height = al_get_bitmap_height(bitmap);
		if (state.x > x && state.x < (x + width)
			&& state.y > y && state.y < (y + height))//If this is true, the mouse cursor is within the bitmap. 
		{
			return true;
		}
		return false;
	}

	void setBitmap(int bitmap) //0 = default, 1 = hover
	{
		switch (bitmap)
		{
		case 0:
			this->bitmap = bitmapNormal;
			break;
		case 1:
			this->bitmap = bitmapHover;
			break;
		default:
			break;
		}
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
		al_draw_text(font, al_map_rgb(0, 0, 0), x + 20, y + 20, NULL, text.c_str());
	}

	void clear() //Garbage control
	{
		al_destroy_bitmap(bitmap);
	}
};

struct Background {
	int x, y;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapEnd;
	ALLEGRO_FONT* font; //For showing score on endscreen

	Background(int x, int y) //Constructor
	{
		this->x = x;
		this->y = y;
		bitmapNormal = al_load_bitmap("Resources/Textures/Background_quiz.bmp");
		bitmapEnd = al_load_bitmap("Resources/Textures/Score_screen.bmp");
		bitmap = bitmapNormal; //Start with normal background
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", SCORE_FONT_SIZE, NULL);
		//al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 255));
	}

	void setBitmap(int bitmap) //0 = default, 1 = end screen
	{
		switch (bitmap)
		{
		case 0:
			this->bitmap = bitmapNormal;
			break;
		case 1:
			this->bitmap = bitmapEnd;
			break;
		default:
			break;
		}
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
		if (gameState == END_SCREEN)
			al_draw_textf(font, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2, (DISPLAY_HEIGHT / 2) - 40, ALLEGRO_ALIGN_CENTER, "Score: %i", playerScore);
	}

	void clear() //Garbage control
	{
		al_destroy_bitmap(bitmap);
	}
};

struct NextQuestionButton {
	int x, y;
	int fontSize;
	int textX;
	int textY;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapHover;
	ALLEGRO_FONT* font = NULL;

	NextQuestionButton()
	{
		x = NEXT_QUESTION_BUTTON_X;
		y = NEXT_QUESTION_BUTTON_Y;
		textX = NEXT_QUESTION_BUTTON_X + 10;
		textY = NEXT_QUESTION_BUTTON_Y + 10;
		bitmapNormal = al_load_bitmap("Resources/Textures/Next_question.bmp");
		bitmapHover = al_load_bitmap("Resources/Textures/Next_question_hover.bmp");
		bitmap = bitmapNormal; //Start with the default bitmap
		fontSize = NEXT_QUESTION_FONT_SIZE;
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", fontSize, NULL);
	}

	bool onHover() //Same code as "onClick()", but better for readability
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		int width, height;
		width = al_get_bitmap_width(bitmap);
		height = al_get_bitmap_height(bitmap);
		if (state.x > x && state.x < (x + width)
			&& state.y > y && state.y < (y + height))//If this is true, the mouse cursor is within the bitmap. 
		{
			return true;
		}
		return false;
	}

	bool onClick() //NEEDS FIX, AS BUTTON IS ALOT SMALLER THAN BITMAP
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		int width, height;
		width = al_get_bitmap_width(bitmap);
		height = al_get_bitmap_height(bitmap);
		if (state.x > x&& state.x < (x + width)
			&& state.y > y&& state.y < (y + height)) //If this is true, the mouse cursor is within the bitmap. 
		{
			return true;
		}
		return false;
	}

	void setBitmap(int bitmap) //0 = default, 1 = hover
	{
		switch (bitmap)
		{
		case 0:
			this->bitmap = bitmapNormal;
			break;
		case 1:
			this->bitmap = bitmapHover;
			break;
		default:
			break;
		}
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
		al_draw_textf(font, al_map_rgb(0, 0, 0), textX, textY, NULL, "Next question");

	}
};

//struct Controller {
//	//Question &question;
//	//Answer* answer[MAX_ANSWERS];
//	//MenuButton* menuButton;
//	//Background* background;
//
//	Controller(const Question &question) //Constructor
//	{
//		//this->question = question;
//		//this->answer = answer;
//		//this->menuButton = menuButton;
//		//this->background = background;
//	}
//
//	void test()
//	{
//		//question.fontSize = 1;
//		question.setQuestion(3);
//	}
//};