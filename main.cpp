#include<iostream>
#include "new_game1.cpp"
#include "ins.cpp"
using namespace std;
int main() {
    char opt;
    main_menu:
    cout<<"**********Welcome to Sudoku!**********\n";
    cout<<"Please pick an option:\n I: Instructions\n P: Play a new game\n L: Load saved game\n Q: Leave Game\n";
    cin>>opt;
    switch (opt)
        {
	    case 'i':
	    case 'I':instructions();goto main_menu; break;//calls instructions function
            case'P':
	    case'p': new_game();//call function new_game
	    break;
            case 'L':
            case'l': load_game();//call function solve_game
            break;
            case 'Q':
            case'q': return 0;//exit
            break;
	    default: cout<<"Incorrect choice!"<<endl; goto main_menu;//exits the game
	    break;
        }

     return 0;
}
