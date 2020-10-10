#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
  char buf[1024];
  char *command[MAXARG];
  while (1) {
    gets(buf, sizeof(buf));
    if (strlen(buf) == 0) {
      break;
    }

    buf[strlen(buf) - 1] = '\0';
    if (fork() == 0) {
      for (int i = 1; i <= argc; i++) {
        command[i - 1] = argv[i];
      }
      command[argc - 1] = buf;
      exec(argv[1], command);
    } else {
      wait(0);
    }
  }

  exit(0);
}