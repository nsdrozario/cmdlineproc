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

    for (auto s : c.args) {
        std::cout << s << std::endl;
    }

    return 0;

}
