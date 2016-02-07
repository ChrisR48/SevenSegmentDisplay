#include "SevSeg.h"

SevSeg sevseg;


float calcFactor(uint32_t cost_per_hour){
  float cost = (float) cost_per_hour;
  return cost / (60 * 60 * 1000.0f);
}

float time_cost_factor = calcFactor(50); 

bool time_running = true;

uint32_t start_time = 0;

void setup() {
  // put your setup code here, to run once:
   byte numDigits = 4;
   byte digitPins[] = {4, 3, 2, 1};
   byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
   sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);

    sevseg.setNumber(time_cost_factor * 1000,3);

    while(millis() < 1000){
      sevseg.refreshDisplay();
    }
}


void loop() {

  if(time_running){
    uint32_t diff = millis() - start_time;

    float costs = diff * time_cost_factor;

    if(costs < 100){
      sevseg.setNumber(costs,2);  
    }else if(costs < 1000){
      sevseg.setNumber(costs,1);  
    }else{
      sevseg.setNumber(costs,0);
    }
    
  }else{
    sevseg.setNumber(0,0);
  }
  
  sevseg.refreshDisplay();
}
