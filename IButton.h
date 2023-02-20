/*
 * IButton.h
 *
 *  Created on: 21 janv. 2023
 *      Author: pascal
 */

#ifndef IBUTTON_H_
#define IBUTTON_H_

#include "Counter.h"

class ITemporisateur;

class IButton {
private:
	unsigned const long debounceDelay = 50L;
	unsigned long lastDebounceTime = 0L;
	int lastButtonState = LOW;
	int buttonState = lastButtonState;

	virtual void buttonAction(ITemporisateur&) = 0;
protected:
public:
	IButton(const uint8_t&);
	virtual ~IButton() {
	}

	int buttonPin;
	void readButtonValue(ITemporisateur&);

	void dummy(ITemporisateur& t);
};

class ButtonStart: public IButton {
public:
	ButtonStart(const uint8_t& id) : IButton(id) {}
	void buttonAction(ITemporisateur&) override;
};

class ButtonStop: public IButton {
public:
	ButtonStop(const uint8_t& id) : IButton(id) {}
	void buttonAction(ITemporisateur&) override;
};

class ButtonIncDigit: public IButton {
public:
	ButtonIncDigit(const uint8_t& id) : IButton(id) {}
	void buttonAction(ITemporisateur&) override;
};


#endif /* IBUTTON_H_ */
