#include "token.h"
#include "interp.h"
#include <csignal>

using std::cout;
using std::cin;

void signal_handler(int s)
{
    if (s==2)
        cout << "\nSIGINT (Ctrl+C) received. Code " << s << ".\n";
    exit(s);
}


int main(void)
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = signal_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

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
