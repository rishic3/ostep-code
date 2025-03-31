#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

// Create two children, connect the stdout of one to the stdin of the other using pipe

int main(int argc, char *argv[]) {
    // Create pipe: pipefd[0] = read, pipefd[1] = write
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int rc_1 = fork();
    if (rc_1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc_1 == 0) {
        // child 1
        printf("hello, I am child 1 (pid:%d)\n", (int) getpid());
        // read from pipe
        char buf[100];
        read(pipefd[0], buf, 100);
        printf("child 1 read: %s\n", buf);
        exit(0);
    }

    int rc_2 = fork();
    if (rc_2 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc_2 == 0) {
        // child 2
        printf("hello, I am child 2 (pid:%d)\n", (int) getpid());
        // write to pipe
        char *msg = "hello child 1, i'm child 2";
        write(pipefd[1], msg, strlen(msg));
        exit(0);
    }

    // parent
    int wc_1 = wait(NULL);
    int wc_2 = wait(NULL);
    assert(wc_1 >= 0 && wc_2 >= 0);
    printf("parent is done waiting for children\n");
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
