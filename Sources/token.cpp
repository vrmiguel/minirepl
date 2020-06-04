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

#include "Headers/token.h"

std::ostream& operator<<(std::ostream &strm, const Token &tok)
{
    string vartype;
    switch (tok.var_type)
    {
        case INTEGER:
            vartype = "INTEGER";
        break;

        case PLUS:
            vartype = "PLUS";
        break;

        case MINUS:
            vartype = "MINUS";
        break;

        case SPACE:
            vartype = "SPACE";  // TODO: SPACE is not getting printed
            return strm << "Token(" << vartype << ", " << "\' \'" << ")";
        break;

        case MULT:
            vartype = "MULT";
        break;

        case DIV:
            vartype = "DIV";
        break;

        case EOL:
            vartype = "EOL";
        break;

        case EOFile:
            vartype = "EOF";
        break;

        case STRING:
            vartype = "STRING";
        break;

        default:
            vartype = "UNKNOWN";    // Control really shouldn't reach this point
        break;
    }
    return strm << "Token(" << vartype << ", " << tok.var_value << ")";
}

bool operator==(const Token t1, const Token t2)
{
    return t1.var_type == t2.var_type && t1.var_value == t2.var_value;
}

bool contains(vector<Token> tokens, Token t)
{
    return std::count(tokens.begin(), tokens.end(), t);
}

inline bool is_valid(int var_type)
{
    return (var_type > -1) && (var_type < TOKEN_TYPE_COUNT);
}

Token::Token(int var_type, string var_value)
{
    if (is_valid(var_type))
    {
        this->var_type  = var_type;
        this->var_value = var_value;
    } else {
        cerr << "The type" << var_type << "is not valid.";
        std::exit(1);
    }
}

Token::Token(int var_type, char var_value)
{
    if (is_valid(var_type))
    {
        this->var_type  = var_type;
        this->var_value = string(1, var_value);
    } else
    {
        cerr << "The type" << var_type << "is not valid.";
        std::exit(1);
    }
}
