#include "Headers/interp.h"
#include "Headers/_os.h"
#include <algorithm>

using std::stoi;
using std::to_string;

inline bool isdigit(char c)
{
     return (c > 47 && c < 58);
}

Interpreter::Interpreter(string text)
{
    this->text      = text;
    this->pos       = 0;
}

void Interpreter::eval_arith(vector<Token> &tokens, int optype, int index)
{
    try
    {
        if(tokens[index-1].var_type == INTEGER && tokens[index+1].var_type == INTEGER)
        {
            int left_oper  = stoi(tokens[index-1].var_value);
            int right_oper = stoi(tokens[index+1].var_value);
            if (optype == PLUS)
                tokens[index-1].var_value = to_string(left_oper + right_oper);
            else if (optype == MINUS)
                tokens[index-1].var_value = to_string(left_oper - right_oper);
            else if (optype == MULT)
                tokens[index-1].var_value = to_string(left_oper * right_oper);
            else if (optype == DIV)
                tokens[index-1].var_value = to_string(left_oper / right_oper);
            tokens.erase(tokens.begin() + index);
            tokens.erase(tokens.begin() + index);
        }
    } catch (const std::exception&) {
        cerr << "Syntax error.\n";
    }
}

Token Interpreter::get_token()
{
    if (pos > (text.size() -1))
    {
        return Token(EOL, "");
    }

    char cur_char = text[pos];

    if (cur_char == ' ')
    {
        pos++;
        return Token(SPACE, cur_char);
    }


    if (isdigit(cur_char))
    {
        pos++;
        return Token(INTEGER, cur_char);
    }

    if (cur_char == '+')
    {
        pos++;
        return Token(PLUS, cur_char);
    }


    if (cur_char == '-')
    {
        pos++;
        return Token(MINUS, cur_char);
    }

    if (cur_char == '*')
    {
        pos++;
        return Token(MULT, cur_char);
    }

    if (cur_char == '/')
    {
        pos++;
        return Token(DIV, cur_char);
    }

    cerr << cur_char << " is an invalid token.\n";
    return Token(EOL, "");
}

Token Interpreter::expr()
{
    vector<Token> created_tokens;
    for(;;)
    {
        Token tok = get_token();
        if(is_verbose)
            cout << tok << ' ';
        if (tok.var_type != SPACE)
            created_tokens.push_back(tok);
        if(tok.var_type == EOL || tok.var_type == EOFile)
            break;
    }

    Token mul(MULT, '*'), div(DIV,  '/');   // TODO: pls optimize this
    while (contains(created_tokens, mul) || contains(created_tokens, div))
    {
        for(unsigned long int i = 0; i < (unsigned int) created_tokens.size(); i++)
        {
            if (created_tokens[i].var_type == MULT)
            {
                eval_arith(created_tokens, MULT, i);
                break;
            }

            if (created_tokens[i].var_type == DIV)
            {
                eval_arith(created_tokens, DIV, i);
                break;
            }
        }
    }

    while (created_tokens.size() > 2)
    {
        for(unsigned long int i = 0; i < (unsigned int) created_tokens.size(); i++)
        {
            if (created_tokens[i].var_type == PLUS)
            {
                eval_arith(created_tokens, PLUS, i);
                break;
            }

            if (created_tokens[i].var_type == MINUS)
            {
                eval_arith(created_tokens, MINUS, i);
                break;
            }
        }
    }

    return created_tokens[0]; // placeholder
}
