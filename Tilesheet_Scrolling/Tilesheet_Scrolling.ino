/*
  DEMO: Tilesheet Scrolling

  TEAM a.r.g.: http://www.team-arg.com/demos.html

  2015 - JO3RI

  Demo License: MIT : https://opensource.org/licenses/MIT

*/

#include "Arglib.h"
#include "bitmaps.h"

#define BACKGROUND_OFFSET_X     0
#define BACKGROUND_OFFSET_Y     0
#define NUMBER_OF_ROWS          8
#define NUMBER_OF_COLUMNS      16
#define PIXELSIZE_OF_TILES      8
#define SCROLL_SPEED            2


byte counter = 0;
byte mapPart1 = 0;
byte mapPart2 = 1;
int arraySize = sizeof(tilemaps) / sizeof(int);

Arduboy arduboy;

void setup() {
  arduboy.start();
  arduboy.setFrameRate(60);
  arduboy.clearDisplay();
  arduboy.display();
  arduboy.drawBitmap(0, 8, TEAMarg, 128, 64, WHITE);
  arduboy.display();
  delay(1500);
}
void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.clearDisplay();
  for (byte row = 0; row < NUMBER_OF_ROWS; row++)
  {
    for (byte column = 0; column < NUMBER_OF_COLUMNS; column++)
    {
      arduboy.drawBitmap(column * PIXELSIZE_OF_TILES + BACKGROUND_OFFSET_X, (row * PIXELSIZE_OF_TILES) + BACKGROUND_OFFSET_Y + counter, tilesheet[pgm_read_byte(&tilemaps[mapPart1][((row * NUMBER_OF_COLUMNS) + column)])], 8, 8, WHITE);
      arduboy.drawBitmap(column * PIXELSIZE_OF_TILES + BACKGROUND_OFFSET_X, (row * PIXELSIZE_OF_TILES) + BACKGROUND_OFFSET_Y + counter - (PIXELSIZE_OF_TILES * NUMBER_OF_ROWS), tilesheet[pgm_read_byte(&tilemaps[mapPart2][((row * NUMBER_OF_COLUMNS) + column)])], 8, 8, WHITE);
    }
  }
  if (arduboy.everyXFrames(SCROLL_SPEED)) counter++;

  if (counter == PIXELSIZE_OF_TILES * NUMBER_OF_ROWS)
  {
    counter = 0;
    mapPart1++;
    mapPart2++;
  }

  if (mapPart1 == arraySize)
  {
    mapPart1 = 0;
  }

  if (mapPart2 == arraySize)
  {
    mapPart2 = 0;
  }

  arduboy.display();
}
