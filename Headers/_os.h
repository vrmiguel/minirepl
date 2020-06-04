/*
 * miniREPL
 * https://github.com/vrmiguel/minirepl
 *
 * Copyright (c) 2020 Vinícius R. Miguel <vinicius.miguel at unifesp.br>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _OS_H
#define _OS_H
#include <csignal>
#include <string>
#include <iostream>
#include <vector>

    // Travis CI really wants these
#include <cstdlib>
#include <cstdio>

using std::cout;
using std::string;

//bool no_hangup;
extern bool is_verbose;

/*!
 * \class SignalHandler
 * \brief Handles SIGHUP and SIGINT signals.
 */
class SignalHandler
{
    struct sigaction signal_action;
public:
    /*!
     * \brief Constructor for SignalHandler. Handles SIGHUP and SIGINT signals.
     */
    SignalHandler();
};

/*!
 * \class CLIInputs
 * \brief Handler for command-line arguments.
 */
class CLIInputs
{
public:
    /*!
     * \brief Constructor for CLIInputs.
     * \param argc Command-line argument count.
     * \param argv Array of strings that representing the command-line argument given.
     */
    CLIInputs(int argc, char ** argv);
};

/*!
 * \class Variable
 * \brief Holds a REPL variable.
 */
class Variable
{
public:
    string var_name;
    string var_value;
    Variable(string var_name, string var_value);
};

extern std::vector<Variable> var_list;
/*!
 * \brief Searches for a variable inside of var_list.
 * \param var_name The name of the variable being searched for.
 */
int var_find(string var_name);

#endif // _OS_H
