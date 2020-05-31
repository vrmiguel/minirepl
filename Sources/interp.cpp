#include "Headers/interp.h"
#include "Headers/_os.h"

inline bool isdigit(char c)
{
     return (c > 47 && c < 58);
}

Interpreter::Interpreter(string text)
{
    this->text      = text;
    this->pos       = 0;
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

    cerr << "Token não válido.\n";
    exit(3);
}

Token Interpreter::expr()
{
    vector<Token> created_tokens;
    for(;;)
    {
        Token tok = get_token();
        if(is_verbose)
            cout << tok << ' ';
        if(tok.var_type == EOL || tok.var_type == EOFile)
            break;
        created_tokens.push_back(tok);
    }

    return Token(INTEGER, "2"); // placeholder
}
