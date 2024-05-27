/**
 * @file	httpUtil.c
 * @brief	HTTP Server Utilities	
 * @author	
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "httpUtil.h"

uint8_t http_get_cgi_handler(uint8_t * uri_name, uint8_t * buf, uint32_t * file_len)
{
	uint8_t ret = HTTP_OK;
	uint16_t len = 0;
	
	if(predefined_get_cgi_processor(uri_name, buf, &len))
	{
		;
	}
	else
	{
		// CGI file not found
		ret = HTTP_FAILED;
	}

	if(ret)	*file_len = len;
	return ret;
}

uint8_t http_post_cgi_handler(uint8_t * uri_name, st_http_request * p_http_request, uint8_t * buf, uint32_t * file_len)
{
	uint8_t ret = HTTP_OK;
	uint16_t len = 0;
	uint8_t * device_ip;
	uint8_t val;

	if(predefined_set_cgi_processor(uri_name, p_http_request, buf, &len))
	{
    	ret = HTTP_FWUP;
	}
	else
	{
		// CGI file not found
		ret = HTTP_FAILED;
	}

	if(ret)	*file_len = len;
	return ret;
}


uint8_t predefined_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len)
{
	;
}


uint8_t predefined_set_cgi_processor(uint8_t * uri_name, st_http_request * p_http_request, uint8_t * buf, uint16_t * len)
{
	uint8_t ret = 1;	// ret = 1 means 'uri_name' matched
	uint8_t val = 0;

	if(strcmp((const char *)uri_name, "update_firmware.cgi") == 0)
	{
		if (http_update_firmware(p_http_request, buf))
		*len = sprintf((char *)buf, "<html><head><title>W5500-EVB-Pico</title><body>F/W Update Complete. Application code will run.</body></html>\r\n\r\n");
	}
	else
	{
		ret = 0;
	}

	return ret;
}
