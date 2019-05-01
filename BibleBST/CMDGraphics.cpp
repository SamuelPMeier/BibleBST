#include <cmath>

#include "CMDGraphics.h"

void swap(int * x, int * y) {
   int i = *x;
   *x = *y;
   *y = i;
}

graphics::graphics() {
   output = GetDC(GetConsoleWindow());
   color = RGB(MAX_VAL, MAX_VAL, MAX_VAL);
}

graphics::graphics(HDC disp, COLORREF col) {
   output = disp;
   color = col;
}

void graphics::line(int x1, int y1, int x2, int y2) {
   if (abs(y2 - y1) < abs(x2 - x1)) {
      if (x1 > x2)
         lineLow(x2, y2, x1, y1);
      else
         lineLow(x1, y1, x2, y2);
   }
   else {
      if (y1 > y2)
         lineHigh(x2, y2, x1, y1);
      else
         lineHigh(x1, y1, x2, y2);
   }
}

void graphics::lineHigh(int x1, int y1, int x2, int y2) {
   int dx = x2 - x1;
   int dy = y2 - y1;

   int di = 1;

   if (dx < 0) {
      di = -1;
      dx = -dx;
   }

   int delta = 2*dx - dy;
   int x = x1, y = y1;

   for (; y < y2; y++) {
      point(x, y);

      if (delta > 0) {
         x += di;
         delta -= 2*dy;
      }
      delta += 2*dx;
   }
}

void graphics::lineLow(int x1, int y1, int x2, int y2) {
   int dx = x2 - x1;
   int dy = y2 - y1;

   int di = 1;

   if (dy < 0) {
      di = -1;
      dy = -dy;
   }
   
   int delta = 2*dy - dx;
   int x = x1, y = y1;

   for (; x < x2; x++) {
      point(x, y);

      if (delta > 0) {
         y += di;
         delta -= 2*dx;
      }
      delta += 2*dy;
   }
}

void graphics::point(int x, int y) {
   SetPixel(output, x, y, color);
}