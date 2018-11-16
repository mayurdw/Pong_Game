/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#ifndef UI_H
#define UI_H

#include "player.h"
namespace UserInterface
{
class UI
{
private:
  int iWidth__;
  int iHeight__;
  int iP1XPos__;
  int iP1YPos__;
  int iP2XPos__;
  int iP2YPos__;
  int iBallXPos__;
  int iBallYPos__;

public:
  inline void vSetP1Location(int iP1XPos, int iP1YPos)
  {
    iP1XPos__ = iP1XPos;
    iP1YPos__ = iP1YPos;
  }

  inline void vSetP2Location(int iP2XPos, int iP2YPos)
  {
    iP2XPos__ = iP2XPos;
    iP2YPos__ = iP2YPos;
  }

  inline void vSetBallPos(int iBallXPos, int iBallYPos)
  {
    iBallXPos__=iBallXPos;
    iBallYPos__=iBallYPos;
  }
  
  UI(int iWidth, int iHeight);
  int iDrawGrid();
};
} // namespace UserInterface
#endif