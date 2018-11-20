/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#ifndef PLAYER_H
#define PLAYER_H

namespace Players
{
enum PLAYER_DIRECTION
{
    PLAYER_STOP,
    PLAYER_UP,
    PLAYER_DOWN,
};

class Player
{
  private:
    int iXPos__;
    int iYPos__;
    int iOriginalXPos__;
    int iOriginalYPos__;
    PLAYER_DIRECTION eDirection__;
    int iUpChar__;
    int iDownChar__;
    int iScore__;

  public:
    // inline getters & setter
    inline int iGetXPos()
    {
        return iXPos__;
    }
    inline int iGetYPos()
    {
        return iYPos__;
    }
    inline PLAYER_DIRECTION eGetDir()
    {
        return eDirection__;
    }
    inline int iGetUpChar()
    {
        return iUpChar__;
    }
    inline int iGetDownChar()
    {
        return iDownChar__;
    }
    inline int iGetScore()
    {
        return iScore__;
    }
    inline void vSetXPos(int iXPos)
    {
        this->iXPos__ = iXPos;
    }
    inline void vSetYPos(int iYPos)
    {
        this->iYPos__ = iYPos;
    }
    inline void vSetDir(PLAYER_DIRECTION eDir)
    {
        this->eDirection__ = eDir;
    }
    inline void vIncrementScore()
    {
        this->iScore__++;
    }
    inline void iReset()
    {
        this->iXPos__ = this->iOriginalXPos__;
        this->iYPos__ = this->iOriginalYPos__;
    }

    // functions
    Player(int iXPos, int iYPos, int iUpChar, int iDownChar);
    int iMove();
};
} // namespace Players

#endif