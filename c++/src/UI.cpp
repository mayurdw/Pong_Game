/*
    Author : Mayur Wadhwani
    Created: Nov 2018
*/

#include <iostream>
#include <cstdlib>
#include "UI.h"

using namespace std;
using namespace UserInterface;

UI::UI(int iWidth, int iHeight)
{
    iWidth__ = iWidth;
    iHeight__ = iHeight;
}

int UI::iDrawGrid()
{
    int iX = 0, iY = 0;
    system("clear");

    while (iY < this->iHeight__)
    {
        iX = 0;
        while (iX < this->iWidth__)
        {
            if (iY == 0 || iY == (this->iHeight__ - 1))
            {
                cout << "_";
            }
            else if ((iY >= this->iP1YPos__ - 2 && iY <= this->iP1YPos__ + 2) &&
                     (iX == this->iP1XPos__))
            {
                cout << "|";
            }
            else if ((iY >= this->iP2YPos__ - 2 && iY <= this->iP2YPos__ + 2) &&
                     (iX == this->iP2XPos__))
            {
                cout << "|";
            }
            else if (iY == this->iBallYPos__ - 2 && iX == this->iBallXPos__)
            {
                cout << "*";
            }
            else if (iY == this->iBallYPos__ - 1 && (iX >= this->iBallXPos__ - 1 && iX <= this->iBallXPos__ + 1))
            {
                cout << "*";
            }
            else if (iY == this->iBallYPos__ && (iX >= this->iBallXPos__ - 2 && iX <= this->iBallXPos__ + 2))
            {
                cout << "*";
            }
            else if (iY == this->iBallYPos__ + 1 && (iX >= this->iBallXPos__ - 1 && iX <= this->iBallXPos__ + 1))
            {
                cout << "*";
            }
            else if (iY == this->iBallYPos__ + 2 && iX == this->iBallXPos__)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            iX++;
        }
        cout << endl;
        iY++;
    }
    return 0;
}