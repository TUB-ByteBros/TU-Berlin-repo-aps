#include <stdio.h>
#include <stdlib.h>
#define NOB_STRIP_PREFIX
#define NOB_IMPLEMENTATION
#include "thirdparty/nob.h/nob.h"
#define FLAG_IMPLEMENTATION
#include "thirdparty/flag.h/flag.h"

typedef struct {
  char **items;
  int capacity;
  int count;
} MY_Flags_args;

Cmd cmd = {0};

MY_Flags_args ARGS = {0};

void usage(FILE *stream) {
  fprintf(stream, "Usage: ./example [OPTIONS] [--] [ARGS]\n");
  fprintf(stream, "OPTIONS:\n");
  flag_print_options(stream);
}

int main(int argc, char **argv) {

  da_append_many(&ARGS, argv, argc);

  NOB_GO_REBUILD_URSELF(argc, argv);

  bool help = false;
  bool hhelp = false;

  bool run_build = false;
  bool rrun_build = false;

  flag_bool_var(&help, "-help", false, "Print this help");
  flag_bool_var(&hhelp, "h", false, "Print this help");
  flag_bool_var(&rrun_build, "r", false, "Run build");
  flag_bool_var(&run_build, "run_build", false, "Run build");

  cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", "main", "src/main.c");
  if (!cmd_run(&cmd))
    return 1;
  cmd.count = 0;

  if (!flag_parse(ARGS.count, ARGS.items)) {
    usage(stderr);
    flag_print_error(stderr);
    exit(1);
  }

  argc = flag_rest_argc();
  argv = flag_rest_argv();

  if (help) {
    usage(stdout);
    exit(0);
  }

  if (run_build || rrun_build) {
    cmd_append(&cmd, "./main");
    if (!cmd_run(&cmd))
      return 1;
  }

  return 0;
}
