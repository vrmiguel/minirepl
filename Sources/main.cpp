#include "Headers/token.h"
#include "Headers/interp.h"
#include "Headers/_os.h"

bool is_verbose;

int main(int argc, char ** argv)
{
    CLIInputs(argc, argv);

    cout << "Verbose: " << is_verbose << '\n';
    SignalHandler sighandler;       // Defined in _os.h

    for (;;)
    {
        string line;
        cout << ">>> ";
        std::getline(cin, line);
        Interpreter interp = Interpreter(line);
        Token ans = interp.expr();
        if (is_verbose)
            putchar('\n');
    }
    return 0;
}
