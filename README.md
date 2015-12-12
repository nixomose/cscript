# cscript

cscript is a scripting language for C and C++

When you want to accomplish a relatively small but non-trivial task and bash and awk don't supply the functionality you need, cscript can provide the solution.

There are lots of scripting languages like perl and python that can be used for general purpose scripting, but cscript has a number of advantages over most other scripting languages:

* cscript scripts are precompiled, so the script runs much faster than any interpreted scripting language script.
* cscript has access to the entire list of standard C library functions, if you can do it in C, you can do it in cscript.
* cscript is fully standards compliant. C is a well understood and robust language, and cscript inhereits all that experience.

To use cscript simply clone and make install...

    git clone git@github.com:nixomose/cscript.git
    cd cscript/cscript
    sudo make install

From there you can create a she-bang script written entirely in C.

Then simply chmod 755 your script and run it.

    chmod 755 test.c
    ./test.c

...and stare in wonder how you lived without the best scripting language on the planet for so long.

Pull up test.c in your favorite editor to see an example script.

    #!/usr/bin/cscript -lm

    #include <stdio.h>
    #include <math.h>

    int main(int num, char *opts[])
      {
        printf("Hi from stu.\n");
        printf("These are the params I got:\n");
        int lp;
        for (lp = 0; lp < num; lp++)
          {
            printf ("param (%d) #%d: %s\n", (int)exp2(lp), lp, opts[lp]);
          }
        
        return 0;
      }


If you use functions that aren't in libc you can add -l<libname> on the she-bang line to include the library in the precompile step. In test.c I use the exp2 function which is in libm.

If you need to pass parameters to your script that shouldn't get picked up by the cscript process you can use the -- flag.

    ./test.c -lm -- --flag-for-script

output:

    Hi from stu.
    These are the params I got:
    param (1) #0: ./test.c
    param (2) #1: --flag-for-script

In that example -lm is passed to cscript for precompiling, and --flag-for-script is passed to the script, you can see the script picked it up as its first parameter.

# Requirements

cscript requires gcc to be installed (for C scripts) and g++ (for C++ scripts) 

# Web site

    http://thecscript.com
    

# What's actually going on.

For 10-15 years now I've wanted a scripting language that was C-like.

The closest thing that exists is awk which is pretty good, but it's geared towards text input parsing and I really just wanted to write a small C program without having to make a makefile or having to keep typing gcc -o file file.c all the time.

So I created a process that can read in a source file, pass it to gcc, create the output file and run it in one step. Thus cscript was born. What makes it workable compared to 10 years ago is that now processors are so fast, you don't notice the compiling step.
Once you start treating it like a scripting language, it becomes incredibly useful. You edit the source file and run it. Just like any other scripting language.

You can think about it this way: It is pretty much the exact opposite of autotools.

If you want to see how some people really have gone off the rails in terms of getting things done, look at the wikipedia page for autotools, you'll find this picture:

    https://en.wikipedia.org/wiki/GNU_build_system#/media/File:Autoconf-automake-process.svg

cscript is the exact opposite. You don't even have to worry about compiling anything, or configuring anything, you just run your source file and it executes.

# Future plans

I'm going to add the ability to pass more compiler switches to the source file so people who feel the need to compile position independant code can do so.
Maybe other gcc languages can be supported.
Suggestions welcome.




