
bool mygtukoBusena = LOW;

const byte mygtukoPinas = 2;
const byte ledoPinas = 3;

const byte leduPinai[] = { 3, 4, 5 };
const size_t leduSkaicius = 3;

byte kelintasIjungtas = 0;

byte dabartineBusena = -1;

void ijungtiKitaLeda() {
	/** išjungti seną */
	digitalWrite(leduPinai[kelintasIjungtas], LOW);

	/**
	 * pasirinkti kitą piną įjungimui
	 * (liekana tam, kad pasiekus paskutinį piną vėl eitume nuo pradžios)
	*/
	kelintasIjungtas = (kelintasIjungtas + 1) % leduSkaicius;

	/**
	 * įjungiam kitą
	 */
	digitalWrite(leduPinai[kelintasIjungtas], HIGH);

	/**
	 * printinam į serial monitorių (šiaip sau),
	 * kuris dabar įjungtas
	 */
	Serial.println(kelintasIjungtas);
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
	mygtukoBusena = digitalRead(mygtukoPinas);

	if (mygtukoBusena != dabartineBusena) {
		ijungtiKitaLeda();
		delay(200);
		dabartineBusena = digitalRead(mygtukoPinas);
	}

	delay(1);
}
