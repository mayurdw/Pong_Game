/*
    Author: Mayur Wadhwani
    Created: Jan 2019
*/

#ifndef ABS_LAYER_H
#define ABS_LAYER_H

#if WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h> // for usleep
#include <termios.h>
#include <fcntl.h>
#include <iostream>
#endif

bool kbhit(int *piKeyPressed)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    *piKeyPressed = 0;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        *piKeyPressed = ch;
        return true;
    }

    return false;
}


void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

#endif