#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define MAX_MSG_LEN 16

#define SRX_CHAN_MASK    0x7800
#define SRX_VAL_MASK_LEN 11
#define SRX_VAL_MASK     0x07FF

const char *byte_to_binary(uint8_t x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 0x80; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

const char *word_to_binary(uint16_t x)
{
    static char b[17];
    b[0] = '\0';

    int z;
    for (z = 0x8000; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

int main(int argc, char** argv)
{
  int i;
  uint16_t msgWord;
  char bMSB[9];
  char bLSB[9];
  char bWord[17];

  //uint8_t input[MAX_MSG_LEN] = {0x04, 0xf9, 0x08, 0x3e, 0x0C, 0xa5, 0x10, 0x9c, 0x14, 0x23, 0x18, 0xbb, 0x1c, 0x1d, 0x20, 0xcf};
  uint8_t input[MAX_MSG_LEN] = {
    0b00001101, 0b11011100,
    0b00010101, 0b11100001,
    0b00011101, 0b11010111,
    0b00100100, 0b00010110,
    0b00101010, 0b11001001,
    0b00110010, 0b01010010,
    0b00111100, 0b00100100,
    0b01000111, 0b11111111,
  };

  for ( i = 0; i < MAX_MSG_LEN; i += 2) {
    
    // What are the two bytes?
    strncpy(bMSB, byte_to_binary(input[i]), 9); 
    strncpy(bLSB, byte_to_binary(input[i+1]), 9); 
    printf("MSB: %4.4hx %s LSB: %4.4hx %s\n", input[i], bMSB, input[i+1], bLSB);
    
    // Assemble the bytes into a word
    uint16_t msgWord = input[i] << 8; msgWord = msgWord | input[i+1];
    strncpy(bWord, word_to_binary(msgWord), 17);
    printf("msgWord: %4.4hx %s\n", msgWord, bWord);

    // Calculate the channel number and value
    int channelNum = ( msgWord & SRX_CHAN_MASK ) >> SRX_VAL_MASK_LEN;
    int channelVal = msgWord & SRX_VAL_MASK;
    printf("CHAN: %4d VAL: %4d\n\n", channelNum, channelVal);
  }
}

