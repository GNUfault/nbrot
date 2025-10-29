#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ncurses.h>

static int mandel(double cx, double cy, int maxit) {
    double x = 0.0, y = 0.0;
    int it = 0;
    double x2 = 0.0, y2 = 0.0;
    while (x2 + y2 <= 4.0 && it < maxit) {
        y = 2.0*x*y + cy;
        x = x2 - y2 + cx;
        x2 = x*x;
        y2 = y*y;
        it++;
    }
    return it;
}

static const char *ramp = " .:-=+*#%@";

int main(void) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    double center_x = -0.75;
    double center_y = 0.0;
    double scale = 3.0;
    int maxit = 128;

    int running = 1;
    while (running) {
        int W, H;
        getmaxyx(stdscr, H, W);

        erase();

        for (int j = 0; j < H - 1; j++) {
            for (int i = 0; i < W; i++) {
                double x = center_x + ((double)i / (double)W - 0.5) * scale;
                double y = center_y + ((double)j / (double)H - 0.5) * scale * ((double)H / (double)W);
                int it = mandel(x, y, maxit);
                int idx = (int)((double)it / (double)maxit * (strlen(ramp)-1));
                mvaddch(j, i, ramp[idx]);
            }
        }

        mvprintw(H-1, 0, "nbrot [center: %.6f, %.6f] [scale: %.6f] [Arrows pan | Z/X zoom | Q quit]",
                 center_x, center_y, scale);

        refresh();

        int c = getch();
        if (c == ERR) continue;

        double pan = scale * 0.1;
        double aspect = (double)H / (double)W;

        switch (c) {
            case 'q': case 'Q': running = 0; break;
            case 'z': case 'Z': scale *= 0.8; break;
            case 'x': case 'X': scale /= 0.8; break;
            case KEY_UP:    center_y -= pan * aspect; break;
            case KEY_DOWN:  center_y += pan * aspect; break;
            case KEY_LEFT:  center_x -= pan; break;
            case KEY_RIGHT: center_x += pan; break;
        }
    }

    endwin();
    return 0;
}
