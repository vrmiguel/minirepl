#include "Headers/token.h"
#include "Headers/interp.h"
#include "Headers/_os.h"

int main(int argc, char ** argv)
{
    cout << "miniREPL -- github.com/vrmiguel/minirepl\n";
    CLIInputs(argc, argv);

    SignalHandler sighandler;

    for (;;)
    {
        string line;
        cout << ">>> ";
        std::getline(cin, line);
        if (cin.eof())
        {
            cout << "\nEOF found. Exiting.\n";
            return 0;
        }
        if(line.empty())    // Checks for carriage return.
            continue;

        Interpreter interp (line);
        Token ans = interp.expr();
        cout << ans.var_value << '\n';
        if (is_verbose)
            putchar('\n');
    }
    return 0;
}
