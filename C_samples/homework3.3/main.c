#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


double getInputDouble(double variableToStoreIn, const char* prompt) {
  printf("%s", prompt);
  scanf(" %lf", &variableToStoreIn);
  return variableToStoreIn;
}

// calc probability from each stage

double calcProbForEachTurn(double numCardsToDraw, double numUndesiredCardsInDeck, double totalCards) {
  int i;
  double probNotDesiredCard;
  probNotDesiredCard = 1.0 ;

  for (i = 1; i <= numCardsToDraw; i++) {
    probNotDesiredCard = (numUndesiredCardsInDeck / totalCards) * probNotDesiredCard;
    numUndesiredCardsInDeck = numUndesiredCardsInDeck - 1;
    totalCards = totalCards - 1;
  }
  return probNotDesiredCard;
}

double calcInitialDrawProb(double totalCards, double copiesOfDesiredCard, double handSize){
  double numUndesiredCardsInDeck, probNotDesiredCard;
  numUndesiredCardsInDeck = totalCards - copiesOfDesiredCard;

  probNotDesiredCard = calcProbForEachTurn(handSize, numUndesiredCardsInDeck, totalCards) ;

  return probNotDesiredCard;
}

double calcMulliganProb(double totalCards, double copiesOfDesiredCard, double handSize, double mulliganNum){
  double numUndesiredCardsInDeck;
  double totalCardsInDeck;
  double cardsToDraw;
  double probNotDesiredCard;

  cardsToDraw = mulliganNum;
  totalCardsInDeck = totalCards - handSize; // hand size includes num you are mulliganing from the previous stage
  numUndesiredCardsInDeck = totalCardsInDeck - copiesOfDesiredCard;

  probNotDesiredCard = calcProbForEachTurn(cardsToDraw, numUndesiredCardsInDeck, totalCardsInDeck);

  return probNotDesiredCard;

}
double calcDrawEachTurnProb(double totalCards, double copiesOfDesiredCard, double handSize, double mulliganNum, double turnToDrawBy) {
  double numUndesiredCardsInDeck;
  double totalCardsInDeck;
  double probNotDesiredCard;

  totalCardsInDeck = totalCards - handSize;
  numUndesiredCardsInDeck = totalCardsInDeck - copiesOfDesiredCard;

  probNotDesiredCard = calcProbForEachTurn(turnToDrawBy, numUndesiredCardsInDeck, totalCardsInDeck);

  return probNotDesiredCard;
}
// calc total probability
double calcTotalProb (double initialDrawProb, double mulliganProb, double drawEachTurnProb, double turnToDrawBy, double mulliganNum) {
  double totalProb;
  totalProb = 1 - (initialDrawProb * mulliganProb * drawEachTurnProb);
  printf("The probability of drawing at least one of the cards by turn %.0lf given you mulliganed %.0lf cards is %.2lf\n", turnToDrawBy, mulliganNum, totalProb);
  return totalProb;
}

int main() {

  double totalCards, copiesOfDesiredCard, handSize, mulliganNum, turnToDrawBy;
  double initialDrawProb, mulliganProb, drawEachTurnProb;

  totalCards = 0;
  copiesOfDesiredCard =0;
  handSize=0;
  mulliganNum=0;
  turnToDrawBy=0;


  // get input
  totalCards = getInputDouble(totalCards, "Enter how many total cards there are in the deck: ");
  copiesOfDesiredCard = getInputDouble(copiesOfDesiredCard, "Enter how many copies of the card that you are looking for are in the deck: ");
  handSize = getInputDouble(handSize, "Enter your initial hand size: ");
  mulliganNum = getInputDouble(mulliganNum, "Enter how many cards you are mulliganing: ");
  turnToDrawBy = getInputDouble(turnToDrawBy, "Enter what turn you want to draw the card by: ");

  initialDrawProb = calcInitialDrawProb(totalCards, copiesOfDesiredCard,handSize);
  mulliganProb = calcMulliganProb(totalCards, copiesOfDesiredCard, handSize, mulliganNum);
  drawEachTurnProb = calcDrawEachTurnProb(totalCards, copiesOfDesiredCard, handSize, mulliganNum, turnToDrawBy);

  calcTotalProb(initialDrawProb, mulliganProb, drawEachTurnProb, turnToDrawBy, mulliganNum);



  return 0;
}