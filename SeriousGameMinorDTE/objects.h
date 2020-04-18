#pragma once

//Question object
struct Question {
	int x, y;
	int textX, textY;
	int fontSize;
	std::string question;
	ALLEGRO_BITMAP* bitmap = NULL;
	ALLEGRO_FONT* font = NULL;

	Question(int x, int y, int textX, int textY, std::string question, int fontSize) //Constructor
	{
		this->x = x;
		this->y = y;
		this->textX = textX;
		this->textY = textY;
		this->question = question;
		this->fontSize = fontSize;
		bitmap = al_load_bitmap("Resources/textures/Question_box.bmp");
		al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 220));
		font = al_load_font("Resources/Fonts/GILLUBCD.ttf", fontSize, NULL);
	}

	void setNextQuestion()
	{
		//this->question =
	}
	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
		al_draw_text(font, al_map_rgb(0, 0, 0), textX, textY, NULL, question.c_str());
	}
};

struct Answer {
	int x, y;
	std::string answer;
	bool isAnswer; //True if it's the correct answer, false if not
	ALLEGRO_BITMAP* bitmap;

	Answer(int x, int y, std::string answer) //Constructor
	{
		this->x = x;
		this->y = y;
		this->answer = answer;
		isAnswer = false; //NEEDS FIX
		bitmap = al_load_bitmap("Resources/textures/Answer1.bmp");
		al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 220));
	}

	void draw()
	{
		al_draw_bitmap(bitmap, 50, 600, NULL);
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
};

struct Background {
	int x, y;
	ALLEGRO_BITMAP* bitmap;

	Background(int x, int y) //Constructor
	{
		this->x = x;
		this->y = y;
		bitmap = al_load_bitmap("Resources/textures/Background_quiz.bmp");
	}

	void draw()
	{
		al_draw_bitmap(bitmap, x, y, NULL);
	}
};