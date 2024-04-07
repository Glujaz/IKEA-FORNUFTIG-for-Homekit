//////////////////////////////////
//   DEVICE-SPECIFIC SERVICES   //
//////////////////////////////////

//extern int currentSwitchPosition; 
//extern int newSwitchPosition;
extern int position;
extern int newPosition;
extern int autoMode;
int memorizedLevel = 33;


struct DEV_AirPurification : Service::AirPurifier {

  SpanCharacteristic *power;
  SpanCharacteristic *activity;
  SpanCharacteristic *level;
  SpanCharacteristic *manualMode;

    DEV_AirPurification() : Service::AirPurifier(){
    power = new Characteristic::Active(0);
    activity = new Characteristic::CurrentAirPurifierState(1);
    level = (new Characteristic::RotationSpeed(0))->setRange(0,99,33);
    manualMode = new Characteristic::LockPhysicalControls(0);

  }

  boolean update() override {

    if(autoMode == 1) {
      if (power->updated()) {
        LOG0("\n-----Homekit Power Update   :");
        if (power->getNewVal() == 1) {
          LOG0("    Homekit on-----\n");
          activity->setVal(2);
          if (level->getNewVal() <= 33) {newPosition=memorizedLevel/33;level->setVal(memorizedLevel);}
        } else {
          Serial.println("     Homekit off-----\n");
          newPosition=0;
          level->setVal(0);
          activity->setVal(0);
        }
      }

      if (level->updated()) {
        LOG0("\nHomekit level update\n");
        if (level->getNewVal() == 0) {newPosition == 0;power->setVal(0);activity->setVal(0);LOG1("level has been turned off\n");}else{power->setVal(1);activity->setVal(2);}
        if (level->getNewVal() == 33) {newPosition=1;memorizedLevel=33;}
        if (level->getNewVal() == 66) {newPosition=2;memorizedLevel=66;}
        if (level->getNewVal() == 99) {newPosition=3;memorizedLevel=99;}
      }
    }
  return (true);
  }

  void loop() {

    if (autoMode == 1 ) {
      if (manualMode->getVal() == 0) {manualMode->setVal(0);LOG1("\nDisabled Physical Lock\n");}
      //if (position == 0) {level->setVal(0);}

    } else {
      Serial.println("manual homekit update");
      if (manualMode->getVal() == 0) {manualMode->setVal(1);LOG1("\nEnabled Physical Lock\n");}
      if (level->getVal()/33 != position) {level->setVal(position*33);}
      if (position > 0) {power->setVal(1);}else{power->setVal(0);}
      if (autoMode == 2) {autoMode=1;}


    }
  }

};