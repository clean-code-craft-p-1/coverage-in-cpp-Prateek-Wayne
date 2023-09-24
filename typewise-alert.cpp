#include "typewise-alert.h"
#include <stdio.h>
#include <map>
using namespace std;
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}



BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;

  map<CoolingType,int> upperLimitMap={
    {PASSIVE_COOLING,35},
    {HI_ACTIVE_COOLING,45},
    {MED_ACTIVE_COOLING,40}
  };
  int upperLimit=upperLimitMap[coolingType];

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, EquipmentCharacter characteristic, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    characteristic.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  map<BreachType,string> = breachMessage{
    {TOO_LOW,"Hi, the temperature is too low\n"},
    {TOO_HIGH,"Hi, the temperature is too high\n"},
    {NORMAL,""}
  };
  // switch(breachType) {
  //   case TOO_LOW:
  //     printf("To: %s\n", recepient);
  //     printf("Hi, the temperature is too low\n");
  //     break;
  //   case TOO_HIGH:
  //     printf("Hi, the temperature is too high\n");
  //     break;
  //   case NORMAL:
  //     break;
  // }
  printf("To: %s\n", recepient);
  printf(breachMessage[breachType])
}
