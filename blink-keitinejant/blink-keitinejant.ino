
bool mygtukoBusena = LOW;

const byte mygtukoPinas = 2;
const byte ledoPinas = 3;

const int leduPinai[] = { 3, 4, 5, -1 };
const size_t leduSkaicius = 4; // sizeof(leduPinai) / sizeof(leduPinai[0]);

byte kelintasIjungtas = 2;

byte dabartineBusena = -1;

/**
 * dimmer
 */

const size_t period = 10;
const size_t dimmerCount = period;

const size_t maxBrightness = 100;

const size_t delayMs = 1000;

const size_t dimmerStep = 10;

const size_t dimStepDelay = 10;

void dimOff(byte ledoPinas) {
	// int ledoAnalogas = analogRead(ledoPinas);

	for (int i = 255; i > 0; i -= dimmerStep) {
		analogWrite(ledoPinas, i);
		delay(dimStepDelay);
	}

	// for (size_t i = dimmerCount; i > 0; i--) {
	// 	// analogWrite(ledoPinas, maxBrightness - ((i - 1) * dimmerStep));
	// 	// analogWrite(ledoPinas, dimmerStep * i);
	// 	analogWrite(ledoPinas, 0);
	// }
}

void dimOn(byte ledoPinas) {
	for (int i = 0; i < 255; i += dimmerStep) {
		analogWrite(ledoPinas, i);
		delay(dimStepDelay);
	}

	// for (size_t i = 0; i < dimmerCount; i++) {
	// 	analogWrite(ledoPinas, 255);
	// }
}


void ijungtiKitaLeda() {
	/** išjungti seną */
	// digitalWrite(leduPinai[kelintasIjungtas], LOW);
	dimOff(leduPinai[kelintasIjungtas]);

	/**
	 * pasirinkti kitą piną įjungimui
	 * (liekana tam, kad pasiekus paskutinį piną vėl eitume nuo pradžios)
	*/
	kelintasIjungtas = (kelintasIjungtas + 1) % leduSkaicius;

	/**
	 * įjungiam kitą
	 */
	// digitalWrite(leduPinai[kelintasIjungtas], HIGH);
	dimOn(leduPinai[kelintasIjungtas]);

	/**
	 * printinam į serial monitorių (šiaip sau),
	 * kuris dabar įjungtas
	 */
	Serial.println(kelintasIjungtas);
}

// void dimintiBangomis() {
// 	const size_t pinuRyskumoSkirtumas = 10;
// 	int tempRyskumas;

// 	for (int i = -3 * dimmerStep; i < 255; i += dimmerStep) {
// 		for (int kelintasLedas = 1; kelintasLedas <= leduSkaicius; kelintasLedas++) {
// 			tempRyskumas = i + (kelintasLedas * pinuRyskumoSkirtumas);
// 			analogWrite(leduPinai[kelintasLedas], tempRyskumas);

// 			Serial.println(kelintasLedas);
// 			Serial.print(" ");
// 			Serial.print(tempRyskumas);
// 		}
// 	}
// }

// void didintiBangomisSuSine() {
// 	const int maxVal = 255;
// 	const int step = 10;
// 	const int delayMs = 20;
// 	int tempRyskumas;

// 	for (int i = 0; i <= 180; i += step) {
// 		tempRyskumas = maxVal * sin(i);
// 		analogWrite(leduPinai[1], tempRyskumas);
// 		delay(delayMs);
// 	}

// 	delay(500);
// }

void junginetiArmonika() {
	const int step = 100;

	for (int i = 0; i < leduSkaicius; i++) {
		digitalWrite(leduPinai[i], HIGH);
		delay(step);
	}

	for (int i = 0; i < leduSkaicius; i++) {
		digitalWrite(leduPinai[i], LOW);
		delay(step);
	}

	delay(200);
}

void pakeistiAutomatiskai() {
	ijungtiKitaLeda();

	/** po tamsos nereikia papildomo delay */
	if (kelintasIjungtas != 3) {
		delay(500);
	}
}

void pakeistiSuMygtuku() {
	mygtukoBusena = digitalRead(mygtukoPinas);

	if (mygtukoBusena != dabartineBusena) {
		ijungtiKitaLeda();
		delay(200);
		dabartineBusena = digitalRead(mygtukoPinas);
	}
}

void setup() {
	Serial.begin(9600);

	pinMode(mygtukoPinas, INPUT);

	/** priskirti visus ledus OUTPUT'ui */
	for (size_t i = 0; i < leduSkaicius; ++i) {
		pinMode(leduPinai[i], OUTPUT);
		analogWrite(leduPinai[i], 0);
	}
}

void loop() {
	/**
 	 * pasirink 1 iš 2 funkcijų LED'o pakeitimui
 	*/

 	// dimintiBangomis();
	//  didintiBangomisSuSine();
	// pakeistiAutomatiskai();
	// pakeistiSuMygtuku();

	junginetiArmonika();

	delay(1);
}
