#pragma once

//Reset all answers to false (NEEDED BEFORE MOVING ON TO NEXT QUESTION)
void resetAnswers(Answer answer[])
{
	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		answer[i].setCorrectAnswer(false);
		answer[i].setVisibility(false);
		answer[i].setFont(true);
	}
}

//Go to the next question in the current quiz
void goToNextQuestion(Question &question, Answer answer[], int gameState, int questionNumber)
{
	int quizIndex = 0;
	switch (gameState)
	{
	case QUIZ_ONE:
		quizIndex = 0;
		questionNumber *= QUIZ_INDEX_ONE;
		break;
	case QUIZ_TWO:
		quizIndex = 1; 
		questionNumber *= QUIZ_INDEX_TWO;
		break;
	case QUIZ_THREE:
		quizIndex = 2;
		questionNumber *= QUIZ_INDEX_THREE;
		break;
	case QUIZ_FOUR:
		quizIndex = 3;
		questionNumber *= QUIZ_INDEX_FOUR;
		break;
	case QUIZ_FIVE:
		quizIndex = 4;
		questionNumber *= QUIZ_INDEX_FIVE;
		break;
	default:
		break;
	}
	question.setQuestion(quizIndex, questionNumber);
	int answersAmount = (sizeof(answers) / sizeof(answers[questionNumber]));

	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		if (!std::empty(answers[questionNumber][i]))
			answer[i].setAnswer(questionNumber, i);
		if (answers[questionNumber][i].length() > ANSWER_RESIZE_LENGTH)
			answer[i].setFont(false); //False means small font
		printf("%i\n", answers[questionNumber][i].length());
	}
	answer[std::stoi(answers[questionNumber][4])].setCorrectAnswer(true);
}

void setGameState(int newGameState)
{
	gameState = newGameState;
}