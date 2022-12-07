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

/*
--- Part Two ---
The Elf finishes helping with the tent and sneaks back over to you. "Anyway, the second column says how the round needs to end: X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win. Good luck!"

The total score is still calculated in the same way, but now you need to figure out what shape to choose so the round ends as indicated. The example above now goes like this:

In the first round, your opponent will choose Rock (A), and you need the round to end in a draw (Y), so you also choose Rock. This gives you a score of 1 + 3 = 4.
In the second round, your opponent will choose Paper (B), and you choose Rock so you lose (X) with a score of 1 + 0 = 1.
In the third round, you will defeat your opponent's Scissors with Rock for a score of 1 + 6 = 7.
Now that you're correctly decrypting the ultra top secret strategy guide, you would get a total score of 12.

Following the Elf's instructions for the second column, what would your total score be if everything goes exactly according to your strategy guide?
*/
#include <iostream>
#include <fstream>
using namespace std;

/* These methods solves part 1 - but are revised for part 2
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

*/

int choicePoints(char letter){
  switch(letter) {
    case 'X':
    case 'A':
      return 1;
    case 'Y':
    case 'B':
      return 2;
    case 'Z':
    case 'C':
      return 3;
    default :
      cout << "error";
      return -100000;
  }
}

int outcomePoints(char opponent, char outcome) {
  // X = Lose, Y = Draw, Z = Win

  // If draw, we need to match the hand and add 3
  if(outcome == 'Y') {
    return choicePoints(opponent) + 3;
  }

  // if lose, we need to find losing reaction
  else if(outcome == 'X'){
    char you;
    if(opponent == 'A') { // R
      return choicePoints('Z');  // S
    }
    else if(opponent == 'B') {  // P
      return choicePoints('X'); // R
    }
    else {  //S
      return choicePoints('Y'); // P
    }
  }
  // if win, we need to find winning reaction and add 6
  else{
    char you;
    if(opponent == 'A') { // R
      return choicePoints('Y') + 6;  // P
    }
    else if(opponent == 'B') {  // P
      return choicePoints('Z') + 6; // S
    }
    else {  //S
      return choicePoints('X') + 6; // R
    }
  }
  cout << "error";
  return -100000;
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
    sum += (outcomePoints(opponent, you));
  }

  cout << sum;

  // Close the file
  MyReadFile.close();
}