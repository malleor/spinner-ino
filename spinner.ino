// https://github.com/malleor/spinner-ino

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

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
  
  // set up webserver
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

void setSpinner(float frequency)  {
  for(int i=0; i<nleds; ++i) {
    float time = millis() / 1e+3;
    int brightness = MAX_BRI/2 + MAX_BRI/2*sin(6.283185*( phase[i] + time * frequency ));
    
    // light up the led
    analogWrite(leds[i], brightness);    
  }   
}

float readFrequency(float prev_freq)  {
  int pot_pos = analogRead(0);
  int pot_neg = analogRead(1);
  
  static const bool LOG_FREQ = false;
  
  if(pot_pos > 0) {    
    prev_freq *= FREQ_BOOST;
    if(LOG_FREQ) {
      Serial.print("freq = ");
      Serial.println(prev_freq);
    }
  }
  
  if(pot_neg > 0) {    
    prev_freq /= FREQ_BOOST;
    if(LOG_FREQ) {
      Serial.print("freq = ");
      Serial.println(prev_freq);
    }
  }
  
  return prev_freq;
}

void loop()  { 
  // light the LEDs
  setSpinner(freq);
  delay(10);                     
  
  // read the encoder; modify frequency
  freq = readFrequency(freq);
  
  // handle Bridge connection
  YunClient client = server.accept();
  if(client) {
    Serial.println("client connected");
    client.print("HELLO");
    client.stop();
  }
}

