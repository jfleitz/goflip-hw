/********************************IO Macros Prototypes and Constants*******************************/

#define SPIMode 1


#define SCLKbit 1    // Serial Clock is on PC0
#define MISObit 2    // MISO is on PC1
#define MOSIbit 16   // MOSI is on PB4
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
#define MOSI() (PBIN & MOSIbit)
#define SCLK() (PCIN & SCLKbit)
#define SSEL() (PCIN & SSELbit)


void SPI_Init();   // Prepares SPI driver
char SPI_SendReceive(char data); // Echange a byte
void SPI_SendReceiveBlock(const char* p_out, char* p_in, unsigned char length);  // Exchange a block

