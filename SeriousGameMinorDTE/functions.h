#pragma once

//Go to the next question in the current quiz
void goToNextQuestion(Question &question, Answer answer[], int quizNumber, int questionNumber)
{
	question.setQuestion(quizNumber, questionNumber);
	int answersAmount = (sizeof(answers) / sizeof(answers[questionNumber]));

	for (int i = 0; i < answersAmount; i++)
	{
		if (!std::empty(answers[questionNumber][i]))
			answer[i].setAnswer(questionNumber, i);
	}
}