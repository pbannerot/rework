#include "rework.h"
#include "ITemporisateur.h"
#include "timerOne.h"

ITemporisateur *iTemporisateur = NULL;
eGamme debugGamme = MM_SS; // <-- Shall be retrieve from HW strap

void updateCurrentValue() {
	if (iTemporisateur->getCounter().isAlive()) {
		iTemporisateur->decreaseCounter();
	}
}

void setup() {
	// Read Program version:
	// T694 E Programme 1, T694 F Programme 2
	iTemporisateur = new Tempo694(debugGamme);
//	 T693 F Programme 3, T693 FA/FE Programme 4
//	iTemporisateur = new Tempo693(debugGamme);
	// T692 FA/FE Programme 5
//	iTemporisateur = new Tempo692(debugGamme);

	// -> DEBUG
	Serial.begin(9600);
	// DEBUG <-

	pinMode(LED_BUILTIN, OUTPUT);

	pinMode(SEG_A, OUTPUT);
	pinMode(SEG_B, OUTPUT);
	pinMode(SEG_C, OUTPUT);
	pinMode(SEG_D, OUTPUT);
	pinMode(SEG_E, OUTPUT);
	pinMode(SEG_F, OUTPUT);
	pinMode(SEG_G, OUTPUT);
	pinMode(SEG_DP, OUTPUT);

	pinMode(DIGIT_1, OUTPUT);
	pinMode(DIGIT_2, OUTPUT);
	pinMode(DIGIT_3, OUTPUT);
	pinMode(DIGIT_4, OUTPUT);

	pinMode(BTN_START, INPUT);
	pinMode(BTN_STOP, INPUT);
	pinMode(BTN_INC_0001, INPUT);
	pinMode(BTN_INC_0010, INPUT);
	pinMode(BTN_INC_0100, INPUT);
	pinMode(BTN_INC_1000, INPUT);

	Timer1.initialize(500000);
	Timer1.attachInterrupt(updateCurrentValue);
}

void loop() {
	int currentValue = iTemporisateur->getCounter().getCurrentValue();

	iTemporisateur->readButtonsState();
	iTemporisateur->printValue(currentValue);
}
