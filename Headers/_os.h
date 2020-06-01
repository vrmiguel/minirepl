#ifndef _OS_H
#define _OS_H
#include <csignal>
#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::string;

//bool no_hangup;
extern bool is_verbose;

class SignalHandler
{
    struct sigaction signal_action;
public:
    /*!
     * \brief Constructor for SignalHandler. Handles SIGHUP and SIGINT signals.
     */
    SignalHandler();
};

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

class Variable
{
public:
    string var_name;
    string var_value;
    Variable(string var_name, string var_value);
};

extern std::vector<Variable> var_list;
Variable var_find(string var_name);

#endif // _OS_H
