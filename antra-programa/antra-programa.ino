const bool buttonPressed = false;
const bool buttonReleased = true;


const byte ledButtonPin = 2;
const byte ledPin = 3;

typedef enum {
	OFF = 0,
	ON = 1
} ledStates_t;

struct button_t {
	int pinNum;

	bool prevState;
	bool currState;

	bool pressed;
};

struct led_t {
	int pinNum;

	ledStates_t currState;
	ledStates_t targetState;
};

button_t ledButton;
led_t	 led;

led_t newLed(int pinNum) {
	pinMode(pinNum, OUTPUT);

	led_t newLedTemp = { pinNum, OFF, OFF };

	return newLedTemp;
}

void updateLed(led_t* led) {
	if (led->currState != led->targetState) {
		led->currState = led->targetState;
		digitalWrite(led->pinNum, led->currState);
	}
}

button_t newButton(int pinNum) {
	button_t button = { pinNum, buttonReleased, buttonPressed, false };

	pinMode(pinNum, INPUT);

	return button;
}

void updateButton(button_t* btn) {
	btn->prevState = btn->currState;
	btn->currState = digitalRead(btn->pinNum);

	if (
		btn->prevState == buttonReleased
		&& btn->currState == buttonPressed
	) {
		btn->pressed = true;
	}
}

bool readButton(button_t* btn) {
	bool tempPressed = btn->pressed;
	btn->pressed = false;

	return tempPressed;
}

void setup() {
	ledButton = newButton(ledButtonPin);
	led = newLed(ledPin);
}

void loop() {
	if (readButton(&ledButton)) {
		led.targetState = (ledStates_t) !led.targetState;
	}

	updateLed(&led);
	updateButton(&ledButton);
}
