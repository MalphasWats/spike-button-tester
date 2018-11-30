#include "MAGE.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

word rngSEED = 5;
word rng( void )
{
    rngSEED = (rngSEED*rngA +rngC) % rngM;
    return rngSEED;
}

void delay_ms( word ms )
{
   for (word i=0; i < ms; i++)
   {
      _delay_ms(1);
   }
}

void delay_us( word us )
{
   for (word i=0; i < us; i++)
   {
      _delay_us(1);
   }
}

void initialise( void )
{
    DDRA = (1<<SDA) | (1<<DC) | (1<<SCL); // Configure Outputs
    
    
    PORTA = 0x0f;
    PORTB = 0x07;
    
    initialise_oled();
    clear_display();
}

/* OLED Functions */

void send_command(byte command)
{
    for (byte i = 0; i < 8; i++)  
    {
        if ( command & (1 << (7 - i)) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
    }
}

void shift_out_byte(byte b)
{
    if ( b & (1 << 0) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
    
    if ( b & (1 << 1) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
    
    if ( b & (1 << 2) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
    
    if ( b & (1 << 3) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
    
    if ( b & (1 << 4) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
    
    if ( b & (1 << 5) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
    
    if ( b & (1 << 6) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
    
    if ( b & (1 << 7) )
    {
        PORTA |= 1 << SDA;
    }
    else
    {
        PORTA &= ~(1 << SDA);
    }
    
    PORTA |= 1 << SCL;      // HIGH
    PORTA &= ~(1 << SCL);   // LOW
}

/* Un-rolling the loop makes this much faster */
void shift_out_block(const __memx byte *block, byte inverted)
{
    byte b;
    for (byte i = 0; i < 8; i++)  
    {
        b = block[i];
        if (inverted)
            b = ~b;
        
        if ( b & (1 << 0) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
        
        if ( b & (1 << 1) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
        
        if ( b & (1 << 2) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
        
        if ( b & (1 << 3) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
        
        if ( b & (1 << 4) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
        
        if ( b & (1 << 5) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
        
        if ( b & (1 << 6) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
        
        if ( b & (1 << 7) )
        {
            PORTA |= 1 << SDA;
        }
        else
        {
            PORTA &= ~(1 << SDA);
        }
        
        PORTA |= 1 << SCL;      // HIGH
        PORTA &= ~(1 << SCL);   // LOW
    }
}

void initialise_oled(void)
{
    PORTA &= ~(1 << DC);        // LOW (Command Mode)
    send_command(0xAE);         // DISPLAYOFF
    
    send_command(0xD5);         // SETDISPLAYCLOCKDIV
    send_command(0x80);         // the suggested ratio 0x80

    send_command(0xA8 );        // SSD1306_SETMULTIPLEX
    send_command(SCREEN_HEIGHT - 1);

    send_command(0xD3 );        // SETDISPLAYOFFSET
    send_command(0x0);          // no offset
    send_command(0x40  | 0x0);  // SETSTARTLINE line #0
  
    send_command(0x8D);        // CHARGEPUMP
    send_command(0x14);         // Not External Vcc
  
    send_command(0x20 );        // MEMORYMODE
    send_command(0x00);         // 0x0 act like ks0108
    send_command(0xA0  | 0x1);  // SEGREMAP
    send_command(0xC8 );        // COMSCANDEC


    send_command(0xDA);        // SETCOMPINS
    send_command(0x12);
  
    send_command(0x81 );        // SETCONTRAST
    send_command(0xCF);         // Not External Vcc


    send_command(0xD9 );        // SETPRECHARGE
    send_command(0xF1);         // Not External Vcc
  
    send_command(0xDB);        // SETVCOMDETECT
    send_command(0x40);
  
    send_command(0xA4 );        // DISPLAYALLON_RESUME
    send_command(0xA6 );        // NORMALDISPLAY

    //send_command(0x2E );        // DEACTIVATE_SCROLL

    send_command(0xAF);         // DISPLAYON
    
    send_command(0xB0 + 0);           // PAGEADDR (0 = reset)
    send_command(0 & 0x0F);           // Column start address (0 = reset)
    send_command(0x10 | (0 >> 4));    // LOW COL ADDR
    
    PORTA |= 1 << DC;           // DATA
}

void clear_display(void)
{
    for (byte row=0 ; row<SCREEN_ROWS ; row++)
    {
        for (byte col=0 ; col<SCREEN_WIDTH ; col++)
        {
            shift_out_byte(0x00);
        }
    }
}

void display_off(void)
{
    PORTA &= ~(1 << DC);    // COMMAND
    send_command(0xAE);     // DISPLAYOFF
    PORTA |= 1 << DC;       // DATA
}

void display_on(void)
{
    PORTA &= ~(1 << DC);    // COMMAND
    send_command(0xAF);     // DISPLAYON
    PORTA |= 1 << DC;       // DATA
}

void display_image(const __memx byte *img, byte col, byte row, byte width, byte height)
{
    for (byte h=0 ; h<height ; h++)
    {
        set_display_col_row(col*8, row+h);
        
        for (byte w=0 ; w<width ; w++)
            shift_out_block(&img[(width * h + w)*8], FALSE);
    }
}

void set_display_col_row(byte col, byte row)
{
    PORTA &= ~(1 << DC);                    // COMMAND
    
    send_command(0xB0 + row);               // PAGEADDR
    send_command(col & 0x0F);               // Column start address (0 = reset)
    send_command(0x10 | (col >> 4));        // LOW COL ADDR
    
    PORTA |= 1 << DC;                       // DATA
}