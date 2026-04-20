#include <ncurses.h>

int main(void) {
	int ch;

	initscr();					//Start curses mode
	raw();						//start raw mode
	keypad(stdscr, TRUE);		//handle arrow keys, f keys, etc.
	noecho();					//don't print typed characters directly
	
	printw("Type a character and i'll bold it\n");	//ncurses print (need refresh to show)

	ch = getch();  					//Wait for user input
	
	if (ch == KEY_F(1))
		printw("F1 Key pressed");
	else {
		printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}

	refresh();					//Refresh window to show printed text
	getch();
	endwin(); 					//End curses mode

	return 0;
}
