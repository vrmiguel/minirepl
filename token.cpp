#include "token.h"
#include "cstdlib"

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

        default:
            vartype ="UNKNOWN";    // Control really shouldn't reach here
        break;
    }

    return strm << "Token(" << vartype << ", " << tok.var_value << ")";
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
        cerr << "Tipo " << var_type << "não é válido.";
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
        cerr << "Tipo " << var_type << "não é válido.";
        std::exit(1);
    }
}
