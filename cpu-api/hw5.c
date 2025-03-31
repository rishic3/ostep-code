#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc_1 = fork();
    if (rc_1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc_1 == 0) {
        printf("hello, I am child 1 (pid:%d)\n", (int) getpid());
    } else {
        int rc_2 = fork();
        if (rc_2 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc_2 == 0) {
            printf("hello, I am child 2 (pid:%d)\n", (int) getpid());
        } else {
            int wc = waitpid(rc_1, NULL, 0);
            assert(wc >= 0);
            printf("hello, I am parent (pid:%d)\n", (int) getpid());
        }
    }
    return 0;
}