#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include "../inc/wrap.h"

void perr_exit(const char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}


int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr) {
    int n;

again:
    if ((n = accept(fd, sa, salenptr)) < 0) {
        if ((errno == ECONNABORTED) || (errno == EINTR))
            goto again;
        else 
          perr_exit("accept error");
    }
    return n;
}

int Connect(int fd, const struct sockaddr *sa, socklen_t salen) {
    int n;

    if ((n = connect(fd, sa, salen)) < 0)
        perr_exit("connect error");

    return n;
}
