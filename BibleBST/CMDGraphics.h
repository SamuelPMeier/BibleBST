#pragma once

#include <windows.h>

#include "utility.h"

class graphics {
private:
   HDC output;
   COLORREF color;
   void lineHigh(int, int, int, int);
   void lineLow(int, int, int, int);

public:
   graphics(HDC, COLORREF);
   graphics();

   void setColor(COLORREF c) { color = c; }

   void point(int, int);
   void line(int, int, int, int);
};