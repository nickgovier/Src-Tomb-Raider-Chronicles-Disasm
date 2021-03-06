#ifndef DISPLAY_H
#define DISPLAY_H

#include "GLOBAL.H"

void InitWindow(int x, int y, int width, int height, int nearz, int farz, int view_angle);
void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag);
void DrawChar(uint16_t x, uint16_t y, uint16_t a2, CHARDEF* def);

extern bool in_loading_screen;

#endif