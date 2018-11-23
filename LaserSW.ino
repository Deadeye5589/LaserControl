  //Define for pin out of high voltage relais
  int laserrelais = 10;   //Red & Blue Laser
  int greenrelais = 9;  //Green Laser
  int galvorelais = 11;  //Power Supply for Galvo System
  int laseractive = 0;
  int laserenable = 1;
  int emergencyshutdown = 2;


  //Variables for main loop
  int bootup = 0;     //Indicator for boot up sequence, will prevent reactivation if killswitch was triggered until main power was cycled
  int emergencypressed = 0; 
  int enabled = 0;
  volatile int emergencytriggered = 0;
  
 
void setup() {

  //Control of relais for laser module power supply
  pinMode(laserrelais,OUTPUT);
  digitalWrite(laserrelais,HIGH);
  pinMode(greenrelais,OUTPUT);
  digitalWrite(greenrelais,HIGH);
  pinMode(galvorelais,OUTPUT);
  digitalWrite(galvorelais,HIGH); 
  
  //Control for external emergency shutdown box
  pinMode(emergencyshutdown,INPUT);
  pinMode(laserenable,INPUT);
  pinMode(laseractive,OUTPUT);
  digitalWrite(laseractive,LOW);
}

void loop() {  
  if(bootup == 0)
  {
    emergencypressed = digitalRead(emergencyshutdown);
    enabled = digitalRead(laserenable);
    if(emergencypressed && enabled)
    {
      {
        digitalWrite(galvorelais,LOW);
        delay(1000);
        digitalWrite(greenrelais,LOW);
        delay(1000);
        digitalWrite(laserrelais,LOW);
        bootup = 1;
        digitalWrite(laseractive,HIGH);
       //Interrup to faling signal on emergencyshutdown line
       attachInterrupt(digitalPinToInterrupt(emergencyshutdown), emergency, LOW);
      }
    }
  }
    if(emergencytriggered)
    {
      delay(1000);
      digitalWrite(laseractive,HIGH);
      delay(1000);
      digitalWrite(laseractive,LOW);
    }
  
}

void emergency(void)
{
      digitalWrite(greenrelais,HIGH);
      digitalWrite(laserrelais,HIGH);
      digitalWrite(galvorelais,HIGH);
      digitalWrite(laseractive,LOW);
      emergencytriggered = 1;
}

