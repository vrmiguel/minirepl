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
