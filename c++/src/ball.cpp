/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#include "ball.h"

Balls::Ball::Ball(int iXPos, int iYPos)
{
    eDirection = STOP;
    iXPos__ = iXPos;
    iStartingXPos__ = iXPos;
    iYPos__ = iYPos;
    iStartingYPos__ = iYPos;
    iRadii__ = iYPos/10;
}

int Balls::Ball::iChangeDirectionAtWall()
{
    int iRet = 0;

    switch (this->eDirection)
    {
    case TOP_RIGHT:
        this->eDirection = BOTTOM_RIGHT;
        break;
    case TOP_LEFT:
        this->eDirection = BOTTOM_LEFT;
        break;
    case BOTTOM_LEFT:
        this->eDirection = TOP_LEFT;
        break;
    case BOTTOM_RIGHT:
        this->eDirection = TOP_RIGHT;
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

int Balls::Ball::iChangeDirectionAtPaddle()
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

int Balls::Ball::iMove()
{
    int iRet = 0;

    switch (this->eDirection)
    {
    case BOTTOM_RIGHT:
        this->iYPos__++;
        // deliberate fallthrough
    case RIGHT:
        this->iXPos__++;
        break;
    case BOTTOM_LEFT:
        this->iYPos__++;
        // deliberate fallthrough
    case LEFT:
        this->iXPos__--;
        break;
    case TOP_LEFT:
        this->iYPos__--;
        this->iXPos__--;
        break;
    case TOP_RIGHT:
        this->iYPos__--;
        this->iXPos__++;
        break;
    default:
        iRet = -1;
        break;
    }

    return iRet;
}