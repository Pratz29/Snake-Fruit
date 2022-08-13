#include<iostream>

#include<cstdlib>

#include<conio.h>

#include<ctime>

#include<windows.h>

#include<time.h>

using namespace std;

bool gameover;//to keep track whether the game status
const int width = 20;//maximum border of the snake
const int height = 20;
int x, y;//coordinates for the snake head
int fx, fy;//coordinates for the fruit
int score;//keeps track of the score
int tx[1000];//this is the array of tail of the snake
int ty[1000];
int nt;//keeps track of the number of snake tails
enum eDirection {
    STOP = 0, LEFT, RIGHT, UP, DOWN
};
eDirection dir;
void setup() {//playground setup
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fx = rand() % width;
    fy = rand() % height;
    score = 0;
}

void draw() {
    //system("cls");//can be used but will blink constantly
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {//used to stop the blinking 
        0,
        0
    });
    for (int i = 0; i < width + 2; i++) {//to make top border
        cout << "#";
    }
    cout << endl;
    //to make the height of the playground
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "#";//printing the left border 
            } else if (i == x && j == y) {
                cout << "O";//printing the snake head
            } else if (i == fx && j == fy) {
                cout << "F";//printing the fruit
            } else {
                bool print = false;
                for (int k = 0; k < nt; k++) {
                    /**/
                    if (tx[k] == i && ty[k] == j) {//printing the snake tail 
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++) {
        cout << "#";//printing the bottom border
    }
    cout << endl;
    cout << "SCORE :" << score << endl;
}
void input() {
    if (_kbhit()) {//records whether the keyboard has been hit or not
        switch (_getch()) {//this gets the character which has been hit in the keyboard
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'w':
                dir = UP;
                break;
            case 'x':
                gameover = true;
                break;
        }
    }
}
void logic() {
    int ptx = tx[0];//ptx is the arrow which will point to the first element in the snake tail
    int pty = ty[0];
    int ptx1, pty1;
    tx[0] = x;//first element of the snake tial will point to the snake head
    ty[0] = y;
    for (int i = 1; i < nt; i++) {
        ptx1 = tx[i];
        pty1 = ty[i];
        tx[i] = ptx;
        ty[i] = pty;
        ptx = ptx1;
        pty = pty1;
    }
    switch (dir) {
        case LEFT:
            y--;
            break;
        case RIGHT:
            y++;
            break;
        case UP:
            x--;
            break;
        case DOWN:
            x++;
            break;
        default:
            break;
    }
    if (x > width || x < 0 || y > height || y < 0) {//if our snake goes out of the boundary then game over
        gameover = true;
    }
    for (int i = 0; i < nt; i++) {//if our snake eats itself then gameover
        if (tx[i] == x && ty[i] == y) {
            gameover = true;
        }
    }
    if (x == fx && y == fy) {//if the snake head eats the fruit then score will increase ,new fruit will be generated and number of tails fo the snake will increase.
        score += 10;
        fx = rand() % width;
        fy = rand() % height;
        nt++;
    }
}
int main() {
    srand(time(NULL));
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(500);//to slow down the game play
    }
    return 0;
}