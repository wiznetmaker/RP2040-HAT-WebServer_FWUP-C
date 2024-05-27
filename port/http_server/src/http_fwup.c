
#include "port_common.h"
#include "httpParser.h"
#include "http_fwup.h"
#include "device_fwup.h"


extern uint8_t *pHTTP_RX;
extern uint8_t *pHTTP_TX;

uint8_t http_update_firmware(st_http_request * p_http_request, uint8_t *buf)
{
  uint8_t ret = 0, sock, end_flag = 0;
  uint8_t *body, *boundary_pos;
  uint8_t boundary[128];
  uint8_t boundary_len;
  uint16_t body_len;
  uint8_t *uri = p_http_request->URI;

  uint16_t write_len = 0;
  uint32_t write_fw_len;
  uint32_t f_addr = APPLICATION_OFFSET;
  uint32_t remain_len = 0, buf_len = 0;
  uint8_t *flash_temp_buf;

  sock = p_http_request->socket;
  boundary_pos = strstr(uri, "boundary=");
  if (boundary_pos != NULL) {
    sscanf(boundary_pos, "boundary=%127s", boundary);
    boundary_len = strlen(boundary);
    printf("boundary = %s, boundary_len = %d\r\n", boundary, boundary_len);
  }

  body = strstr((char*)pHTTP_RX + p_http_request->header_len + 4, "\r\n\r\n");
  if (body != NULL) {
    body += 4;
    body_len = p_http_request->recv_len - (body - pHTTP_RX);
    
    flash_temp_buf = malloc(FLASH_SECTOR_SIZE);
    memset(flash_temp_buf, 0xFF, FLASH_SECTOR_SIZE);
    memcpy(flash_temp_buf, body, body_len);
    buf_len = body_len;
    
    while(1) {
      if((body_len = getSn_RX_RSR(sock)) > 0)
      {
        memset(pHTTP_RX, 0x00, DATA_BUF_SIZE);
        body_len = recv(sock, (uint8_t *)pHTTP_RX, body_len);

        if (!(memcmp(pHTTP_RX + (body_len - boundary_len - 4), boundary, boundary_len)))  //end boundary = "\r\n--boundary--\r\n"
        {
          memset(pHTTP_RX + (body_len - boundary_len - 8), 0xFF, boundary_len + 8);
          end_flag = 1;
        }

        if (buf_len + body_len < FLASH_SECTOR_SIZE)
        {
            memcpy(flash_temp_buf + buf_len, pHTTP_RX, body_len);
            buf_len += body_len;
        }
        else
        {
            remain_len = (buf_len + body_len) - FLASH_SECTOR_SIZE;
            memcpy(flash_temp_buf + buf_len, pHTTP_RX, body_len - remain_len);

            flash_range_erase(f_addr, FLASH_SECTOR_SIZE);
            flash_range_program(f_addr, (uint8_t *)flash_temp_buf, FLASH_SECTOR_SIZE);
            f_addr += FLASH_SECTOR_SIZE;

            memset(flash_temp_buf, 0xFF, FLASH_SECTOR_SIZE);
            memcpy(flash_temp_buf, pHTTP_RX + (body_len - remain_len), remain_len);
            buf_len = remain_len;  
        }
        if (end_flag)
          break;
      }
    }

    if (buf_len > 0)
    {
      flash_range_erase(f_addr, FLASH_SECTOR_SIZE);
      flash_range_program(f_addr, flash_temp_buf, FLASH_SECTOR_SIZE);
    }
    free(flash_temp_buf);
    ret = 1;
  }
  else
    ret = 0;
  return ret;
}
