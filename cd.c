#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void cd(char *dir) {
    char cwd[MAX_DIR_LEN];
    if (dir[0] == '/') {
        if (chdir(dir) != 0) {
            perror("cd");
        }
    } else {
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, dir);
        if (chdir(cwd) != 0) {
            perror("cd");
        }
    }
}

void cd_dash() {
    char *prev_dir = getenv("OLDPWD");
    if (prev_dir != NULL) {
        cd(prev_dir);
        printf("%s\n", prev_dir);
    } else {
        fprintf(stderr, "cd: OLDPWD not set\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dir|->\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-") == 0) {
        cd_dash();
    } else {
        cd(argv[1]);
    }

    return 0;
}
