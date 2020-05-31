#ifndef _OS_H
#define _OS_H
#include <csignal>
#include <string>
#include <iostream>

using std::cout;
using std::string;

//bool no_hangup;
extern bool is_verbose;

class SignalHandler
{
    struct sigaction signal_action;
public:
    SignalHandler();
};

class CLIInputs
{
public:
    bool is_verbose;
    CLIInputs(int argc, char ** argv);
};

#endif // _OS_H
