/**automatated watering program **/

#include <avr/sleep.h>
#include <avr/wdt.h>
#define BEAT 300   // define time for the tone.
#define PINNO 12

int led = 13;

void setup() { // setup code to run once: 
  pinMode(led, OUTPUT);     
}



void loop() { //  main code here, to run repeatedly:
  
  tone(PINNO,262,BEAT) ;  // C(do)
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // D(re)
  delay(BEAT) ;
  tone(PINNO,330,BEAT) ;  // E(mi)
  delay(BEAT) ;
  tone(PINNO,262,BEAT) ;  // C (do)
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // D(re)
  delay(BEAT) ;
  tone(PINNO,330,BEAT) ;  // E(mi)
  delay(BEAT) ;
  tone(PINNO,392,BEAT) ;  // G(so)
  delay(BEAT) ;    
  tone(PINNO,330,BEAT) ;  // E(mi)
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // D(re)
  delay(BEAT) ;
  tone(PINNO,262,BEAT) ;  // C(do)
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // D(re)
  delay(BEAT) ;
  tone(PINNO,330,BEAT) ;  // E(mi)
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // D(re)
  delay(BEAT) ;
  delay(1000) ;           // Wait for 1 second
  digitalWrite(led,HIGH); //Make No. 11pin output HIGH = 5V
  delay(500); // Watering time
  digitalWrite(led,LOW); //Make No.11 pin output LOW = 0V
 
  //Shutdown program to save battery using by watchdogtimer 24h standby mode
   
   
  int var = 0;
  while(var < 10800){
    delayWDT(9);     // 9seconds of shutdown                  
    var++;           // 10800times repeat ＝24h                 
  } 
}
 
void delayWDT(unsigned long t) {        // delay excute while using powerdown mode 
  delayWDT_setup(t);                    // watchdog timer setting 
  ADCSRA &= ~(1 << ADEN);               // ADEN bit clear and stop ADC
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Powerdow mode
  sleep_enable();
 
  sleep_mode();                         // sleep mode
 
  sleep_disable();                      // WatchDog Timer times up and start working agian  
  ADCSRA |= (1 << ADEN);                // turn on the ADC 
}
 
void delayWDT_setup(unsigned int ii) {  // setting uup timer
  // 0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
  // 6=1sec, 7=2sec, 8=4sec, 9=8sec
  byte bb;
  if (ii > 9 ){                         // get rid of strage numbers
    ii = 9;
  }
  bb =ii & 7;                           
  if (ii > 7){                          
    bb |= (1 << 5);                     
  }
  bb |= ( 1 << WDCE );
 
  MCUSR &= ~(1 << WDRF);                // MCU Status Reg. Watchdog Reset Flag ->0
  // start timed sequence
  WDTCSR |= (1 << WDCE) | (1<<WDE);     // allow to edit watchdog（
  // set new watchdog timeout value
  WDTCSR = bb;                          // 
  WDTCSR |= _BV(WDIE);
} 
 
ISR(WDT_vect) {                         // the work after time up, WDT
  //  wdt_cycle++;                        
}

