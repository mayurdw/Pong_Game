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
    // Inline Getters and Setters
    inline int iGetXPos()
    {
        return iXPos__;
    }
    inline int iGetYPos()
    {
        return iYPos__;
    }
    inline void vSetXPos(int iXPos)
    {
        this->iXPos__ = iXPos;
    }
    inline void vSetYPos(int iYPos)
    {
        this->iYPos__ = iYPos;
    }

    Ball(int iXPos, int iYPos);
    int iChangeDirection();
};

#endif
