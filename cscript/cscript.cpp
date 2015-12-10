/*  cscript.cpp
    Copyright (C) 2015 Stu Mark
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>

#ifndef VERSION_DATE
  #include "version.h"
#endif

#include "cscript.h"

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

int cscript::go(int num, char *opts[], char *link_options)
  {
    if (num < (optind+1))
      {
        printf("Missing filename parameter\n");
        return 1;
      }

    int realoptind = optind;
    int realparamcount = num - realoptind;
    char *filename = opts[optind++];

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
    int slen = strlen(filename) + 100 + strlen(link_options);
    char *slash = rindex(filename, '/');
    if (slash == NULL)
      slash = filename;
    else
      slash = slash + 1; // skip the slash
    char cmd[slen];

    char binname[slen];
    sprintf(binname, "/tmp/%s.%d", slash, getpid());

    char empty[1] = {'\0'};
    if (link_options == NULL)
      link_options = empty;
    sprintf(cmd, "gcc -Wall -o %s -xc++ - %s", binname, link_options);
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
            linecount++;
            if (strlen(line) > 1)
              {
                if (line[0] == '#' && line[1] == '!')
                  continue; // if the first line is shebang, skip it
              }
          }
        fprintf(gcc, "%s", line);
        fprintf(stdout, "%s", line);
      }

    free(line);
    fclose(f);
    f = NULL;
    int gccretcode = pclose(gcc);
    gcc = NULL;

    if (gccretcode != 0)
      {
        printf("\ncscript: compile failed.\n");
        return 1;
      }

    // now, if it compiled, run it
    char *scriptopts[realparamcount];
    /* Copy over the params we got skipping the first one. */
    scriptopts[0] = filename;
    int lp;
    for (lp = 1; lp < realparamcount+1; lp++)
      { // realparamcount+1 will copy the null
        scriptopts[lp] = opts[realoptind + lp];
        printf("Passing param #%d %s\n",lp, scriptopts[lp]);
      }
    hey_killer(binname);
    int ret = execv(binname, scriptopts);
    if (ret == -1)
      {
        printf("Unable to start %s, errno: %d\n", cmd, errno);
        return 1;
      }
    return 0;
  }

void cscript::hey_killer(const char *binname)
  {
    /* we want to delete the process out of temp but we have to wait
     * for the process to start to do that, but by the time the process starts,
     * we lose execution control so we fork, wait 10 seconds then kill then exit. */

    int childpid = fork();
    if (childpid == -1)
      {
        /* If we fail to fork, then the binary will sit in /tmp and get cleaned up
         * by somebody else. */
        return;
      }
    if (childpid != 0)
      return; // we're the parent, go run the binary.

    sleep(5);
    // not much point in checking for errors.
    unlink(binname);
    exit(0);
  }

static struct option long_options[] = {
  { "help", no_argument, 0, 'h' },
  { "link", required_argument, 0, 'l' },
  { 0, 0, 0, 0 }
};

void print_help()
  {
    printf("cscript. version %s.\n\n", VERSION_DATE);
    printf("cscript [options] [program file] [parameters]\n\n");
    printf("Options:\n");
    printf("  -h, --help\n");
    printf("  Help: display this help and exit.\n");
    printf("\n");
    printf("  -l\n");
    printf("  add a library to the link list.\n");
    printf("\n");
  }


void process_command_line(int argc, char *argv[], char **link_options)
  {
    while (1)
      {
        int idx = 0;
        int c = getopt_long(argc, argv, "hl:", long_options, &idx);
        if (c == -1)
          break;
        if (c == 0)
          c = long_options[idx].val;
        switch (c)
          {
            case 'h':
              print_help();
              exit(0);
            case 'l':
              if (optarg == NULL)
                {
                  printf("Library required.\n");
                  exit(1);
                }
              if (*link_options == NULL)
                {
                  *link_options = (char *)malloc(strlen(optarg) + 10);
                  **link_options = '\0';
                }
              else
                *link_options = (char *)realloc(*link_options, strlen(*link_options) + strlen(optarg) + 10);
              strcat(*link_options, " -l");
              strcat(*link_options, optarg);
              break;
            case '?':
              print_help();
              printf("Unrecognized argument.\n" );
              exit(1);
          }
      }
  }


int main(int num, char *opts[])
  {
    /* read std in and print it out, and pipe to gcc */
    char *link_options = NULL;
    process_command_line(num, opts, &link_options);
    cscript c;
    int ret = c.go(num, opts, link_options);
    if (link_options != NULL)
      free(link_options);
    return ret;
  }
