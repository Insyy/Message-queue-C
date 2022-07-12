#include "msq-common.h"

void printHServer()
{
    fprintf(stderr, "\nUsage: ./msq-server.out [OPTION]...\n"
                    "Receive washers from clients through shared memory.\n"
                    "\nOptions:\n"
                    "\t-h, --help\n"
                    "\t\tdisplay this help and exit\n"
                    "\t-i, --key-proj-id=PROJ_ID\n"
                    "\t\tset the key project identifier to PROJ_ID (the default value is \"1\")\n"
                    "\t-p, --key-pathname=PATHNAME\n"
                    "\t\tset the key pathname to PATHNAME (the default value is \"file.ftok\")\n"
                    "\t-s, --seconds=SECONDS\n");
    fprintf(stderr, "\t\tset the seconds between each try (the default value is \"1\", a value less than or\n"
                    "\t\tequal to 0 enables the interactive mode where the input stream is read)\n"
                    "\t-t, --tries=TRIES\n"
                    "\t\tset the number of tries to TRIES (the default value is \"-1\", a negative\n"
                    "\t\tvalue means repeat for ever)\n"
                    "\t-v, --version\n"
                    "\t\toutput version information and exit\n"
                    "\nReport bugs to Alonso Ivan"
                    " <ivan.alonso-diaz-munio@etud.univ-pau.fr> "
                    "and Dudes Arnaud "
                    "<arnaud.dudes@univ-pau.fr>.\n");
}

void printHClient()
{
    fprintf(stderr, "\nUsage: ./msq-client.out [OPTION]...\n"
                    "Send a washer to a server through shared memory.\n"
                    "\nOptions:\n"
                    "\t-b, --washer-brand=BRAND\n"
                    "\t\tset the washer brand to BRAND (the default value is \"Default brand\")\n"
                    "\t-h, --help\n");
    fprintf(stderr, "\t\tdisplay this help and exit\n"
                    "\t-i, --key-proj-id=PROJ_ID\n"
                    "\t\tset the key project identifier to PROJ_ID (the default value is \"1\")\n"
                    "\t-m, --washer-model=MODEL\n"
                    "\t\tset the washer model to MODEL (the default value is \"Default model\")\n"
                    "\t-p, --key-pathname=PATHNAME\n"
                    "\t\tset the key pathname to PATHNAME (the default value is \"file.ftok\")\n");
    fprintf(stderr, "\t-s, --seconds=SECONDS\n"
                    "\t\tset the seconds between each try (the default value is \"1\", a value less than or\n"
                    "\t\tequal to 0 enables the interactive mode where the input stream is read)\n"
                    "\t-t, --tries=TRIES\n"
                    "\t\tset the number of tries to TRIES (the default value is \"1\", a negative\n"
                    "\t\tvalue means repeat for ever)\n"
                    "\t-v, --version\n"
                    "\t\toutput version information and exit\n"
                    "\nReport bugs to Alonso Ivan <ivan.alonso-diaz-munio@etud.univ-pau.fr> "
                    "and Dudes Arnaud <arnaud.dudes@univ-pau.fr>.");
}

void printVServer()
{
    fprintf(stderr, "\nmsq-server %f\n"
                    "Copyright (C) 2021 Alonso Ivan and Dudes Arnaud.\n"
                    "Written by Alonso Ivan <ivan.alonso-diaz-munio@etud.univ-pau.fr> "
                    "and Dudes Arnaud <arnaud.dudes@univ-pau.fr>.\n",SRV_VERSION);
}

void printVClient()
{
    fprintf(stderr, "\nmsq-client %f\n"
                    "Copyright (C) 2021 Alonso Ivan and Dudes Arnaud.\n"
                    "Written by Alonso Ivan <ivan.alonso-diaz-munio@etud.univ-pau.fr> "
                    "and Dudes Arnaud <arnaud.dudes@univ-pau.fr>.\n",CLI_VERSION);
}

void printOpts(argOpts_t options)
{
    fprintf(stderr, "\nProj_id = \"%d\""
                    "\nPathname = \"%s\"\n",
        options.PROJ_ID, options.pathname);
}

