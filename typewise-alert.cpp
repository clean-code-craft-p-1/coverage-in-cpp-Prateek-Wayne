#include "typewise-alert.h"
#include<iostream>
#include <stdio.h>
#include <map>
#include <string>
using namespace std;
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    return (value < lowerLimit) ? TOO_LOW : 
         (value > upperLimit) ? TOO_HIGH : 
         NORMAL;
}



BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;

  map<CoolingType,int> upperLimits={
    {PASSIVE_COOLING,35},
    {HI_ACTIVE_COOLING,45},
    {MED_ACTIVE_COOLING,40}
  };
  int upperLimit=upperLimits[coolingType];

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
  AlertTarget alertTarget, EquipmentCharacter characteristic, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    characteristic.coolingType, temperatureInC
  );

  map<AlertTarget, void(*)(BreachType)> alertFunctions = {
    {TO_CONTROLLER, sendToController},
    {TO_EMAIL, sendToEmail}
  };
  
  alertFunctions[alertTarget](breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  map<BreachType,string> breachMessage={
    {TOO_LOW,"Hi, the temperature is too low\n"},
    {TOO_HIGH,"Hi, the temperature is too high\n"},
    {NORMAL,""}
  };
  printf("To: %s\n", recepient);
  cout<<breachMessage[breachType];
}
