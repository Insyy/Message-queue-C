#include "msq-common.h"

int main(int argc, char *argv[])
{
    argOpts_t opts;
    key_t key;
    msq_washer_t washerToReceive;
    msq_washer_message_t msg;
    int index = 0, MSQid;

    /*    get server options    */
    if (getServerOptions(&opts, argc, argv) == -1)
        return -1;
    printOpts(opts);
    /*    get msq key    */
    if ((key = ftok(opts.pathname, opts.PROJ_ID)) == -1)
    {
        fprintf(stderr, "Unable to create the System V IPC key from the \"%s\""
                        "pathname and the \"%d\" project identifier.",
                opts.pathname, opts.PROJ_ID);
        return -1;
    }

    if ((MSQid = msgget(key, IPC_CREAT | 0600)) == -1)
    {
        fprintf(stderr, "Unable to retrieve msg queue from key %d", key);
        perror("Error msgget:");
        return -1;
    }

    /*    launch server    */
    while (index != opts.tries)
    {
        if (opts.seconds <= 0)
        {
            fprintf(stderr, "Press the Enter key to continue...");
            getchar();
        }

        if (!(opts.tries < 1))
            index++;
        else
            sleep(opts.seconds);

        if (msgrcv(MSQid, &msg, MSQ_WASHER_BRAND_SIZE + MSQ_WASHER_MODEL_SIZE, 0, 0) == -1)
        {

            fprintf(stderr, "Error retrieving message from queue\n");
            return -1;
        }
        else
        {
            msq_washer_deserialize(&washerToReceive, msg);
            msq_washer_print(washerToReceive);
        }
    }
    if (msgctl(MSQid, IPC_RMID, NULL) == -1)
        return 1;

    return 0;
}
