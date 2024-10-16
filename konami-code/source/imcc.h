// IMCC stands for Input Method Cheat Codes

#ifndef IMCC_H_
#define IMCC_H_

// this definitions cannot be above 255 because of the use of unsigned chars as types for the index search
#define MAX_CHEAT_CODES 32
#define MAX_CHEAT_CODE_NAME_LENGTH 32
#define MAX_CHEAT_CODE_INPUTS 32

typedef struct _CheatCode CheatCode;
struct _CheatCode {
  char name[MAX_CHEAT_CODE_NAME_LENGTH];
  u32 keyInputs[MAX_CHEAT_CODE_INPUTS];
  unsigned char length;
  unsigned char index;
};

extern CheatCode *createCheatCode(const char name[MAX_CHEAT_CODE_NAME_LENGTH], const u32 keyInputs[], const unsigned char inputsLength);
extern void deleteCheatCode(CheatCode *cheatCode);

extern void checkCheatCodes(u32 *curKey);

#endif // IMCC_H_
