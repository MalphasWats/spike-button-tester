#include <avr/io.h>

#include "main.h"

int main (void) 
{    
    initialise();
        
    display_image(&LOGO[0], 3, 3, 10, 2);
    
    delay_ms(SPLASH_DELAY);
    
    for(ever)
    {
        word btn_val = (~PINA & 0x0f) | ((~PINB << 4) & 0x70);
        
        for (byte d=0 ; d<4 ; d++)
        {
            set_display_col_row((9-d)*8, 4);
            shift_out_block( &GLYPHS[((btn_val % 10)+1)*8], FALSE);
            btn_val = btn_val / 10;
        }
    }
}
