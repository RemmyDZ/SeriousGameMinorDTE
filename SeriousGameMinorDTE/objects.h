#pragma once

//Question object
struct Question {
	int x, y;
	std::string question;
	ALLEGRO_BITMAP* bitmap = NULL;

	Question(int x, int y, std::string question) //Constructor
	{
		this->x = x;
		this->y = y;
		this->question = question;
		bitmap = al_load_bitmap("Resources/textures/Question_box.bmp");
	}

	void setNextQuestion()
	{
		//this->question =
	}
	void draw()
	{
		//Draw bitmap and text
	}
};

struct Answer {
	int x, y;
};

struct MenuButton {
	int x, y;
};