#include "Headers/interp.h"
#include "Headers/_os.h"
#include <algorithm>
#include <cmath>

using std::stoi;
using std::to_string;

inline bool isdigit(char c)
{
    return (c > 47 && c < 58);
}

inline bool ischar(char c)
{
    return (c > 64 && c < 91) || (c > 96 && c < 123);
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
            else if (optype == EXP)
                tokens[index-1].var_value = to_string((int) pow(left_oper, right_oper));
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

    if (cur_char == '=')
    {
        pos++;
        return Token(ATTRIB, cur_char);
    }

    if (cur_char == '^')
    {
        pos++;
        return Token(EXP, cur_char);
    }

//    if (cur_char == '(')
//    {
//        pos++;
//        return Token(OPENPAR, cur_char);
//    }

//    if (cur_char == ')')
//    {
//        pos++;
//        return Token(CLOSEPAR, cur_char);
//    }

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

    if (ischar(cur_char))
    {
        string varname (1, cur_char);
        try
        {
            while(ischar(text[pos+1]))
                varname = varname + text[++pos];
            pos++;
            return Token(STRING, varname);
        }
        catch (const std::out_of_range& oor)
        {
            cout << "Exception " << oor.what() << " catched.";
            pos++;
            return Token(STRING, varname);
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

void Interpreter::perform_exp(vector<Token> &tokens)
{
    Token exp(EXP, '^');
    while (contains(tokens, exp))
    {
        for(unsigned long int i = 0; i < (unsigned int) tokens.size(); i++)
        {
            if (tokens[i].var_type == EXP)
            {
                eval_bin_op(tokens, EXP, i);
                break;
            }
        }
    }
}

Token Interpreter::replace_variable(vector<Token>& tokens)
{
    //Token var_symbol (STRING, var.var_name);
        for(unsigned long int i = 0; i < (unsigned int) tokens.size(); i++)
        {
            if (tokens[i].var_type == STRING)
            {
                Variable var = var_find(tokens[i].var_value); // Looks for a variable with the given string value
                if (!var.var_value.compare("not found"))  // Variable not found
                {
                    cerr << "Variable " << tokens[i].var_value << " is not defined.";
                    return Token(EOL, "");
                }
                else{
                        // The variable was found
                    tokens[i].var_type  = INTEGER;
                    tokens[i].var_value = var.var_value;   // so we'll replace it on the expression.
                }
            }
        }
    return Token(STRING, "success");
}

Token Interpreter::expr()
{
    vector<Token> created_tokens;
    string var_name;

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

        // Verifies if a string was read
    if (created_tokens[0].var_type == STRING)
    {
            // Verifies if there was an attribution of value
        if (created_tokens[1].var_type != ATTRIB)
        {
            Variable res = var_find(created_tokens[0].var_value);
            if (!res.var_value.compare("not found"))  // Variable not found
            {
                cerr << "Variable " << created_tokens[0].var_value << " is not defined.";
                return Token(EOL, "");
            }
            if(created_tokens.size() == 2)              // User wants to print a variable
                return Token(INTEGER, res.var_value);   // so let's return the value of that variable
        }
        else
        {
            // In this case, there was attribution. We'll calculate the value of the expression and then
            // attribute this value to the given variable later on.
        var_name = created_tokens[0].var_value;
        created_tokens.erase(created_tokens.begin());
        created_tokens.erase(created_tokens.begin());
        }
    }


    Token response = replace_variable(created_tokens);
    if (response.var_type == EOL)
    {
        return response;    // Expression uses an undefined variable.
    }

    perform_unary_minus(created_tokens);
    perform_exp(created_tokens);

        // Does multiplication and division operations, if they exist
    perform_mult_and_div(created_tokens);

        // Does addition and subtraction operations, if they exist
    perform_add_and_subtraction(created_tokens);

    if (!var_name.empty())
    {
        // var_name isn't empty, so we'll create (or TODO: update) a variable with that value.
        var_list.push_back(Variable(var_name, created_tokens[0].var_value));
    }
    return created_tokens[0];
}
