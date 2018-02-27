

/********************************IO Macros Prototypes and Constants*******************************/

#define SPIMode 1


#define SCLKbit 8    // Serial Clock is on PC3
#define MISObit 32    // MISO is on PC5
#define MOSIbit 16   // MOSI is on PC4
#define SSELbit 4    // SSELbit is on PC2
#define SSELirq C2   // Which interrupt to use


// Macros for different SPI modes

#if SPIMode == 0
   #define Transmitting() (!(PCIN & SCLKbit))
#endif

#if SPIMode == 1
   #define Transmitting() (PCIN & SCLKbit)
#endif

#if SPIMode == 2
   #define Transmitting() (PCIN & SCLKbit)
#endif

#if SPIMode == 3
   #define Transmitting() (!(PCIN & SCLKbit))
#endif


#define MISO_H() (PCOUT |= MISObit)
#define MISO_L() (PCOUT &= ~MISObit)
#define MOSI() (PCIN & MOSIbit)
#define SCLK() (PCIN & SCLKbit)
#define SSEL() (PCIN & SSELbit)


void InitializeSPI();   // Prepares SPI driver
void SPI_Send(char data); // Echange a byte
void SPI_SendReceiveBlock(char* p_out, char* p_in, unsigned char length);  // Exchange a block

