
void readSwitchPosition() {

  if (digitalRead(switchPin0) == LOW) {newSwitchPosition=0;
  } else if (digitalRead(switchPin1) == LOW) {newSwitchPosition=1;
  } else if (digitalRead(switchPin2) == LOW) {newSwitchPosition=2;
  } else if (digitalRead(switchPin3) == LOW) {newSwitchPosition=3;
  } else {
    newSwitchPosition=currentSwitchPosition;  // No switch is activated
    if (currentSwitchPosition == -1) {currentSwitchPosition = 0;Serial.println("applied the -1 removal");}  
  }

  if (newSwitchPosition != currentSwitchPosition) {
    Serial.print("Detectected new rotary switch position. New switch position is now :");
    Serial.println(newSwitchPosition);
    if (newSwitchPosition > 0) {
      autoMode=0;
      Serial.println("Purifier is now controlled manually");
     } else {
      if (newSwitchPosition == -1) {newSwitchPosition = 0;Serial.println("applied the -1 removal");}
      autoMode=2;
      Serial.println("Purifier can now be managed by Homekit");
     }
    currentSwitchPosition = newSwitchPosition;
    newPosition = currentSwitchPosition;
  }
}


void setOutputPosition() {
  // Deactivate all circuits
  if (position != newPosition){

    digitalWrite(circuitPin0, LOW);
    digitalWrite(circuitPin1, LOW);
    digitalWrite(circuitPin2, LOW);
    digitalWrite(circuitPin3, LOW);

    // Activate the selected circuit
    switch (newPosition) {
      case 0:
        digitalWrite(circuitPin0, HIGH);
        break;
      case 1:
        digitalWrite(circuitPin1, HIGH);
        break;
      case 2:
        digitalWrite(circuitPin2, HIGH);
        break;
      case 3:
        digitalWrite(circuitPin3, HIGH);
        break;
      default:
        break;
    }
    position = newPosition;
    Serial.print("Applied new fan speed : ");
    Serial.println(position);
  }
}
