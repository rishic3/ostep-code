#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // Open a new file for writing
    const int fd = open("./hw2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if (fd < 0) {
        fprintf(stderr, "open failed\n");
        exit(1);
    }

    // Fork a child process
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        char buff[100];
        int len = sprintf(buff, "hello i'm child (pid:%d)\n", (int) getpid());
        write(fd, buff, len);
        for (int i = 0; i < 20; i++) {
            sleep(1);
            int len = sprintf(buff, "child sleeping... %d\n", i);
            write(fd, buff, len);
        }
    } else {
        // Parent process
        char buff[100];
        int len = sprintf(buff, "hello i'm parent of %d (pid:%d)\n", rc, (int) getpid());
        write(fd, buff, len);
        for (int i = 0; i < 20; i++) {
            sleep(1);
            int len = sprintf(buff, "parent sleeping... %d\n", i);
            write(fd, buff, len);
        }
    }
    close(fd);
    return 0;
}