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
    PLAYER_DIRECTION eDirection__;

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

    // functions
    Player(int iXPos, int iYPos);
    int iMove();
};
} // namespace Players

#endif