#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

// input validation functions

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;

  do{
    scanf("%c", &character);
    if(!isspace(character)){
      formatIsGood = false;
    }
    //formatIsGood = formatIsGood && isspace(character);
    //formatIsGood = isspace(character) ? formatIsGood : false;
  }while(character != '\n');

  return formatIsGood;

}

int getValidInt(const char* prompt){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num);
  }while(!(isValidFormat(numArgsRead, numArgsNeeded) && num >= 0));

  return num;
}

double getValidDouble(const char* prompt){
  double num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %lf", &num);
  }while(!(isValidFormat(numArgsRead, numArgsNeeded) && num >= 0.0));
  return num;
}

int getValidIntInRange(const char* prompt, int lowerBound){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num);
  }while(!(isValidFormat(numArgsRead, numArgsNeeded) && num >= lowerBound));

  return num;
}

void checkInvestmentGreaterThanMinPayment(double investmentMoney, double minimumPayment){
  if (investmentMoney < minimumPayment){
    printf("You didn't set aside enough money to pay off our loans. Ending program.\n");
    exit(0);
  }
}

// how much money you will make if you invest this much money over this many years
// takes monetly interst rate and num of years

double investmentReturn(double monthlyRateOfReturn, int numMonths, double investmentMoney) {
  int i ;
  double moneyReturn = investmentMoney;
  for (i = 0; i < (numMonths) ; ++i) {
    moneyReturn += (moneyReturn * monthlyRateOfReturn);
    moneyReturn += investmentMoney;
  }
  return moneyReturn;
}

// how many years it takes to pay off loan based on monthly payment
int monthsToPayOffLoan(double loansAmount, double monthlyPayment, double interestRateMonthly) {
  int months = 0;
  while (loansAmount > 0) {
    months = months + 1;
    loansAmount += (loansAmount * interestRateMonthly);
    loansAmount = loansAmount - monthlyPayment;
  }
  return months;
}


// payLoanOffFirst
double payLoanFirst(double investmentMoney, double loansAmount, double loanInterestRateMonthly,int currentAge,int retirementAge, double investmentInterestRateMonthly ) {
  double investmentreturn = 0;

  int m = 0; // count the # of months it takes to pay off the loan
  double monthlyPayment = investmentMoney;
  double moneyToInvest;

  // pay max against the loan every month until loan is payed.
  while (loansAmount > 0) {
    loansAmount = loansAmount + (loansAmount * loanInterestRateMonthly); // add compounded interest for the month
    if (loansAmount >= monthlyPayment) {
      loansAmount = loansAmount - monthlyPayment; // subtract monthly payment from loan amount
    }
    else {
      // the loan amount is less then our monthly payment then figure out how much is left on this last month after we pay the loan amount
      // and invest that.
      moneyToInvest = monthlyPayment - loansAmount;
      investmentreturn = investmentreturn + (investmentreturn * investmentInterestRateMonthly);     // add interest to investmentreturn
      investmentreturn = investmentreturn + moneyToInvest;
      loansAmount = 0;
    }
    m = m + 1; // increment the month
  }

  // calculate number of months left to retirement based on how may months it took to pay off the loan.
  int monthsLeftToRetirement = ((retirementAge - currentAge) * 12) - m;

  // invest maximum for the months you have left in retirement
  moneyToInvest = investmentMoney;
  for (int i = 0; i < monthsLeftToRetirement; i++) {
    investmentreturn = investmentreturn + (investmentreturn * investmentInterestRateMonthly);     // add interest to investmentreturn
    investmentreturn = investmentreturn + moneyToInvest;
  }

  return investmentreturn;

}

