const int nleds = 4;
const int leds[nleds] = { 6, 9, 10, 11 };

const float FREQ = 3, MAX_BRI = 180;
const float phase[nleds] = { .0, .25, .5, .75 };

void setup()  { 
  // reset leds
  for(int i=0; i<nleds; ++i) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()  { 
  for(int i=0; i<nleds; ++i) {
    float time = millis() / 1e+3;
    int brightness = MAX_BRI/2 + MAX_BRI/2*sin(6.283185*( phase[i] + time * FREQ ));
    
    // light up the led
    analogWrite(leds[i], brightness);    
  }   
  
  // wait for 30 milliseconds to see the dimming effect    
  delay(10);                     
}

