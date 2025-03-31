#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int x = 100;
    fprintf(stdout, "parent - x: %d (pid:%d)\n", x, (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        fprintf(stdout, "child - x: %d (pid:%d)\n", x, (int) getpid());
        x += 1;
        fprintf(stdout, "child - x: %d (pid:%d)\n", x, (int) getpid());
    } else {
        int rc_wait = wait(NULL);
        assert(rc_wait >= 0);
        x -= 1;
        fprintf(stdout, "parent - x: %d (pid:%d)\n", x, (int) getpid());
    }
    return 0;
}