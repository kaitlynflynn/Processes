// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main()
{
    // Your code here
    char inbuf[MSGSIZE];
    int p[2], pid, nbytes;

    if (pipe(p) < 0) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    if ((pid = fork()) > 0) {
        printf("child writing to pipe\n");
        write (p[1], msg1, MSGSIZE);
        write (p[1], msg2, MSGSIZE);
        write (p[1], msg3, MSGSIZE);
    } else {
        close(p[1]);
        printf("parent reading from pipe\n");
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) {
            printf("%s\n", inbuf);
        }
        if (nbytes != 0) {
            exit(2);
        }
        printf("finished reading\n");
    }

    return 0;
}

//instructor solve

int main()
{
    char inbuf[MSGSIZE];
    int p[2]; //2 holds the read/write files that we get when we call pipe

    if (pipe(p) < 0) { //p = array
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(2);
    }

    else if (rc == 0) {
        printf("child writing to pipe\n");

        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
    }

    else {
        wait(NULL);

        close(p[1]);
        printf("parent reading from pipe\n");

        while (read(p[0], inbuf, MSGSIZE) > 0) {
            printf("%s\n", inbuf);
        }

        printf("finished reading\n");
    }

    return 0;
}
