/*
 * ITemporisateur.cpp
 *
 *  Created on: 29 janv. 2023
 *      Author: pascal
 */

#include "Arduino.h"
#include "configuration.h"
#include "ITemporisateur.h"
#include "IButton.h"

#define MINUTE 60

ITemporisateur::~ITemporisateur() {
}

Counter& ITemporisateur::getCounter() {
	return counter;
}

void ITemporisateur::setGamme(enum eGamme gamme) {
	this->gamme = gamme;
}

eGamme& ITemporisateur::getGamme() {
	return gamme;
}

void ITemporisateur::clearSegments() {
	for (uint8_t segment = 0; segment < NUM_OF_SEGMENTS; segment++) {
		digitalWrite(segments[segment], LOW);
	}
}

void ITemporisateur::clearDigits() {
	for (uint8_t digit = 0; digit < getNbDigits(); digit++) {
		digitalWrite(getDigits()[digit], HIGH);
	}
}

void ITemporisateur::clearLEDs() {
	clearSegments();
	clearDigits();
}

int8_t* ITemporisateur::getDisplayValue(uint8_t value) {
	uint8_t *displayValue = NULL;
	switch (value) {
	case 0:
		displayValue = zero;
		break;
	case 1:
		displayValue = one;
		break;
	case 2:
		displayValue = two;
		break;
	case 3:
		displayValue = three;
		break;
	case 4:
		displayValue = four;
		break;
	case 5:
		displayValue = five;
		break;
	case 6:
		displayValue = six;
		break;
	case 7:
		displayValue = seven;
		break;
	case 8:
		displayValue = eight;
		break;
	case 9:
		displayValue = nine;
		break;
	default:
		break;
	}
	return displayValue;
}

void ITemporisateur::displayNumber() {
	for (uint8_t digit = 0; digit < getNbDigits(); digit++) {
		clearLEDs();
		digitalWrite(getDigits()[digit], LOW);

		// Update dp switch
		getDisplayValue(getDigitValues()[digit])[7] = dpSwitch;

		for (uint8_t segment = 0; segment < NUM_OF_SEGMENTS; segment++) {
			digitalWrite(segments[segment],	getDisplayValue(getDigitValues()[digit])[segment]);
		}
		NOP;
	}
}

void ITemporisateur::triggerAlarm() {
	Serial.println("Alarm");
}

void ITemporisateur::decreaseCounter() {
	dpSwitch = !dpSwitch;
	if (dpSwitch == HIGH) return;

	if (getGamme() == HH_MM) {
		minuteCounter += 1;
		if (minuteCounter < MINUTE) {
			return;
		} else {
			minuteCounter = 0;
		}
	}

	int currentValue = counter.getCurrentValue();

	currentValue -= 1;
	if (currentValue < 0) {
		currentValue = 0;

		dpSwitch = LOW;
		counter.stopCounter();
		triggerAlarm();
	}

	counter.setCurrentValue(currentValue);
}

Tempo692::Tempo692(enum eGamme gamme) {
	setGamme(gamme);
	getCounter().setMaxValue(100);
	getCounter().setCurrentValue(99);
}

uint8_t Tempo692::getNbDigits() {
	return NUM_OF_DIGITS;
}

uint8_t* Tempo692::getDigits() {
	return digits;
}

uint8_t* Tempo692::getDigitValues() {
	return digitValues;
}

void Tempo692::printValue(int16_t value) {
//	digitValues[0] = (int8_t) ((value % 100) / 10);
//	digitValues[1] = (int8_t) (value % 10);

	int minutes = floor(value / 60);
	int secondes = value - (minutes * 60);

	digitValues[0] = (int8_t) (secondes / 10);
	digitValues[1] = (int8_t) (secondes % 10);

	displayNumber();
}

void Tempo692::readButtonsState() {
	start.readButtonValue(*this);
	stop.readButtonValue(*this);
	buttonDigit0.readButtonValue(*this);
	buttonDigit1.readButtonValue(*this);
}

void Tempo692::incrementDigit(int buttonId) {
	Serial.print("Tempo692 Increment button -> ");
	Serial.print("before: ");
	Serial.print(getCounter().getCurrentValue());
	Serial.print(" ");
//	Serial.println(buttonId);

	int currentValue = getCounter().getCurrentValue();

	switch(buttonId) {
//	case BTN_INC_1000:
//		if (digitValues[0] < 9) {
//			getCounter().setCurrentValue(currentValue + 600);
//		} else {
//			getCounter().setCurrentValue(currentValue - 5400);
//		}
//		break;
//	case BTN_INC_0100:
//		if (digitValues[0] < 9) {
//			getCounter().setCurrentValue(currentValue + 60);
//		} else {
//			getCounter().setCurrentValue(currentValue - 540);
//		}
//		break;
	case BTN_INC_0010:
		if (digitValues[0] < 9) {
			getCounter().setCurrentValue(currentValue + 10);
		} else {
			getCounter().setCurrentValue(currentValue - 50);
		}
		break;
	case BTN_INC_0001:
		if (digitValues[1] < 9) {
			getCounter().setCurrentValue(currentValue + 1);
		} else {
			getCounter().setCurrentValue(currentValue - 9);
		}
		break;
	}
	Serial.print("After: ");
	Serial.print(getCounter().getCurrentValue());
	Serial.println(" ");

	printValue(getCounter().getCurrentValue());
}

