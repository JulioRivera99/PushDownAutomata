/**
Name: Julio Rivera
Class: CS 341
Proffesoor: Marvin
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stack> 
#include <ctype.h>

using namespace std;

void PDA();


/******************************************************************
The main Function will be used to ask the userif he wants to enter
a string  if the user chooses yes then we will call the
DFA function if the user declines the program will terminate.
******************************************************************/
int main(int argc, char *argv[])
{
	string asn;// Variable used to decide if the program will run

	cout << "Do you want to enter a string?\n y for yes, or n for no \n";
	getline(cin, asn);

	while ((asn != "y") && (asn != "n"))//loop to make sure the user only enters y or n
	{
		cout << "Please enter either y or n \n";
		getline(cin, asn);
	}

	while (asn == "y"){

		PDA();// function call to where the DFA is to be executed

		cout << "Do you want to enter a string?\n y for yes, or n for no \n";
		getline(cin, asn);

		while ((asn != "y") && (asn != "n"))
		{
			cout << "Please enter either y or n \n";
			getline(cin, asn);
		}
	};

	return 0;
}

/***************************************************************************
This is the function where the PDA will be executed to do this I used a
switch statement to determine what action the PDA will use depending on
the character that the automata is working on. Each different state compares
the current character of the string with the options available to said state
and then goes sends the next character to the corresponding state.
***************************************************************************/

void PDA(){
	string str;
	std::stack<int> mystack;// creating the stack
	int state = 0;// initializing the state to the initial state q0
	ofstream output;
	output.open("output.txt", ios::out | ios::app | ios::ate);//opening the file where we will write the output of the machine
	//the file will append the output to the back of the file
	cout << "Please enter a string \n";
	getline(cin, str);//getting the string that the PDA will work on from the user

	//Couple of messages telling the user the string that the progam is workoing on and the initial state of the machine
	cout << "The string to be worked on is \n" << str << endl;
	output << "The string to be worked on is \n" << str << endl;
	cout << "The current state is q" << state << endl;
	output << "The current state is q" << state << endl;

	//loop that will go through each individual character of the string and work on evry one of them there is a switch
	//statement that will be used as the PDA if the string contains any characters that are not in the language or that don't
	//follow the rules of the DFA the switch will default to the trap state(state 5)
	for (int i = 0; i < str.length(); i++){
		switch (state){
		case 0:
			if (str[i] == '$'){
				mystack.push(36);//pushing the ASCII value of $
				state = 1;
			}
			else
				state = 5;
			break;
		case 1:
			if (str[i] == '('){
				mystack.push(40);// pushing the ASCII value of (
			}
			else if ('a' <= str[i] && 'z' >= str[i])
				state = 2;
			else
				state = 5;
			break;
		case 2:
			if (('a' <= str[i] && 'z' >= str[i]) || ( ('0' <= str[i] && str[i] <= '9') || str[i] == '_'))
				state = 2;
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
				state = 1;
			else if (str[i] == '('){
				mystack.push(40);
				state = 1;
			}
			else if (str[i] == ')' && mystack.top() == 40){
				mystack.pop();
				state = 3;
			}
			else if (str[i] == '$' && !mystack.empty()){
				mystack.pop();
				if (mystack.empty())
					state = 4;
			}
			else
				state = 5;
			break;
		case 3:
			if (str[i] == ')' && mystack.top() == 40)
				mystack.pop();
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
				state = 1;
			else if (str[i] == '$' && !mystack.empty()){
				mystack.pop();
				if (mystack.empty())
					state = 4;
			}
			else
				state = 5;
			break;
		default:
			state = 5;
		}
		
		//Here we are telling the user the current character being worked on and the current state on the machine
		//We are also saving this to an output file
		cout << "The character that was just processed was " << str[i] << endl;
		output << "The character that was just processed was " << str[i] << endl;
		cout << "The current state is q" << state << endl << endl;
		output << "The current state is q" << state << endl << endl;
	}

	//this if else statement checks if the string that the user entered ended on one of the final/acceptance states of the
	//PDA, then proceeds to inform the user if the string was accepted and writes the output to a file
	if (state == 4){
		cout << "The string " << str << " is accepted in the language \n \n";
		output << "The string " << str << " is accepted in the language \n \n";
	}
	else{
		cout << "The string " << str << " is not accepted in the language \n \n";
		output << "The string " << str << " is not accepted in the language \n \n";
	}

	output.close();
}