#include "msq-washer.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

void msq_washer_serialize(msq_washer_t washer, msq_washer_message_t *message)
{
    message->type = 1l;
    size_t b = 0, m = 0;
    for (b; b < strlen(washer.brand); b++)
    {
        message->text[b] = washer.brand[b];
    }
    message->text[b] = '|';
    for (m; m < strlen(washer.model); m++)
    {
        message->text[m + b + 1] = washer.model[m];
    }
    message->text[m + b + 1] = '\0';
}

void msq_washer_deserialize(msq_washer_t *washer, msq_washer_message_t message)
{
    int foundDelim = 0;
    size_t brandSize;
    msq_washer_t deserialWash;
    if (message.type == 1l)
    {
        for (size_t i = 0; i < strlen(message.text); i++)
        {
            if (message.text[i] == '|')
            {
                foundDelim == 1;
                brandSize == i;
            }
            if (!foundDelim)
            {
                deserialWash.brand[i] = message.text[i];
                brandSize++;
            }
            else
            {
                deserialWash.model[i-brandSize-1] = message.text[i];
            }
        }
        washer = deserialWash;
    }
}

void msq_washer_print(msq_washer_t washer)
{
    time_t timenow;
    struct tm *timedata;
    time(&timenow);
    timedata = localtime(&timenow);
    printf("%d-%d-%d %d:%d:%d: %s:%s\n",
           timedata->tm_year + 1900,
           timedata->tm_mon,
           timedata->tm_mday,
           timedata->tm_hour,
           timedata->tm_min,
           timedata->tm_sec,
           washer.brand,
           washer.model);
}

int msq_washer_set_brand(msq_washer_t *washer, const char *brand)
{
    msq_washer_error_t errorCode;
    if (strlen(brand) > MSQ_WASHER_BRAND_SIZE - 1)
    {
        errorCode = msq_washer_error_brand;
        return errorCode;
    }
    strcpy(washer->brand, brand);
    return 0;
}
int msq_washer_set_model(msq_washer_t *washer, const char *model)
{
    msq_washer_error_t errorCode;
    if (strlen(model) > MSQ_WASHER_MODEL_SIZE - 1)
    {
        errorCode = msq_washer_error_model;
        return errorCode;
    }
    strcpy(washer->model, model);
    return 0;
}
