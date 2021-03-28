#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include "hangman.h"


int main(int argc, char *argv[])
{
    int a;
    char c;
    int randNum;
    int randNum2;
    int lifeline = 50;
    FILE *w;
    char word[20];  
    Hangman *h;
    int i = 0;
    int over = 0;
    char userletter;
    char userChoice;
    char userWord[20];
    int playersPoints;
    int tries = 4;
    int length;
    
    int userInput;
    int userFight;
    int attack = 0;
    int randGuess;
    int userGuess;
    
    srand(time(0));
    
    if(argc != 2){                             
       printf("ERROR NO ARGS"); 
       return 1;
    }
   
    w = fopen(argv[1], "r");
    if(w == NULL){
         printf("ERROR FILE NOT OPEN"); 
         return 1;
    }
    
    h = (Hangman*)malloc(20*sizeof(Hangman));
    
    do
    {
        printf("You have %d lifeline points, play the following minigames and reach 80 to win\n", lifeline);
        printf("Please enter 1 for guess the number, 2 for hangman, 3 for monster battle, or 4 for quit: ");
        scanf("%d", &userInput);
        if(userInput == 1){
            printf("Guess the random number from 0 - 100\n");
            randGuess = (rand() % 100);
            tries = 7;
            while(tries > 0){
                printf("You have %d tries left, enter a number: ", tries);
                scanf("%d", &userGuess);
                if(userGuess > randGuess){
                    printf("%d is higher than the number\n", userGuess);
                }
                else if(userGuess < randGuess){
                    printf("%d is lower than the number\n", userGuess);
                }
                else{
                    printf("You guessed %d correctly and earned 10 lifeline points!\n\n", userGuess);
                    lifeline+=10;
                    tries = 0;
                }
                tries--;
            }
            if(userGuess != randGuess){
                printf("The number was %d, You ran out of tries and lost 10 lifeline points.\n\n", randGuess);
                lifeline-=10;
            }
        }
        else if(userInput == 2){
            tries = 3;
            for(i = 0; i < 20; i++){
            fscanf(w, "%s ",h[i].randomWord);
        }
    
      
    //printf("%s\n", h[2].randomWord);
      //printf("%s\n", h[5].randomWord);
      
      randNum = (rand() % (19));
        strcpy(word,h[randNum].randomWord);
        for(i = 0; i < 9; i ++){
            randNum2 = (rand() % (strlen(word)));
            word[randNum2] = '-';
        }
    length = strlen(h[randNum].randomWord);
    
    while(tries > 0){
        printf("Guess the word: %s\n", word);
        printf("Do you want to guess the letter or word? Provide your choice - \nw - guess the word\nl - guess the letter\n");
        fflush(stdout);
    scanf(" %c", &userChoice);
        
        if(userChoice == 'w'){
            printf("Enter the word(make sure to have the same length):\n");
            scanf("%s", userWord);
            //printf("%s", userWord);
            
            if(strcmp(userWord, h[randNum].randomWord) == 0){
                printf("Congralatuations! You have correctly guessed the word.\n\n");
                //printf("You earn 10 lifeline points.\n");
                lifeline = lifeline + 10;
                break;
            }
            else{
                printf("Sorry try again.\n");
                tries--;
                printf("Tries Left: %d\n", tries);
            }
            
        }


else if (userChoice == 'l' ){
     printf("Please enter a letter: ");
    fflush(stdout);
    scanf(" %c", &userletter);

    
    for(int k=0; k < length; k++) {
      if (h[randNum].randomWord[k] == userletter) {
	   word[k] = h[randNum].randomWord[k];
	   printf("Yay! You got it.\n");
	    exit;
      }
      else{
          over = over + 1;
      }

    }
   
   
	   
  if (over == length){
    printf("Sorry try again\n");
           tries--;
         printf("Tries Left: %d\n", tries);

}
    
    //printf("%s\n", word);
    printf("\n");

   
}




       else{
           printf("invalid input, please try again\n");
           fflush(stdout);
    scanf(" %c", &userletter);
       }
       
    }




        if(tries == 0){
          
            if(strcmp(userWord, h[randNum].randomWord) != 0){
                printf("Game Over.\n");
            }
            
        }
        }
        
        else if(userInput == 3){
            tries = 5;
            printf("Starting monster battle!\n");
            while(tries > 0){
                printf("You have %d tries\nEnter 1 to attack or 2 to defend: ", tries);
                scanf("%d", &userFight);
                if(userFight == 1){
                    if(rand()%2 == 0){
                        printf("Attack successful, gain 10 lifepoints for defeating monster!\n\n");
                        attack = 1;
                        lifeline+=10;
                        tries = 0;
                    }
                    else{
                        printf("Attack failed, lose 2 tries\n");
                        tries-=2;
                    }
                }
                else if(userFight == 2){
                    if(rand()%2 == 0){
                        printf("Blocked successfully! Gain one more try!\n");
                        tries++;
                    }
                    else{
                        printf("Block failed, lose 2 tries\n");
                        tries -= 2;
                    }
                }
                else{
                    printf("Invalid input try again\n");
                }
            }
            if(attack==0){
                printf("You lost the monster battle, lose 10 lifepoints\n\n");
                lifeline-=10;
            }
        }
        else if(userInput!=4){
            printf("Invalid input, try again!\n\n");
        }
    }
    while(userInput != 4 && lifeline > 0 && lifeline < 80);
    
    if(lifeline >= 70){
        printf("You won!!\n");
        
    }
    else if(userInput!=4){
        printf("You lost, try again next time!\n");
    }
    printf("Thanks for playing!\n");
    return 0;
}
