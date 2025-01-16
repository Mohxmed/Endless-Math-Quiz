
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

// enums
enum enTypes  { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };
enum enLevels { Easy = 1, Mid = 2, Hard = 3, Mixed = 4};

// Structures
struct GameInfo {
    int TotalQuestions = 0;
    int GameLevel = 0;
    int GameType = 0;
    int CurrentQuestion = 0;
    int RightTotal = 0;
    int WrongTotal = 0;
};
struct CurrentQuestion {
    int FirstNum = 0;
    int SecondNum = 0;
    int result = 0;
    int UserInput = 0;
    string type = "";
};

// Methods
int RandomNumber(int from, int to) {
    return rand() % (to - from + 1) + from;
}

void ClearScreen() {
    system("cls");
    system("Color 0F");
}

void PrintRed(const string& message) {
    cout << "\033[31m" << message << "\033[0m";
}

void PrintGreen(const string& message) {
    cout << "\033[32m" << message << "\033[0m"; // ANSI escape code for green
}

int ReadNumber(string Message) {
    int Number;
    while (true) {
        cout << Message;
        cin >> Number;
        return Number;
    }
}

int ReadGameTimes() {
    int GameTimes;

    do {
        GameTimes = ReadNumber("How Many Questions do you want to answer : ");
        cout << endl;
        if (GameTimes < 1) {
            PrintRed("\n## Please Enter a Vaild Positive Number!\n");
        }
    } while (GameTimes < 1);
    
    return GameTimes;
}

int ReadLevel() {
    int Level;
    do {
        Level = ReadNumber("Enter Questions Level? [1] Easy , [2] Mid , [3] Hard , [4] Mix : ");
        cout << endl;
        if (Level > 5 || Level <= 0) {
            PrintRed("\n## Please Enter Number From 1:4 \n");
        }
    } while (Level > 5 || Level <= 0);
    return Level;
}

int ReadQuestionType() {
    int Type;
    do {
        Type = ReadNumber("Enter Questions Type? [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix : ");
        cout << endl;
        if (Type > 5 || Type <= 0) {
            PrintRed("\n## Please Enter Number From 1:5 \n");
        }
    } while (Type > 6 || Type <= 0);
    return Type;
}

int ReadAnswer() {
    int Answer = ReadNumber("");
    return Answer;
}

string GetType(int Type) {
    switch (Type)
    {
    case enTypes::Add :
        return "Addition";
        break;
    case enTypes::Sub:
        return "Subtraction";
        break;
    case enTypes::Mul:
        return "Multiplication";

        break;
    case enTypes::Div:
        return "Division";
        break;
    case enTypes::Mix:
        return "Mix";
        break;
    }
}

string GetLevel(int Level) {
    switch (Level)
    {
    case enLevels::Easy:
        return "Easy";
        break;
    case enLevels::Mid:
        return "Meduim";
        break;
    case enLevels::Hard:
        return "Hard";

        break;
    case enLevels::Mixed:
        return "Mixed";
        break;
    }
}

int MixedLevel() {
    int RandomLevel = RandomNumber(1, 3);

    switch (RandomLevel)
    {
    case enLevels::Easy:
        return RandomNumber(1, 9);
        break;
    case enLevels::Mid:
        return RandomNumber(10, 99);
        break;
    case enLevels::Hard:
        return RandomNumber(100, 999);
        break;
    }
}

int RandomNumberByLevel(GameInfo GameData) {
    switch (GameData.GameLevel)
    {
    case enLevels::Easy:
        return RandomNumber(1, 9);
        break;
    case enLevels::Mid:
        return RandomNumber(10, 99);
        break;
    case enLevels::Hard:
        return RandomNumber(100, 999);
        break;
    case enLevels::Mixed:
        return MixedLevel();
        break;
    }
}

void PrintQuestion(int Current, int Total, int FirstNumb, int SecondNum, string Type) {
    cout << "\nQuestion [" << Current << "/" << Total << "] \n\n";
    cout << FirstNumb << "\n";
    cout << SecondNum << " " << Type << "\n";
    cout << "________\n";
}

void CheckAnswer(int Result, int UserInput, GameInfo & GameData) {
    if (Result == UserInput) {
        GameData.RightTotal++;
        system("Color 2F");
        cout << "Right Answer! \n";
    }
    else {
        GameData.WrongTotal++;
        system("Color 4F");
        cout << "Wrong Answer! \nThe Right Answer is \a " << Result << "\n";
    }
}

void GenerateAddQuestion(GameInfo& GameData, CurrentQuestion CurrentQ) {
    CurrentQ.FirstNum = RandomNumberByLevel(GameData);
    CurrentQ.SecondNum = RandomNumberByLevel(GameData);
    int Result = CurrentQ.FirstNum + CurrentQ.SecondNum;
    //
    PrintQuestion(GameData.CurrentQuestion, GameData.TotalQuestions, CurrentQ.FirstNum, CurrentQ.SecondNum, "+");
    int UserInput = ReadAnswer();
    CheckAnswer(Result, UserInput, GameData);

}

void GenerateSubQuestion(GameInfo& GameData, CurrentQuestion CurrentQ) {
    CurrentQ.FirstNum = RandomNumberByLevel(GameData);
    CurrentQ.SecondNum = RandomNumberByLevel(GameData);
    int Result = CurrentQ.FirstNum - CurrentQ.SecondNum;
    //
    PrintQuestion(GameData.CurrentQuestion, GameData.TotalQuestions, CurrentQ.FirstNum, CurrentQ.SecondNum, "-");
    int UserInput = ReadAnswer();
    CheckAnswer(Result, UserInput, GameData);
}

