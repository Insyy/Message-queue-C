#if !defined(MSQCOMON)
#define MSQCOMON
#define CLI_VERSION 1.2
#define SRV_VERSION 1.2

#include"msq-washer.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    int PROJ_ID;
    char pathname[30];
    int seconds;
    int tries;
} argOpts_t;

typedef struct
{
    argOpts_t argOpts;
    char brand[MSQ_WASHER_BRAND_SIZE];
    char model[MSQ_WASHER_MODEL_SIZE];
} clientOpts_t;


int getServerOptions(argOpts_t *opts, int argc, char *argv[]);
int getClientOptions(clientOpts_t *cliOps, int argc, char *argv[]);
void printHServer();
void printHClient();
void printVClient();
void printVServer();
void printOpts(argOpts_t options);

#endif