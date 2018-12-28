/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#ifndef BALL_H
#define BALL_H

namespace Balls
{
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
    int iRadii__;
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
    inline int iGetRadii()
    {
        return iRadii__;
    }
    inline int iGetWidth()
    {
        return iGetRadii() + 1;
    }
    inline void vSetXPos(int iXPos)
    {
        this->iXPos__ = iXPos;
    }
    inline void vSetYPos(int iYPos)
    {
        this->iYPos__ = iYPos;
    }
    inline BALL_DIRECTION eGetDirection()
    {
        return eDirection;
    }
    inline void vSetDirection(BALL_DIRECTION eDir)
    {
        this->eDirection = eDir;
    }
    inline void iReset()
    {
        this->iXPos__ = this->iStartingXPos__;
        this->iYPos__ = this->iStartingYPos__;
    }

    Ball(int iXPos, int iYPos);
    int iChangeDirectionAtWall();
    int iChangeDirectionAtPaddle();
    int iMove();
};

} // namespace Ball

#endif
