#include "p24HJ256GP610A.h"
#include "commons.h"

void inic_Timer7 ()
{
    TMR7 = 0 ; 	// Inicializar el registro de cuenta
    PR7 =  0xc350;	// Periodo del timer 50000
		// Queremos que cuente 10 ms.
		// Fosc= 80 MHz (vease Inic_oscilator()) de modo que
		// Fcy = 40 MHz (cada instruccion dos ciclos de reloj)
		// Por tanto, Tcy= 25 ns para ejecutar una instruccion
		// Para contar 10 ms se necesitan XXX ciclos.
    T7CONbits.TCKPS = 1;	// escala del prescaler 1:8
    T7CONbits.TCS = 0;	// reloj interno
    T7CONbits.TGATE = 0;	// Deshabilitar el modo Gate
    
    T7CONbits.TON = 1;	// puesta en marcha del timer
}	

unsigned int mili, deci, seg, min;
void inic_crono()	
// inicializacion de las variables del cronometro
{
	//completad codigo
    mili = 0;
    deci = 0;
    seg = 0;
    min = 0;
}

void delay_10ms()	// detecta que el timer ha llegado a 10 milisegundos
{
	//completad codigo
    while (!IFS3bits.T7IF);	// encuesta continua    
    // ACORDARSE )DE PONER EL IF A 0 
    mili += 10;
    IFS3bits.T7IF = 0;
}

void cronometro()	
// control del tiempo espera 10 ms y luego actualiza
{
    delay_10ms();	// espera a que pasen 10 milisegundos
  // completad codigo
    if (mili == 100) {
        LATAbits.LATA2 = !LATAbits.LATA2;
        mili = 0;
        deci++;
    }
    if (deci == 10) {
        LATAbits.LATA0 = !LATAbits.LATA0;
        deci = 0;
        seg++;
    }
    if (seg == 60) {
        seg = 0;
        min++;
    }
}

