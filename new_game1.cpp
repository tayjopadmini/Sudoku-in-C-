#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include "Board1.cpp"

using namespace std;

int load_game();

int new_game()//new game function
{
	int level;
	int numbers[81];
	int solutions[81];
	int i=0;
	int n=0;
	char ch;
        char choice;
        int arr[9][9];
	menu:
	cout<<"Select level from 1 to 10. Enter any other key to quit."<<endl;
	cin>>level;
        std::ifstream myfile;//creates object for game file
	std::ifstream mysolfile;//creates object for solution file
	switch(level)//opens appropriate gam file and solution file
	{
		case 1: myfile.open("levelone.txt");
                	mysolfile.open("sol1.txt");
			break;
		case 2: myfile.open("leveltwo.txt");
                	mysolfile.open("sol2.txt");
                	break;
		case 3: myfile.open("levelthree.txt");
                	mysolfile.open("sol3.txt");
                	break;
		case 4: myfile.open("levelfour.txt");
                	mysolfile.open("sol4.txt");
                	break;
		case 5: myfile.open("levelfive.txt");
                	mysolfile.open("sol5.txt");
                	break;
 		case 6: myfile.open("levelsix.txt");
                        mysolfile.open("sol6.txt");
                        break;
 		case 7: myfile.open("levelseven.txt");
                        mysolfile.open("sol7.txt");
                        break;
 		case 8: myfile.open("leveleight.txt");
                        mysolfile.open("sol8.txt");
                        break;
		case 9: myfile.open("levelnine.txt");
                        mysolfile.open("sol9.txt");
                        break;
 		case 10: myfile.open("levelten.txt");
                        mysolfile.open("sol10.txt");
                        break;
		case 0: return 0;//case to quit
		default:cout<<"Incorrect choice. Please select level again"<<endl;//case for wrong entry
			goto menu;
                	break;
	}

	while (myfile.get(ch))//reads numbers from game file
        {
        	if(ch == '\t')
                break;
                numbers[i]=(ch-'0');//stores the numbers in a 1D array
                i++;
        }
        i=0;

	Initial_board b1(9,9);//creates an initial_board object to show the player what the game looks like
	int **sudok;//creates a pointer to a 2D integer array
	sudok= new int*[9];
	for(i=0;i<9;i++)//creating a 2D array dynamically
	sudok[i]=new int[9];
	sudok =  b1.create_board(numbers,81,level);//calls th ecreate_board funtion of initial_board class
	b1.display_board(sudok);//displays board to user
	i=0;

        while (mysolfile.get(ch))//reads numbers from solution file
        {
                if(ch == '\t')
                break;
                solutions[i]=(ch-'0');//reads all numbers from solution file to 1D array
                i++;
        }
	i=0;

	Initial_board sol1(9,9);
	int **sudoksol;//creates an initial_board function to show player the solution
	sudoksol= new int*[9];//creates a pointer to the 2 D integer array
	for(i=0;i<9;i++)//dynamically creating  a 2D array
	sudoksol[i]=new int[9];
	sudoksol =  sol1.create_board(solutions,81,level);//calls the create board funtion of the initial_board class


	cout<<"Up for the challenge? Enter Y to go on or any other key to go back"<<endl;//asks user if he is okay with the current level
	cin>>choice;
	if(choice=='y'||choice=='Y')//if yes
	{
		cout<<"OKAY! Begin"<<endl;
		Play_board b2(9,9);//creates an object for play_board class
		b2.display_board(sudok);//calls the diaply board funtion
		b2.fix_values(sudok);//calls the fix values function to check which values are entered before
		b2.play(sudok,sudoksol);//calls the play funtion of play_board class

	}
	else
	{
	cout<<"Do you want to choose another level or quit? L or Q"<<endl;//asks user if he wants to select another level
	cin>>choice;
	switch (choice)
	{
		case'l'://case choose another level
		case'L':goto menu;
			break;
		case'q'://case quit
		case'Q':myfile.close();//closes game file
			mysolfile.close();//
			cout<<"Closing files..."<<endl;
			delete[] sudoksol;//deletes the arrays created on heap
			delete[] sudok;
			cout<<"Deleting board..."<<endl;
			return 0;
			break;
		default:cout<<"Incorrect choice! Select again"<<endl;//case for incorrect choice
			choice=' ';
			goto menu;
			break;
		}
	}
return 0;
}

int load_game()//load game function
{
        int level;
        int numbers[81];
        int solutions[81];
        int i=0;
        int n=0;
        char ch;
        char choice;
	char p;
        int arr[9][9];
        std::ifstream myfile;//creates object for game file
        std::ifstream mysolfile;//creates object for solution file
	std::ifstream levelfile;//creates object for level file
	myfile.open("saved_game.txt");//opens the saved game
	levelfile.open("level_game.txt");//opens the file that stores the level that was saved previosly

	while (levelfile.get(ch))//reads value of the level of the game savel
        {
                if(ch == '\t')
                break;
                level=(ch-'0');

        }
	//opens appropriate level's solution file
	if(level==1)
        {

                mysolfile.open("sol1.txt");
 	}

	if(level==2)
        {

                mysolfile.open("sol2.txt");
        }

	if(level==3)
        {

                mysolfile.open("sol3.txt");
        }

	if(level==4)
        {

                mysolfile.open("sol4.txt");
        }

	if(level==5)
        {

                mysolfile.open("sol5.txt");
        }
       while (myfile.get(ch))//reads the game file that was saved
        {
                if(ch == '\t')
                break;
                numbers[i]=(ch-'0');//stores the values into a 1D array
                i++;
        }
        i=0;

	Initial_board b1(9,9);//creates an object for initial_board class for game board
	int **sudok;//creates a pointer for a 2D array
	sudok= new int*[9];
	for(i=0;i<9;i++)//creates a dynamic array
	sudok[i]=new int[9];
	sudok =  b1.create_board(numbers,81,level);//calls create board function
	b1.display_board(sudok);

	i=0;

        while (mysolfile.get(ch))//reads the solution file
        {
                if(ch == '\t')
                break;
                solutions[i]=(ch-'0');//stores the values into a 1D array
 		i++;
        }
 	i=0;

	Initial_board sol1(9,9);//creates an object for initial_board class for solution board
	int **sudoksol;//creates a pointer for 2 D array
	sudoksol= new int*[9];
	for(i=0;i<9;i++)//creates a dynamic array
	sudoksol[i]=new int[9];
	sudoksol =  sol1.create_board(solutions,81,level);//calls create function for solution board


	cout<<"Want to continue? Enter Y or N"<<endl;//asks the user if he interested in continuing
	cin>>choice;
	if(choice=='y'||choice=='Y')//if he wants to go ahead playing
	{
		cout<<"OKAY! Begin"<<endl;
		Play_board b2(9,9);//creates play_board function
		b2.display_board(sudok);//diaplys game board
		b2.fix_values(sudok);//calls fixed values function
		b2.play(sudok,sudoksol);//calls play function

	}
	else
	{
		cout<<"Do you want to start a new game or leave? N for new game. Any other key to exit"<<endl;
		cin>>p;
		if (p=='n'||p=='N')
			new_game();
		else
		{
			return 0;
			myfile.close();
			mysolfile.close();
		}
	}
return 0;
}
