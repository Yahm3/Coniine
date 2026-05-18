#define NOB_IMPLEMENTATION

#include "nob.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define APP_VERSION "0.0.1"

bool generate_build_h();

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "gcc");
  nob_cmd_append(&cmd, "-ggdb");
  nob_cmd_append(&cmd, "main.c");
  nob_cmd_append(&cmd, "-o");
  nob_cmd_append(&cmd, "main");

  if (!generate_build_h()) {
    return 1;
  }

  if (!nob_cmd_run(&cmd)) {
    return 1;
  }
}

bool generate_build_h() {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  const char *path = "./build.h";
  nob_log(NOB_INFO, "Generating %s", path);

  FILE *f = fopen(path, "w");
  if (f == NULL) {
    nob_log(NOB_ERROR, "Failed to open %s for writing", path);
    return false;
  }
  Nob_String_Builder sb = {0};
  nob_sb_appendf(&sb, "#ifndef __BUILD_DATE__\n\n");
  nob_sb_appendf(&sb,
                 "#define __BUILD_DATE__ \"%d-%02d-%02d %02d:%02d:%02d\"\n",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
                 tm.tm_min, tm.tm_sec);
    nob_sb_appendf(&sb, "#define __CONIINE_VERSION__ \"%s\"\n", APP_VERSION);
    nob_sb_appendf(&sb, "#define __GIT_REPO__ \"%s\"\n", "https://github.com/Yahm3/Coniine.git");


  char *os = NULL;
#if defined(__linux__) || defined(__unix__)
  char *user = getenv("USER");
  os = "Linux/Unix";
#elif defined(_WIN32) || defined(_WIN64)
  os = "Windows";
#endif

  nob_sb_appendf(&sb, "#define __BUILD_BY__ \"%s\"\n", user);
  nob_sb_appendf(&sb, "#define __BUILD_OS__ \"%s\"\n", os);

  nob_sb_appendf(&sb, "\n#endif // RASEN_BUILD_H\n");
  fwrite(sb.items, 1, sb.count, f);

  nob_da_free(sb);
  fclose(f);
  nob_log(NOB_INFO, "Successfully generated %s", path);
  return true;
}
