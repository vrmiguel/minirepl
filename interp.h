#ifndef INTERP_H
#define INTERP_H

#include "token.h"

class Interpreter
{   // TODO: Singleton
    string text;
    unsigned long pos;
    //Token cur_token;
    Token get_token();
public:
    Interpreter(string text);
    Token expr();
};

#endif // INTERP_H
