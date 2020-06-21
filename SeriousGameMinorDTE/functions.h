#pragma once

//Forward declerations
void resetAnswers(Answer answer[]);
void goToNextQuestion(Question &question, Answer answer[], SourceBox &sourceBox, int quizNumber, int questionNumber);
bool checkForAnswers(Question &question, Answer answer[], bool randomized);
void showExplaination(Question &question, int quizNumber, int questionNumber, ALLEGRO_COLOR color);
void setGameState(int newGameState);

//Reset all answers to false (NEEDED BEFORE MOVING ON TO NEXT QUESTION)
void resetAnswers(Answer answer[])
{
	isAnswerGiven = false;
	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		answer[i].setCorrectAnswer(false);
		answer[i].setVisibility(false);
		answer[i].setFont(true);
		answer[i].setBitmap(DEFAULT);
	}
}

//Go to the next question in the current quiz
void goToNextQuestion(Question &question, Answer answer[], SourceBox &sourceBox, int quizNumber, int questionNumber) //Questionnumber -1 means the question
{
	int quizStartIndex = 0; //Give it a value so the code below doesn't use uninitialized memory FIX WARNING
	switch (quizNumber)
	{
	case 0:
		quizStartIndex = QUIZ_INDEX_ONE;
		break;
	case 1:
		quizStartIndex = QUIZ_INDEX_TWO;
		break;
	case 2:
		quizStartIndex = QUIZ_INDEX_THREE;
		break;
	case 3:
		quizStartIndex = QUIZ_INDEX_FOUR;
		break;
	case 4:
		quizStartIndex = QUIZ_INDEX_FIVE;
		break;
	case 5:
		quizStartIndex = QUIZ_INDEX_SIX;
		break;
	default:
		break;
	}

	if(questionNumber >= 0) //Question is NOT random
		question.setQuestion(quizNumber, questionNumber);
	else if (questionNumber == -1)
	{
		start: 
		int random = rand() % MAX_QUESTIONS; //Random number between 0 and maximum amount of questions
		if (std::find(randomQuestions.begin(), randomQuestions.end(), random) != randomQuestions.end()) //If this is true, the question has already been given
			goto start;
		else //Question hasn't been used yet
		{
			questionNumber = random; //For setting the correct answers
			currentRandomQuestion = random;
			question.setQuestion(quizNumber, currentRandomQuestion);
			randomQuestions.push_back(currentRandomQuestion);
		}
	}

	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		if (!std::empty(answers[questionNumber+quizStartIndex][i]))
			answer[i].setAnswer(questionNumber+quizStartIndex, i);
		if (answers[questionNumber+quizStartIndex][i].length() > ANSWER_RESIZE_LENGTH)
			answer[i].setFont(false); //False means small font
	}
	answer[std::stoi(answers[questionNumber+quizStartIndex][4])].setCorrectAnswer(true);

	sourceBox.setSourceAndURL(questionNumber, quizStartIndex);
}

bool checkForAnswers(Question &question, Answer answer[], bool randomized) 
{
	if (!isAnswerGiven) //Only proceed with the code if an answer hasn't been given yet
	{
		ALLEGRO_COLOR color;
		for (int i = 0; i < MAX_ANSWERS; i++)
		{
			if (answer[i].onClick())
			{
				if (answer[i].isAnswer) //Player answered right
				{
					answer[i].setBitmap(GREEN);
					playerScore++; //Increase score by 1
					color = al_map_rgb(0, 255, 0); //Set explaination to green for right answers
				}
				else if (!answer[i].isAnswer) //Player answered wrong
				{
					answer[i].setBitmap(RED);
					color = al_map_rgb(255, 0, 0); //Set explaination to red for wrong answers
					for (int i = 0; i < MAX_ANSWERS; i++)
					{
						if (answer[i].isAnswer)
						{
							answer[i].setBitmap(GREEN);
						}
					}
				}
				isAnswerGiven = true;
				if(randomized)
					showExplaination(question, gameState, currentRandomQuestion, color);
				else if(!randomized)
					showExplaination(question, gameState, currentQuestion, color);
				return true;
			}
		}
	}
	return false;
}

void showExplaination(Question &question, int quizNumber, int questionNumber, ALLEGRO_COLOR color)
{
	question.setExplaination(quizNumber, questionNumber, color);
}

void setGameState(int newGameState)
{
	gameState = newGameState;
}