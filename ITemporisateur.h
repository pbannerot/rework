/*
 * ITemporisateur.h
 *
 *  Created on: 29 janv. 2023
 *      Author: pascal
 */

#ifndef ITEMPORISATEUR_H_
#define ITEMPORISATEUR_H_

#include "Arduino.h"
#include "configuration.h"
#include "Counter.h"
#include "IButton.h"

#define NUM_OF_SEGMENTS 8
#define NOP __asm__("nop\n\t")

enum eGamme {HH_MM = 0, MM_SS = 1};

class ITemporisateur {
private:
	Counter counter;
	eGamme gamme;
	uint8_t minuteCounter = 0;

	uint8_t segments[NUM_OF_SEGMENTS] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP };

	uint8_t zero[NUM_OF_SEGMENTS] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW };
	uint8_t one[NUM_OF_SEGMENTS] = { LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW };
	uint8_t two[NUM_OF_SEGMENTS] =	{ HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW };
	uint8_t three[NUM_OF_SEGMENTS] = { HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW };
	uint8_t four[NUM_OF_SEGMENTS] =	{ LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW };
	uint8_t five[NUM_OF_SEGMENTS] = { HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW };
	uint8_t six[NUM_OF_SEGMENTS] = { HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW };
	uint8_t seven[NUM_OF_SEGMENTS] = { HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW };
	uint8_t eight[NUM_OF_SEGMENTS] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW };
	uint8_t nine[NUM_OF_SEGMENTS] = { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH,LOW };

	void clearSegments();
	void clearDigits();
	void clearLEDs();
public:
	virtual ~ITemporisateur();

	Counter& getCounter();
	void setGamme(enum eGamme);
	eGamme& getGamme();

	ButtonStart start = ButtonStart(BTN_START);
	ButtonStop stop = ButtonStop(BTN_STOP);

	uint8_t dpSwitch = LOW;

	virtual uint8_t getNbDigits() = 0;
	virtual uint8_t* getDigits() = 0;
	virtual uint8_t* getDigitValues() = 0;

	int8_t* getDisplayValue(uint8_t value);
	void displayNumber();
	virtual void printValue(int16_t value) = 0;

	virtual void readButtonsState() = 0;

	void decreaseCounter();

	virtual void incrementDigit(int) = 0;

	void triggerAlarm();
};

class Tempo692 : public ITemporisateur {
private:
	static const uint8_t NUM_OF_DIGITS = 2;
	uint8_t digits[NUM_OF_DIGITS] = { DIGIT_1, DIGIT_2 };
	uint8_t digitValues[NUM_OF_DIGITS] = { 0, 0 };

	ButtonIncDigit buttonDigit0 = ButtonIncDigit(BTN_INC_0001);
	ButtonIncDigit buttonDigit1 = ButtonIncDigit(BTN_INC_0010);
public:
	Tempo692(enum eGamme);

	uint8_t getNbDigits() override;
	uint8_t* getDigits() override;
	uint8_t* getDigitValues() override;

	void printValue(int16_t value) override;

	void readButtonsState() override;

	void incrementDigit(int) override;
};

class Tempo693 : public ITemporisateur {
private:
	static const uint8_t NUM_OF_DIGITS = 3;
	uint8_t digits[NUM_OF_DIGITS] = { DIGIT_1, DIGIT_2, DIGIT_3 };
	uint8_t digitValues[NUM_OF_DIGITS] = { 0, 0, 0 };

	ButtonIncDigit buttonDigit0 = ButtonIncDigit(BTN_INC_0001);
	ButtonIncDigit buttonDigit1 = ButtonIncDigit(BTN_INC_0010);
	ButtonIncDigit buttonDigit2 = ButtonIncDigit(BTN_INC_0100);
public:
	Tempo693(enum eGamme);

	uint8_t getNbDigits() override;
	uint8_t* getDigits() override;
	uint8_t* getDigitValues() override;

	void printValue(int16_t value) override;

	void readButtonsState() override;

	void incrementDigit(int) override;
};

class Tempo694 : public ITemporisateur {
private:
	static const uint8_t NUM_OF_DIGITS = 4;
	uint8_t digits[NUM_OF_DIGITS] = { DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4 };
	uint8_t digitValues[NUM_OF_DIGITS] = { 0, 0, 0, 0 };

	ButtonIncDigit buttonDigit0 = ButtonIncDigit(BTN_INC_0001);
	ButtonIncDigit buttonDigit1 = ButtonIncDigit(BTN_INC_0010);
	ButtonIncDigit buttonDigit2 = ButtonIncDigit(BTN_INC_0100);
	ButtonIncDigit buttonDigit3 = ButtonIncDigit(BTN_INC_1000);
public:
	Tempo694(enum eGamme);

	uint8_t getNbDigits() override;
	uint8_t* getDigits() override;
	uint8_t* getDigitValues() override;

	void printValue(int16_t value) override;

	void readButtonsState() override;

	void incrementDigit(int i) override;
};



#endif /* ITEMPORISATEUR_H_ */
