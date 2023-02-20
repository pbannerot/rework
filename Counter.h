/*
 * Counter.h
 *
 *  Created on: 22 janv. 2023
 *      Author: pascal
 */

#ifndef COUNTER_H_
#define COUNTER_H_

class Counter {
private:
	int currentValue = 0;
	int maxValue = 0;
	bool counterIsAlive = false;
public:
	Counter();
	virtual ~Counter() {
	}

	void startCounter();
	void stopCounter();

	bool isAlive() const;

	int getCurrentValue() const;
	void setCurrentValue(int currentValue);

	int getMaxValue() const;
	void setMaxValue(int maxValue = 0);

	void setCounterIsAlive(bool counterIsAlive = false);

};
#endif /* COUNTER_H_ */
