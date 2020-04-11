#ifndef __CRCX
#define __CRCX

#include <stdio.h>
#include <stdint.h>

/* CRC-8 */
#define     CRC8            0x0800000100UL
#define     CRC8_DARC       0x0811000200UL
#define     CRC8_DVB        0x0800000000UL
#define     CRC8_EBU        0x0811100400UL
#define     CRC8_GSM        0x0800110300UL
#define     CRC8_ICODE      0x0800200400UL
#define     CRC8_ITU        0x0800030100UL
#define     CRC8_ROHC       0x0811100100UL

/* CRC-16 */
#define     CRC16_A         0x1011500500UL
#define     CRC16_ARC       0x1011000D00UL
#define     CRC16_ACCITT    0x1000300500UL
#define     CRC16_BUYPASS   0x1000000D00UL
#define     CRC16_CCIT      0x1000100500UL
#define     CRC16_CDMA      0x1000100700UL
#define     CRC16_DDS110    0x1000400D00UL
#define     CRC16_DECTR     0x1000020900UL
#define     CRC16_DECTX     0x1000000900UL
#define     CRC16_DNP       0x1011010B00UL
#define     CRC16_EN13757   0x1000010B00UL
#define     CRC16_GENIBUS   0x1000110500UL
#define     CRC16_KERMIT    0x1011000500UL
#define     CRC16_MAXIM     0x1011010D00UL
#define     CRC16_MODBUS    0x1011100D00UL
#define     CRC16_RIELLO    0x1011600500UL
#define     CRC16_TMS       0x1011700500UL
#define     CRC16_USB       0x1011110D00UL
#define     CRC16_X25       0x1011110500UL
#define     CRC16_XMODEM    0x1000000500UL

/* CRC-32 */
#define     CRC32           0x2011110F00UL
#define     CRC32_BZIP2     0x2000110F00UL
#define     CRC32_C         0x2011111300UL
#define     CRC32_EXT4      0x2011111300UL
#define     CRC32_GZIP      0x2000001700UL
#define     CRC32_JAMCRC    0x2011100F00UL
#define     CRC32_MPEG2     0x2000100F00UL
#define     CRC32_PNG       0x2011100F00UL
#define     CRC32_POSIX     0x2000010F00UL
#define     CRC32_SATA      0x2000200F00UL
#define     CRC32_SCTP      0x2011001300UL
#define     CRC32_ZMODEM    0x2000000F00UL

/* Functions */
int        crcx_use    (uint64_t crc_x, const unsigned char * table_path);
int32_t    crcx        (const unsigned char * data, uint32_t data_length);
int32_t    crcx_update (int32_t crc, unsigned char data);

#endif