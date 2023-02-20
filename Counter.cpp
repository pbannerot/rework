/*
 * Counter.cpp
 *
 *  Created on: 22 janv. 2023
 *      Author: pascal
 */

#include "Counter.h"

Counter::Counter() {
}

void Counter::startCounter() {
	setCounterIsAlive(true);
}
void Counter::stopCounter() {
	setCounterIsAlive(false);
}

bool Counter::isAlive() const {
	return counterIsAlive;
}

int Counter::getCurrentValue() const {
	return currentValue;
}

void Counter::setCurrentValue(int currentValue) {
	this->currentValue = currentValue;
}

int Counter::getMaxValue() const {
	return maxValue;
}

void Counter::setMaxValue(int maxValue) {
	this->maxValue = maxValue;
}

void Counter::setCounterIsAlive(bool counterIsAlive) {
	this->counterIsAlive = counterIsAlive;
}
