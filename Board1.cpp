#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;

int level;

class Board //Virtual class to declare the functions required for inherited classes
{
public:
	int row;
	int col;
	int sud[9][9];
	Board(int r, int c) //Base class constructor
	{
 		row=r;
		col=c;
	}
	~Board() //Base class destructor
	{}
	virtual int** create_board(int a[],int length,int leveln)
    	{ //Base class create_board function
	return 0;
	}
	virtual void display_board(int **sud)
	{ //Base class display_board function
	}
};


class Initial_board:public Board //Initial_board class that inherits the virtual board class
{
public:
	Initial_board(int row, int col):Board(row,col)
	{
	//Child class inherits base class constructor
	}
	~Initial_board()
	{
	cout<<"Deleting boards..."<<endl; //Child class destructor
	}
    	int** create_board(int a[],int length,int leveln) // create_board function to generate board
    	{
	level=leveln;
        int i=0;
	int j=0;
	int** sudo =0;
	sudo = new int*[9];
	for(i=0;i<9;i++) //recieves a 1-D array and converts it to a 2-D array
		{
		sudo[i]=new int[9];
		for(j=0;j<9;j++)
		sudo[i][j]=a[9*i + j];
		}

	return sudo;

}

void display_board(int **sud) //Function to display the board to user
{
        cout<<"Game Board Level "<<level<<endl;
        int i=0;
        int j=0;
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {

            	cout<<sud[i][j]<<" ";
	    	if((j+1)%3==0)
            	cout<<"|"<<" ";
            }

            cout<<"\n";
            if((i+1)%3==0)
		cout<<"__________________________"<<"\n"<<endl;
        }
    }

};


class Play_board:public Board //Second child class that inherits from virtual class
{
public:

	Play_board(int row, int col):Board(row,col) //Base class constructor inherited
	{
	}
	~Play_board() //Child class destructor
	{
		cout<<"Deleting Playing boards..."<<endl;
	}
int i;
int j;
int fix[9][9];

