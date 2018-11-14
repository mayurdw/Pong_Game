/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#ifndef BALL_H
#define BALL_H

enum BALL_DIRECTION
{
    STOP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT,
    LEFT,
    TOP_LEFT,
};

class Ball
{
  private:
    int iXPos__;
    int iYPos__;
    int iStartingXPos__;
    int iStartingYPos__;
    BALL_DIRECTION eDirection;

  public:
    Ball(int iXPos, int iYPos)
    {
        eDirection = STOP;
        iXPos__ = iXPos;
        iStartingXPos__ = iXPos;
        iYPos__ = iYPos;
        iStartingYPos__ = iYPos;
    }
    inline int iGetXPos()
    {
        return iXPos__;
    }
    inline int iGetYPos()
    {
        return iYPos__;
    }
    void vSetXPos(int iXPos);
    void vSetYPos(int iYPos);
    int iChangeDirection();
};

#endif