Tempo693::Tempo693(enum eGamme gamme) {
	setGamme(gamme);
	getCounter().setMaxValue(600);
	getCounter().setCurrentValue(600);
}

uint8_t Tempo693::getNbDigits() {
	return NUM_OF_DIGITS;
}

uint8_t* Tempo693::getDigits() {
	return digits;
}

uint8_t* Tempo693::getDigitValues() {
	return digitValues;
}

void Tempo693::printValue(int16_t value) {
//	digitValues[0] = (int8_t) ((value % 1000) / 100);
//	digitValues[1] = (int8_t) ((value % 100) / 10);
//	digitValues[2] = (int8_t) (value % 10);

	int minutes = floor(value / 60);
	int secondes = value - (minutes * 60);

	digitValues[0] = (int8_t) (minutes % 10);
	digitValues[1] = (int8_t) (secondes / 10);
	digitValues[2] = (int8_t) (secondes % 10);

	displayNumber();
}

void Tempo693::readButtonsState() {
	start.readButtonValue(*this);
	stop.readButtonValue(*this);
	buttonDigit0.readButtonValue(*this);
	buttonDigit1.readButtonValue(*this);
	buttonDigit2.readButtonValue(*this);
}

void Tempo693::incrementDigit(int buttonId) {
	Serial.print("Tempo693 Increment button -> ");
	Serial.print("before: ");
	Serial.print(getCounter().getCurrentValue());
	Serial.print(" ");
//	Serial.println(buttonId);

	int currentValue = getCounter().getCurrentValue();

	switch(buttonId) {
//	case BTN_INC_1000:
//		if (digitValues[0] < 9) {
//			getCounter().setCurrentValue(currentValue + 600);
//		} else {
//			getCounter().setCurrentValue(currentValue - 5400);
//		}
//		break;
	case BTN_INC_0100:
		if (digitValues[0] < 9) {
			getCounter().setCurrentValue(currentValue + 60);
		} else {
			getCounter().setCurrentValue(currentValue - 540);
		}
		break;
	case BTN_INC_0010:
		if (digitValues[1] < 5) {
			getCounter().setCurrentValue(currentValue + 10);
		} else {
			getCounter().setCurrentValue(currentValue - 50);
		}
		break;
	case BTN_INC_0001:
		if (digitValues[2] < 9) {
			getCounter().setCurrentValue(currentValue + 1);
		} else {
			getCounter().setCurrentValue(currentValue - 9);
		}
		break;
	}
	Serial.print("After: ");
	Serial.print(getCounter().getCurrentValue());
	Serial.println(" ");

	printValue(getCounter().getCurrentValue());
}

Tempo694::Tempo694(enum eGamme gamme) {
	setGamme(gamme);
	getCounter().setMaxValue(6000);
	getCounter().setCurrentValue(5999);
}

uint8_t Tempo694::getNbDigits() {
	return NUM_OF_DIGITS;
}

uint8_t* Tempo694::getDigits() {
	return digits;
}

uint8_t* Tempo694::getDigitValues() {
	return digitValues;
}

void Tempo694::printValue(int16_t value) {
//	digitValues[0] = (int8_t) (value / 1000);
//	digitValues[1] = (int8_t) ((value % 1000) / 100);
//	digitValues[2] = (int8_t) ((value % 100) / 10);
//	digitValues[3] = (int8_t) (value % 10);

	int minutes = floor(value / 60);
	int secondes = value - (minutes * 60);

	digitValues[0] = (int8_t) (minutes / 10);
	digitValues[1] = (int8_t) (minutes % 10);
	digitValues[2] = (int8_t) (secondes / 10);
	digitValues[3] = (int8_t) (secondes % 10);

	displayNumber();
}

void Tempo694::readButtonsState() {
	start.readButtonValue(*this);
	stop.readButtonValue(*this);
	buttonDigit0.readButtonValue(*this);
	buttonDigit1.readButtonValue(*this);
	buttonDigit2.readButtonValue(*this);
	buttonDigit3.readButtonValue(*this);
}

void Tempo694::incrementDigit(int buttonId) {
	int currentValue = getCounter().getCurrentValue();

	switch(buttonId) {
	case BTN_INC_1000:
		if (digitValues[0] < 9) {
			getCounter().setCurrentValue(currentValue + 600);
		} else {
			getCounter().setCurrentValue(currentValue - 5400);
		}
		break;
	case BTN_INC_0100:
		if (digitValues[1] < 9) {
			getCounter().setCurrentValue(currentValue + 60);
		} else {
			getCounter().setCurrentValue(currentValue - 540);
		}
		break;
	case BTN_INC_0010:
		if (digitValues[2] < 5) {
			getCounter().setCurrentValue(currentValue + 10);
		} else {
			getCounter().setCurrentValue(currentValue - 50);
		}
		break;
	case BTN_INC_0001:
		if (digitValues[3] < 9) {
			getCounter().setCurrentValue(currentValue + 1);
		} else {
			getCounter().setCurrentValue(currentValue - 9);
		}
		break;
	}
	printValue(getCounter().getCurrentValue());
}
