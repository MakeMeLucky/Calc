// 3 приоритет * и /
// 2 приоритет - и +
// скобки ()

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
constexpr auto NMAX = 15;
char ch;

struct Numerals {
	float num[NMAX];
	int top;
};

struct Operation {
	char operat[NMAX];
	int top;
};

void initNumerals(struct Numerals *stk);
void pushNumerals(struct Numerals *stc, float value);
float popNumerals(struct Numerals *stc);
void initOperation(struct Operation *stk);
void pushOperation(struct Operation *stc, char value);
char popOperation(struct Operation *stc);
float peek(const Numerals *stc);
char peekOp(const Operation *stc);
int returnPrior(char p);
int isempty(struct Operation *stc);
float check(char c, float x1, float x2);
void equal(struct Numerals *stk, struct Operation *operation, char ch);



// 40 ( , 41 ), 42 *, 43 +, 45 -, 47 / ;
int main()
{
	Numerals numerals;
	initNumerals(&numerals);
	Operation operation;
	initOperation(&operation);

	float sum = 0;
	int prior = 0;
	int priorStc = 0;
	unsigned i = 0;
	char *p = new char[256];

	cin.getline(p, 256);
	// system("cls");

	while (i < strlen(p)) {


		if(47 < p[i] && p[i] < 58){
			char *push = new char[256];
			int k = 0;
			while (47 < p[i] && p[i] < 58) {

				push[k] = p[i];
				k++;
				i++;
			}
			float t = atof(push);

			pushNumerals(&numerals, t); // в стек чисел
			delete[] push;
		}

		ch = p[i];


		if (ch == 40) pushOperation(&operation, ch);

		else if (ch == 41) {
			while (peekOp(&operation) != 40) {

				float x1 = popNumerals(&numerals);
				float x2 = popNumerals(&numerals);

				sum = check(popOperation(&operation), x2, x1);
				pushNumerals(&numerals, sum);


			}
			popOperation(&operation);
		}

		else if (ch == 42) equal(&numerals, &operation, ch);	//	*
		else if (ch == 43) equal(&numerals, &operation, ch);//	+
		else if (ch == 45) equal(&numerals, &operation, ch);//	-
		else if (ch == 47) equal(&numerals, &operation, ch);//  /

		i++;
	}

	while (isempty(&operation) != 1) {
		float x1 = popNumerals(&numerals);
		float x2 = popNumerals(&numerals);

		sum = check(popOperation(&operation), x2, x1);
		pushNumerals(&numerals, sum);
	}

	cout << peek(&numerals);
	delete[] p;
}

void equal(struct Numerals *stcN, struct Operation *stcO, char ch) {
	float sum = 0;
	int prior;
	int priorT;
	while (isempty(stcO) != 1) {

		if (peekOp(stcO) == 40) break;

		prior = returnPrior(ch);

		priorT = returnPrior(peekOp(stcO));


		if (priorT >= prior) {


			float x1 = popNumerals(stcN);
			float x2 = popNumerals(stcN);


			sum = check(popOperation(stcO), x2, x1);

			pushNumerals(stcN, sum);

		}
		else break;
	}

	pushOperation(stcO, ch);

}

float check(char c, float x2, float x1) {
	float sum = 0;
	switch (c)
	{
	case 42: sum = x2 * x1; break;
	case 43: sum = x2 + x1; break;
	case 45: sum = x2 - x1; break;
	case 47: sum = x2 / x1; break;
	}
	return sum;
}

int returnPrior(char p) {
	int x = 0;
	switch (p) {
	case 47: x = 2; break;
	case 42: x = 2; break;
	case 45: x = 1; break;
	case 43: x = 1; break;
	case 40: x = 0; break;
	case 41: x = 0; break;
	}
	return x;
}

void initNumerals(struct Numerals *stk) {
	stk->top = 0;
}

void pushNumerals(struct Numerals *stc, float value) { //добавление
	if (stc->top >= NMAX) {
		exit(SW_STACKOVERFLOW);
	}
	stc->num[stc->top] = value;
	stc->top++;
}

float popNumerals(struct Numerals *stc) { // удаление
	if (stc->top == 0) {
		exit(STACK_UNDERFLOW);
	}
	stc->top--;
	return stc->num[stc->top];
}

void initOperation(struct Operation *stk) {
	stk->top = 0;
}

void pushOperation(struct Operation *stc, char value) { //добавление
	if (stc->top >= NMAX) {
		exit(SW_STACKOVERFLOW);
	}
	stc->operat[stc->top] = value;
	stc->top++;
}

char popOperation(struct Operation *stc) { // удаление
	if (stc->top == 0) {
		exit(STACK_UNDERFLOW);
	}
	stc->top--;
	return stc->operat[stc->top];
}

float peek(const Numerals *stc) {
	if (stc->top <= 0) {
		exit(STACK_UNDERFLOW);
	}
	return stc->num[stc->top - 1];
}

char peekOp(const Operation *stc) {
	if (stc->top <= 0) {
		exit(STACK_UNDERFLOW);
	}
	return stc->operat[stc->top - 1];
}


int isempty(struct Operation *stc) {
	if ((stc->top) == 0)    return(1);
	else return(0);
}


