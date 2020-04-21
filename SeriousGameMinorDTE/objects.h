#pragma once

//Question object
struct Question {
	int x, y;
	int textX, textY;
	int nrTextX, nrTextY; //Coordinations for the question number
	int fontSize;
	int nrFontSize; //Font size for the question number
	std::string question;
	ALLEGRO_BITMAP* bitmap = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_FONT* nrFont = NULL; //Font for the question number

	Question(int x, int y, int textX, int textY, int nrTextX, int nrTextY, std::string question, int fontSize, int nrFontSize) //Constructor
	{
		this->x = x;
		this->y = y;
		this->textX = textX;
		this->textY = textY;
		this->nrTextX = nrTextX;
		this->nrTextY = nrTextY;
		this->question = question;
		this->fontSize = fontSize;
		this->nrFontSize = nrFontSize;
		bitmap = al_load_bitmap("Resources/Textures/Question_box.bmp");
		al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 220));
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", fontSize, NULL);
		nrFont = al_load_font("Resources/Fonts/GILLUBCD.ttf", nrFontSize, NULL); //CHANGE FONT, THIS ONE IS NOT SUITABLE FOR NUMBERS
	}

	void setNextQuestion()
	{
		//this->question =
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
		al_draw_text(font, al_map_rgb(0, 0, 0), textX, textY, NULL, question.c_str());
		al_draw_textf(nrFont, al_map_rgb(0, 0, 0), nrTextX, nrTextY, NULL, "%i/%zu", currentQuestion+1, std::size(questions)); //Plus 1, because currentQuestion is an index number, and we want to display a correct number
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
	//Add text coordinates here
	int textOffset;
	std::string answer;
	bool isAnswer; //True if it's the correct answer, false if not
	bool isVisible;
	int positionV, positionH;
	ALLEGRO_BITMAP* bitmap = NULL;
	ALLEGRO_FONT* font = NULL;
	//Question &question;

	Answer(std::string answer, int positionV, int positionH, Question question) //Constructor (positionV = vertical, positionH = horizontal)
	{
		textOffset = ANSWER_FONT_SIZE / 2;
		//this->answer = answer;
		this->answer = answers[currentQuestion][1];
		this->positionV = positionV;
		this->positionH = positionH;
		isAnswer = false; //NEEDS FIX
		isVisible = true; //NEEDS FIX
		if (positionV == LEFT)
		{
			x = DISPLAY_WIDTH / 4;
			bitmap = al_load_bitmap("Resources/Textures/Answer1.bmp"); //Load Answer1 bitmap for answers on the left
		}
		else if (positionV == RIGHT)
		{
			x = (DISPLAY_WIDTH / 4) * 3;
			bitmap = al_load_bitmap("Resources/Textures/Answer2.bmp"); //Load Answer2 bitmap for answers on the right
		}
		al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 220));
		offsetX = al_get_bitmap_width(bitmap) / 2;
		offsetY = al_get_bitmap_height(bitmap) / 2;
		if (positionH == TOP)
			y = ((DISPLAY_HEIGHT - al_get_bitmap_height(question.bitmap)) / 4) + al_get_bitmap_height(question.bitmap);
		else if (positionH == BOTTOM)
			y = (((DISPLAY_HEIGHT - al_get_bitmap_height(question.bitmap)) / 4) * 3) + al_get_bitmap_height(question.bitmap);
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", ANSWER_FONT_SIZE, NULL);
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x-offsetX, y-offsetY, NULL);
		al_draw_text(font, al_map_rgb(0, 0, 0), x, y-textOffset, ALLEGRO_ALIGN_CENTER, answer.c_str());
		//al_draw_textf(NULL, al_map_rgb(0, 0, 0), 10, 10, NULL, "y: %i", y);
	}

	void clear() //Garbage control
	{
		al_destroy_bitmap(bitmap);
	}
};

struct MenuButton {
	int x, y;
	std::string text;
	ALLEGRO_BITMAP* bitmap;

	MenuButton(int x, int y, std::string text)
	{
		this->x = x;
		this->y = y;
		this->text = text;
		//bitmap = ...
	}

	void onMouseHover()
	{
		//Change color?
	}

	void onClick()
	{
		//Redirect to quiz
	}

	void draw()
	{
		//Draw bitmap + text
	}

	void clear() //Garbage control
	{
		al_destroy_bitmap(bitmap);
	}
};

struct Background {
	int x, y;
	ALLEGRO_BITMAP* bitmap;

	Background(int x, int y) //Constructor
	{
		this->x = x;
		this->y = y;
		bitmap = al_load_bitmap("Resources/Textures/Background_quiz.bmp");
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
	}

	void clear() //Garbage control
	{
		al_destroy_bitmap(bitmap);
	}
};