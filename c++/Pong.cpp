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

static const int iWidth = 20;
static const int iHeight = 10;

static inline bool bDrawObject(int iY, int iYPos)
{
    return ((iY >= iYPos - ( iHeight / 10 )) &&
            (iY <= iYPos + ( iHeight / 10 )));
}

static int Draw(Player cP1, Player &cP2, Ball &Pong)
{
    int iX = 0, iY = 0;

    // clear the console
    system("clear");

    while (iY <= iHeight)
    {
        iX = 0;
        if (iY == 0 || iY == iHeight)
        {
            cout << std::string((iWidth - 1), '-');
        }

        if (bDrawObject(iY, cP1.iGetYPos()))
        {
            cout << "|";
            iX++;
        }

        if( bDrawObject( iY, cP2.iGetYPos()))
        {
            cout << std::string(iWidth - iX - 1, ' ');
            cout << "|";
            iX++;
        }

        cout << "\n";
        iY++;
    }

    cout << "Player 1: " << cP1.iGetScore() << "\tPlayer 2: " << cP2.iGetScore() << "\n";
    return 0;
}

int main(int argc, char const *argv[])
{
    Player cP1(0, iHeight, 'w', 's'), cP2(iWidth, iHeight, 'o', 'l');
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
#if 1
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
            if (iKeyPressed == cP1.iGetUpChar() && cP1.iGetYPos() - Pong.iGetWidth() > 0)
            {
                cP1.vSetDir(PLAYER_UP);
            }
            else if (iKeyPressed == cP1.iGetDownChar() && cP1.iGetYPos() + Pong.iGetWidth() < iHeight)
            {
                cP1.vSetDir(PLAYER_DOWN);
            }
            else if (iKeyPressed == cP2.iGetUpChar() && cP2.iGetYPos() - Pong.iGetWidth() > 0)
            {
                cP2.vSetDir(PLAYER_UP);
            }
            else if (iKeyPressed == cP2.iGetDownChar() && cP2.iGetYPos() + Pong.iGetWidth() < iHeight)
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
#endif
    }

    return 0;
}
