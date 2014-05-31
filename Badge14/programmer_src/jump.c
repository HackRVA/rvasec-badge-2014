/*
"pic32usb1388 -v1.0- by Michele Costantino - PIC32 programmer for the Microchip AN1388 USB HID Bootloader"
Copyright (C) 2013  Michele Costantino

This program is entirely based on pic32prog by Serge Vakulenko and it represents a modified version of a small part of it

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA


Release notes:

18/11/2013  - V1.0
-   Initial release.

*/

// Linux required packages: libusb-dev, libusb-1.0-0-dev
// Codeblocks settings: Projects->Build Options->Linker Setting-> add link libraries:usb-1.0 and pthread

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hidapi.h"


#define FRAME_SOH           0x01
#define FRAME_EOT           0x04
#define FRAME_DLE           0x10

#define CMD_READ_VERSION    0x01
#define CMD_ERASE_FLASH     0x02
#define CMD_PROGRAM_FLASH   0x03
#define CMD_READ_CRC        0x04
#define CMD_JUMP_APP        0x05

#define MICROCHIP_VID           0x04d8  /* Microchip Vendor ID */
#define BOOTLOADER_PID          0x003c  /* Microchip AN1388 Bootloader */


#define MAXLINETEXT 300 // maximum number of characters per line in the text file
#define debug_level 0 // compile with this to 1 will enable debug messages


// Macros
/* Converting between hex and binary. */
#define NIBBLE(x)       (isdigit(x) ? (x)-'0' : tolower(x)+10-'a')
#define HEX(buffer)     ((NIBBLE((buffer)[0])<<4) + NIBBLE((buffer)[1]))

// Variables
char inputhexfile[MAXLINETEXT], bootloader_rev[3]="000";


//  Function prototypes
int parse_hex_file (char *filename);
void bootloader_command (hid_device *hiddev, unsigned char cmd,unsigned char *data, unsigned data_len);
unsigned calculate_crc (unsigned crc, unsigned char *data, unsigned nbytes);
inline unsigned add_byte (unsigned char c, unsigned char *buf, unsigned indx);
void send_command (hid_device *hiddev, unsigned char *buf, unsigned nbytes);
int recv_command (hid_device *hiddev, unsigned char *buf);

// Main Program
int main (int argc, char **argv)
{
    printf("\n");
    printf("pic32usb1388 -v1.0- by Michele Costantino - PIC32 programmer for the Microchip AN1388 USB HID Bootloader.\n");
    printf("This program is entirely based on pic32prog by Serge Vakulenko and it represents a modified version of a small part of it.\n");

    switch (argc)
    {
    case 1:
        printf("Usage: ");
        printf("pic32usb1388 [filename.hex]\n");
        printf("\nProgram terminated.\n");
        return 0;
        break;
    case 2:
        sprintf(inputhexfile,"%s",argv[1]);
        parse_hex_file(argv[0]);
        return 0;
        break;

    default:
        return 0;
        break;

    }

}


int parse_hex_file (char *filename)
{

    FILE *fd;
    unsigned char buf [256], data[64];
    int i,j,line;
    hid_device *hiddev;

    hiddev = hid_open (MICROCHIP_VID, BOOTLOADER_PID, 0);
    if (! hiddev)
    {
        printf ("AN1388 bootloader not found: Is your USB cable connected and your board in bootloader mode?\n");
        printf("\nProgram terminated.\n");
        return 1;
    }
    else
        printf ("AN1388 bootloader found -");

    // Read AN1388 bootloader version
    bootloader_command (hiddev, CMD_READ_VERSION, 0, 0);
    printf (" version %d.%d\n",bootloader_rev[1], bootloader_rev[2]);


/*
    if ((fd = fopen(inputhexfile,"r"))== NULL)
    {
        printf ("ERROR: Cannot open the input %s file\n",inputhexfile);
        printf("\nProgram terminated.\n");
        return 1;
    }

    printf("Erasing...");
    fflush (stdout);
    bootloader_command (hiddev, CMD_ERASE_FLASH, 0, 0);
    printf("done.\n");
    fflush (stdout);

    line=0;
    while (fgets ((char*) buf, sizeof(buf), fd)) {

        j=0;
        for (i=1; i<10+2*HEX(buf+1); i+=2) {
             data[j]=HEX(buf+i);
             //printf("%02x",data[j]);
             j++;
        }
        printf("Programming hex file line: %d\r",++line);
        fflush (stdout);
        bootloader_command (hiddev, CMD_PROGRAM_FLASH, data, j);
    }

    fclose (fd);

    printf("\ndone.\n");
    fflush (stdout);
*/

    printf("Jumping to the application.\n");
    fflush (stdout);
    bootloader_command (hiddev, CMD_JUMP_APP, 0, 0);
    printf("Please disconnect the USB cable.\nEnd of the process.\n");
    fflush (stdout);

    /* sleep(1) seems to fix a race condition:
       ./jump: symbol lookup error: /usr/lib/libhidapi-libusb.so.0: undefined symbol: libusb_handle_events_completed
    */
    sleep(1);

    hid_close(hiddev);

    return 0;
}