int getServerOptions(argOpts_t *opts, int argc, char *argv[])
{
    int ch;
    argOpts_t defaultOpts = {
        1,
        "file.ftok",
        1,
        -1};

    static struct option long_options[] =
        {
            {"key-proj-id", required_argument, NULL, 'i'},
            {"key-pathname", required_argument, NULL, 'p'},
            {"seconds", required_argument, NULL, 's'},
            {"tries", required_argument, NULL, 't'},
            {"help", required_argument, NULL, 'h'},
            {"version", required_argument, NULL, 'v'},
            {NULL, 0, NULL, 0}};

    while ((ch = getopt_long(argc, argv, "i:p:s:t:hv", long_options, NULL)) != -1)
    {
        char *endPtr;
        switch (ch)
        {
        case 'h':
            printHServer();
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            printVServer();
            exit(EXIT_SUCCESS);
            break;
        case 'i':
            if ((defaultOpts.PROJ_ID = strtol(optarg, &endPtr, 10)) == 0 && optarg == endPtr)
            {
                fprintf(stderr, "PROJ_ID ERROR.\n");
                return -1;
            }
            break;
        case 'p':
            if (strcmp(strcpy(defaultOpts.pathname, optarg), optarg) != 0)
            {
                fprintf(stderr, "PATHNAME COPY ERROR.\n");
                return -1;
            }
            break;
        case 's':
            if ((defaultOpts.seconds = strtol(optarg, &endPtr, 10)) == 0 && optarg == endPtr)
            {
                fprintf(stderr, "SECONDS VALUE ERROR.\n");
                return -1;
            }
            break;
        case 't':
            if ((defaultOpts.tries = strtol(optarg, &endPtr, 10)) == 0 && optarg == endPtr)
            {
                fprintf(stderr, "TRIES VALUE ERROR.\n");
                return -1;
            }
            break;
        }
    }
    memcpy(opts, &defaultOpts, sizeof(argOpts_t));
    return 0;
}

int getClientOptions(clientOpts_t *cliOps, int argc, char *argv[])
{
    int ch;
    clientOpts_t defaultCliOpts = {
        {1,
         "file.ftok",
         1,
         1},
        "Default brand",
        "Default model"};

    static struct option long_options[] =
        {
            {"key-proj-id", required_argument, NULL, 'i'},
            {"key-pathname", required_argument, NULL, 'p'},
            {"seconds", required_argument, NULL, 's'},
            {"tries", required_argument, NULL, 't'},
            {"help", required_argument, NULL, 'h'},
            {"version", required_argument, NULL, 'v'},
            {"washer-brand", required_argument, NULL, 'b'},
            {"washer-model", required_argument, NULL, 'm'},
            {NULL, 0, NULL, 0}};

    while ((ch = getopt_long(argc, argv, "b:m:i:p:s:t:hv", long_options, NULL)) != -1)
    {
        char *endPtr;
        switch (ch)
        {

        case 'h':
            printHClient();
            exit(EXIT_SUCCESS);
            break;

        case 'v':
            printVClient();
            exit(EXIT_SUCCESS);
            break;
        case 'i':
            if ((defaultCliOpts.argOpts.PROJ_ID = strtol(optarg, &endPtr, 10)) == 0 && optarg == endPtr)
            {
                fprintf(stderr, "PROJ_ID VALUE ERROR.\n");
                return -1;
            }
            break;

        case 'p':
            if (strcmp(strcpy(defaultCliOpts.argOpts.pathname, optarg), optarg) != 0)
            {
                fprintf(stderr, "PATHNAME COPY ERROR.\n");
                return -1;
            }
            break;
        case 'b':
            if (strcmp(strcpy(defaultCliOpts.brand, optarg), optarg) != 0 
                || strlen(optarg) > MSQ_WASHER_BRAND_SIZE)
            {
                fprintf(stderr, "BRANDNAME COPY ERROR.\n");
                return -1;
            }
            break;
        case 'm':
            if (strcmp(strcpy(defaultCliOpts.model, optarg), optarg) != 0
                || strlen(optarg) > MSQ_WASHER_MODEL_SIZE)
            {
                fprintf(stderr, "MODELNAME COPY ERROR.\n");
                return -1;
            }
            break;
        case 's':
            if ((defaultCliOpts.argOpts.seconds = strtol(optarg, &endPtr, 10)) == 0 && optarg == endPtr)
            {
                fprintf(stderr, "SECONDS VALUE ERROR.\n");
                return -1;
            }
            break;

        case 't':
            if ((defaultCliOpts.argOpts.tries = strtol(optarg, &endPtr, 10)) == 0 && optarg == endPtr)
            {
                fprintf(stderr, "TRIES VALUE ERROR.\n");
                return -1;
            }
            break;
        }
    }
    *cliOps = defaultCliOpts;
    return 0;
}
