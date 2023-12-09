#include <iostream>
#include <ncurses.h>
#include <windows.h>
#include "log.h"
#include "loadpage.h"
#include "MMSystem.h"

class Car {
public:
    Car(int x, int y) : x(x), y(y) {}

    void draw() {
        init_pair(1, COLOR_BLUE, COLOR_BLACK);

        attron(COLOR_PAIR(1));
        mvprintw(y, x,     " 000");
        mvprintw(y + 1, x, "00000");
        mvprintw(y + 2, x, " 000 ");
        mvprintw(y + 3, x, "00000");
        attroff(COLOR_PAIR(1));
    }

    void moveLeft() {
        if (x > 0)
            x -= move;
    }

    void moveRight() {
        if (x < maxX - 5)
            x += move;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

private:
    int x, y;
    static const int move = 3;
    static const int maxX = 80;
};

class Enemy {
public:
    Enemy() {}

    void initialize(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void draw() {
        init_pair(2, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(2));
        mvprintw(y, x,     " oo ");
        mvprintw(y + 1, x, "oooo");
        mvprintw(y + 2, x, " oo ");
        mvprintw(y + 3, x, "oooo");
        attroff(COLOR_PAIR(2));
    }

    void moveDown() {
        y += speed;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

private:
    int x, y;
    static const int speed = 1;
};

class Game {
public:
    Game() {
        player = new Car(maxX / 2, maxY - 3);
        generateEnemies();
    }

    ~Game() {
        delete player;
    }

    void LoginPage() {
        PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC | SND_LOOP);
        Login();
        Menu();
    }

    void Menu() {
        initscr();
        curs_set(0);
        clear();
        start_color();

        init_pair(1, COLOR_BLUE, COLOR_BLACK);

        attron(COLOR_PAIR(1));

        mvprintw(3, maxX / 2 - 2, " .d8888b.        d8888 8888888b.   .d8888b. ");
        mvprintw(4, maxX / 2 - 2, "d88P  Y88b      d88888 888   Y88b d88P  Y88b");
        mvprintw(5, maxX / 2 - 2, "888    888     d88P888 888    888 Y88b.     ");
        mvprintw(6, maxX / 2 - 2, "888           d88P 888 888   d88P  ^Y888b.  ");
        mvprintw(7, maxX / 2 - 2, "888          d88P  888 8888888P^      ^Y88b.");
        mvprintw(8, maxX / 2 - 2, "888    888  d88P   888 888 T88b         ^888");
        mvprintw(9, maxX / 2 - 2, "Y88b  d88P d8888888888 888  T88b  Y88b  d88P");
        mvprintw(10, maxX / 2 - 2, " ^Y8888P^ d88P     888 888   T88b  ^Y8888P^ ");
        attroff(COLOR_PAIR(1));

        mvprintw(maxY / 2 + 5, maxX / 2 + 10, "1. Start Game");
        mvprintw(maxY / 2 + 6, maxX / 2 + 10, "   2. Quit");

        mvprintw(maxY + 3, 2, "by : nando & ratu & lian");
        refresh();

        int choice;
        choice = getch();
        switch (choice) {
        case '1':
            clear();
            load();
            start();
            break;

        default:
            endwin();
            std::cout << "Thanks for playing!\n";
            exit(0);
            break;
        }
    }

    void start() {
        PlaySound(TEXT("megalovania.wav"), NULL, SND_ASYNC | SND_LOOP);
        initscr();
        timeout(0);
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);

        int ch;
        while ((ch = getch()) != 'q') {
            clear();

            switch (ch) {
            case 'a':
                player->moveLeft();
                break;
            case 'd':
                player->moveRight();
                break;
            }

            moveEnemies();
            checkCollisions();
            draw();

            refresh();
            Sleep(100);
        }

        endwin();
    }

private:
    int score = 0;

    Car* player;
    Enemy enemies[5];
    static const int maxX = 80;
    static const int maxY = 24;

    void generateEnemies() {
        for (int i = 0; i < 5; ++i) {
            int x = rand() % (maxX - 4);
            int y = rand() % 10;
            enemies[i].initialize(x, y);
        }
    }

    void moveEnemies() {
        for (auto& enemy : enemies) {
            enemy.moveDown();
            if (enemy.getY() > maxY) {
                int x = rand() % (maxX - 4);
                int y = rand() % 2;
                enemy.initialize(x, y);
            }
        }
    }

    void GameOver() {
        system("color 5");
        std::cout << "  .oooooo.                                                 .oooooo.                                 " << std::endl;
        std::cout << " d8P'  `Y8b                                               d8P'  `Y8b                                " << std::endl;
        std::cout << "888            .oooo.   ooo. .oo.  .oo.    .ooooo.       888      888 oooo    ooo  .ooooo.  oooo d8b" << std::endl;
        std::cout << "888           `P  )88b  `888P^Y88bP^Y88b  d88' `88b      888      888  `88.  .8'  d88' `88b `888""8P" << std::endl;
        std::cout << "888     ooooo  .oP^888   888   888   888  888ooo888      888      888   `88..8'   888ooo888  888    " << std::endl;
        std::cout << "`88.    .88'  d8(  888   888   888   888  888    .o      `88b    d88'    `888'    888    .o  888    " << std::endl;
        std::cout << " `Y8bood8P'   `Y888^^8o o888o o888o o888o `Y8bod8P'       `Y8bood8P'      `8'     `Y8bod8P' d888b   " << std::endl;

        exit(0);
    }

    void checkCollisions() {
        int playerX = player->getX();
        int playerY = player->getY();

        for (auto& enemy : enemies) {
            int enemyX = enemy.getX();
            int enemyY = enemy.getY();

            if (enemyY + 4 >= maxY) {
                score += 1;
            }

            if (playerX < enemyX + 4 && playerX + 5 > enemyX &&
                playerY < enemyY + 2 && playerY + 2 > enemyY) {
                endwin();
                GameOver();
            }
        }
    }

    void draw() {
        for (int i = 0; i < maxY + 6; i++) {
            mvprintw(i, maxX, "///////");
        }

        mvprintw(5, maxX + 17, "  Control   ");
        mvprintw(6, maxX + 17, "------------");
        mvprintw(7, maxX + 17, "A Key - Left");
        mvprintw(8, maxX + 17, "D Key - Right");

        int scores = score / 4.5;
        mvprintw(10, maxX + 17, "  Score: %d", scores);

        player->draw();
        for (auto& enemy : enemies) {
            enemy.draw();
        }
    }
};

int main() {
    Game game;
    game.LoginPage();

    return 0;
}

