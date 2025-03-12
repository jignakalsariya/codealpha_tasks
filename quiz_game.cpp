#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 5
#define MAX_NAME 50

typedef struct 
{
    char question[256];
    char options[4][100];
    char correct_option;
} QuizQuestion;

void registerUser(char username[]) 
{
    printf("Enter your name: ");
    fgets(username, MAX_NAME, stdin);
    username[strcspn(username, "\n")] = 0;
}

void startQuiz(QuizQuestion quiz[], int *score) 
{
    char answer;
    *score = 0;
    
    printf("\n--- Quiz Started! ---\n");
    for (int i = 0; i < MAX_QUESTIONS; i++) 
	{
        printf("\nQ%d: %s\n", i + 1, quiz[i].question);
        for (int j = 0; j < 4; j++) 
		{
            printf("%c) %s\n", 'A' + j, quiz[i].options[j]);
        }
        
        printf("Your answer: ");
        scanf(" %c", &answer);
        getchar(); // Clear buffer

        if (answer == quiz[i].correct_option) 
		{
            printf("Correct!\n");
            (*score)++;
        } else 
		{
            printf("Wrong! Correct answer: %c\n", quiz[i].correct_option);
        }
    }
}

void displayResult(int score) 
{
    printf("\n--- Quiz Over! ---\n");
    printf("Your final score: %d/%d\n", score, MAX_QUESTIONS);
    if (score == MAX_QUESTIONS) 
	{
        printf("Excellent! You're a quiz master!\n");
    } else if (score >= 3) 
	{
        printf("Good job!\n");
    } else 
	{
        printf("Keep learning and try again!\n");
    }
}

int main() 
{
    char username[MAX_NAME];
    int score;

    QuizQuestion quiz[MAX_QUESTIONS] = 
	{
        {"What is the capital of France?", {"Berlin", "Madrid", "Paris", "Rome"}, 'C'},
        {"Which planet is known as the Red Planet?", {"Earth", "Mars", "Jupiter", "Venus"}, 'B'},
        {"Who wrote 'Hamlet'?", {"Shakespeare", "Dickens", "Hemingway", "Austen"}, 'A'},
        {"What is 10 + 5?", {"10", "15", "20", "25"}, 'B'},
        {"Which element has the chemical symbol 'O'?", {"Oxygen", "Gold", "Silver", "Iron"}, 'A'}
    };

    printf("Welcome to the Online Quiz Game!\n");
    registerUser(username);

    printf("\nHello, %s! Get ready for the quiz!\n", username);
    startQuiz(quiz, &score);
    displayResult(score);

    return 0;
}

