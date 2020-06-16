#include <stdio.h>
#include <stdint.h>

/*
	You can find what generator polynomial a protocol or standard uses by
	reading its documentation.
*/
#define CRC8        0xD5U
#define CRC8_CCITT  0x07U
#define CRC8_DARC   0x39U
#define CRC8_GSM    0x49U
#define CRC8_SAE    0x1DU
uint8_t crc8_poly_table[] = {
        CRC8, CRC8_CCITT, CRC8_DARC, CRC8_GSM, CRC8_SAE
};

#define CRC16_CCITT 0x1021U
#define CRC16_CDMA  0xC867U
#define CRC16_DECT  0x0589U
#define CRC16_DNP   0x3D65U
#define CRC16_IBM   0x8005U
uint16_t crc16_poly_table[] = {
        CRC16_CCITT, CRC16_CDMA, CRC16_DECT, CRC16_DNP, CRC16_IBM
};

#define CRC32       0x04C11DB7U
#define CRC32_C     0x1EDC6F41U
#define CRC32_GZIP  0xEDB88320U
uint32_t crc32_poly_table[] = {
        CRC32, CRC32_C, CRC32_GZIP
};

int 
main(int argc, char ** argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "%s: No filename provided.", argv[0]);
        return 1;
    }

	FILE * tables_fd;

    int i;
    for (i = 1; i < argc; ++i)
    {
	    tables_fd = fopen(argv[i], "w");

        printf("%s: Writing tables to %s\n", argv[0], argv[i]);

        int poly_index;
        for (poly_index = 0; poly_index < (int)(sizeof(crc8_poly_table)/sizeof(uint8_t)); ++poly_index)
        {
	        uint8_t crc;
	        int i, j;
	        for (i = 0; i < 256; ++i){
	        	crc = i;
	        	for (j = 0; j < 8; ++j)
	        			crc = (crc & 0x80) ? ((crc << 1) ^ crc8_poly_table[poly_index]) : crc << 1;
	        	fwrite(&crc, 1, 1, tables_fd);
	        }
        }
        for (poly_index = 0; poly_index < (int)(sizeof(crc16_poly_table)/sizeof(uint16_t)); ++poly_index)
        {
	        uint16_t crc;
	        int i, j;
	        for (i = 0; i < 256; ++i){
	        	crc = (i << 8);
	        	for (j = 0; j < 8; ++j)
	        			crc = (crc & 0x8000) ? ((crc << 1) ^ crc16_poly_table[poly_index]) : crc << 1;
	        	fwrite(&crc, 2, 1, tables_fd);
	        }
        }
        for (poly_index = 0; poly_index < (int)(sizeof(crc32_poly_table)/sizeof(uint32_t)); ++poly_index)
        {
	        uint32_t crc;
	        int i, j;
	        for (i = 0; i < 256; ++i){
	        	crc = (i << 24);
	        	for (j = 0; j < 8; ++j)
	        			crc = (crc & 0x80000000) ? ((crc << 1) ^ crc32_poly_table[poly_index]) : crc << 1;
	        	fwrite(&crc, 4, 1, tables_fd);
	        }
        }

	    fclose(tables_fd);

        printf("%s: Done.\n", argv[0]);
    }

    return 0;
}
