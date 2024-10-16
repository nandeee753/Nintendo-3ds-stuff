// IMCC stands for Input Method Cheat Codes

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <3ds.h>

#include "imcc.h"

static CheatCode *cheatCodes[MAX_CHEAT_CODES];
static unsigned char cheatCodesLength = 0;

CheatCode *createCheatCode(const char name[MAX_CHEAT_CODE_NAME_LENGTH], const u32 keyInputs[], const unsigned char inputsLength) {
  CheatCode *cheatCode = malloc(sizeof(CheatCode));
  
  strcpy(cheatCode->name, name);
  memcpy(cheatCode->keyInputs, keyInputs, inputsLength * sizeof(u32));
  cheatCode->length = inputsLength;
  cheatCode->index = 0;
  
  cheatCodes[cheatCodesLength] = cheatCode;
  cheatCodesLength++;
  
  return cheatCode;
}

void deleteCheatCode(CheatCode *cheatCode) { 
  unsigned char index = 0;
  while (cheatCodes[index] != cheatCode) { index++; }
  for (int i = index; i < cheatCodesLength; i++) { cheatCodes[i] = cheatCodes[i+1]; }
  cheatCodesLength--;
  free(cheatCode); 
}

void checkCheatCode(u32 *curKey, CheatCode *code) {
  if (code->keyInputs[code->index] == *curKey) { 
    (code->index)++; 
    if (code->index == code->length) { printf("%s activated\n", code->name); } // TODO : add a pointer to a function as variable in CheatCode so that when you activate the code, it runs the function
    else { return; }
  }
  code->index = 0;
}

void checkCheatCodes(u32 *curKey) {
  if (cheatCodesLength == 0) return;
  if (!*curKey) return;

  for (int i = 0; i < cheatCodesLength; i++) { checkCheatCode(curKey, cheatCodes[i]); }
}
