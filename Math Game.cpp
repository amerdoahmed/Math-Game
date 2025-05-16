#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enumeration: enQuestionsLevel
enum enQuestionsLevel {EasyLevel = 1, MedLevel = 2, HardLevel=3, Mix = 4};

// Enumeration: enOperationType
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

// Structure: stQuestion
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

// Structure: stQuizz
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

//Function RandomNumber
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

//Function ReadHowManyQuestions
short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
	return NumberOfQuestions;
}

// Function ReadQuestionsLevel
enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel>4);
	return enQuestionsLevel(QuestionLevel);
}

// Function ReadOpType
enOperationType ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return enOperationType(OpType);
}

// Function: GetOpTypeSymbol
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
			return "/";
	default:
		return "Mix";
	}
}

// Function: GetRandomOperationType
enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

// Function: SimpleCalculator
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;
	default:
		return Number1 + Number2;
	}
}

// Function: GenerateQuestion
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = GetRandomOperationType();
	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}
	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionLevel = QuestionLevel;

	return Question;
}

// Function GenerateQuizzQuestions
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions;Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}

// Function: GetQuestionLevelText
string GetQuestionsLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Medium", "Hard", "Mixed" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

// Function: SetScreenColor
void setScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color4F");
		cout << "\a";
	}
}


// Function PrintTheQuestion
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_______" << endl;
}

// Function ReadQuestionAnswer
int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

//Function CorrectTheQuestionAnswer
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is : ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;
}
// Function: AskAndCorrectQuestionListAnswers
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

// Function GetQuestionLevelText
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

// Function GetFinalResultsText
string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

// Function PrintQuizzResults
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "___________________________________________\n\n";
	cout << " Final Results is " << GetFinalResultsText(Quizz.isPass) << endl;
	cout << "___________________________________________\n\n";

	cout << "Number Of Questions :" << Quizz.NumberOfQuestions << endl;
	cout << "Question Level      :" << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "Operation Type      :" << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answers :" << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers :" << Quizz.NumberOfWrongAnswers << endl;
	cout << "___________________________________________\n\n";
}

// Function: PlayMathGame
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	
	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);

	PrintQuizzResults(Quizz);
}

// Function ResetScreen
void ResetScreen()
{
	system("cls");
	system("color 0F");
}

// Function StartGame
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again ? Y/N ?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


// Main Function
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	

	return 0;
}