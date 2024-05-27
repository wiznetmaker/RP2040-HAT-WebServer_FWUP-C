
#ifndef __HTTPHANDLER_H
#define __HTTPHANDLER_H

#include <stdint.h>
#include "httpParser.h"

#define DATA_BUF_SIZE 2048

uint8_t http_update_firmware(st_http_request * p_http_request, uint8_t *buf);

#endif //__HTTPHANDLER_H


