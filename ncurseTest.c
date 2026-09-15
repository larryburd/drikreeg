#include <ncurses.h>
#include <stdio.h>

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors() == FALSE) {
        endwin();
        puts("Your terminal doesn't support colors.");
        return 1;
    }

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    attron(COLOR_PAIR(1));

    int x, y;
    getmaxyx(stdscr, y, x);
    y = y * 0.5;
    x = x * 0.5;
    mvwprintw(stdscr, y, x, "Hello world!");
    mvwprintw(stdscr, 2, 2, "Hello world!");
    refresh();

    attroff(COLOR_PAIR(1));
    getch();
    endwin();
    return 0;
}
