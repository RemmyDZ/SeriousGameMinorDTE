#pragma once

//Question object
struct Question {
	int x, y;
	int textX, textY; //TextX won't be needed as the text is being drawn in the center, so 'x' can be used for that
	int textMaxWidth;
	int nrTextX, nrTextY; //Coordinations for the question number
	int nrFontSize; //Font size for the question number
	std::string question;
	ALLEGRO_COLOR fontColor;
	ALLEGRO_BITMAP* bitmap = NULL;
	ALLEGRO_BITMAP* bitmapCounter = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_FONT* fontNormal = NULL;
	ALLEGRO_FONT* fontLong = NULL;
	ALLEGRO_FONT* fontExtraLong = NULL;
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
		nrFontSize = QUESTION_NUMBER_FONT_SIZE;
		bitmap = al_load_bitmap("Resources/Textures/Question_box.bmp");
		bitmapCounter = al_load_bitmap("Resources/Textures/Question_counter.bmp");
		fontNormal = al_load_font("Resources/Fonts/GILLUBCD.ttf", QUESTION_FONT_SIZE, NULL);
		fontLong = al_load_font("Resources/Fonts/GILLUBCD.ttf", QUESTION_FONT_SIZE_LONG, NULL);
		fontExtraLong = al_load_font("Resources/Fonts/GILLUBCD.ttf", QUESTION_FONT_SIZE_EXTRA_LONG, NULL);
		font = fontNormal; //Start with default font size
		nrFont = al_load_font("Resources/Fonts/GILLUBCD.ttf", nrFontSize, NULL); //CHANGE FONT, THIS ONE IS NOT SUITABLE FOR NUMBERS
	}

	void setQuestion(int quizNumber, int questionNumber)
	{
		fontColor = al_map_rgb(0, 0, 0);
		question = questions[quizNumber][questionNumber];
		if (question.length() > QUESTION_LONG_FONT_TRESHOLD)
			font = fontLong;
		else
			font = fontNormal;
	}

	void setExplaination(int quizNumber, int questionNumber, ALLEGRO_COLOR color)
	{
		fontColor = color;
		question = explainations[quizNumber][questionNumber];
		if (question.length() > QUESTION_EXTRA_LONG_TRESHOLD)
			font = fontExtraLong;
		else if (question.length() > QUESTION_LONG_FONT_TRESHOLD)
			font = fontLong;
		else
			font = fontNormal;
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
		al_draw_bitmap(bitmapCounter, x, 456, NULL);
		al_draw_multiline_text(font, fontColor, textX, textY, textMaxWidth, 0, NULL, question.c_str());
		al_draw_textf(nrFont, al_map_rgb(0, 0, 0), nrTextX, nrTextY, NULL, "Question: %i/%zu", currentQuestion+1, std::size(questions[0])); //Plus 1, because currentQuestion is an index number, and we want to display a correct number
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

	Answer(int positionV, int positionH, Question question) //Constructor
	{ //FIX 'Answer::y is unitialized' WARNING
		textOffset = ANSWER_FONT_SIZE * 2;
		answersAmount = std::size(questions[currentQuestion]);
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
		}
		else if (positionV == RIGHT)
		{
			x = (DISPLAY_WIDTH / 4) * 3;
		}
		bitmap = bitmapNormal; //Start with the normal bitmap
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
			al_draw_multiline_text(font, al_map_rgb(0, 0, 0), x, y-textOffset, al_get_bitmap_width(bitmap) - 50, 0, ALLEGRO_ALIGN_CENTER, answer.c_str());
		}
	}

	void clear() //Garbage control
	{
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
	int quizNumber;
	std::string text;
	std::string author;
	std::string quizType;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapHover;
	ALLEGRO_FONT* font;
	ALLEGRO_FONT* authorFont;

	MenuButton(int index, std::string text, MenuBox menuBox, int quizNumber, std::string author, std::string quizType) //Index acts as a multiplier for the y position, quizNumber is the quiz it links to, for non-quiz buttons the value doesn't matter
	{
		this->text = text;
		this->author = author;
		this->quizType = quizType;
		this->quizNumber = quizNumber; //0 to 4, acts as an index
		bitmapNormal = al_load_bitmap("Resources/Textures/menu_option.bmp");
		bitmapHover = al_load_bitmap("Resources/Textures/menu_option_hover.bmp");
		bitmap = bitmapNormal; //Start with the default bitmap
		x = (al_get_bitmap_width(menuBox.bitmap) - al_get_bitmap_width(bitmap)) / 2;
		y = (al_get_bitmap_height(bitmap) * index) + MENU_BUTTON_START_Y;
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", MENU_BUTTON_FONT_SIZE, NULL);
		authorFont = al_load_font("Resources/Fonts/GILLUBCD.ttf", MENU_BUTTON_AUTHOR_FONT_SIZE, NULL);
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
		if (!author.empty())
			al_draw_text(authorFont, al_map_rgb(0, 0, 255), x + 520, y + 80, NULL, author.c_str());
		if (!quizType.empty())
			al_draw_text(authorFont, al_map_rgb(255, 0, 0), x + 10, y + 80, NULL, quizType.c_str());
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
			al_draw_textf(font, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2, (DISPLAY_HEIGHT / 2) - 40, ALLEGRO_ALIGN_CENTER, "Score: %i\%%", playerScore*10);
	}

	void clear() //Garbage control
	{
		al_destroy_bitmap(bitmap);
	}
};

