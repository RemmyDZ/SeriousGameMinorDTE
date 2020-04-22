#pragma once

//Reset all answers to false (NEEDED BEFORE MOVING ON TO NEXT QUESTION)
void resetAnswers(Answer answer[])
{
	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		answer[i].setCorrectAnswer(false);
		answer[i].setVisibility(false);
	}
}

//Go to the next question in the current quiz
void goToNextQuestion(Question &question, Answer answer[], int quizNumber, int questionNumber)
{
	question.setQuestion(quizNumber, questionNumber);
	int answersAmount = (sizeof(answers) / sizeof(answers[questionNumber]));

	for (int i = 0; i < MAX_ANSWERS; i++)
	{
		if (!std::empty(answers[questionNumber][i]))
			answer[i].setAnswer(questionNumber, i);
	}
	answer[std::stoi(answers[questionNumber][4])].setCorrectAnswer(true);
}