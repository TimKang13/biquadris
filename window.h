#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  static const int NUM_COLORS = 13;
  unsigned long colours[NUM_COLORS];

 public:
  Xwindow(int width=500, int height=500, int background_color = 0);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue,
        SkyBlue, Orange, Yellow, Lime, Purple, Scarlet, Teal, 
        Brown};

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a rectangle with an outline
  void drawRectangleWithStroke(int x, int y, int width, int height, 
                                int fill_colour, int stroke_colour, int stroke_width);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour = Black);
};

#endif
