/*
    Author: Mayur Wadhwani
    Created: Nov 2018
*/

#include <string>
#include "abs_layer.h"
#include "error.h"
#include "ball.h"
#include "player.h"

using namespace Players;
using namespace Balls;
using namespace std;

static const int iWidth = 40;
static const int iHeight = 20;

static inline int iPaddleHeight()
{
    return iHeight / 10;
}

static inline bool bDrawObject(int iY, int iYPos)
{
    return ((iY >= (iYPos - iPaddleHeight())) &&
            (iY <= (iYPos + iPaddleHeight())));
}

static int Draw(Player &cP1, Player &cP2, Ball &Pong)
{
    int iX = 0, iY = 0;

    // clear the console
    system("clear");

    while (iY <= iHeight)
    {
        iX = 0;
        if (iY == 0 || iY == iHeight)
        {
            cout << std::string(iWidth, '_');
        }

        if (bDrawObject(iY, cP1.iGetYPos()))
        {
            cout << "|";
            iX++;
        }

        if (iY == Pong.iGetYPos())
        {
            cout << std::string(Pong.iGetXPos() - 1, ' ');
            iX += (Pong.iGetXPos() - 1);
            cout << "*";
            iX++;
        }

        if (bDrawObject(iY, cP2.iGetYPos()))
        {
            cout << std::string(iWidth - iX, ' ');
            cout << "|";
        }

        cout << "\n";
        iY++;
    }

    cout << "Player 1: " << cP1.iGetScore() << "\tPlayer 2: " << cP2.iGetScore() << "\n";
    return 0;
}

static int iHandleCollision(Player &cP1, Player &cP2, Ball &Pong, bool *pbRestart)
{
    if (pbRestart == NULL)
        return -1;

    if (Pong.iGetYPos() - 1 == 0 || Pong.iGetYPos() + 1 == iHeight)
    {
        Pong.iChangeDirectionAtWall();
    }
    else if (cP1.iGetXPos() == (Pong.iGetXPos() - 1))
    {
        if (((cP1.iGetYPos() - iPaddleHeight()) <= Pong.iGetYPos()) &&
            ((cP1.iGetYPos() + iPaddleHeight()) >= Pong.iGetYPos()))
        {
            Pong.iChangeDirectionAtPaddle();
        }
        else
        {
            *pbRestart = true;
            cP2.vIncrementScore();
        }
    }
    else if (cP2.iGetXPos() == (Pong.iGetXPos() + 1))
    {
        if (((cP2.iGetYPos() - iPaddleHeight()) <= Pong.iGetYPos()) &&
            ((cP2.iGetYPos() + iPaddleHeight()) >= Pong.iGetYPos()))
        {
            Pong.iChangeDirectionAtPaddle();
        }
        else
        {
            *pbRestart = true;
            cP1.vIncrementScore();
        }
    }
    else
    {
        // do nothing
    }

    return 0;
}

static int iHandleKeypress(Player &cP1, Player &cP2, Ball &Pong)
{
    int iKeyPressed = 0;

    if (kbhit(&iKeyPressed))
    {
        if (iKeyPressed == cP1.iGetUpChar() && ((cP1.iGetYPos() - iPaddleHeight()) > 1))
        {
            cP1.vSetDir(PLAYER_UP);
        }
        else if (iKeyPressed == cP1.iGetDownChar() && ((cP1.iGetYPos() + iPaddleHeight()) < iHeight - 1))
        {
            cP1.vSetDir(PLAYER_DOWN);
        }
        else if (iKeyPressed == cP2.iGetUpChar() && ((cP2.iGetYPos() - iPaddleHeight()) > 1))
        {
            cP2.vSetDir(PLAYER_UP);
        }
        else if (iKeyPressed == cP2.iGetDownChar() && ((cP2.iGetYPos() + iPaddleHeight()) < iHeight - 1))
        {
            cP2.vSetDir(PLAYER_DOWN);
        }
        else
        {
            // do nothing
        }
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    Player cP1(0, iHeight, 'w', 's'), cP2(iWidth, iHeight, 'o', 'l');
    Ball Pong(iWidth / 2, iHeight / 2);
    Pong.vSetDirection(BOTTOM_RIGHT);
    bool bRestart = false;

    while (1)
    {
        sleep_ms(iHeight * 10);
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
        Return_if_Error(iHandleCollision(cP1, cP2, Pong, &bRestart));
        Return_if_Error(iHandleKeypress(cP1, cP2, Pong));
        Pong.iMove();
        cP1.iMove();
        cP2.iMove();
    }

    return 0;
}
