#include "kernel/types.h"
#include "user/user.h"

int main(void) {
  int p[2];
  char buf[100] = {};

  pipe(p);
  if (fork() == 0) {
    read(p[0], buf, sizeof(buf));
    printf("%d: %s", getpid(), buf);
    close(p[0]);

    write(p[1], "received pong\n", 14);
    close(p[1]);
  } else {
    write(p[1], "received ping\n", 14);
    close(p[1]);
    wait(0);

    read(p[0], buf, sizeof(buf));
    printf("%d: %s", getpid(), buf);
    close(p[0]);
  }

  exit(0);
}