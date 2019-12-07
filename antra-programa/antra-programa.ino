#define HW_PIN_OUTPUT 1
#define HW_PIN_INPUT 0

const byte ledButtonPin = 2;
const byte ledPin = 3;

bool buttonPressed = false;
bool buttonReleased = true;

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

void updateLed(led_t *led) {
	if (led->currState != led->targetState) {
		led->currState = led->targetState;
		digitalWrite(led->pinNum, led->currState);
	}
}

void setup() {

}

void loop() {

}
