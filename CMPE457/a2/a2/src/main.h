// main.h

#ifndef MAIN_H
#define MAIN_H

#include "headers.h"

extern GLFWwindow *window;

class Canvas;
extern Canvas *canvas;

class StrokeFont;
extern StrokeFont *strokeFont;

class Editor;
extern Editor *editor;

typedef enum { UP, DOWN } KeyState;
extern KeyState upKey, downKey, leftKey, rightKey, spaceBar;

extern int screenWidth, screenHeight;

#endif
