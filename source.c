/*
	Author: Dwight Goins
	Date: 11/27/2019
	Description: 
		Loan Monthly Payment
		Calculates the monthly payment for a loan
		based on a generated amortization table
		written in C
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

// Method to calculate the monthly payments
double calculateMonthlyPayment(double principal, double interestRateAnnual, int numberOfPayments, double* monthlyInterestRate);

void printAmortizationTable(double principal, double interestRateAnnual, int numberOfPayments);

int main()
{
	double purchasePrice = 0.0;
	double downPayment = 0.0;
	double annualInterestRate = 0.0;
	int totalNumberOfPayments = 0;

	printf("Please enter in the purchase price:>");

	int success = scanf("%lf", &purchasePrice);

	printf("Please enter in the down payment> ");
	success = scanf("%lf", &downPayment);

	printf("Please enter in the annual interest rate> ");
	success = scanf("%lf", &annualInterestRate);
	annualInterestRate /= 100;
	printf("Please enter in the total number of payments> ");
	success = scanf("%d", &totalNumberOfPayments);

	double amountBorrowed = purchasePrice - downPayment;
	double monthlyRate = 0.0;

	double payments = calculateMonthlyPayment(amountBorrowed, annualInterestRate, totalNumberOfPayments, &monthlyRate);

	printf("\n***************************\n\nThe Amount Borrowed:\t%.2f\nThe Monthly Payments are:\t%.2f\n\n\n***************************\n\n", amountBorrowed, payments);

	printf("\n***************************\n\nPrinting out Amortization Table\n\n***************************\n");
	printAmortizationTable(amountBorrowed, annualInterestRate, totalNumberOfPayments);
	printf("\n\n***************************\n");

	return 0;
}

/*

	Uses the formula payments =  monthly Interest * Principal / ( 1 -   raise ( 1 + monthly interest) to the power of (-number of payments) 

*/
double calculateMonthlyPayment(double principal, double interestRateAnnual, int numberOfPayments, double * monthlyInterestRate)
{
	double payment = 0.0;
	*monthlyInterestRate = interestRateAnnual / 12.0;
	payment = (*monthlyInterestRate * principal) / ( 1 -  ( pow((1 + *monthlyInterestRate), (-numberOfPayments) )) );	
	return payment;
}

/*
	simply prints out the payment schedule to screen

*/
void printAmortizationTable(double principal, double interestRate, int numberOfPayments)
{

	double monthlyRate = 0.0;
	double payments = calculateMonthlyPayment(principal, interestRate, numberOfPayments, &monthlyRate);
	double wholeInterest = interestRate *= 100;
	int term = numberOfPayments;

	printf("Principal:\t%.2f\t\tMonthly Payments:\t%.2f\nAnnual Interest:\t%.2f\t\tTerm %d months\n", principal, payments, wholeInterest, term);

	printf("\nPayment\t\tInterest\t\tPrincipal\t\tPrincipal Balance\n-------------------------------------------------------------------------------------------------------------------\n");
	double principalBalance = principal;

	for (int i = 0; i < term; i++)
	{
		double calculatedInterest = monthlyRate * principalBalance;
		double principalPayment = payments - calculatedInterest;
		printf("%d\t\t%.2f\t\t\t%.2f\t\t\t%.2f\n", i + 1, calculatedInterest, principalPayment, principalBalance);
		principalBalance -= principalPayment;
	}

}