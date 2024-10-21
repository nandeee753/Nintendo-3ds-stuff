#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <3ds.h>

#include "./input_combinations.h"
#include "./input_combinations.inc"

static InputCombination *inputCombinations[MAX_INPUT_COMBINATIONS];
static unsigned char inputCombinationsLength = 0;

InputCombination *createInputCombination(const char name[], const u32 keyInputs[], const unsigned char inputsLength, const void (*fn)()) {
  InputCombination *inputCombination = malloc(sizeof(InputCombination));
  assert(strlen(name) <= MAX_INPUT_COMBINATION_NAME_LENGTH)// TODO : add asserts to avoid putting strings too long
  strcpy(inputCombination->name, name);
  memcpy(inputCombination->keyInputs, keyInputs, inputsLength * sizeof(u32));
  inputCombination->length = inputsLength;
  inputCombination->index = 0;
  inputCombination->fn = fn;
  
  inputCombinations[inputCombinationsLength] = inputCombination;
  inputCombinationsLength++;
  
  return inputCombination;
}

void deleteInputCombination(InputCombination *inputCombination) { 
  unsigned char index = 0;
  while (inputCombinations[index] != inputCombination) { index++; }
  for (int i = index; i < inputCombinationsLength; i++) { inputCombinations[i] = inputCombinations[i+1]; }
  inputCombinationsLength--;
  free(inputCombination); 
}

void checkInputCombination(u32 *curKey, InputCombination *code) {
  if (code->keyInputs[code->index] == *curKey) { 
    (code->index)++; 
    if (code->index == code->length) { printf("%s activated\n", code->name); (*(code->fn))(); }
    else { return; }
  }
  code->index = 0;
}

void checkForInputCombinations(u32 *curKey) {
  if (inputCombinationsLength == 0) return;
  if (!*curKey) return;
  for (int i = 0; i < inputCombinationsLength; i++) { checkInputCombination(curKey, inputCombinations[i]); }
}
