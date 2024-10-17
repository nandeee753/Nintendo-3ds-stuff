#ifndef IMCC_H_
#define IMCC_H_

#include "./input_combinations.inc"

#define MAX_INPUT_COMBINATIONS 32
#define MAX_INPUT_COMBINATION_NAME_LENGTH 30
#define MAX_COMBINED_INPUTS 32

extern InputCombination *createInputCombination(const char name[], const u32 keyInputs[], const unsigned char inputsLength, const void (*fn)());
extern void deleteInputCombination(InputCombination *cheatCode);

extern void checkForInputCombinations(u32 *curKey);

#endif // IMCC_H_
