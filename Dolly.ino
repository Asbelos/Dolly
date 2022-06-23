

#include "IRremote.h"

const int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
bool lightsOn[10]={true,true,true,true,true,true,true,true,true,true}; 

void swap(byte light) {
  lightsOn[light]=!lightsOn[light];
  byte pin=light+6;
  Serial.print("Switching light ");
  Serial.print(light);
  Serial.print(" pin ");
  Serial.print(pin);
  Serial.println(lightsOn[light]?" ON":" OFF");
  
  digitalWrite(pin,lightsOn[light]?LOW:HIGH);
}
bool powerOn=false;

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); for (int i=0;i<10;i++) if (lightsOn[i]) swap(i); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1"); swap(2);    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3"); swap(1);   break;
  case 0xFF10EF: Serial.println("4"); swap(4);   break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6"); swap(3);   break;
  case 0xFF42BD: Serial.println("7"); swap(6);   break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9"); swap(5);   break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

 

} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(115200);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  for (int pin=3;pin<13;pin++) pinMode(pin,OUTPUT);

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    delay(250); // Do not get immediate repeat
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */
