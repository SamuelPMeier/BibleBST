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
   double delta;
   int a1, a2, b1, b2, di = 1;
   bool b;


   if (y1 > y2)
      swap(&y1, &y2);

   double dx = abs(x2 - x1);
   double dy = abs(y2 - y1);

   if (dy < 0) {
      dy = -dy;
      di = -1;
   }

   if (dx < 0) {
      dx = -dx;
      di = -1;
   }

   if (dy < dx) {
      if (x1 > x2) {
         swap(&x1, &x2);
         swap(&y1, &y2);
      }

      a1 = y1;
      a2 = y2;
      b1 = x1;
      b2 = x2;
      b = true;
   }
   else {
      if (y1 > y2) {
         swap(&x1, &x2);
         swap(&y1, &y2);
      }

      a1 = x1;
      a2 = x2;
      b1 = y1;
      b2 = y2;
      b = false;
   }

   delta = 2*dx-dy;

   for (; a1 <= a2; a1++) {
      point(b?b1:a1, b?a1:b1);

      if (delta > 0) {
         b ? a1 : b1 += di;
         delta -= 2*b?dx:dy;
      }

      delta += 2*b?dy:dx;
   }
}

void graphics::point(int x, int y) {
   SetPixel(output, x, y, color);
}