/*
    Author:Mayur Wadhwani
    Created: Nov 2018
*/

#include <iostream>
#include <ball.h>

using namespace std;

void vPrintLine(int iTestCount, const char *pszText)
{
    cout << "------------- " << iTestCount << ". " << pszText << " -------------" << endl;
}

int main(int argc, char const *argv[])
{
    Ball cBall(10, 10);
    int iTestCount = 1;

    cout << "------------- STARTING TESTS FOR BALL LIB -------------" << endl;
    vPrintLine(iTestCount++, "GETTER TEST FOR BALL.H");

    if (cBall.iGetXPos() != 10 || cBall.iGetYPos() != 10)
    {
        cout << "Test" << iTestCount << "Failed" << endl;
    }

    vPrintLine(iTestCount++, "SETTER TEST FOR BALL.H");

    cBall.vSetXPos(20);
    cBall.vSetYPos(30);

    if (cBall.iGetXPos() != 20 || cBall.iGetYPos() != 30)
    {
        cout << "Test" << iTestCount << "Failed" << endl;
    }

    cout << "------------- " << iTestCount - 1 << " TESTS SUCCESSFUL -------------" << endl;

    return 0;
}
