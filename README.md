# cmdlineproc

A header-only, lightweight library for processing command line arguments and options/flags using only C++ STL structures and methods.

## How to use

First, make sure you Include `cmdlineproc.hpp` in your project's include search paths.
Then, for example, we can do the following code, which outputs all arguments of the flag `-b`:

```
#include <iostream>
#include <cmdlineproc.hpp>

cmdlineproc::cmd_args c; // initialize the cmd_args class

int main (int argc, char *argv[]) {

    c.set_flag("-h"); // register the -h option, requiring 0 arguments
    c.set_flag("-a", 1); // register the -a option, which will require one argument after the flag (for example, [program] -a [arg])  
    c.set_flag("-b", 2); // same as -a but with two arguments (e.g. [program] -b [arg1] [arg2])
    
    c.init_args(argc, argv); // load command line arguments
    auto it_range = c.flag_args.equal_range("-b"); // get an iterator pair with all arguments of flag "-b"
   
    for (auto it1 = it_range.first; it1 != it_range.second; it1++) {
        std::cout << (*it1).second << std::endl; // print all arguments of flag "-b"
    }

    return 0;

}

```

When running this program with the arguments `-b string1 string2`, the output should be:

```
string1
string2
```

Regular arguments that are passed to the program, not related to any flag/option, can be found in the vector `cmd_args.args`.
Flags/options that are passed to the program that require 0 arguments can be found in the vector `cmd_args.flags`.
Any flags that aren't registered with `cmd_args.set_flag` will be ignored.

# Installing

Use the following command:

```
sudo make install
```

You can edit the install path variable in the Makefile if you don't want `cmdlineproc.hpp` to be installed to `/usr/include`.

## License

This library is under the MIT License.
