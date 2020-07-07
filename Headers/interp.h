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

#ifndef INTERP_H
#define INTERP_H

#include "token.h"
#include "os.h"
/*!
 * \class Interpreter
 * \brief The REPL's interpreter.
 *
 *  Reads the expressions from all lines given from std::cin, evaluates them
 *  through the several private methods below, and returns a result Token.
 *
 */
class Interpreter
{   // TODO: Singleton
    string text;
    unsigned long pos;
    /*!
     * \brief Reads a token from the text fed into the interpreter.
     */
    Token get_token();

    /*!
     * \brief Evaluates one single binary arithmetic operation
     * \param tokens The list of tokens to be operated on.
     * \param optype The type of operation, as stated in tokentypes.h.
     * \param index  The index where the operator is.
     */
    void eval_bin_op(vector<Token> &tokens, int optype, int index);
    void perform_exp(vector<Token>& tokens);
    void perform_unary_minus(vector<Token> & tokens);
    void perform_mult_and_div(vector<Token> &tokens);
    void perform_add_and_subtraction(vector<Token> &tokens);
    /*!
     * \brief Replaces a variable inside an arithmetic operation
     * \param tokens The list of tokens to be operated on.
     * \param optype The variable to be found and replaced with its value.
     */
    Token replace_variable(vector<Token>& tokens);
public:
    /*!
     * \brief Constructor for an Interpreter.
     * \param text The text to be interpreted.
     */
    Interpreter(string text);
    Token expr();
};

#endif // INTERP_H
