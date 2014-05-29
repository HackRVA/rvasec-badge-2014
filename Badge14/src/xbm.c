//============================================================================
// Name: xbmto5110.cpp - host side code to convert .xbm to c
// Author: rick@kimballsoftware.com
// Version: 1.0
// Date:  2-1-2013
// Copyright: copyright (c) 2013 rick@kimballsoftware.com
// License: public domain
// Description: .xbm to nokia 5110 c unsigned array .c
//============================================================================

// PEB ripped and converted to run in pic32

unsigned getpixel(unsigned row, unsigned col, unsigned char *bm_bits, unsigned bm_width) {
  unsigned byte_offset = (row * ((bm_width + 7) / 8)) + (col / 8);
  unsigned bitmask_offset = 1 << (col % 8);

  return (bm_bits[byte_offset] & bitmask_offset) ? 1 : 0;
}

/*
* flip bitmap bytes from xbm style where each byte is a row by 8 columns of bits to
* 5510 style where each byte is a column by 8 rows of bits
*
* see: nokia 5110 datasheet for details
*/
void writeXBM(unsigned char *bm, unsigned bm_width, unsigned bm_height) {
  unsigned row, col;

  for (row = 0; row < bm_height; row += 8) {
    for (col = 0; col < bm_width; col++) {
      unsigned ucol_8rows = 0; // one column by 8 rows of bits
      unsigned indx;

      // repack bits into new col order
      for (indx = 0; indx < 8; indx++) {
        unsigned bit = getpixel(row + indx, col, bm, bm_width);
        ucol_8rows |= (bit << indx);

        LCDWrite(LCD_DATA, ucol_8rows);
      }
    }
  }
}

