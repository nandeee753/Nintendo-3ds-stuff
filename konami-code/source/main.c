#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "input_combinations.h"

const u32 KONAMI_CODE[] = {KEY_DUP, KEY_DUP, KEY_DDOWN, KEY_DDOWN, KEY_DLEFT, KEY_DRIGHT, KEY_DLEFT, KEY_DRIGHT, KEY_B, KEY_A, KEY_SELECT};
const unsigned char KONAMI_CODE_LENGTH = sizeof(KONAMI_CODE) / sizeof(KONAMI_CODE[0]);

void fn(void) {
  printf("Hello World!\n");
}

const char keysNames[32][32] = {
    "KEY_A", "KEY_B", "KEY_SELECT", "KEY_START",
    "KEY_DRIGHT", "KEY_DLEFT", "KEY_DUP", "KEY_DDOWN",
    "KEY_R", "KEY_L", "KEY_X", "KEY_Y",
    "", "", "KEY_ZL", "KEY_ZR",
    "", "", "", "",
    "KEY_TOUCH", "", "", "",
    "KEY_CSTICK_RIGHT", "KEY_CSTICK_LEFT", "KEY_CSTICK_UP", "KEY_CSTICK_DOWN",
    "KEY_CPAD_RIGHT", "KEY_CPAD_LEFT", "KEY_CPAD_UP", "KEY_CPAD_DOWN"
};


int main()
{
  gfxInitDefault();
  consoleInit(GFX_TOP, NULL);

  createInputCombination("konami code", KONAMI_CODE, KONAMI_CODE_LENGTH, &fn);

  u32 kDownOld = 0;
  u32 kHeldOld = 0;
  u32 kUpOld = 0;

  while (aptMainLoop())
  {
    hidScanInput();

    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();
    u32 kUp = hidKeysUp();

    if (kDown != kDownOld || kHeld != kHeldOld || kUp != kUpOld)
    {
      checkForInputCombinations(&kDown);

      if (kDown == KEY_START) { break; }

      for (int i = 0; i < 32; i++)
      {
        if (kDown & BIT(i))
          printf("%s down\n", keysNames[i]);
        if (kHeld & BIT(i))
          printf("%s held\n", keysNames[i]);
        if (kUp & BIT(i))
          printf("%s up\n", keysNames[i]);
      }
    }

    kDownOld = kDown;
    kHeldOld = kHeld;
    kUpOld = kUp;

    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
  }

  gfxExit();
  return EXIT_SUCCESS;
}