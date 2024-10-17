typedef struct _InputCombination InputCombination;

struct _InputCombination {
  char name[32];
  u32 keyInputs[32];
  unsigned char length;
  unsigned char index;
  void (*fn)();
};