[![LGTM
C](https://img.shields.io/lgtm/grade/c/github/r0bin-dood/crcx)](https://lgtm.com/projects/g/r0bin-dood/crcx/context:cpp)
https://img.shields.io/lgtm/grade/c/github/r0bin-dood/crcx
# CRCx
**Small CRC library in C**

Cyclic Redundancy Checks (CRCs) are data integrity codes calculated over a stream of data, and are usually appended to the end of such data. The most commonly used CRCs in the industry range from 3 to 64 bits, depending on the application. This library features 8, 16, and 32 bit CRCs. CRCs are calculated using generator polynomials, which are numbers specifically chosen for their effectiveness at detecting burst errors in data of varying sizes. There are two accepted approaches to calculating CRCs, the bitwise approach and the lookup table approach; this library uses the latter. Organizations such as CCITT, IBM, and others have standardized genearator polynomials that are used in protocols and standards worldwide. CRCs are not cryptographically safe codes and should not be used to encrypt data.

CRCs in this library:
- CRC-8:
    - DARC, DVB, EBU, GSM, I-CODE, ITU, ROHC
- CRC-16:
    - ARC, AUG-CCITT, BUYPASS, CCITT, CDMA, DDS-110, DECT, DNP, EN-13757, GENIBUS, KERMIT, MAXIM, MODBUS, RIELLO, TMS, USB, X.25, XMODEM
- CRC-32:
    - BZIP2, C, EXT4, GZIP, JAMCRC, MPEG2, PNG, POSIX, SATA, SCTP, ZMODEM

If you would like to learn more about CRCs, the math behind them, and the protocols and standards you can find them in, I would urge you to click on the links below.

If you would like to use a generator polynomial for your own purposes and applications, don't just choose any. See here:

(https://users.ece.cmu.edu/~koopman/crc/index.html) 

(https://www.youtube.com/watch?v=4y_rowNNVUQ)

An intro:

(https://en.wikipedia.org/wiki/Cyclic_redundancy_check)

(https://en.wikipedia.org/wiki/Mathematics_of_cyclic_redundancy_checks)

(https://en.wikipedia.org/wiki/Polynomial_code)

(https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks)

More on it:

(https://web.archive.org/web/20180402205812/http://www.wolfgang-ehrhardt.de/crc_v3.html#chap_09)

(http://reveng.sourceforge.net/crc-catalogue/all.htm)

(https://users.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf)

(https://web.archive.org/web/20110719042902if_/http://sar.informatik.hu-berlin.de/research/publications/SAR-PR-2006-05/SAR-PR-2006-05_.pdf#subsection.A.2)

