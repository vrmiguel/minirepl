#ifndef INTERP_H
#define INTERP_H

#include "token.h"

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
    void perform_unary_minus(vector<Token> & tokens);
    void perform_mult_and_div(vector<Token> &tokens);
    void perform_add_and_subtraction(vector<Token> &tokens);
public:
    /*!
     * \brief Constructor for an Interpreter.
     * \param text The text to be interpreted.
     */
    Interpreter(string text);
    Token expr();
};

#endif // INTERP_H
