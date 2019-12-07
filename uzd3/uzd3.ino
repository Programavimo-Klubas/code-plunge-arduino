#define HW_PIN_OUTPUT 1
#define HW_PIN_INPUT 0

#define LED_BUTTON_HW_PIN 2
#define BUTTON_PRESSED 0
#define BUTTON_RELEASED 1

#define RED_LED_HW_PIN 3
#define YELLOW_LED_HW_PIN 4
#define GREEN_LED_HW_PIN 5
#define TOTAL_NUM_OF_LEDS 3
#define FIRST_LED_COLOR_IN_LIST 0

#define DIMMER_DEFAULT_PERIOD 10
#define TOTAL_NUM_OF_DIMMERS TOTAL_NUM_OF_LEDS
#define DIMMER_MAX_BRIGHTNESS 100

#define APP_STATE_DELAY 1000
#define APP_DIMMER_STEP 10

enum LEDS {
  RED,
  GREEN,
  YELLOW,
  LED_COLOR_COUNT,
};

typedef enum{
  LED_ON = 1,
  LED_OFF = 0,
} ledStates_t;

struct button_t {
  int hwPinNum;
  bool currentState;
  bool previousState;
  bool pressed;
};

struct led_t {
  int hwPinNum;
  ledStates_t currentState;
  ledStates_t targetState;
};

struct dimmer_t{
  led_t *led;
  char brightness;
  int switchingPeriod;
  int currentCount;
};

typedef enum{
  APP_ON,
  APP_OFF,
  APP_INCREASE_BRIGHTNESS,
  APP_DECREASE_BRIGHTNESS,
} appState_t;

struct app_t {
  appState_t currentState;
  char currentColor;
  char nextColor;
  dimmer_t *dimmers;
  button_t *inputButton;
  int timerDelay;
};

// Globals 
button_t ledButton;
led_t    leds[TOTAL_NUM_OF_LEDS];
dimmer_t dimmers[TOTAL_NUM_OF_DIMMERS];
app_t app;

// Functions

led_t newLed( int hwPinNum )
{
    led_t nLed;
    nLed.hwPinNum = hwPinNum;
    nLed.currentState = LED_OFF;
    nLed.targetState = LED_OFF;
    pinMode( hwPinNum, HW_PIN_OUTPUT );
    return nLed;
}

void updateLed( led_t *lLed )
{
  if ( lLed->currentState != lLed->targetState )
  {
     lLed->currentState = lLed->targetState;
     digitalWrite( lLed->hwPinNum, (bool) lLed->currentState ) ;
  }
}

void updateLeds()
{
  char i=0;
  for ( i=0; i< TOTAL_NUM_OF_LEDS; i++ )
  {
    updateLed(&leds[i]);
  }
}

button_t newButton( int hwPinNum )
{
    button_t nButton;
    nButton.hwPinNum = hwPinNum;
    nButton.currentState = BUTTON_RELEASED;
    nButton.previousState = BUTTON_RELEASED;
    nButton.pressed = false;
    pinMode(hwPinNum, HW_PIN_INPUT );
    return nButton;
}

void updateButton( button_t *btn )
{
  btn->previousState = btn->currentState;
  btn->currentState = digitalRead(btn->hwPinNum);
  if ( (btn->previousState == BUTTON_RELEASED )
        &&( btn->currentState == BUTTON_PRESSED))
        {
          btn->pressed = true;
        }
}

bool readButton( button_t *btn )
{
  bool temp = btn-> pressed;
  btn->pressed = false;
  return temp;
}

dimmer_t newDimmer( led_t *lLed)
{
   dimmer_t nDimmer;
   nDimmer.led =lLed;
   nDimmer.brightness = 0;
   nDimmer.switchingPeriod= DIMMER_DEFAULT_PERIOD;
   nDimmer.currentCount = 0;
   return nDimmer;
}

void dimmerIncrement ( dimmer_t *dimmer )
{
  dimmer->currentCount++;
  if ( dimmer->currentCount >= dimmer->switchingPeriod)
  {
    dimmer->currentCount =0;
  }
}

