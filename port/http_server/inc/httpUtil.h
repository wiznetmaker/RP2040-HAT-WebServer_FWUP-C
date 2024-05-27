/**
 * @file	httpUtil.h
 * @brief	Header File for HTTP Server Utilities
 */

#ifndef	__HTTPUTIL_H__
#define	__HTTPUTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "httpServer.h"
#include "httpParser.h"

uint8_t http_get_cgi_handler(uint8_t * uri_name, uint8_t * buf, uint32_t * file_len);
uint8_t http_post_cgi_handler(uint8_t * uri_name, st_http_request * p_http_request, uint8_t * buf, uint32_t * file_len);

uint8_t predefined_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len);
uint8_t predefined_set_cgi_processor(uint8_t * uri_name, st_http_request * p_http_request, uint8_t * buf, uint16_t * len);

#ifdef __cplusplus
}
#endif

#endif
