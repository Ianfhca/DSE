/* Funciones para trabajar con el modulo UART2
================================================
Comentarios!!!!!!!!!!!
Autorxs: 
Fecha:
*/

#include "p24HJ256GP610A.h"
#include "commons.h"
#include "commons_P4.h"
#include "UART2_RS232.h"
#include "timers.h"
#include "memoria.h"



void inic_UART2 ()
{
	
     // Velocidad de transmision
     // Hay que hacer solo una de las dos asignaciones siguientes
	U2BRG = BAUD_RATEREG_2_BRGH1;
	// U2BRG = BAUD_RATEREG_2_BRGH0;

     // U2MODE: habilitar el modulo (UARTEN), 8 bits, paridad par (PDSEL),
     // 1 bit de stop (STSEL), BRGH ...
	U2MODE = 0;
	U2MODEbits.BRGH = 1;

     // U2STA: modo de interrupcion en el envio (UTXISEL), habilitacion del
     // envio (UTXEN), modo de interrupcion en la recepcion (URXISEL)
	U2STA = 0;

     // inicializacion de los bits IE e IF relacionados (IP si se quiere modificar)
	IFS1bits.U2RXIF = 0;
     	IFS1bits.U2TXIF = 0;
	IEC1bits.U2RXIE = 1;
     	IEC1bits.U2TXIE = 0;

     	//IPC7bits.U2RXIP=xx;
	//IPC7bits.U2TXIP=xx;

     // interrupciones debidas a errores + bug
	IEC4bits.U2EIE = 0;
	U2STAbits.OERR = 0;

     // Habilitar el modulo y la linea TX.
     // Siempre al final y en ese orden!!!

	U2MODEbits.UARTEN = 1;    // habilitar UART2
	U2STAbits.UTXEN = 1;      // habilitar transmision tras habilitar modulo

	Delay_us(T_1BIT_US); 	// Esperar tiempo de 1 bit 
}

void _ISR_NO_PSV _U2RXInterrupt() {
    char c = U2RXREG;
    if (c == 'p' || c == 'P') {
        LATAbits.LATA6 = !LATAbits.LATA6;
    }
    Ventana_LCD[1][0] = c;
    Ventana_LCD[1][15] = c;
    // if (U2RXREG == )
    IFS1bits.U2RXIF = 0;
}