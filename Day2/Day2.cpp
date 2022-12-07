/*
"The first column is what your opponent is going to play: A for Rock, B for Paper, and C for Scissors. 
The second column--" Suddenly, the Elf is called away to help with someone's tent.

The second column, you reason, must be what you should play in response:
 X for Rock, Y for Paper, and Z for Scissors. Winning every time would be suspicious, 
 so the responses must have been carefully chosen.

The winner of the whole tournament is the player with the highest score. 
Your total score is the sum of your scores for each round. The score for a single round is the score
 for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus the score
  for the outcome of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).
*/
#include <iostream>
#include <fstream>
using namespace std;

int outcomePoints(char opponent, char you) {
  // DRAW
  if(opponent == 'A' && you == 'X' || opponent == 'B' && you == 'Y' || opponent == 'C' && you == 'Z') {
    return 3;
  }
  // LOSE
  if(opponent == 'A' && you == 'Z' || opponent == 'B' && you == 'X' || opponent == 'C' && you == 'Y'){
    return 0;
  }
  // WIN
    if(opponent == 'A' && you == 'Y' || opponent == 'B' && you == 'Z' || opponent == 'C' && you == 'X'){
    return 6;
  }
  cout << "error";
  return -100000;
}

int choicePoints(char letter){
  switch(letter) {
    case 'X':
      return 1;
    case 'Y':
      return 2;
    case 'Z':
      return 3;
    default :
      cout << "error";
      return -100000;
  }
}

int main() {


  // Create a text string, which is used to output the text file
  string myText;

  // Read from the text file
  ifstream MyReadFile("guide.txt");

  int sum = 0;
  // Use a while loop together with the getline() function to read the file line by line
  while (getline (MyReadFile, myText)) {
    char you;
    char opponent;
    // Output the text from the file
    if(myText.length() >= 3) {
      opponent = myText[0];
      you = myText[2];
    }
    sum += (outcomePoints(opponent, you) + choicePoints(you));
  }

  cout << sum;

  // Close the file
  MyReadFile.close();
}