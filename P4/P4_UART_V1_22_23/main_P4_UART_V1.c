/*
 * File:   main_P3_LCD_V2.c
 * Author: Ian
 *
 * Created on 16 de febrero de 2023, 15:55
 */

#include "p24HJ256GP610A.h"

#include "oscilator.h"
#include "GPIO.h"
#include "timers.h"
#include "commons.h"
#include "commons_P4.h"
#include "LCD.h"
#include "memoria.h"
#include "utilidades.h"
#include "UART2_RS232.h"

// TCKPS para el prescaler

int main()
{
	inic_oscilator();	// Selecc�n e inicializaci�n del reloj: 80 MHz
	
	inic_leds();	// Inicializaci�n leds: sentido y valor inicial.
    
    inic_pulsadores(); // Inicializaci�n de pulsadores
    
    inic_LCD(); // Inicializaci�n de la pantalla LCD
    
    copiar_FLASH_RAM(Mens_LCD_1, 0);
    copiar_FLASH_RAM(Mens_LCD_2, 1);
    
    line_1();    
    puts_lcd(Ventana_LCD[0], 16);
    line_2();
    puts_lcd(Ventana_LCD[1], 16);
    
    while(PORTDbits.RD6){
        
    }
    
    copiar_FLASH_RAM(Mens_LCD_3, 0);
    copiar_FLASH_RAM(Mens_LCD_4, 1);
    
    line_1();    
    puts_lcd(Ventana_LCD[0], 16);
    line_2();
    puts_lcd(Ventana_LCD[1], 16);
    
    while(PORTDbits.RD13){
        
    }
    
    copiar_FLASH_RAM(Mens_LCD_5, 0);
    copiar_FLASH_RAM(Mens_LCD_6, 1);
    
    line_1();    
    puts_lcd(Ventana_LCD[0], 16);
    line_2();
    puts_lcd(Ventana_LCD[1], 16);
    
    inic_crono();	// Inicializaci�n variables cronometro.

	inic_Timer7();	// Inicializaci�n T7 con un periodo de 10 milisegundos.
    inic_Timer5(); // Inicializaci�n T5 con un periodo de 2.5 milisegundos.
    
    inic_CN(); // Inicializaci�n de las interrupciones para los pulsadores.
    
    inic_UART2();
    
    U2TXREG = 0;
    
	while(1) {
        crono();     
        comprobar_inic_crono();
	}
	return (0);
}