#pragma once

#include <windows.h>

class graphics {
private:
   HDC output;
   COLORREF color;

public:
   graphics(HDC, COLORREF);

   void point(int, int);
   void line(int, int, int, int);
};