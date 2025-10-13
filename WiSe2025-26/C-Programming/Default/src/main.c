#define NOB_IMPLEMENTATION
#include "../thirdparty/nob.h/nob.h"

int main(int argc, char **argv) {
  NOB_UNUSED(argc);
  NOB_UNUSED(argv);
  nob_log(NOB_INFO, "Hello, World!\n");
  return 0;
}
