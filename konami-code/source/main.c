#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

const u32 KONAMI_CODE[] = {KEY_DUP, KEY_DUP, KEY_DDOWN, KEY_DDOWN, KEY_DLEFT, KEY_DRIGHT, KEY_DLEFT, KEY_DRIGHT, KEY_B, KEY_A, KEY_SELECT};
const int KONAMI_CODE_LENGTH = sizeof(KONAMI_CODE) / sizeof(KONAMI_CODE[0]);

const char keysNames[32][32] = {
    "KEY_A", "KEY_B", "KEY_SELECT", "KEY_START",
    "KEY_DRIGHT", "KEY_DLEFT", "KEY_DUP", "KEY_DDOWN",
    "KEY_R", "KEY_L", "KEY_X", "KEY_Y",
    "", "", "KEY_ZL", "KEY_ZR",
    "", "", "", "",
    "KEY_TOUCH", "", "", "",
    "KEY_CSTICK_RIGHT", "KEY_CSTICK_LEFT", "KEY_CSTICK_UP", "KEY_CSTICK_DOWN",
    "KEY_CPAD_RIGHT", "KEY_CPAD_LEFT", "KEY_CPAD_UP", "KEY_CPAD_DOWN"};

void checkKeysCode(u32 key, int *index)
{
  printf("%ld\n", key);
  if (!key)
  {
    return;
  }
  if (KONAMI_CODE[*index] == key)
  {
    (*index)++;
    if (*index == KONAMI_CODE_LENGTH)
    {
      printf("konami code activated!");
      *index = 0;
    }
  }
  else
  {
    printf("reset\n");
    *index = 0;
  }

  printf("%d\n", *index);
}

int main()
{
  gfxInitDefault();
  consoleInit(GFX_TOP, NULL);

  int code_key_correct = 0;

  printf("KONAMI_CODE_LENGTH = %d\n", KONAMI_CODE_LENGTH);

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
      checkKeysCode(kDown, &code_key_correct);
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