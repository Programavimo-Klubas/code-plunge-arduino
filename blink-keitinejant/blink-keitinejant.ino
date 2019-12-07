
bool mygtukoBusena = LOW;

const byte mygtukoPinas = 2;
const byte ledoPinas = 3;

const byte leduPinai[] = { 3, 4, 5 };
const size_t leduSkaicius = 3;

byte kelintasIjungtas = 0;

byte dabartineBusena = -1;

void ijungtiKitaLeda() {
	digitalWrite(leduPinai[kelintasIjungtas], LOW);
	kelintasIjungtas = (kelintasIjungtas + 1) % leduSkaicius;
	Serial.println(kelintasIjungtas);
	digitalWrite(leduPinai[kelintasIjungtas], HIGH);
}

void setup() {
	Serial.begin(9600);
	pinMode(mygtukoPinas, INPUT);

	for (size_t i = 0; i < leduSkaicius; ++i) {
		pinMode(leduPinai[i], OUTPUT);
	}
}

void loop() {
	mygtukoBusena = digitalRead(mygtukoPinas);

	if (mygtukoBusena != dabartineBusena) {
		ijungtiKitaLeda();
		delay(200);
		dabartineBusena = digitalRead(mygtukoPinas);
	}

	delay(1);
}
