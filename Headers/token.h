#ifndef TOKEN_H
#define TOKEN_H

#include "tokentypes.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cerr;
using std::cin;
using std::cout;

class Token
{
public:
    int var_type;
    string var_value;
    /*!
     * \brief Constructor for a token.
     * \param var_type  Token type, as per tokentypes.h.
     * \param var_value The value the token represents.
     */
    Token(int var_type, string var_value);
    /*!
     * \brief Constructor for a token.
     * \param var_type  Token type, as per tokentypes.h.
     * \param var_value The value the token represents.
     */
    Token(int var_type, char   var_value);
};

std::ostream& operator<<(std::ostream &strm, const Token &tok);
bool operator==(const Token t1, const Token t2);
bool contains(vector<Token> tokens, Token t);

#endif // TOKEN_H
