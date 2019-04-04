
#include "header1.h"
#include "spi.h"
#include <xc.h>
#define USE_OR_MASKS
#include "delays.h"
#include <p18cxxx.h>
#include "stdlib.h"
#include "stdio.h"

#define CS1 LATBbits.LATB5 
#define LOW 0
#define HIGH 1

unsigned char rd;
unsigned char ret;
void main (void)
{
    OSCCONbits.SCS0 = 1;
 	OSCCONbits.SCS1= 1;
    OSCCONbits.IRCF0 = 1; 		//Bits corresponding $to 8Mhz internal oscillator
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 0;
    OSCTUNEbits.INTSRC = 1;   //séléctionner quelle horloge interne utilisée */
    
   
    /*OSCCONbits.SCS0 = 1;
 	OSCCONbits.SCS1= 0;*/
    
    
    
    
    PIE1bits.SSPIE =1;
    INTCONbits.PEIE = 1;
    PIR1bits.SSPIF = 0;
    
    
    
    TRISBbits.RB5 = 0;
    TRISBbits.RB6 = 0;
    LATBbits.LATB6 =1;
    
    initialiseSPI();
    
    while (1)
    {
       /*CS1 = LOW;
       SPIWrite (0xF0); 
       SPIWrite(0x02);
       CS1 = HIGH;*/
      // ret = SSPBUF;
        DelayMs(2000);
        CS1 = LOW;
        ret = SPIWrite (0x02);
        rd = SPIRead();
        ret = SPIWrite(0x0F);
       // rd = SPIRead();
        
        
        
        CS1 = HIGH;
       
        
        
         //rd = SPIRead();
         
        if(rd == 0xF2)
        {
           
            
          LATBbits.LATB6 = 0;
          DelayMs(2000);
          LATBbits.LATB6 = 1; 
            
        }
        
        DelayMs(2000);
        
         
        
       
    }


}

unsigned char SPIWrite (unsigned char d)
{   
    
    SSPBUF = d;
    while(!SSPSTATbits.BF);
    return SSPBUF;
 }


void DelayMs(unsigned int Delay)
 {
     unsigned int i,j;

     for(i=0;i<Delay;i++);
        
 }

 void initialiseSPI(void)
 {
    //ADCON1 = 0x0F;
    TRISBbits.RB0 = 1; // SDI configured as input
    TRISBbits.RB1 = 0; // SCLK configured as input
    TRISCbits.RC7 = 0; // SDO configured as output
   // TRISAbits.RA5 = 0; // SS configured as output
    
    /* SPI Register Configuration */
    SSPCON1bits.SSPEN = 0;
    
    SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 0;
    
    SSPCON1bits.WCOL = 0;
    SSPCON1bits.SSPOV =0;
    SSPCON1bits.CKP = 1;
    SSPCON1bits.SSPM = 0b0000;
    
    SSPCON1bits.SSPEN = 1;
    

 }
 
 unsigned char SPIRead (void)
{   
    unsigned char w;
    SSPBUF = 0x00;            
    //while(!SSPSTATbits.BF);  // Test transmission ends up
    //w = SSPBUF;
    if (SSPSTATbits.BF == 0)
    {
    return SSPBUF;
    }
    
    
}
 
 