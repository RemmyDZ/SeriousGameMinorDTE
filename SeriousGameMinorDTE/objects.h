#pragma once

//Question object
struct Question {
	int x, y;
	char* question;
	ALLEGRO_BITMAP* bitmap;

	Question(int x, int y, char* question) //Constructor
	{
		this->x = x;
		this->y = y;
		this->question = question;
	}

	void setNextQuestion()
	{
		//this->question =
	}
};

struct Answer {
	int x, y;
};

struct MenuButton {
	int x, y;
};