#include <stdio.h>

/* print file contents to stdout */
int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc < 2)
        fp = stdin;              /* no argument: use stdin */
    else
        fp = fopen(argv[1], "r");

    if (fp == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[1]);
        return 1;
    }

    c = getc(fp);
    while (c != EOF) {           /* until end of file */
        putc(c, stdout);
        c = getc(fp);
    }

    if (fp != stdin)
        fclose(fp);
    return 0;
}
