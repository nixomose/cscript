#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#ifndef VERSION_DATE
  #include "version.h"
#endif

#include "cscript.h"

/* apparently if you specify the language you can pipe
 gcc -o lexer.o -xc -
 now, how to link...
 */

cscript::cscript()
  {
    f = NULL;
    gcc = NULL;
    pid = 0;
    pipefds[0] = 0;
    pipefds[1] = 0;
  }

cscript::~cscript()
  {
    if (f != NULL)
      fclose (f);
    f = NULL;
    if (gcc !=  NULL)
      pclose(gcc);
    gcc = NULL;
  }

int cscript::go(int num, char *opts[])
  {
    if (num < 2)
      {
        printf("Missing first parameter: filename\n");
        return 1;
      }
//    int lp;
//    for (lp = 0; lp < num; lp++)
//      {
//        printf ("param #%d: %s\n", lp, opts[lp]);
//      }

    char *filename = opts[1];

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    f = fopen(filename, "r");
    if (f == NULL)
      {
        printf("Unable to open input file: %s errno: %d\n", filename, errno);
        return 1;
      }

    /* we have the file, do our preprocessing on it and pipe to gcc.
     * start the pipe. */
    int slen = strlen(filename) + 100;
    char *slash = rindex(filename, '/');
    if (slash == NULL)
      slash = filename;
    else
      slash = filename + 1; // skip the slash
    char cmd[slen];

    // first, we delete any old copy if there.
    sprintf(cmd, "/tmp/%s.bin", slash);
    int ret = unlink(cmd);
    if (ret != 0)
      {
        if (errno != ENOENT) // not there is okay
          {
            printf("Unable to remove existing script binary: %s errno: %d\n", cmd, errno);
            return 1;
          }
      }

    sprintf(cmd, "gcc -Wall -o /tmp/%s.bin -xc -", slash);
    gcc = popen(cmd, "w");
    if (gcc == NULL)
      {
        printf("Unable to start gcc, errno: %d\n", errno);
        return 1;
      }

    int linecount = 0;
    while ((read = getline(&line, &len, f)) != -1)
      {
        if (linecount == 0)
          {
            line[0] = '/';
            line[1] = '/';
          }
        fprintf(gcc, "%s", line);
        linecount++;
      }

    free(line);
    fclose(f);
    f = NULL;
    fclose(gcc);
    gcc = NULL;

    // now, if it compiled, run it
    sprintf(cmd, "/tmp/%s.bin", slash);
    char *scriptopts[num];
    /* Copy over the params we got skipping the first one. */
    scriptopts[0] = filename;
    int lp;
    for (lp = 1; lp < num; lp++)
      { // lp+1 will copy the null
        scriptopts[lp] = opts[lp+1];
        printf("Passing param #%d %s\n",lp, scriptopts[lp]);
      }
    ret = execv(cmd, scriptopts);
    if (ret == -1)
      {
        printf("Unable to start %s, errno: %d\n", cmd, errno);
        return 1;
      }
    return 0;
  }


int main(int num, char *opts[])
  {
    /* read std in and print it out, and pipe to gcc */
    cscript c;
    return c.go(num, opts);
  }