double payMinimum(double investmentMoney, double loansAmount, double loanInterestRateMonthly,double minimumPayment, int currentAge,int retirementAge, double investmentInterestRateMonthly) {
  double investmentreturn = 0;
  int monthsToRetirement = (retirementAge - currentAge) * 12;

  int m = 0; // count the # of months it takes to pay off the loan
  double monthlyPayment = minimumPayment;
  double moneyToInvest;
  double extraOnLastMonth;

  // pay min against the loan every month, and invest the rest until the loan is payed off.
  while (loansAmount > 0) {
    // pay off loan figure out what is left
    loansAmount = loansAmount + (loansAmount * loanInterestRateMonthly); // add compounded interest for the month
    if (loansAmount >= monthlyPayment) {
      loansAmount = loansAmount - monthlyPayment; // subtract monthly payment from loan amount
      moneyToInvest = investmentMoney - monthlyPayment;
    }
    else {
      // the loan amount is less then our monthly payment then figure out how much is left on this last month after we pay the loan amount
      // then set the loan amount to zero taking us out of the loop;
      moneyToInvest = investmentMoney - loansAmount;
      loansAmount = 0;
    }

    // invest the rest
    investmentreturn = investmentreturn + (investmentreturn * investmentInterestRateMonthly);
    investmentreturn = investmentreturn + moneyToInvest;

    m = m + 1; // increment the month
    if (m >= monthsToRetirement) {
      printf("Warning! After you retire you will still have $%.2lf in loans left.\n", loansAmount);
      break;
    }
  }

  // calculate number of months left to retirement based on how may months it took to pay off the loan.
  int monthsLeftToRetirement = ((retirementAge - currentAge) * 12) - m;

  // invest maximum for the months you have left in retirement
  int i;
  moneyToInvest = investmentMoney;
  for (i = 0; i < monthsLeftToRetirement; i++) {
    investmentreturn = investmentreturn + (investmentreturn * investmentInterestRateMonthly);     // add interest to investmentreturn
    investmentreturn = investmentreturn + moneyToInvest; // add money to invest
  }

  return investmentreturn;
}


// compare the two options, print the solutions
void compareScenarios(double investmentMoney, double loansAmount, double loanInterestRateMonthly,double minimumPayment, int currentAge,int retirementAge, double investmentInterestRateMonthly) {

  double payLoanFirstScenario;
  double payMinimumScenario;

  payLoanFirstScenario = payLoanFirst(investmentMoney,  loansAmount,  loanInterestRateMonthly, currentAge, retirementAge,  investmentInterestRateMonthly);
  payMinimumScenario = payMinimum(investmentMoney,  loansAmount,  loanInterestRateMonthly, minimumPayment,  currentAge, retirementAge,  investmentInterestRateMonthly);

  if (payMinimumScenario > payLoanFirstScenario) {
    printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
    printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you payed off your loan before investing.\n", payMinimumScenario, payLoanFirstScenario);
  }
  else {
    printf("You should apply all $%.2lf towards your loan before making investments.\n", investmentMoney);
    printf("If you do you will have $%.2lf  when you retire as opposed to $%.2lf if you only made minimum payments.\n", payLoanFirstScenario, payMinimumScenario);

  }
}


int main() {
  double investmentMoney = getValidDouble("Enter how much money you will be putting towards loans/retirement each month: ");//double loansNum = getValidInt("Enter how much you owe in loans: ");
  double loansAmount = getValidDouble("Enter how much you owe in loans: ");
  double loanInterestRateMonthly = (getValidDouble("Enter the annual interest rate of the loans: ")) / 12.0;
  double minimumPayment = getValidDouble("Enter your minimum monthly loan payment: ");
  checkInvestmentGreaterThanMinPayment(investmentMoney, minimumPayment);
  int currentAge = getValidInt("Enter your current age: ");
  int retirementAge = getValidIntInRange("Enter the age you plan to retire at: ", currentAge);
  double investmentInterestRateMonthly = (getValidDouble("Enter the annual rate of return you predict for your investments: ")) / 12.0;

  compareScenarios( investmentMoney, loansAmount, loanInterestRateMonthly, minimumPayment, currentAge, retirementAge, investmentInterestRateMonthly);

  return 0;
}