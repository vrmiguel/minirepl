#include "token.h"
#include "interp.h"

using std::cout;
using std::cin;

int main(void)
{
    for (;;)
    {
        string line;
        cout << "REPL >>> ";
        std::getline(cin, line);
        Interpreter interp = Interpreter(line);
        Token ans = interp.expr();
        putchar('\n');
    }
    return 0;
}
