
const byte mygtukoPinas = 2;

const byte red = 3;
const byte green = 4;
const byte yellow = 5;

const byte leduPinai[] = { red, green, yellow };
const unsigned int leduSkaicius = 3;

void on(byte pinas) {
	digitalWrite(pinas, HIGH);
}

void off(byte pinas) {
	digitalWrite(pinas, LOW);
}

unsigned long pradinisLaikas;

void wait(unsigned long laikasMs) {
	pradinisLaikas = laikasMs;

	while (millis() < pradinisLaikas + laikasMs) {
		/** laukti */
	}
}

void onSuLaiku(byte pinas, unsigned long laikasMs) {
	on(pinas);
	delay(laikasMs);
	off(pinas);
}

const int laikas = 500;
const int trumpasLaikas = 200;

void keitinetiLedus() {
	onSuLaiku(red, laikas);
	onSuLaiku(green, laikas);
	onSuLaiku(yellow, laikas);

	delay(trumpasLaikas);

	on(red);
	on(green);
	on(yellow);

	delay(trumpasLaikas);

	off(red);
	off(green);
	off(yellow);

	delay(trumpasLaikas);

	on(red);
	on(green);
	on(yellow);

	delay(trumpasLaikas);

	off(red);
	off(green);
	off(yellow);

	delay(trumpasLaikas);

	on(red);
	on(green);
	on(yellow);

	delay(trumpasLaikas);

	off(red);
	off(green);
	off(yellow);

	delay(laikas);
}

void setup() {
	Serial.begin(9600);

	pinMode(mygtukoPinas, INPUT);

	/** priskirti visus ledus OUTPUT'ui */
	for (size_t i = 0; i < leduSkaicius; ++i) {
		pinMode(leduPinai[i], OUTPUT);
	}
}

void loop() {
	keitinetiLedus();

	delay(1);
}
