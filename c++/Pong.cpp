/*
    Author: Mayur Wadhwani
    Created: Nov 2018
*/

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include "error.h"
#include "ball.h"
#include "player.h"

using namespace Players;
using namespace Balls;
using namespace std;

static const int iWidth = 40;
static const int iHeight = 40;

static inline int iObjectToWallBoundry()
{
    return (iHeight/10);
}

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

    // clear the console
    // TODO: Migrate to an abstraction file
    system("clear");

    while (iY <= iHeight)
    {
        iX = 0;
        if (iY == 0 || iY == iHeight)
        {
            while (iX < iWidth)
            {
                cout << '_';
                iX++;
            }
        }
        else
        {

            if ((iY >= cP1.iGetYPos() - iObjectToWallBoundry()) && (iY <= cP1.iGetYPos() + iObjectToWallBoundry()))
            {
                cout << "|";
                iX++;
            }

            if ((iY >= Pong.iGetYPos() - iObjectToWallBoundry()) && (iY <= Pong.iGetYPos() + iObjectToWallBoundry()))
            {
                while (iX < Pong.iGetXPos() - Pong.iGetRadii())
                {
                    cout << " ";
                    iX++;
                }
                cout << std::string(Pong.iGetWidth(), '*');
                iX += Pong.iGetWidth();
            }

            if ((iY >= cP2.iGetYPos() - iObjectToWallBoundry()) && (iY <= cP2.iGetYPos() + iObjectToWallBoundry()))
            {
                while (iX < iWidth - 1)
                {
                    cout << " ";
                    iX++;
                }
                cout << "|";
                iX++;
            }
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
        if (Pong.iGetYPos() == Pong.iGetWidth() || Pong.iGetYPos() == (iHeight - Pong.iGetWidth()))
        {
            Pong.iChangeDirectionAtWall();
        }
        else if ((cP1.iGetXPos() == (Pong.iGetXPos() - Pong.iGetWidth()) &&
                  (cP1.iGetYPos() - iObjectToWallBoundry()) <= Pong.iGetYPos() &&
                  (cP1.iGetYPos() + iObjectToWallBoundry()) >= Pong.iGetYPos()) ||
                 (cP2.iGetXPos() == (Pong.iGetXPos() + Pong.iGetWidth()) &&
                  (cP2.iGetYPos() - iObjectToWallBoundry()) <= Pong.iGetYPos() &&
                  (cP2.iGetYPos() + iObjectToWallBoundry()) >= Pong.iGetYPos()))
        {
            Pong.iChangeDirectionAtPaddle();
        }
        else if ((Pong.iGetXPos() - Pong.iGetRadii()) <= cP1.iGetXPos())
        {
            bRestart = true;
            cP2.vIncrementScore();
        }
        else if ((Pong.iGetXPos() + Pong.iGetRadii()) >= cP2.iGetXPos())
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
            if (iKeyPressed == cP1.iGetUpChar() && cP1.iGetYPos() - Pong.iGetWidth() > 0 )
            {
                cP1.vSetDir(PLAYER_UP);
            }
            else if (iKeyPressed == cP1.iGetDownChar() && cP1.iGetYPos() + Pong.iGetWidth() < iHeight )
            {
                cP1.vSetDir(PLAYER_DOWN);
            }
            else if (iKeyPressed == cP2.iGetUpChar() && cP2.iGetYPos() - Pong.iGetWidth() > 0 )
            {
                cP2.vSetDir(PLAYER_UP);
            }
            else if (iKeyPressed == cP2.iGetDownChar() && cP2.iGetYPos() + Pong.iGetWidth() < iHeight )
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
