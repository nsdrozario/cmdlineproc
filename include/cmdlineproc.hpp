/*

cmdlineproc.hpp (c) 2020 Nathaniel D'Rozario

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef CMDLINEPROC_HPP
#define CMDLINEPROC_HPP

#include <string>
#include <map>
#include <vector>

namespace cmdlineproc {

    class cmd_args {

        public:

            std::multimap<std::string, std::string> flag_args; // multimap with arguments for flags that have args > 0
            std::vector<std::string> flags; // flags from argv[] that have args == 0
            std::vector<std::string> args; // regular arguments

            cmd_args() {};

            void set_flag(std::string s, int args=0) { // args is how many arguments the flag takes, default=0

                flag_arg_count.insert(std::make_pair(s,args));

            }
        
            bool flag_exists(std::string f) {
            
                return std::find(flags.begin(), flags.end(), f) != flags.end();
                
            }

            void init_args(int argc, char *argv[]) { // takes argc and argv from int main() and processes them

                for (int i = 1; i < argc; i++) {
                    
                    std::string current_arg (argv[i]);

                    if (current_arg[0] == '-') { 
                        
                        if (flag_arg_count.find(current_arg) != flag_arg_count.end()) {

                            if (flag_arg_count[current_arg] == 0) {

                                flags.push_back(current_arg);

                            } else {
                                
                                int current_i = i;
                                i++;
                                
                                while (i < current_i+flag_arg_count[current_arg]+1 && i < argc) {

                                    std::string flag_arg (argv[i]);
                                    flag_args.insert(make_pair(current_arg, flag_arg));
                                    i++;

                                }

                            }

                        } // ignore unknown flags

                    } else {
                        args.push_back(current_arg);
                    }
                
                }

            } 

        private:

            std::map<std::string, int> flag_arg_count;

    };

}

#endif
