#include "my.h"

int my_strrindex(char* cptr, char c) {
  if (!cptr || !c) {
    return -1;
  }
  int i = -1;
  int res = i;
  while (*cptr != '\0') {
    i++;
    if (*cptr == c) {
      res = i;
    }
    cptr++;
  }
  return res;
}
