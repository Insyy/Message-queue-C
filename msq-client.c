#include "msq-common.h"

int main(int argc, char *argv[])
{
    clientOpts_t opts;
    key_t key;
    msq_washer_t washerToSend;
    msq_washer_message_t msg;
    int try = 0, MSQid, msgflg = IPC_CREAT;
    /*    get client options    */
    if (getClientOptions(&opts, argc, argv) == -1)
        return -1;
    /*    get msq key    */
    if ((key = ftok(opts.argOpts.pathname, opts.argOpts.PROJ_ID)) == -1)
    {
        fprintf(stderr, "Unable to create the System V IPC key from the \"%s\""
                        "pathname and the \"%d\" project identifier.",
                opts.argOpts.pathname, opts.argOpts.PROJ_ID);
        return -1;
    }
    if ((MSQid = msgget(key, msgflg)) == -1)
    {
        fprintf(stderr, "Unable to retrieve msg queue from key %d", key);
        return -1;
    }

    printOpts(opts.argOpts);
    /*    launch client    */
    while (try != opts.argOpts.tries)
    {
        if (opts.argOpts.seconds <= 0)
        {
            fprintf(stderr, "Press the Enter key to continue...");
            getchar();
        }
        if (!(opts.argOpts.tries < 1)) try++;
        else
            sleep(opts.argOpts.seconds);

        if (msq_washer_set_brand(&washerToSend, opts.brand) == msq_washer_error_brand)
        {
            fprintf(stderr, "Unable to set the washer brand to \"%s\" of length %ld.\n", opts.brand, strlen(opts.brand));
            return -1;
        }
        if (msq_washer_set_model(&washerToSend, opts.model) == msq_washer_error_model)
        {
            fprintf(stderr, "Unable to set the washer model to \"%s\" of length %ld.\n", opts.model, strlen(opts.model));
            return -1;
        }
        msq_washer_serialize(washerToSend,&msg);
        if (msgsnd(MSQid,&msg,strlen(msg.text),IPC_NOWAIT) == -1)
        {
            fprintf(stderr, "Unable to add message to queue\n");
            return -1;
        } else msq_washer_print(washerToSend);

        
    }
    return 0;
}
