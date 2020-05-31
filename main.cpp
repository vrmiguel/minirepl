#include "token.h"
#include "interp.h"
#include "_os.h"

int main(int argc, char ** argv)
{
    if (argc > 1)
        CLIInputs(argc, argv);

    std::ios_base::sync_with_stdio(false);

    SignalHandler sighandler;       // Defined in _os.h

    for (;;)
    {
        string line;
        cout << ">>> ";
        std::getline(cin, line);
        Interpreter interp = Interpreter(line);
        Token ans = interp.expr();
        putchar('\n');
    }
    return 0;
}
