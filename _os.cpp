#include "_os.h"

void signal_handler(int s)
{
    if (s==SIGINT)
    {
        cout << "\nSIGINT (Ctrl+C) received. Code " << s << ".\n";
        exit(s);
    }

    if (s==SIGHUP)
    {
        cout << "\nSIGHUP received. Code " << s << ".\n";
        exit(s);
    }
}

SignalHandler::SignalHandler()
{
    signal_action.sa_handler = signal_handler;
    sigemptyset(&signal_action.sa_mask);
    signal_action.sa_flags = 0;
    sigaction(SIGINT, &signal_action, NULL);
}

CLIInputs::CLIInputs(int argc, char **argv)
{
    if(argc > 1)
    {
        for(short unsigned int i = 1; i < argc; i++)
        {
            string s_argv = argv[i];
            if (!s_argv.compare("-h") || !s_argv.compare("--help"))
            {
                printf("miniREPL -- github.com/vrmiguel/minirepl\n");
                printf("%-20s\tObtain help.\n", "-h, --help");
                printf("%-20s\tShows additional execution data.\n", "-v, --verbose");
                exit(0);
            }
            if (!s_argv.compare("-v") || !s_argv.compare("--verbose"))
            {
                printf("Executing in verbose mode.\n");
                is_verbose = true;
            }
        }
    }
}
