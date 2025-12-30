#ifndef INPUT_H
#define INPUT_H

#include "var.h"

void input_update();

int getKey(int key);
int getKeyDown(int key);
int getKeyUp(int key);

int getMouseOver(Shape* s);
int getMouseButton(int button);
int getMouseButtonDown(int button);
int getMouseButtonUp(int button);

#endif // INPUT_H