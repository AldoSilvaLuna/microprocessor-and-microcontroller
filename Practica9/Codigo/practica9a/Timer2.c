#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>
#define BYTE unsigned char 

static uint8_t Flag;

void Timer2_Ini( void ){
   
	TIMSK2 = 0x00;//&=~((1<<OCIE2A)|(1<<TOIE2));//deshabilitar interrupciones
	ASSR = (1 << AS2); //seleccion de fuente de reloj
	TCCR2A = (2 << WGM20); // modo ctc
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);//(7<<CS20); //prescalador de 1024
	TCNT2 = 0x00; // Clear Counter
	OCR2A = 31; //32768/1024=32 
	while( ASSR & ((1<<TCN2UB)|(1<<OCR2AUB)|(1<<TCR2AUB)) );//esperar para cambio a modo asincrono
	TIFR2 = 0x00; //clear interrupt flags
	TIMSK2 =(1<<OCIE2A);//activar interrupcion para output compare A
	sei();
	
}

uint8_t Timer2_Flag ( void ){
      
	  if( Flag )
	  {
		  Flag=0;
          return 1;
     } else {
        return 0;
      }
}

/* Rutina de Servicio de Interrupci�n para atender la interrupci�n */
/* por Comparaci�n del Timer2 (TCNT2 y OCR2 son iguales) */
ISR(SIG_OUTPUT_COMPARE2A){

 Flag = 1; /* Activa Bandera para indicar los 1 segundos */
} /* fin de la rutina de servicio de Interrupci�n (RSI) */ 


