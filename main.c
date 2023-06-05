#include <stdio.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>

char* texts[11][5] = {
    { // 0
        " ██████ ",
        " ██  ██ ",
        " ██  ██ ",
        " ██  ██ ",
        " ██████ ",
    },
    { // 1
        "     ██ ",
        "     ██ ",
        "     ██ ",
        "     ██ ",
        "     ██ ",
    },
    { // 2
        " ██████ ",
        "     ██ ",
        " ██████ ",
        " ██     ",
        " ██████ ",
    },
    { // 3
        " ██████ ",
        "     ██ ",
        " ██████ ",
        "     ██ ",
        " ██████ ",
    },
    { // 4
        " ██  ██ ",
        " ██  ██ ",
        " ██████ ",
        "     ██ ",
        "     ██ ",
    },
    { // 5
        " ██████ ",
        " ██     ",
        " ██████ ",
        "     ██ ",
        " ██████ ",
    },
    { // 6
        " ██████ ",
        " ██     ",
        " ██████ ",
        " ██  ██ ",
        " ██████ ",
    },
    { // 7
        " ██████ ",
        " ██  ██ ",
        " ██  ██ ",
        "     ██ ",
        "     ██ ",
    },
    { // 8
        " ██████ ",
        " ██  ██ ",
        " ██████ ",
        " ██  ██ ",
        " ██████ ",
    },
    { // 9
        " ██████ ",
        " ██  ██ ",
        " ██████ ",
        "     ██ ",
        " ██████ ",
    },
    { // :
        "        ",
        "   ██   ",
        "        ",
        "   ██   ",
        "        ",
    },
};

int* getNumbers() {
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    int hour = lt->tm_hour;
    int min = lt->tm_min;
    int sec = lt->tm_sec;

    static int numbers[8];
    numbers[0] = hour / 10;
    numbers[1] = hour % 10;
    numbers[2] = 10;
    numbers[3] = min / 10;
    numbers[4] = min % 10;
    numbers[5] = 10;
    numbers[6] = sec / 10;
    numbers[7] = sec % 10;

    return numbers;
}

void getSize(struct winsize* win, int* width, int* height) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, win);
    *width = win->ws_col;
    *height = win->ws_row;
}

void printNumbers(int* numbers, int width, int height) {
    printf("\033[2J");
    printf("\033[H");

    for (int i = 0; i < (height - 5) / 2; ++i) {
        printf("\n");
    }

    for (int r = 0; r < 5; ++r) {
        for (int i = 0; i < (width - 64) / 2; ++i) {
            printf(" ");
        }

        for (int c = 0; c < 8; ++c) {
            printf(
                "%s",
                texts[numbers[c]][r]
            );
        }
        printf("\n");
    }
}

int main() {
    struct winsize win;
    int width, height;

    printf("\e[?25l");

    while (1) {
        getSize(&win, &width, &height);
        printNumbers(getNumbers(), width, height);

        sleep(1);
    }

    return 0;
}