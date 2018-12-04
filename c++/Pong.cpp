/*
    Author: Mayur Wadhwani
    Created: Nov 2018
*/

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "error.h"
#include "ball.h"
#include "player.h"

using namespace Players;
using namespace Balls;
using namespace std;

static const int iWidth = 40;
static const int iHeight = 20;

static bool kbhit(int *piKeyPressed)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    *piKeyPressed = 0;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        *piKeyPressed = ch;
        return true;
    }

    return false;
}

static int Draw(Player cP1, Player &cP2, Ball &Pong)
{
    int iX = 0, iY = 0;

    system("clear");
    while (iY <= iHeight)
    {
        iX = 0;
        while (iX <= iWidth)
        {
            if (iY == 0)
            {
                cout << '_';
            }
            else if (iY == iHeight)
            {
                cout << "_";
            }
            else if ((iY >= cP1.iGetYPos() - 2 && iY <= cP1.iGetYPos() + 2) &&
                     (iX == cP1.iGetXPos()))
            {
                cout << "|";
            }
            else if ((iY >= cP2.iGetYPos() - 2 && iY <= cP2.iGetYPos() + 2) &&
                     (iX == cP2.iGetXPos()))
            {
                cout << "|";
            }
            else if (iY == Pong.iGetYPos() - 2 && iX == Pong.iGetXPos())
            {
                cout << "*";
            }
            else if (iY == Pong.iGetYPos() - 1 && (iX >= Pong.iGetXPos() - 1 && iX <= Pong.iGetXPos() + 1))
            {
                cout << "*";
            }
            else if (iY == Pong.iGetYPos() && (iX >= Pong.iGetXPos() - 2 && iX <= Pong.iGetXPos() + 2))
            {
                cout << "*";
            }
            else if (iY == Pong.iGetYPos() + 1 && (iX >= Pong.iGetXPos() - 1 && iX <= Pong.iGetXPos() + 1))
            {
                cout << "*";
            }
            else if (iY == Pong.iGetYPos() + 2 && iX == Pong.iGetXPos())
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            iX++;
        }
        cout << "\n";
        iY++;
    }

    cout << "Player 1: " << cP1.iGetScore() << "\tPlayer 2: " << cP2.iGetScore() << "\n";
    return 0;
}

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}

int main(int argc, char const *argv[])
{
    Player cP1(0, iHeight / 2, 'w', 's'), cP2(iWidth, iHeight / 2, 'o', 'l');
    Ball Pong(iWidth / 2, iHeight / 2);
    Pong.vSetDirection(BOTTOM_RIGHT);
    int iKeyPressed = 0;
    bool bRestart = false;

    while (1)
    {
        cP1.vSetDir(PLAYER_STOP);
        cP2.vSetDir(PLAYER_STOP);
        if (bRestart)
        {
            bRestart = false;
            Pong.iReset();
            cP1.iReset();
            cP2.iReset();
        }

        Return_if_Error(Draw(cP1, cP2, Pong));
        if (Pong.iGetYPos() == 3 || Pong.iGetYPos() == (iHeight - 3))
        {
            Pong.iChangeDirectionAtWall();
        }
        else if ((cP1.iGetXPos() == (Pong.iGetXPos() - 3) &&
                  (cP1.iGetYPos() - 2) <= Pong.iGetYPos() &&
                  (cP1.iGetYPos() + 2) >= Pong.iGetYPos()) ||
                 (cP2.iGetXPos() == (Pong.iGetXPos() + 3) &&
                  (cP2.iGetYPos() - 2) <= Pong.iGetYPos() &&
                  (cP2.iGetYPos() + 2) >= Pong.iGetYPos()))
        {
            Pong.iChangeDirectionAtPaddle();
        }
        else if ((Pong.iGetXPos() - 2) <= cP1.iGetXPos())
        {
            bRestart = true;
            cP2.vIncrementScore();
        }
        else if ((Pong.iGetXPos() + 2) >= cP2.iGetXPos())
        {
            bRestart = true;
            cP1.vIncrementScore();
        }
        else
        {
            //do nothing
        }
        sleep_ms(500);
        if (kbhit(&iKeyPressed))
        {
            if (iKeyPressed == cP1.iGetUpChar() && cP1.iGetYPos() - 3 > 0 )
            {
                cP1.vSetDir(PLAYER_UP);
            }
            else if (iKeyPressed == cP1.iGetDownChar() && cP1.iGetYPos() + 3 < iHeight )
            {
                cP1.vSetDir(PLAYER_DOWN);
            }
            else if (iKeyPressed == cP2.iGetUpChar() && cP1.iGetYPos() - 3 > 0 )
            {
                cP2.vSetDir(PLAYER_UP);
            }
            else if (iKeyPressed == cP2.iGetDownChar() && cP1.iGetYPos() + 3 < iHeight )
            {
                cP2.vSetDir(PLAYER_DOWN);
            }
            else
            {
                // do nothing
            }
        }
        //Pong.iMove();
        cP1.iMove();
        cP2.iMove();
    }

    return 0;
}
