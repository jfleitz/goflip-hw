/*********************************************SPISlave*********************************************
These are the functions required for the SPI Slave.  The driver waits for an IRQ caused by the
Slave Select going High.  The ISR for the Slave Select will loop until the SSEL is released by
the master.
**************************************************************************************************/

#include <ez8.h>
#include <defines.h>
#include "spibase.h"

extern char DataOut[];
extern char DataIn[];

char* pBaseOut;            // Out Base Pointer
char* pOut;                // Out Pointer
char* pBaseIn;             // In Base Pointer
char* pIn;                 // In Pointer

unsigned char ByteBlock;   // Flag Byte or Block mode
unsigned short Length;     // Number of bytes to exchange (1 to 256)

volatile char DataReady;   // Flag indicating that data is/are ready


/*********************************************InitSPI*********************************************
Prepares the SPI driver.  Set the outputs needed and get the interrupt ready.  The clock interrupt
is polled, so we won't need that turned on
**************************************************************************************************/
void InitializeSPI()
{


    PCDD &= ~MISObit;      // MISO is an output
    IRQ2 &= ~SSELbit;      // Make sure it hasn't fired yet
    IRQ2ENH |= SSELbit;    // Turn on SSEL interrupt
    IRQ2 &= ~SCLKbit;      // Push the flag down
    DataReady = FALSE;     // Nothing exchange	
}


void SPI_Send(char data)
{
   char data_in;
   DataReady = FALSE;
   pOut = pBaseOut = &data;
   pIn = pBaseIn = &data_in;
   Length = 1;
   ByteBlock = 0;

   //took out the while loop here, as we want to just return
}

void SPI_SendReceiveBlock(char* p_out, char* p_in, unsigned char length)
{
   pOut = pBaseOut = p_out;
   pIn = pBaseIn = p_in;
   DataReady = FALSE;

   if (length)
   {
      Length = length;
   }
   else
   {
      Length = 256;     // Zero = 256
   }

   ByteBlock = 0xFF;    // Mode Block
	//took out the while loop here, as we want to just return
}


/*********************************************SSELISR**********************************************
This is the ISR for the Slave Select.  Once the Slave has been selected by the Master the Slave 
will spend all of its resources communicating with the Master until the Select is released
**************************************************************************************************/
void interrupt SSELISR()            // Slave Select ISR
{
   unsigned char data_out = *pOut;  // Temp used for easier compiler addressing
   unsigned char bmin = 0x80;       // bit mask for input
   unsigned char bmout = 0x80;      // bit mask for output

   while (1)
   {
      if (ByteBlock)
      {
         IRQ2 &= ~SCLKbit;          // Push the flag down
   
         while (!(IRQ2 & SCLKbit))  // Wait for clock to trip
         {
            if (SSEL())             // But abort if /SS line goes high
            {
               IRQ2 &= ~SSELbit;    // Turn off IRQ to prevent new ISR
               DataReady = TRUE;    // Flag that data has been received
               return;
            }
         }
      }

      if (Transmitting())           // Clock ready to update transmitter
      {
         if (data_out & bmout)
         {
            MISO_H();
         }
         else
         {
            MISO_L();
         }

         bmout = bmout >> 1;

         if (bmout == 0x00)         // Done with this character?
         {
            bmout = 0x80;           // Reset the mask
            data_out = *(++pOut);   // Advance the pointer and read the new value

            if (pOut >= pBaseOut + Length)   // Buffer empty?
            {
               pOut--;              // Resend last byte if requested to do so
            }
         }
      }
      else                          // Receiving
      {
         if (MOSI())                // Data High?
         {
            *pIn |= bmin;           // Then OR into byte
         }
         else
         {
            *pIn &= ~bmin;          // Else AND into byte
         }

         bmin = bmin >> 1;          // Next bit

         if (bmin == 0)             // Byte finished?
         {
            bmin = 0x80;            // Reset the mask
            pIn++;                  // Advance the buffer pointer

            if (pIn >= pBaseIn + Length)  // Over run?
            {
               pIn--;               // Last buffer byte will over run
            }
         }
      }

      if (!ByteBlock)               // Byte mode?
      {
         IRQ2 &= ~SCLKbit;          // Push the flag down
   
         while (!(IRQ2 & SCLKbit))  // Wait for clock to trip
         {
            if (SSEL())             // But abort if /SS line goes high
            {
               IRQ2 &= ~SSELbit;    // Turn off IRQ to prevent new ISR
               DataReady = TRUE;    // Flag that data has been received
               return;
            }
         }

         ByteBlock = 0xFF;          // Switch to byte mode
      }
   }
}


/*******************************************SetupVectors*******************************************
Not a real function, but tells the compiler which vector to use
**************************************************************************************************/
void SetupVectors()
{
    SET_VECTOR(C2, SSELISR);  // Setup vector
}

