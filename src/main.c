#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>

#define BASIC_ELEMENTS 5
int menu_basic( int do_window ) {

    // Local variables
    int x, y, ch, done;
	int itemwidth = 0;
    int hpad = 12; //NOT WORKING
    ITEM *basic_items[BASIC_ELEMENTS + 1];
    MENU *basic_menu;
    WINDOW *win;

	getmaxyx(stdscr, y, x); //get window size

    // Create the basic items, menu
    basic_items[0] = new_item("1. |", "Description 1");
    basic_items[1] = new_item("2. |", "Description 2");
    basic_items[2] = new_item("3. |", "Description 3");
    basic_items[3] = new_item("4. |", "Beam Calculator");
    basic_items[4] = new_item("5. |", "Structural Steel Data");
    basic_items[5] = NULL;
    basic_menu = new_menu((ITEM **)basic_items);

    int itemdescwidth = 0;
    for (int i = 0; i < BASIC_ELEMENTS; i++) {
        int namelen = strlen(item_name(basic_items[i]));
        int desclen = strlen(item_description(basic_items[i]));
        if (namelen > itemwidth)
            itemwidth = namelen;
        if (desclen > itemdescwidth)
            itemdescwidth = desclen;
    }
    itemwidth += itemdescwidth + 7; // include description spacing and padding

    // Add some color to the menu
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    set_menu_fore(basic_menu, COLOR_PAIR(1) | A_REVERSE);
    set_menu_back(basic_menu, COLOR_PAIR(2));
    set_menu_grey(basic_menu, COLOR_PAIR(3));

    // Create a centered menu window
    int menu_h = BASIC_ELEMENTS + 6;
    int menu_w = itemwidth; //Add numbers here to add space to the right
    if (menu_h > y - 2) menu_h = y - 2;
    if (menu_w > x - 2) menu_w = x - 2;
    int menu_y = (y - menu_h) / 2;
    int menu_x = (x - menu_w) / 2;

    win = newwin(menu_h, menu_w, menu_y, menu_x);
    box(win, 0, 0);
    set_menu_win(basic_menu, win);
    set_menu_sub(basic_menu, derwin(win, menu_h - 4, menu_w - 2, 3, 2));
    wmove(win, 1, 1);
    keypad(win, TRUE);
    mvwprintw(win, 1, 1, "Engbench - The Engineering Workbench");
    post_menu(basic_menu);
    wrefresh(win);

    // Get input for the menu
    done = 0;
    while ( !done ) {
        ch = do_window ? wgetch(win) : getch();
        switch (ch) {
            case KEY_DOWN:
            case 's': // s is up:
                mvwprintw(win, 9, 1, "You pressed the down arrow key");
                menu_driver(basic_menu, REQ_DOWN_ITEM);
                break;
            case 'w': // w is up
            case KEY_UP:
                mvwprintw(win, 9, 1, "You pressed the up arrow key  "); //whitespace is a bodge to prevent text overlap
                menu_driver(basic_menu, REQ_UP_ITEM);
                break;
			case '\n':
            case '\r':
				mvwprintw(win, 9, 1, "Opening submenu...            ");
				break;
            case 'q': // Quit
                done = 1;
                break;
        }

        // Do a refresh
        if ( do_window == 1 ) {
            wrefresh(win);
        } else {
            refresh();
        }
    }

    // Cleanup the menu
    unpost_menu(basic_menu);
    for (int i=0; i<BASIC_ELEMENTS; i++) {
        free_item(basic_items[i]);
    }
    free_menu(basic_menu);

    // Return successfully
    return 0;
}

int main(void) {
// curses startup
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(2);

// do stuff
	menu_basic(1);

// curses shutdown
	endwin();
	echo();
	curs_set(1);

	printf("Great success!\n");
	return 0;
}