struct Fadeout {
	int x, y;
	bool isVisible;
	ALLEGRO_BITMAP* bitmap;

	Fadeout()
	{
		x = BACKGROUND_X;
		y = BACKGROUND_Y;
		isVisible = false; //Only make this visible when player clicked "View source"
		bitmap = al_load_bitmap("Resources/Textures/fadeout.bmp");
	}

	void setVisibility(bool visible)
	{
		isVisible = visible;
	}

	void draw()
	{
		if(isVisible)
			al_draw_bitmap(bitmap, x, y, NULL);
	}

	void clear()
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

	bool onClick() 
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
		if (currentQuestion < 9)
			al_draw_textf(font, al_map_rgb(0, 0, 0), textX, textY, NULL, "Next question");
		else if (currentQuestion == 9)
			al_draw_textf(font, al_map_rgb(0, 0, 0), textX, textY, NULL, "Check results");

	}

	void clear()
	{
		al_destroy_bitmap(bitmap);
		al_destroy_font(font);
	}
};

struct MainMenuButton {
	int x, y;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapHover;
	ALLEGRO_FONT* font;

	MainMenuButton(int x, int y)
	{
		this->x = x;
		this->y = y;
		bitmapNormal = al_load_bitmap("Resources/Textures/Back_to_start_button.bmp");
		bitmapHover = al_load_bitmap("Resources/Textures/Back_to_start_button_hover.bmp");
		bitmap = bitmapNormal; //Start with the default bitmap
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", MAIN_MENU_BUTTON_FONT_SIZE, NULL);
	}

	bool onClick()
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
		al_draw_text(font, al_map_rgb(0, 0, 0), x + 47, y + 12, NULL, "Main Menu");
	}

	void clear()
	{
		al_destroy_bitmap(bitmap);
		al_destroy_font(font);
	}
};

struct SourceButton {
	int x, y;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapHover;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_FONT* font;

	SourceButton()
	{
		x = SOURCE_BUTTON_X;
		y = SOURCE_BUTTON_Y;
		bitmapNormal = al_load_bitmap("Resources/Textures/Back_to_start_button.bmp");
		bitmapHover = al_load_bitmap("Resources/Textures/Back_to_start_button_hover.bmp");
		bitmap = bitmapNormal; //Start with default bitmap
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", SOURCE_BUTTON_FONT_SIZE, NULL);
	}

	bool onClick()
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
		al_draw_text(font, al_map_rgb(0, 0, 0), x + 42, y + 12, NULL, "View source");
	}

	void clear()
	{
		al_destroy_bitmap(bitmap);
		al_destroy_font(font);
	}
};

struct CloseSourceButton {
	int x, y;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapHover;
	ALLEGRO_BITMAP* bitmap;

	CloseSourceButton()
	{
		x = CLOSE_SOURCE_BUTTON_X;
		y = CLOSE_SOURCE_BUTTON_Y;
		bitmapNormal = al_load_bitmap("Resources/Textures/close.bmp");
		bitmapHover = al_load_bitmap("Resources/Textures/close_hover.bmp");
		al_convert_mask_to_alpha(bitmapNormal, al_map_rgb(255, 255, 255));
		al_convert_mask_to_alpha(bitmapHover, al_map_rgb(255, 255, 255));
		bitmap = bitmapNormal; //Start with default bitmap
	}

	bool onClick()
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
	}

	void clear()
	{
		al_destroy_bitmap(bitmap);
	}
};