void GenerateMulQuestion(GameInfo& GameData, CurrentQuestion CurrentQ) {
    CurrentQ.FirstNum = RandomNumberByLevel(GameData);
    CurrentQ.SecondNum = RandomNumberByLevel(GameData);
    int Result = CurrentQ.FirstNum * CurrentQ.SecondNum;
    //
    PrintQuestion(GameData.CurrentQuestion, GameData.TotalQuestions, CurrentQ.FirstNum, CurrentQ.SecondNum, "*");
    int UserInput = ReadAnswer();
    CheckAnswer(Result, UserInput, GameData);

}

void GenerateDivQuestion(GameInfo& GameData, CurrentQuestion CurrentQ) {
    CurrentQ.FirstNum = RandomNumberByLevel(GameData);
    CurrentQ.SecondNum = RandomNumberByLevel(GameData);
    int Result = CurrentQ.FirstNum / CurrentQ.SecondNum;
    //
    PrintQuestion(GameData.CurrentQuestion, GameData.TotalQuestions, CurrentQ.FirstNum, CurrentQ.SecondNum, "/");
    int UserInput = ReadAnswer();
    CheckAnswer(Result, UserInput, GameData);

}

void GenerateQuestionsByType(GameInfo& GameData, CurrentQuestion CurrentQ) {
    switch (GameData.GameType)
    {
    case enTypes::Add:
        return GenerateAddQuestion(GameData, CurrentQ);
        break;
    case enTypes::Sub:
        return GenerateSubQuestion(GameData, CurrentQ);
        break;
    case enTypes::Mul:
        return GenerateMulQuestion(GameData, CurrentQ);
        break;
    case enTypes::Div:
        return GenerateDivQuestion(GameData, CurrentQ);
        break;
    case enTypes::Mix:
        break;
    }
}

void GenerateMixedQuestions(GameInfo& GameData, CurrentQuestion CurrentQ) {
    int QuestionType = RandomNumber(1, 4);

    switch (QuestionType)
    {
    case enTypes::Add:
        return GenerateAddQuestion(GameData, CurrentQ);
        break;
    case enTypes::Sub:
        return GenerateSubQuestion(GameData, CurrentQ);
        break;
    case enTypes::Mul:
        return GenerateMulQuestion(GameData, CurrentQ);
        break;
    case enTypes::Div:
        return GenerateDivQuestion(GameData, CurrentQ);
        break;
    }
}

void HandleQuestions(GameInfo & GameData, CurrentQuestion CurrentQ) {
    GameData.CurrentQuestion = 0;
    for (int Time = 1; Time <= GameData.TotalQuestions; Time++) {
        GameData.CurrentQuestion++;
        if (GameData.GameType == enTypes::Mix) {
            GenerateMixedQuestions(GameData, CurrentQ);
        }
        else {
            GenerateQuestionsByType(GameData, CurrentQ);
        }
    }
}

string PassOrFail(int Wrong, int Right) {
    if (Wrong > Right) {
        return "FAIL";
        system("Color 2F");
    }
    else {
        return "PASS";
        system("Color 4F");
    }
}

void EndMessage(int Wrong, int Right) {
    cout << "\n___________________________\n\n";
    cout << " Final Result is " << PassOrFail(Wrong, Right) << " ";
    cout << "\n___________________________\n";
}

void PrintStatistics(GameInfo GameData) {
    cout << "\n\nDegree [ " << GameData.RightTotal << "/" << GameData.TotalQuestions << " ]\n";
    cout << "\nNumber of Questions is    :  " << GameData.TotalQuestions << "\n";
    cout << "Questions Level           :  " << GetLevel(GameData.GameLevel) << "\n";
    cout << "Exam Type                 :  " << GetType(GameData.GameType) << "\n";
    cout << "Number of Right Answers   :  " << GameData.RightTotal << "\n";
    cout << "Number of Wrong Answers   :  " << GameData.WrongTotal << "\n";
    cout << "___________________________\n\n";
    cout << "By Mohxmed Amr <3 \n";
    cout << "___________________________\n";
}

void HandleEndGame(GameInfo GameData) {
    EndMessage(GameData.WrongTotal, GameData.RightTotal);
    PrintStatistics(GameData);

}

bool PlayAgain() {
    char again;
    cout << "\n\nDo you want to play again? [Y/N] : ";
    cin >> again;

    if (again == 'y' || again == 'Y') {
        ClearScreen();
        PrintGreen("Welcom Again, Seems you Enjoyed! Let's Do It Again! \n");
        return true;
    }
    else {
        return false;
    }
}

// Start Game
void Start() {
    GameInfo GameData;
    CurrentQuestion CurrentQ;
    PrintGreen("Welcome in MadMath Game! Let's Start..\n");
    do {
        GameData.RightTotal = 0;
        GameData.WrongTotal = 0;
    // User Choices
    GameData.TotalQuestions = ReadGameTimes();
    GameData.GameLevel = ReadLevel();
    GameData.GameType = ReadQuestionType();
    HandleQuestions(GameData, CurrentQ);
    HandleEndGame(GameData);

    } while (PlayAgain());
    
}

int main()
{
    srand((unsigned)time(NULL));
    Start();
}

