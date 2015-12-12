# cscript

cscript is a scripting language for C and C++

When you want to accomplish a relatively small but non-trivial task and bash and awk don't supply the functionality you need, cscript can provide the solution.

There are lots of scripting languages like perl and python that can be used for general purpose scripting, but cscript has a number of advantages over most other scripting languages:

* cscript scripts are precompiled, so the script runs much faster than any interpreted scripting language script.
* cscript has access to the entire list of standard C library functions, if you can do it in C, you can do it in cscript.
* cscript is fully standards compliant. C is a well understood and robust language, and cscript inhereits all that experience.

To use script simply clone and make install...

    git clone git@github.com:nixomose/cscript.git
    cd cscript/cscript
    sudo make install

From there you can create a she-bang script written entirely in C.

Then simply chmod 755 your script and run it.

    chmod 755 test.c
    ./test.c

...and stare in wonder how you lived without the best scripting language on the planet for so long.

Pull up test.c in your favorite editor for an example script.

# What's actually going on.

It is pretty much the exact opposite of autotools