	void display_board(int **sud) //Displays the playing board to the user
    	{
        	cout<<"Playing board"<<endl;
		cout<<endl;
		cout<<"      1 2 3   4 5 6   7 8 9"<<endl;
		cout<<"_____________________________"<<endl;
        	for(i=0;i<9;i++)
        	{
			cout<<" "<<i+1<<" |  ";
            		for(j=0;j<9;j++)
            		{
            			cout<<sud[i][j]<<" ";
            			if((j+1)%3==0)
            			cout<<"|"<<" ";
            		}
	    		cout<<"\n";
            		if((i+1)%3==0)
           		cout<<"_____________________________"<<"\n"<<endl;

        	}
 	}

void fix_values(int **sud) //Function to check which cell values cannot be changed
{
	for(i=0;i<9;i++)
	for(j=0;j<9;j++)
	{
		if(sud[i][j]==0)
		{
			fix[i][j]=0;
		}
		else
		{
		fix[i][j]=1;
		}
	}
}

int hints(int k,int row,int col,int ** sud) //Function to generate hints
{
	int flag1=0;
	int flag2=0;
	int flag3=0;

	for(i=0;i<9;i++)
	{
		if(k!= sud[i][col]) //checks for occurance of number in given column
		{
			flag1=1; // if not present then sets flag to 1
		}
		else
		{
			flag1=0;
			break;
		}
	}
	for(j=0;j<9;j++)
	{
		if(k!= sud[row][j]) //checks for occurence of number in given row
		{
			flag2=1; //if not present then sets flag to 1
		}
		else
		{
			flag2=0;
			break;
		}
	}

	if(flag1==0 ||flag2==0)//If number has occured in either row or column then go back
	{
	return 0;
	}
	else //If it has not occured check for occurence in 3X3 box
	{
		while(col%3 != 0) //Move to first col of 3X3 box
		col--;
		while(row%3 != 0) //Move to first row of 3X3 box
		row--;
		for(i=row;i<(row+3);i++)
		for(j=col;j<(col+3);j++)
		{
			if(sud[i][j]==k)
			{
				return 0; //If number occurs then return 0 and exit
			}
			else
			{
				flag3=1;
			}
		}
	}
	if(flag1==1 && flag2==1 && flag3==1) //If all flags are 1 then the number is fit to be a  hint
	{
		return 1;
	}
	else
		return 0; //Return 0 if any of the flags are 0
}

void savefile(int **sud) //Function to save the progress of the game
{
int i,j;
ofstream myfile ("saved_game.txt"); //open file to save game played so far
if (myfile.is_open())
	{
	for(i=0;i<9;i++)
	for(j=0;j<9;j++)
	myfile << sud[i][j]; //write game so far to the file
	myfile.close(); //close the file
	}
ofstream levelfile ("level_game.txt");
	if (levelfile.is_open())
  	{
    		levelfile << level; //stores current level in another file
    		levelfile.close(); //close the file
  	}
}



int play(int **sud, int **sudsol) //Funtion to enable user to play the game
{
	int value;
	char op;
	char ch;
	int rows,cols;
	int n=0;
	int k=1;
	int res;
	int hints_arr[9];
	int num_hints=10;
	char rowc;
	char colc;
	int sum;
	float time;
	menu:
	cout<<"*********"<<"\n";
	cout<<"Game Menu"<<endl<<"\n";
	cout<<"Please select an option"<<endl<<"\n";
	cout<<"C: Continue playing game \nH: Get a hint \nS: Save your progress \nV: If you think you are done get your board checked! \nG: Giving up? Want to see the solution? \nQ: Want to quit?"<<endl;
	cin>>op;
	switch(op) // takes user input to perform action
	{
	case 'C': //case for playing
	case 'c':
		cout<<"Enter Row number and Column number of the cell you wish to change"<<endl;
		cin>>rowc>>colc; //Takes row and col value
		if(rowc<48 || rowc>57 ||colc <48 || colc>57) //checks if value entered is a character
		{
			cout<<"Enter a number!"<<endl;
			goto menu;
		}
		row=rowc-48;
		col=colc-48;
		if(row<1 || row>9 || col<1 || col>9) //checks if number is between 1 and 9
		{
			cout<<"Invalid row/col number please check"<<endl;
			goto menu;
		}
		rows=row-1;
		cols=col-1;
		if(fix[rows][cols]==1)//checks if cell entered is a fixed cell
		{
			cout<<"This is a fixed cell. You can't change it's value!"<<endl;
			goto menu;
		}
		cout<<"Enter a value between 1-9 to enter in that cell"<<endl; //If not then enter a number between 1 and 9
		cin>>value;
		if(value<1 || value>9) //checks if number enteres is between 1 and 9
		{
			cout<<"Invalid number"<<endl;
			goto menu;
		}
		for(i=0;i<9;i++) //checks if number entered is duplicated in col
		if(value==sud[i][cols])
		{
			cout<<"Check your answer, is that value duplicated in that column?"<<endl;
			goto menu;
		}
		for(j=0;j<9;j++) //checks if number entered is duplicated in row
		if(value==sud[rows][j])
		{
			cout<<"Check your answer, is that value duplicated in that row?"<<endl;
			goto menu;
		}

		while(cols%3 != 0) //Goes to first col of 3X3 box
		cols--;
		while(rows%3 != 0) //goes to first row of 3X3 box
		rows--;
		for(i=rows;i<(rows+3);i++)
		for(j=cols;j<(cols+3);j++)
		{
			if(sud[i][j]==value) //checks if number entered is duplicated in 3X3 box
			{
				cout<<"Check your answer, is the value duplicated in that 3X3 square?"<<endl;
				goto menu;
			}
		}

		rows=row-1;
		cols=col-1;
		sud[rows][cols]=value;// If all above conditions are by passed, value is stored in board
		display_board(sud);//board is displayed
		goto  menu;
		break;
	case 'H'://case for getting hints
	case 'h':
		if(num_hints>0) //checks if the number of hints left is greater than 0
		{
			cout<<"Enter the row and column value for which you would like a hint!"<<endl;
			cin>>rowc>>colc;// Takes the row and col for which the hint is required
			if(rowc<48 || rowc>57 ||colc <48 || colc>57) // checks if entered values are numbers
			{
				cout<<"Enter a number!"<<endl;
				goto menu;
			}
			row=rowc-48; //converts row and col into a numeric value
			col=colc-48;
			if(row<1 || row>9 || col<1 || col>9)//checks if the row and col value entered is between 1 and 9
			{
				cout<<"Invalid row/col number please check"<<endl;
				goto menu;
			}
			rows=row-1;
			cols=col-1;
			if(fix[rows][cols]==1)// check is entered cell is a fixed cell
			{
				cout<<"This is a fixed cell. You can't change it's value!"<<endl;
				goto menu;
			}

			for(k=1;k<10;k++)//for all numbers between 1 and 9
			{
				res=hints(k,rows,cols,sud);//calls the hints fuction
				if(res==1)//if 1 is returned from the hints function then
				{
					hints_arr[n]=k;//write that number to the hints array
					n++;
				}
			}
			cout<<"Hints for this cell are:"<<endl;
			for(i=0;i<n;i++) //display all the hints for that cell
			{
				cout<<hints_arr[i]<<endl;
			}
			n=0;
			num_hints--; //reduce number of hints by 1
			cout<<"You have only "<<num_hints<<" hints left! Use them carefully!"<<endl;//display number of hints left
		}
		else
		{
			cout<<"Sorry you have used up all your hints. Try harder!"<<endl;
		}
		break;
	case 'S'://case for saving game progress
	case 's':
	savefile(sud);//call th esave function
	cout<<"You have succesfully saved your game progress. Do you want to continue playing? Y or N"<<endl;
	cin>>ch;
	if(ch=='y'||ch=='Y')//checks if user wants to continue playing
	{
		goto menu;
	}
	if(ch=='n'||ch=='N')//if not the game is quit
	{
		return 0;
	}
	else
	cout<<"Enter correct choice!"<<endl;
	break;
	case 'V'://case for validating board
	case 'v':
	cout<<"Validating..."<<endl;
	for(i=0;i<9;i++) //First level of validation
	{
	for(j=0;j<9;j++)
	{
		if(sud[i][j]==0)//checks if all cells  have been answered
		{
			cout<<"You have not entered a value in row "<<i+1<<" and col "<<j+1<<"!"<<endl;
			goto menu;
		}
	}
	}
	cout<<"Validating rows..."<<endl;
	for(i=0;i<9;i++)//Second level of validation
	{
		sum=0;
		for(j=0;j<9;j++)
		{
			sum=sum+sud[i][j];
		}
		if(sum!=45)//checks if sum of each row is equal to 45 as it should be
		{
			cout<<"Something is not right in row "<<i<<"  Check your board"<<endl;//else display error message
			goto menu;
		}
	}
	cout<<"Validating cols..."<<endl;
	for(i=0;i<9;i++)//Third level of validation
	{
		sum=0;
		for(j=0;j<9;j++)
		{
			sum=sum+sud[j][i];
		}
		if(sum!=45)//checks if sum of  each column is equal to 45 as it should be
		{
			cout<<"Something is not right in col "<<i<<"  Check your board"<<endl;//else display error message
			goto menu;
		}
	}
	cout<<"Validating the whole board..."<<endl;
	for(i=0;i<9;i++)//level four of validation
	{
	for(j=0;j<9;j++)
	{
		if(sud[i][j]!=sudsol[i][j])//compares the solution with the solution file
		{
			cout<<"There seems to be an  error in row "<<i<<" and col "<<j<<endl;//else display error message
			goto menu;
		}
	}
	}
	cout<<"*****CONGRATULATIONS!!!*****"<<endl<<"You have solved this level succesfully!"<<endl<<"Try solving harder levels now that you are getting smarter!"<<endl;
	break;// Displays a WINNING message
	case 'g'://Case for giving up
	case 'G':
		cout<<"Here is the solution for level "<<level<<endl;
		display_board(sudsol);//displays the solution board
		cout<<"Sorry you have failed this level. Better Luck Next Time!"<<endl;//Displays Losing message
		return 0;
		goto menu;
	case 'Q':// case for quitting
	case 'q':
		return 0;
	default: cout<<"Incorrect choice! Try again"<<endl;//If incorrect choice is enetered then it comes to default case
		op=' ';//clears value of choice
		goto menu;
	}
	goto menu;
	}



};//end of Play_board class
