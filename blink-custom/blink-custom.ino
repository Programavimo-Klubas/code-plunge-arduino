
const byte mygtukoPinas = 2;

const byte red = 3;
const byte green = 4;
const byte yellow = 5;

const byte leduPinai[] = { red, green, yellow };

void on(byte pinas) {
	digitalWrite(pinas, HIGH);
}

void off(byte pinas) {
	digitalWrite(pinas, LOW);
}

void onSuLaiku(byte pinas, unsigned long laikasMs) {
	on(pinas);
	delay(laikasMs);
}

const int laikas = 500;

void keitinetiLedus() {
	onSuLaiku(red, laikas);
	onSuLaiku(green, laikas);
	onSuLaiku(yellow, laikas);

	on(red);

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

}
