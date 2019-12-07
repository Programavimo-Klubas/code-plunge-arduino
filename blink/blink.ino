
bool mygtukoBusena = LOW;
bool arIjungtas = false;

const byte mygtukoPinas = 2;
const byte ledoPinas = 3;

void setup() {
	Serial.begin(9600);
	pinMode(mygtukoPinas, INPUT);
	pinMode(ledoPinas, OUTPUT);
}

void loop() {
	mygtukoBusena = digitalRead(mygtukoPinas);

	if (mygtukoBusena == LOW && !arIjungtas) {
		digitalWrite(ledoPinas, !digitalRead(ledoPinas));
		arIjungtas = true;
	} else if (mygtukoBusena == HIGH && arIjungtas) {
		arIjungtas = false;
	}

	delay(1);
}
