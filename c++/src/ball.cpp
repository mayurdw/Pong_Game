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

int Ball::iChangeDirection()
{
    int iRet = 0;

    switch (this->eDirection)
    {
    case TOP_RIGHT:
        this->eDirection = TOP_LEFT;
        break;
    case TOP_LEFT:
        this->eDirection = TOP_RIGHT;
        break;
    case BOTTOM_LEFT:
        this->eDirection = BOTTOM_RIGHT;
        break;
    case BOTTOM_RIGHT:
        this->eDirection = BOTTOM_LEFT;
        break;
    case RIGHT:
        this->eDirection = LEFT;
        break;
    case LEFT:
        this->eDirection = RIGHT;
        break;
    default:
        iRet = -1;
        break;
    }
    return iRet;
}

int Ball::iMove()
{
    int iRet = 0;

    switch (this->eDirection)
    {
    case TOP_RIGHT:
        this->iYPos__++;
        // deliberate fallthrough
    case RIGHT:
        this->iXPos__++;
        break;
    case TOP_LEFT:
        this->iYPos__++;
        // deliberate fallthrough
    case LEFT:
        this->iXPos__--;
        break;
    case BOTTOM_LEFT:
        this->iYPos__--;
        this->iXPos__--;
        break;
    case BOTTOM_RIGHT:
        this->iYPos__--;
        this->iXPos__++;
        break;
    default:
        iRet = -1;
        break;
    }

    return iRet;
}