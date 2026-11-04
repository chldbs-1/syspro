#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(void)
{
    struct passwd *user;
    struct group *group;

    user = getpwuid(getuid());
    printf("Real UID: %lu (%s)\n",
           (unsigned long)getuid(),
           user != NULL ? user->pw_name : "unknown");

    user = getpwuid(geteuid());
    printf("Effective UID: %lu (%s)\n",
           (unsigned long)geteuid(),
           user != NULL ? user->pw_name : "unknown");

    group = getgrgid(getgid());
    printf("Real GID: %lu (%s)\n",
           (unsigned long)getgid(),
           group != NULL ? group->gr_name : "unknown");

    group = getgrgid(getegid());
    printf("Effective GID: %lu (%s)\n",
           (unsigned long)getegid(),
           group != NULL ? group->gr_name : "unknown");

    return 0;
}