struct SourceBox {
	int x, y;
	int offsetX, offsetY;
	bool hover;
	std::string source;
	std::string url;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_FONT* font;

	SourceBox(std::string source, std::string url)
	{
		this->source = source;
		this->url = url;
		hover = false;
		x = SOURCE_BOX_X;
		y = SOURCE_BOX_Y;
		bitmap = al_load_bitmap("Resources/Textures/menu_option.bmp");
		offsetX = al_get_bitmap_width(bitmap) / 2;
		offsetY = al_get_bitmap_height(bitmap) / 2;
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", SOURCE_FONT_SIZE, NULL);
	}

	bool onHover() //Same code as "onClick()", but better to have both for code readability
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		if (state.x > (x - offsetX) && state.x < (x + offsetX)
			&& state.y >(y - offsetY) && state.y < (y + offsetY)) //If this is true, the mouse cursor is within the bitmap. Also, the answer has to be visible
		{
			return true;
		}
		return false;
	}

	bool onClick()
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		if (state.x > (x - offsetX) && state.x < (x + offsetX)
			&& state.y >(y - offsetY) && state.y < (y + offsetY)) //If this is true, the mouse cursor is within the bitmap. Also, the answer has to be visible
		{
			return true;
		}
		return false;
	}

	void setHover(bool hover)
	{
		this->hover = hover;
	}

	std::string getURL()
	{
		return url;
	}

	void setSourceAndURL(int questionNumber, int quizStartIndex)
	{
		source = sources[questionNumber + quizStartIndex][0];
		url = sources[questionNumber + quizStartIndex][1];
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x - offsetX, y - offsetY, NULL);
		if (hover)
			al_draw_text(font, al_map_rgb(0, 0, 200), x, y - (SOURCE_FONT_SIZE / 2), ALLEGRO_ALIGN_CENTER, source.c_str());
		else if (!hover)
			al_draw_text(font, al_map_rgb(0, 0, 0), x, y - (SOURCE_FONT_SIZE / 2), ALLEGRO_ALIGN_CENTER, source.c_str());
	}

	void clear()
	{
		al_destroy_bitmap(bitmap);
		al_destroy_font(font);
	}
};

struct TextBox {
	int x, y;
	bool multiline;
	int maxWidth, lineHeight;
	std::string text;
	ALLEGRO_FONT* font;

	TextBox(int x, int y, int fontSize, std::string text, bool multiline, int maxWidth, int lineHeight)
	{
		this->x = x;
		this->y = y;
		this->text = text;
		this->multiline = multiline;
		this->maxWidth = maxWidth; //Only used when multiline is true, use "0" otherwise
		this->lineHeight = lineHeight; //Only used when multiline is true, use "0 otherwise
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", fontSize, NULL);
	}

	void draw()
	{
		if (multiline)
			al_draw_multiline_text(font, al_map_rgb(0, 0, 0), x, y, maxWidth, lineHeight, NULL, text.c_str());
		else if(!multiline)
			al_draw_text(font, al_map_rgb(0, 0, 0), x, y, NULL, text.c_str());
	}

	void clear()
	{
		al_destroy_font(font);
	}
};

struct SoundButton {
	int x, y;
	bool isMuted;
	ALLEGRO_BITMAP* bitmapNormal;
	ALLEGRO_BITMAP* bitmapMute;
	ALLEGRO_BITMAP* bitmap;

	SoundButton()
	{
		x = SOUND_BUTTON_X;
		y = SOUND_BUTTON_Y;
		isMuted = false;
		bitmapNormal = al_load_bitmap("Resources/Textures/speaker0.bmp");
		bitmapMute = al_load_bitmap("Resources/Textures/speaker1.bmp");
		bitmap = bitmapNormal; //Start with regular bitmap
	}

	bool onClick()
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		int width, height;
		width = al_get_bitmap_width(bitmap);
		height = al_get_bitmap_height(bitmap);
		if (state.x > x && state.x < (x + width)
			&& state.y > y && state.y < (y + height)) //If this is true, the mouse cursor is within the bitmap. 
		{
			return true;
		}
		return false;
	}

	bool getMuteStatus()
	{
		return isMuted;
	}

	void setMuteStatus(bool mute)
	{
		isMuted = mute;
	}

	void setBitmap(int bitmap) //0 = default, 1 = mute
	{
		switch (bitmap)
		{
		case 0:
			this->bitmap = bitmapNormal;
			break;
		case 1:
			this->bitmap = bitmapMute;
			break;
		default:
			break;
		}
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