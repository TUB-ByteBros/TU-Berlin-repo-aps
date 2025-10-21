#include <stdlib.h>
#define NOB_STRIP_PREFIX
#define NOB_IMPLEMENTATION
#include "nob.h"
#define FLAG_IMPLEMENTATION
#include "flag.h"

typedef struct
{
  char **items;
  int capacity;
  int count;
} MY_Flags_args;

Cmd cmd = {0};

MY_Flags_args ARGS = {0};

int group = 2;

char *BUILD_DIR = "./build";
char *PRACTICE_DIR;
char *EX_DIR;
char *EX_TEST;
char *PRACTICE_TEST;
char *EX_TEST_C;
char *PRACTICE_TEST_C;

void cmd_cc()
{
#ifdef _WIN32
  cmd_append(&cmd, "clang");
#else
  cmd_append(&cmd, "cc");
#endif

  cmd_append(&cmd, "-std=c11", "-Wall", "-lm");
}

void usage(FILE *stream)
{
  fprintf(stream, "Usage: ./example [OPTIONS] [--] [ARGS]\n");
  fprintf(stream, "OPTIONS:\n");
  flag_print_options(stream);
}

int main(int argc, char **argv)
{

  da_append_many(&ARGS, argv, argc);

  NOB_GO_REBUILD_URSELF(argc, argv);

  EX_DIR = temp_sprintf("./%02d_Aufgaben", group);
  PRACTICE_DIR = temp_sprintf("./%02d_Uebungen", group);

  PRACTICE_TEST = temp_sprintf("%02dpractice_test.o", group);
  EX_TEST = temp_sprintf("%02dex_test.o", group);
  PRACTICE_TEST_C = temp_sprintf("%s/%02dpractice_test.c", PRACTICE_DIR, group);
  EX_TEST_C = temp_sprintf("%s/%02dex_test.c", EX_DIR, group);

  bool help = false;

  bool run_ex = false;

  bool run_practice = false;

  bool build_ex = false;

  bool build_practice = false;

  bool clean = false;

  flag_bool_var(&help, "-help", false, "Print this help");
  flag_bool_var(&help, "h", false, "Print this help");
  flag_bool_var(&rrun_ex, "rex", false, "Run Exercise");
  flag_bool_var(&run_ex, "-run_ex", false, "Run Exercise");
  flag_bool_var(&build_ex, "bex", false, "Build Exercise");
  flag_bool_var(&build_ex, "-build_ex", false, "Build Exercise");
  flag_bool_var(&run_practice, "rpr", false, "Run Practice");
  flag_bool_var(&run_practice, "-run_pr", false, "Run Practice");
  flag_bool_var(&build_practice, "bpr", false, "Build Practice");
  flag_bool_var(&build_practice, "-build_pr", false, "Build Practice");
  flag_bool_var(&clean, "-clean", false, "Clean build directory");

  if (!flag_parse(ARGS.count, ARGS.items))
  {
    usage(stderr);
    flag_print_error(stderr);
    exit(1);
  }

  argc = flag_rest_argc();
  argv = flag_rest_argv();

  if (help)
  {
    usage(stdout);
    exit(0);
  }

  if (build_ex)
  {

    if (!nob_mkdir_if_not_exists(BUILD_DIR))
      return 1;

    cmd_cc();
    cmd_append(&cmd, "-o", temp_sprintf("%s/%s", BUILD_DIR, EX_TEST));
    cmd_append(&cmd, temp_sprintf("-I%s", EX_DIR));
    cmd_append(&cmd, EX_TEST_C);
    if (!cmd_run(&cmd))
      return 1;
    cmd.count = 0;
  }

  if (build_practice)
  {

    if (!nob_mkdir_if_not_exists(BUILD_DIR))
      return 1;

    cmd_cc();
    cmd_append(&cmd, "-o", temp_sprintf("%s/%s", BUILD_DIR, PRACTICE_TEST));
    cmd_append(&cmd, temp_sprintf("-I%s", PRACTICE_DIR));
    cmd_append(&cmd, PRACTICE_TEST_C);
    if (!cmd_run(&cmd))
      return 1;
    cmd.count = 0;
  }

  if (run_ex)
  {
    set_current_dir(BUILD_DIR);
    cmd_append(&cmd, temp_sprintf("./%s", EX_TEST));
    if (!cmd_run(&cmd))
      return 1;
    cmd.count = 0;
    set_current_dir("..");
  }

  if (run_practice)
  {
    set_current_dir(BUILD_DIR);
    cmd_append(&cmd, temp_sprintf("./%s", PRACTICE_TEST));
    if (!cmd_run(&cmd))
      return 1;
    cmd.count = 0;
    set_current_dir("..");
  }

  if (clean)
  {
#ifdef _WIN32
    cmd_append(&cmd, "rmdir", "/s", "/q", BUILD_DIR);
#else
    cmd_append(&cmd, "rm", "-rf", BUILD_DIR);
#endif
    if (!cmd_run(&cmd))
      return 1;
    cmd.count = 0;
  }

  return 0;
}
