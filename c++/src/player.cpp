/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#include "player.h"

using namespace Players;

Player::Player(int iXPos, int iYPos, int iUpChar, int iDownChar)
{
    this->iOriginalXPos__ = iXPos;
    this->iOriginalYPos__ = iYPos / 2;
    this->iXPos__ = iXPos;
    this->iYPos__ = iYPos / 2;
    this->iDownChar__ = iDownChar;
    this->iUpChar__ = iUpChar;
    this->iScore__ = 0;
}

int Player::iMove()
{
    int iRet = 0;

    switch (this->eDirection__)
    {
    case PLAYER_UP:
        this->iYPos__--;
        break;
    case PLAYER_DOWN:
        this->iYPos__++;
        break;
    default:
        iRet = -1;
        break;
    }

    return iRet;
}