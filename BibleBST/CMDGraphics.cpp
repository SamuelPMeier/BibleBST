#include <cmath>

#include "CMDGraphics.h"

void swap(int * x, int * y) {
   int i = *x;
   *x = *y;
   *y = i;
}

graphics::graphics(HDC disp, COLORREF col) {
   output = disp;
   color = col;
}

void graphics::line(int x1, int y1, int x2, int y2) {
   double dErr, error = 0;
   int y = y1;

   if (x1 > x2)
      swap(&x1, &x2);
   if (y1 > y2)
      swap(&y1, &y2);

   double dx = x2 - x1;
   double dy = y2 - y1;

   dErr = dx ? abs(dy/dx) : 0;

   for (int x = x1; x <= x2; x++) {
      point(x, y);
      error += dErr;
      if (error >= 0.5) {
         y += ((int)dy);
         error -= 1;
      }
   }
}

void graphics::point(int x, int y) {
   SetPixel(output, x, y, color);
}