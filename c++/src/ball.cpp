/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#include "ball.h"

Ball::Ball(int iXPos, int iYPos)
{
    eDirection = STOP;
    iXPos__ = iXPos;
    iStartingXPos__ = iXPos;
    iYPos__ = iYPos;
    iStartingYPos__ = iYPos;
}