void updateDimmer( dimmer_t *dimmer )
{
  dimmerIncrement( dimmer );
  if ( dimmer->brightness > DIMMER_MAX_BRIGHTNESS )
  {
    dimmer->brightness = DIMMER_MAX_BRIGHTNESS;
  }

  if ( dimmer->currentCount >= (( dimmer->switchingPeriod*dimmer->brightness)
  / DIMMER_MAX_BRIGHTNESS))
  {
    dimmer->led->targetState= LED_OFF;
  } else {
    dimmer->led->targetState= LED_ON;
  }
}

void updateDimmers(){
  char i = 0;
  for ( i=0; i< TOTAL_NUM_OF_DIMMERS; i++ )
  {
    updateDimmer(&dimmers[i]);
  }
}

app_t newApp( dimmer_t *lDimmers, button_t *inputBtn )
{
  app_t nApp;
  nApp.currentState = APP_OFF;
  nApp.currentColor = LED_COLOR_COUNT -1; // Assign las collor in list
  nApp.dimmers =lDimmers;
  nApp.timerDelay = 0;
  nApp.inputButton =inputBtn;
  return nApp;
}

void appDecrementDelay( app_t *lApp)
{
  if (lApp->timerDelay>0 )
  {
    lApp->timerDelay--;
  }
}

void updateApp( app_t *lApp)
{
  appDecrementDelay(lApp);
  dimmer_t *lDimmers = lApp->dimmers;

  switch ( lApp->currentState )
  {
    case APP_ON:
            if( readButton(lApp->inputButton))
            {
                if ( lApp->nextColor != ( LED_COLOR_COUNT-1))
                {
                  lApp->nextColor++;
                }
                lApp->currentState= APP_DECREASE_BRIGHTNESS;
            }
            break;

     case APP_INCREASE_BRIGHTNESS:
          if (( lApp->timerDelay == 0 ) 
                && ( lDimmers[lApp->currentColor].brightness != DIMMER_MAX_BRIGHTNESS))
           {     
                lDimmers[lApp->currentColor].brightness += APP_DIMMER_STEP;
                lApp->timerDelay = APP_STATE_DELAY;       
          } else if ( lDimmers[lApp->currentColor].brightness == DIMMER_MAX_BRIGHTNESS)
          {
            lApp->currentState = APP_ON;
          }
          break;
     case APP_DECREASE_BRIGHTNESS:
          if (( lApp->timerDelay == 0 )
          && ( lDimmers[lApp->currentColor].brightness >= APP_DIMMER_STEP ))
          {
              lDimmers[lApp->currentColor].brightness -= APP_DIMMER_STEP;
              lApp->timerDelay = APP_STATE_DELAY;
          } else if ( lDimmers[lApp->currentColor].brightness < APP_DIMMER_STEP ) {
             lDimmers[lApp->currentColor].brightness =0;
             if ( lApp->currentColor == lApp->nextColor )
             {
               lApp->currentState = APP_OFF;
             } else {
               lApp->currentState = APP_INCREASE_BRIGHTNESS;
               lApp->currentColor = lApp->nextColor;
             }
          }
          break;

      case APP_OFF:
      default:
          if (readButton(lApp->inputButton ))
          {
            lApp->currentColor = FIRST_LED_COLOR_IN_LIST;
            lApp->nextColor = FIRST_LED_COLOR_IN_LIST;
            lApp->currentState = APP_INCREASE_BRIGHTNESS;
          }
          break;
  }
}

void setup() {
  // put your setup code here, to run once:
  ledButton = newButton( LED_BUTTON_HW_PIN);
  leds[RED] = newLed(RED_LED_HW_PIN );
  leds[YELLOW] = newLed(YELLOW_LED_HW_PIN );
  leds[GREEN]  = newLed(GREEN_LED_HW_PIN );

  dimmers[RED] = newDimmer( &leds[RED]);
  dimmers[YELLOW] = newDimmer ( &leds[YELLOW]);
  dimmers[GREEN] = newDimmer (&leds[GREEN]);

  app = newApp( &dimmers[0], &ledButton);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateApp(&app);
  updateDimmers();
  updateLeds();
  updateButton(&ledButton);
  delay(1);
}
