#include "crcx.h"

/*
39     31      23      15              0
----------------------------------------
|   B   | RI RO | II IF |       O      |
----------------------------------------
B  : X-bit (08-64)       RO : Reverse Output     IF : Final XOR index
RI : Reverse Input       II : Init XOR index     O  : Table offset
*/
#define     BITS    0xFF00000000UL
#define     REVI    0x00F0000000UL
#define     REVO    0x000F000000UL
#define     IIND    0x0000F00000UL
#define     FIND    0x00000F0000UL
#define     TOFF    0x000000FFFFUL

#define     get_bits(x)         ((x & BITS) >> 32)
#define     reverse_input(x)    ((x & REVI) >> 28)
#define     reverse_output(x)   ((x & REVO) >> 24)
#define     init_index(x)       ((x & IIND) >> 20)
#define     final_index(x)      ((x & FIND) >> 16)
#define     table_offset(x)      (x & TOFF)

static const uint8_t bit_reversal_table[256] = {
    #define R2(n)    n ,    n + 2*64 ,    n + 1*64 ,    n + 3*64
    #define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
    #define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};
#define     reverse_bits_8(x)  ((bit_reversal_table[x & 0xFF]) |\
                                (bit_reversal_table[(x >> 8) & 0xFF]))
#define     reverse_bits_16(x) ((bit_reversal_table[x & 0xFF] << 8) |\
                                (bit_reversal_table[(x >> 8) & 0xFF]) |\
                                (bit_reversal_table[x & 0xFF] >> 8))
#define     reverse_bits_32(x) ((bit_reversal_table[x & 0xFF] << 24) |\
                                (bit_reversal_table[(x >> 8) & 0xFF] << 16) |\
                                (bit_reversal_table[(x >> 16) & 0xFF] << 8) |\
                                (bit_reversal_table[(x >> 24) & 0xFF]))

static uint8_t crc8_xor_table[]     = {0x00U, 0xFFU, 0xFDU, 0x55U};
static uint16_t crc16_xor_table[]   = {0x0000U, 0xFFFFU, 0x0001U, 0x1D0FU, 0x800DU, 0xC6C6U, 0xB2AAU, 0x89ECU};
static uint32_t crc32_xor_table[]   = {0x00000000U, 0xFFFFFFFFU, 0x52325032U};

static uint64_t crc_x;

static uint8_t loaded;
static uint8_t table[1024];

static struct {
    union{
        uint8_t     _8;
        uint16_t    _16;
        uint32_t    _32;
    } crc;
    union {
        uint8_t *   _8;
        uint16_t *  _16;
        uint32_t *  _32;
    } iter;
    uint8_t bits;
    uint8_t rev_in;
    uint8_t rev_out;
    uint8_t init_index;
    uint8_t final_index;
} CRCParams;

int32_t
crcx(const unsigned char * data, uint32_t data_length)
{
    if (!loaded)
        return -1;

    switch (CRCParams.bits)
    {
        case 8:
        {
            CRCParams.crc._8 = crc8_xor_table[CRCParams.init_index];

            int i;
            for (i = 0; i < data_length; ++i)
                CRCParams.crc._8 = *(CRCParams.iter._8 + (CRCParams.crc._8 ^ ((CRCParams.rev_in) ? reverse_bits_8(data[i]) : data[i])));

            return ((CRCParams.rev_out) ? reverse_bits_8(CRCParams.crc._8) : CRCParams.crc._8) ^ crc8_xor_table[CRCParams.final_index];
        }
        case 16:
        {
            CRCParams.crc._16 = crc16_xor_table[CRCParams.init_index];

            int i;
            for (i = 0; i < data_length; ++i)
                CRCParams.crc._16 = (CRCParams.crc._16 << 8) ^ *(CRCParams.iter._16 + ((CRCParams.crc._16 >> 8) ^ ((CRCParams.rev_in) ? reverse_bits_8(data[i]) : data[i])));

            return ((CRCParams.rev_out) ? reverse_bits_16(CRCParams.crc._16) : CRCParams.crc._16) ^ crc16_xor_table[CRCParams.final_index];
        }
        case 32:
        {
            CRCParams.crc._32 = crc32_xor_table[CRCParams.init_index];
            
            int i;
            for (i = 0; i < data_length; ++i)
                CRCParams.crc._32 = (CRCParams.crc._32 << 8) ^ *(CRCParams.iter._32 + ((CRCParams.crc._32 ^ (((CRCParams.rev_in) ? reverse_bits_8(data[i]) : data[i]) << 24)) >> 24));
            
            return ((CRCParams.rev_out) ? reverse_bits_32(CRCParams.crc._32) : CRCParams.crc._32) ^ crc32_xor_table[CRCParams.final_index];
        }
        default:
            return -1;
    }
}

int32_t
crcx_update(int32_t crc, unsigned char data)
{
    if (!loaded)
        return -1;
    
    switch (CRCParams.bits)
    {
        case 8:
        {
            CRCParams.crc._8 = (uint8_t) crc;

            CRCParams.crc._8 = *(CRCParams.iter._8 + (CRCParams.crc._8 ^ ((CRCParams.rev_in) ? reverse_bits_8(data) : data)));

            return ((CRCParams.rev_out) ? reverse_bits_8(CRCParams.crc._8) : CRCParams.crc._8) ^ crc8_xor_table[CRCParams.final_index];
        }
        case 16:
        {
            CRCParams.crc._16 = (uint16_t) crc;

            CRCParams.crc._16 = (CRCParams.crc._16 << 8) ^ *(CRCParams.iter._16 + ((CRCParams.crc._16 >> 8) ^ ((CRCParams.rev_in) ? reverse_bits_8(data) : data)));

            return ((CRCParams.rev_out) ? reverse_bits_16(CRCParams.crc._16) : CRCParams.crc._16) ^ crc16_xor_table[CRCParams.final_index];
        }
        case 32:
        {
            CRCParams.crc._32 = (uint32_t) crc;

            CRCParams.crc._32 = (CRCParams.crc._32 << 8) ^ *(CRCParams.iter._32 + ((CRCParams.crc._32 ^ (((CRCParams.rev_in) ? reverse_bits_8(data) : data) << 24)) >> 24));

            return ((CRCParams.rev_out) ? reverse_bits_32(CRCParams.crc._32) : CRCParams.crc._32) ^ crc32_xor_table[CRCParams.final_index];
        }
        default:
            return -1;
    }
}

static int
load_table(const unsigned char * table_path)
{
    FILE * tables_fd;
    if (!(tables_fd = fopen(table_path, "r")))
        return -1;

    fseek(tables_fd, table_offset(crc_x), 0);
    fread(table, CRCParams.bits/8, 256, tables_fd);

    fclose(tables_fd);

    loaded = 1;
    return 0;
}

int
crcx_use(uint64_t x, const unsigned char * table_path)
{
    if (!(crc_x ^ x))
        return 0;

    crc_x = x;
    
    switch (get_bits(crc_x))
    {
        case 8:
            CRCParams.iter._8     = (uint8_t *) &table;
            break;
        case 16:
            CRCParams.iter._16    = (uint16_t *) &table;
            break;
        case 32:
            CRCParams.iter._32    = (uint32_t *) &table;
            break;
        default:
            return -1;
    }
    CRCParams.bits          = get_bits(crc_x);
    CRCParams.rev_in        = reverse_input(crc_x);
    CRCParams.rev_out       = reverse_output(crc_x);
    CRCParams.init_index    = init_index(crc_x);
    CRCParams.final_index   = final_index(crc_x);
    
    if (load_table(table_path))
        return -1;
    
    return 0;
}