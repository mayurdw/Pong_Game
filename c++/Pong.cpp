/*
    Author: Mayur Wadhwani
    Created: Nov 2018
*/

#include <iostream>
#include <unistd.h>
#include "error.h"
#include "ball.h"
#include "player.h"
#include "UI.h"

using namespace Players;
using namespace Balls;
using namespace UserInterface;

int main(int argc, char const *argv[])
{
    const int iWidth = 40;
    const int iHeight = 20;
    BALL_DIRECTION eLastBallDirection = TOP_LEFT;
    UI cGrid(iWidth, iHeight);
    Player P1(1, iHeight / 2), P2(iWidth - 1, iHeight / 2);
    Ball Pong(iWidth/2,iHeight/2);
    Pong.vSetDirection(eLastBallDirection);

    while( 1 )
    {
        cGrid.vSetP1Location(P1.iGetXPos(),P1.iGetYPos());
        cGrid.vSetP2Location(P2.iGetXPos(),P2.iGetYPos());
        cGrid.vSetBallPos(Pong.iGetXPos(),Pong.iGetYPos());
        Return_if_Error(cGrid.iDrawGrid());
        sleep(1);
        Pong.iMove();
    }
    

    return 0;
}
