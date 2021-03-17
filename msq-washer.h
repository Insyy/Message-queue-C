/**
* \file msq-washer.h
*/
#ifndef MSQ_WASHER_H
#define MSQ_WASHER_H
/**
* The size of the washer brand.
*/
#define MSQ_WASHER_BRAND_SIZE 15
/**
* The size of the washer model.
*/
#define MSQ_WASHER_MODEL_SIZE 20
/**
* A washer.
*/
typedef struct
{
    char brand[MSQ_WASHER_BRAND_SIZE]; /**< The washer brand (example: "Whirlpool"). */
    char model[MSQ_WASHER_MODEL_SIZE]; /**< The washer model (example: "FSCR-10427"). */
} msq_washer_t;
/**
* A message.
*/
typedef struct
{
    long type;                                                /**< The message type (example: "1"). */
    char text[MSQ_WASHER_BRAND_SIZE + MSQ_WASHER_MODEL_SIZE]; /**< The message text (example:
"Whirlpool|FSCR-10427"). */
} msq_washer_message_t;
/**
* A washer error.
*/
typedef enum
{
    msq_washer_error_brand = -2,
    msq_washer_error_model
} msq_washer_error_t;
/**
* Serializes a washer to a message (the message type is "1" and the message text is using the
"brand|model" format).
* \param washer The washer.
* \param message The message.
*/
void msq_washer_serialize(msq_washer_t washer, msq_washer_message_t *message);
/**
* Deserializes a message to a washer (the message type is "1" and the message text is using the
"brand|model" format).
* \param washer The washer.
* \param message The message.*/
void msq_washer_deserialize(msq_washer_t *washer, msq_washer_message_t message);
/**
* Prints a washer using the "YYYY-MM-DD HH:MM:SS: brand: model" format.
* \param washer The washer.
*/
void msq_washer_print(msq_washer_t washer);
/**
* Sets the brand of a washer.
* \param washer The washer.
* \param brand The brand.
* \return msq_washer_error_brand if the washer brand length is greater than MSQ_WASHER_BRAND_SIZE
- 1, else 0.
*/
int msq_washer_set_brand(msq_washer_t *washer, const char *brand);
/**
* Sets the model of a washer.
* \param washer The washer.
* \param model The model.
* \return msq_washer_error_model if the washer model length is greater than MSQ_WASHER_MODEL_SIZE
- 1, else 0.
*/
int msq_washer_set_model(msq_washer_t *washer, const char *model);
#endif
