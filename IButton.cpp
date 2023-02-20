/*
 * IButton.cpp
 *
 *  Created on: 21 janv. 2023
 *      Author: pascal
 */

#include "Arduino.h"
#include "IButton.h"
#include "ITemporisateur.h"

IButton::IButton(const uint8_t& id) {
	buttonPin = id;
}

void IButton::readButtonValue(ITemporisateur& iTempo) {
	int reading = digitalRead(buttonPin);

	if (reading != lastButtonState) {
		lastDebounceTime = millis();
	}

	if ((millis() - lastDebounceTime) > debounceDelay) {
		if (reading != buttonState) {
			buttonState = reading;

			if (buttonState == HIGH) {
				buttonAction(iTempo);
			}
		}
	}
	lastButtonState = reading;
}

void ButtonStart::buttonAction(ITemporisateur& iTempo) {
	Serial.println("button start action");
	iTempo.getCounter().startCounter();
}

void ButtonStop::buttonAction(ITemporisateur& iTempo) {
	Serial.println("button stop action");
	iTempo.dpSwitch = LOW;
	iTempo.getCounter().stopCounter();
}

void ButtonIncDigit::buttonAction(ITemporisateur& iTempo) {
	Serial.print("button -> ");
	Serial.print(iTempo.getCounter().getCurrentValue());
	Serial.print(" <-> ");
	Serial.print(buttonPin);
	Serial.println(" action");

	iTempo.getCounter().stopCounter();
	iTempo.incrementDigit(buttonPin);
}

