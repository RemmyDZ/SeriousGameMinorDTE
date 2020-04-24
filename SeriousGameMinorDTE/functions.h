#pragma once

//Reset all answers to false (NEEDED BEFORE MOVING ON TO NEXT QUESTION)
void resetAnswers(Answer answer[])
{
	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		answer[i].setCorrectAnswer(false);
		answer[i].setVisibility(false);
		answer[i].setFont(true);
		answer[i].setBitmap(DEFAULT);
	}
}

//Go to the next question in the current quiz
void goToNextQuestion(Question &question, Answer answer[], int quizNumber, int questionNumber)
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
	default:
		break;
	}
	question.setQuestion(quizNumber, questionNumber);
	//int answersAmount = (sizeof(answers) / sizeof(answers[questionNumber]));

	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		if (!std::empty(answers[questionNumber+quizStartIndex][i]))
			answer[i].setAnswer(questionNumber+quizStartIndex, i);
		if (answers[questionNumber+quizStartIndex][i].length() > ANSWER_RESIZE_LENGTH)
			answer[i].setFont(false); //False means small font
		//printf("%i\n", answers[questionNumber][i].length());
	}
	answer[std::stoi(answers[questionNumber+quizStartIndex][4])].setCorrectAnswer(true);
}

void checkForAnswers(Answer answer[])
{
	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		if (answer[i].onClick())
		{
			if (answer[i].isAnswer)
			{
				answer[i].setBitmap(GREEN);
			}
			else if (!answer[i].isAnswer)
			{
				answer[i].setBitmap(RED);
				for (int i = 0; i < MAX_ANSWERS; i++)
				{
					if (answer[i].isAnswer)
					{
						answer[i].setBitmap(GREEN);
					}
				}
			}
		}
	}
}

void showExplaination(Question question, int quizNumber, int questionNumber)
{
	question.setExplaination(quizNumber, questionNumber);
}

void setGameState(int newGameState)
{
	gameState = newGameState;
}