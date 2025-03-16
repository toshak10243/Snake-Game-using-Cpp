#include <iostream.h>   // Turbo C++ header
#include <conio.h>       // For clrscr(), getch(), kbhit()
#include <dos.h>         // For delay()
#include <stdlib.h>      // For random number generation

#define WIDTH 30
#define HEIGHT 20

class SnakeGame {
    int x, y, foodX, foodY, score;
    int tailX[100], tailY[100]; // Arrays for storing tail positions
    int length;
    char direction;
    int gameOver;

public:
    SnakeGame() {
        x = WIDTH / 2;
        y = HEIGHT / 2;
        length = 0;
        score = 0;
        direction = ' ';
        gameOver = 0;
        randomize();  // Initialize random function
        generateFood();
    }

    void generateFood() {
        foodX = random(WIDTH - 2) + 1;
        foodY = random(HEIGHT - 2) + 1;
    }

    void draw() {
        clrscr();
        int i, j;
        for (i = 0; i < WIDTH; i++) cout << "#";
        cout << endl;

        for (i = 0; i < HEIGHT; i++) {
            for (j = 0; j < WIDTH; j++) {
                if (j == 0 || j == WIDTH - 1) cout << "#";
                else if (i == y && j == x) cout << "O";  // Snake head
                else if (i == foodY && j == foodX) cout << "@";  // Food
                else {
                    int isTail = 0;
                    for (int k = 0; k < length; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            cout << "o";
                            isTail = 1;
                        }
                    }
                    if (!isTail) cout << " ";
                }
            }
            cout << endl;
        }

        for (i = 0; i < WIDTH; i++) cout << "#";
        cout << "\nScore: " << score;
    }

    void input() {
        if (kbhit()) {
            char key = getch();
            if (key == 75) direction = 'L';  // Left Arrow
            if (key == 77) direction = 'R';  // Right Arrow
            if (key == 72) direction = 'U';  // Up Arrow
            if (key == 80) direction = 'D';  // Down Arrow
            if (key == 'x') gameOver = 1;
        }
    }

    void logic() {
        int prevX = tailX[0], prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;

        int i;
        for (i = 1; i < length; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        if (direction == 'L') x--;
        if (direction == 'R') x++;
        if (direction == 'U') y--;
        if (direction == 'D') y++;

        if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1) gameOver = 1;

        for (i = 0; i < length; i++) {
            if (tailX[i] == x && tailY[i] == y) gameOver = 1;
        }

        if (x == foodX && y == foodY) {
            score += 10;
            length++;
            generateFood();
        }
    }

    void run() {
        while (!gameOver) {
            draw();
            input();
            logic();
            delay(100); // Speed control
        }
        cout << "\n\nGame Over! Final Score: " << score;
        getch();
    }
};

void main() {
    SnakeGame game;
    game.run();
}
