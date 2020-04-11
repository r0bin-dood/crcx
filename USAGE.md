# Usage

After installation is complete, you can use the library by compiling your program with the statically compiled library file. You must have the table file generated during compilation in the same directory as your binary executable. Additionally, you may generate as many table files as you wish with the gen_tables program. At the time of this writing, the size of the table file generated will always be 6912 bytes, or ~7 Kb.

Assuming installation went through without errors, and the table file generated is in the same directory as the to-be-compiled binary, you can use the library in the following ways:

```c
#include <crcx.h>       //stdio.h and stdint.h included
#include <string.h>

int
main(void)
{
    char *  data        = "This is a message";
    int     data_length = strlen(data);

    if (crcx_use(CRC32, "tables")) // table file called "tables" is in current directory
    {
        fprintf(stderr, "There was an oopsie during setup. Is the file in the right directory? Can it only be read by root?");
        return 1;
    }

    int crc;
    if ((crc = crcx(data, data_length)) == -1)
    {
        fprintf(stderr, "Hmm, error during calculation of the CRC. Was crcx_use() called before?");
        return 1;
    }

    printf("Message: %s\n", data);
    printf("    CRC: 0x%X\n", crc);
    return 0;
}
```

If you would like to get all the CRCs of some data (though I don't know why you'd want to do that) and have patiance (or copy the array from here, in which case you don't need any), you can do the following:

```c
#include <crcx.h>       //stdio.h and stdint.h included
#include <string.h>

int
main(void)
{
    char *      data        = "This is a message";
    int         data_length = strlen(data);

    uint64_t    all_crcs[]  = {
        CRC8, CRC8_DARC, CRC8_DVB, CRC8_EBU, CRC8_GSM, CRC8_ICODE, CRC8_ITU, CRC8_ROHC,     
        CRC16_A, CRC16_ARC, CRC16_ACCITT, CRC16_BUYPASS, CRC16_CCIT, CRC16_CDMA, CRC16_DDS110, CRC16_DECTR,   
        CRC16_DECTX, CRC16_DNP, CRC16_EN13757, CRC16_GENIBUS, CRC16_KERMIT, CRC16_MAXIM, CRC16_MODBUS, CRC16_RIELLO,  
        CRC16_TMS, CRC16_USB, CRC16_X25, CRC16_XMODEM, CRC32, CRC32_BZIP2, CRC32_C, CRC32_EXT4,    
        CRC32_GZIP, CRC32_JAMCRC, CRC32_MPEG2, CRC32_PNG, CRC32_POSIX, CRC32_SATA, CRC32_SCTP, CRC32_ZMODEM,
    };
    int crc;

    printf("Message: %s\n", data);
    int i;
    for (i = 0; i < sizeof(all_crcs)/sizeof(uint64_t); ++i) {
        crcx_use(all_crcs[i], "tables");
        crc = crcx(data, data_length);
        printf("    CRC %d: 0x%X\n", i, crc);
    }
    
    return 0;
}
```

The follwing example uses crcx_update() which is used on running checksums, or in this case running CRCs. Given a CRC and a character, it will calculate the next CRC and such will be the current running CRC. This is usually used on arriving data.

```c
#include <crcx.h>       //stdio.h and stdint.h included
#include <string.h>

int
main(void)
{
    char *      data        = "This is a message";
    int         data_length = strlen(data);

    int crc;

    crcx_use(CRC32, "tables");

    crc = crcx(data, 1);

    printf("\'T\' 0x%X\n", crc);

    int i;
    for (i = 1; i < data_length; ++i)
    {
        crc = crcx_update(crc, data[i]);
        printf("\'%c\' 0x%X\n", data[i], crc);
    }

    return 0;
}
```
