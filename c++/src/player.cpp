/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#include "player.h"

using namespace Players;

Player::Player(int iXPos, int iYPos)
{
    this->iXPos__ = iXPos;
    this->iYPos__ = iYPos;
}

int Player::iMove()
{
    int iRet = 0;

    switch (this->eDirection__)
    {
    case PLAYER_UP:
        this->iYPos__++;
        break;
    case PLAYER_DOWN:
        this->iYPos__--;
        break;
    default:
        iRet = -1;
        break;
    }

    return iRet;
}
