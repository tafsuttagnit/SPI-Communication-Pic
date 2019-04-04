
#include "header_slave.h"
#include "spi.h"
#include <xc.h>
#define USE_OR_MASKS
#include <p18cxxx.h>
#include "stdlib.h"
#include "stdio.h"
 unsigned char rd ;
 unsigned char ret ;
//void GPIO_Init(void);

void main (void)
{
    /* Configurer Oscillateur */
    
    /* Configuration GPIO */

    /* Configurer les peripheriques */
    /* SPI_Init();*/
    
    /* ACtiver les périphériques */
    
    /* boucle infinie */
    
   
    
    OSCCONbits.SCS0 = 1;
 	OSCCONbits.SCS1 = 1;
    OSCCONbits.IRCF0 = 1; 		//Bits corresponding to 8Mhz internal oscillator
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 0;
    OSCTUNEbits.INTSRC = 1;   //séléctionner quelle horloge interne utilisée */
    
   
    
    // OSCCONbits.SCS0 = 1;
 	//OSCCONbits.SCS1= 0;
    
    PIE1bits.SSPIE =1;
    INTCONbits.PEIE = 1;
    //PIR1bits.SSPIF = 0;

    
   
    TRISBbits.RB4 = 0;
    TRISBbits.RB5 = 0;
    TRISBbits.RB6 = 0;
    //TRISBbits.RB7 = 0;
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
    LATBbits.LATB6 =1;
   
    
    

    
    initialiseSPI();
    
    
    
    while(1)
    {    
       
        
        
        rd = SPIRead();
        
       /* LATAbits.LATA5 = 0;
        DelayMs(2000);
       
        ret = SPIWrite (0xF2);
         LATAbits.LATA5 = 1;
        //DelayMs(2000);*/
        
       /* rd = SPIRead();
        rd = SPIRead();*/
        //while(SSPSTATbits.BF==0);
        
        //rd = SSPBUF;
        
      //if (rd == 0xF0)
     
    //////////////: test de la bonne réception /////////////////:  
      if (rd == 0x0F)
      {
          LATBbits.LATB4 = 1;//!LATBbits.LATB4;
          LATBbits.LATB5 = 0;
          
          
      }
      else if (rd == 0x02)
      {
          LATBbits.LATB4 = 0;//!LATBbits.LATB5;
          LATBbits.LATB5 = 1;
      } 
        
        
        
        //////////////: test si il envoi bien //////////////////////:
      if (ret == 0xF2 ) 
      {   
          LATBbits.LATB6 = 0;
          
          LATBbits.LATB6 = 1;
      }
        
      /* switch(rd)
        {
           case 0x0F:
                LATBbits.LATB4 = 0;
                LATBbits.LATB5 = 0;
                break;
            case 0xF0:
                LATBbits.LATB4 = 0;
                LATBbits.LATB5 = 1;
                break;
            case 0x02:
                LATBbits.LATB4 = 0;
                LATBbits.LATB5 = 1;
                break;
           // default:
                //LATBbits.LATB4 = 0;
                //LATBbits.LATB5 = 0;
                //LATBbits.LATB5 = !LATBbits.LATB5;
                //break;
        } */
       
       
       
          

    }
}



unsigned char SPIRead (void)
{   
    unsigned char w;
    SSPBUF = 0x00;            
    //while(!SSPSTATbits.BF);  // Test transmission ends up
    //w = SSPBUF;
    while (!PIR1bits.SSPIF);
    return SSPBUF;
    
    
}




void DelayMs(unsigned int Delay)
 {
     unsigned int i,j;

     for(i=0;i<Delay;i++);
        // for(j=0;j<1000;j++);
 }



void initialiseSPI(void) 

{
    ADCON1 = 0x0F;
    TRISBbits.RB0 = 1; // SDI configured as input
    TRISBbits.RB1 = 1; // SCLK configured as input
    TRISCbits.RC7 = 0; // SDO configured as output
    TRISAbits.RA5 = 1; // SS configured as input
    
    /* SPI Register Configuration */
    SSPCON1bits.SSPEN = 0;
    
    SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 0;
    
    //SSPCON1bits.WCOL = 0;
    SSPCON1bits.SSPOV =0;
    SSPCON1bits.CKP = 1;
    SSPCON1bits.SSPM = 0b0101;
    
    SSPCON1bits.SSPEN = 1;
   
} 

unsigned char SPIWrite (unsigned char d)
{  
    
    while(SSPSTATbits.BF == 0)
        
    {
        SSPBUF = 0x00;
        SSPBUF = d;
    }
    //while(!SSPSTATbits.BF);
    return SSPBUF;
 }
