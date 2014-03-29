const int nleds = 4;
const int leds[nleds] = { 6, 9, 10, 11 };

const float MAX_BRI = 180;
const float phase[nleds] = { .0, .25, .5, .75 };
float freq = 2.;
const float FREQ_BOOST = 1.1;

void setup()  { 
  // reset leds
  for(int i=0; i<nleds; ++i) {
    pinMode(leds[i], OUTPUT);
  }
  
  // set up logging
  Serial.begin(9600);
  Serial.println("I'm in.");
}

void setSpinner(float frequency)  {
  for(int i=0; i<nleds; ++i) {
    float time = millis() / 1e+3;
    int brightness = MAX_BRI/2 + MAX_BRI/2*sin(6.283185*( phase[i] + time * frequency ));
    
    // light up the led
    analogWrite(leds[i], brightness);    
  }   
}

void loop()  { 
  // light the LEDs
  setSpinner(freq);
  delay(10);                     
  
  // read the encoder; modify frequency
  int pot_pos = analogRead(0);
  int pot_neg = analogRead(1);
  if(pot_pos > 0) {    
    freq *= FREQ_BOOST;
    Serial.print("freq = ");
    Serial.println(freq);
  }
  if(pot_neg > 0) {    
    freq /= FREQ_BOOST;
    Serial.print("freq = ");
    Serial.println(freq);
  }
}