void bootloader_command (hid_device *hiddev, unsigned char cmd,unsigned char *data, unsigned data_len)
{
    unsigned char buf [64];
    unsigned i, n, c, crc;
    unsigned char reply [64];
    int reply_len;

    if (debug_level > 0) {
        int k;
        fprintf (stderr, "---Cmd%d", cmd);
        for (k=0; k<data_len; ++k) {
            if (k != 0 && (k & 15) == 0)
                fprintf (stderr, "\n       ");
            fprintf (stderr, " %02x", data[k]);
        }
        fprintf (stderr, "\n");
    }
    memset (buf, FRAME_EOT, sizeof(buf));
    n = 0;
    buf[n++] = FRAME_SOH;

    n = add_byte (cmd, buf, n);
    crc = calculate_crc (0, &cmd, 1);

    if (data_len > 0) {
        for (i=0; i<data_len; ++i)
            n = add_byte (data[i], buf, n);
        crc = calculate_crc (crc, data, data_len);
    }
    n = add_byte (crc, buf, n);
    n = add_byte (crc >> 8, buf, n);

    buf[n++] = FRAME_EOT;
    send_command (hiddev, buf, n);

    if (cmd == CMD_JUMP_APP) {
        /* No reply expected. */
        return;
    }

    n = recv_command (hiddev, buf);



    c = 0;
    for (i=0; i<n; ++i) {
        switch (buf[i]) {
        default:
            reply[c++] = buf[i];
            continue;
        case FRAME_DLE:
            reply[c++] = buf[++i];
            continue;
        case FRAME_SOH:
            c = 0;
            continue;
        case FRAME_EOT:
            reply_len = 0;
            if (c > 2) {
                unsigned crc = reply[c-2] | (reply[c-1] << 8);
                if (crc == calculate_crc (0, reply, c-2))
                    reply_len = c - 2;
            }

            if ((reply_len == 3) && (cmd == CMD_READ_VERSION)) {
                bootloader_rev[1]=reply[1];
                bootloader_rev[2]=reply[2];
            }

            if (reply_len > 0 && debug_level > 0) {
                int k;
                fprintf (stderr, "--->>>>");
                for (k=0; k<reply_len; ++k) {
                    if (k != 0 && (k & 15) == 0)
                        fprintf (stderr, "\n       ");
                    fprintf (stderr, " %02x", reply[k]);
                }
                fprintf (stderr, "\n");
            }
            return;
        }
    }

}


void send_command (hid_device *hiddev, unsigned char *buf, unsigned nbytes)
{
    if (debug_level > 0) {
        int k;
        fprintf (stderr, "---Send");
        for (k=0; k<nbytes; ++k) {
            if (k != 0 && (k & 15) == 0)
                fprintf (stderr, "\n       ");
            fprintf (stderr, " %02x", buf[k]);
        }
        fprintf (stderr, "\n");
    }
    hid_write (hiddev, buf, 64);
}


int recv_command (hid_device *hiddev, unsigned char *buf)
{
    int n;

    n = hid_read (hiddev, buf, 64);
    if (n <= 0) {
        fprintf (stderr, "hidboot: error %d receiving packet\n", n);
        exit (-1);
    }
    if (debug_level > 0) {
        int k;
        fprintf (stderr, "---Recv");
        for (k=0; k<n; ++k) {
            if (k != 0 && (k & 15) == 0)
                fprintf (stderr, "\n       ");
            fprintf (stderr, " %02x", buf[k]);
        }
        fprintf (stderr, "\n");
    }
    return n;
}


inline unsigned add_byte (unsigned char c, unsigned char *buf, unsigned indx)
{
    if (c == FRAME_EOT || c == FRAME_SOH || c == FRAME_DLE)
        buf[indx++] = FRAME_DLE;
    buf[indx++] = c;
    return indx;
}

unsigned calculate_crc (unsigned crc, unsigned char *data, unsigned nbytes)
{
    static const unsigned short crc_table [16] = {
        0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
        0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    };
    unsigned i;

    while (nbytes--) {
        i = (crc >> 12) ^ (*data >> 4);
        crc = crc_table[i & 0x0F] ^ (crc << 4);
        i = (crc >> 12) ^ (*data >> 0);
        crc = crc_table[i & 0x0F] ^ (crc << 4);
        data++;
    }
    return crc & 0xffff;
}




