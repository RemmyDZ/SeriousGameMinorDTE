#pragma once

//Go to the next question in the current quiz
void goToNextQuestion(Question &question, Answer answer[], int questionNumber)
{
	question.setQuestion(questionNumber);
	int answersAmount = (sizeof(answers) / sizeof(answers[questionNumber]));

	for (int i = 0; i < answersAmount; i++)
	{
		if (!std::empty(answers[currentQuestion][i]))
			answer[i].setAnswer(currentQuestion, i);
	}
}