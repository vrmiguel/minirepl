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

void Interpreter::eval_bin_op(vector<Token> &tokens, int optype, int index)
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
    } catch (const std::exception& e) {
        cerr << "Syntax error.\n" << e.what() << '\n';
        exit(2);
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
        string intval (1, cur_char);
        try
        {
            while(isdigit(text[pos+1]))
                intval = intval + text[++pos];
            pos++;
            return Token(INTEGER, intval);
        }
        catch (const std::out_of_range& oor)
        {
            cout << "Exception " << oor.what() << " catched.";
            pos++;
            return Token(INTEGER, intval);
        }
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

    cerr << cur_char << " is an invalid token.";
    return Token(EOL, "");
}

void Interpreter::perform_mult_and_div(vector<Token>& tokens)
{
    Token mul(MULT, '*'), div(DIV,  '/');   // TODO: pls optimize this
    while (contains(tokens, mul) || contains(tokens, div))
    {
        for(unsigned long int i = 0; i < (unsigned int) tokens.size(); i++)
        {
            if (tokens[i].var_type == MULT)
            {
                eval_bin_op(tokens, MULT, i);
                break;
            }

            if (tokens[i].var_type == DIV)
            {
                eval_bin_op(tokens, DIV, i);
                break;
            }
        }
    }
}

void Interpreter::perform_add_and_subtraction(vector<Token>& tokens)
{
    while (tokens.size() > 2)
    {
        for(unsigned long int i = 0; i < (unsigned int) tokens.size(); i++)
        {
            if (tokens[i].var_type == PLUS)
            {
                eval_bin_op(tokens, PLUS, i);
                break;
            }

            if (tokens[i].var_type == MINUS)
            {
                eval_bin_op(tokens, MINUS, i);
                break;
            }
        }
    }
}

void Interpreter::perform_unary_minus(vector<Token> &tokens)
{
    if(tokens[0].var_type == MINUS)
    {
        if(tokens[1].var_type != INTEGER)
        {
            cerr << "Syntax error.\n";
            exit(0);
        }
        if(stoi(tokens[1].var_value) > 0)
            tokens[1].var_value = "-" + tokens[1].var_value;


        tokens.erase(tokens.begin());

    }
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


    perform_unary_minus(created_tokens);

        // Does multiplication and division operations, if they exist
    perform_mult_and_div(created_tokens);

        // Does addition and subtraction operations, if they exist
    perform_add_and_subtraction(created_tokens);


    return created_tokens[0]; // placeholder
}
