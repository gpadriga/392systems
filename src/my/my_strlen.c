#include "my.h"

int my_strlen(char* c) {
  if (!c) {
    return -1;
  }
  int res = 0;
  while (*c != '\0') {
    res++;
    c++;
  }
  return res;
}
