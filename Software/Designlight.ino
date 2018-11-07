// define constants
#define FLASH_RATE_HZ 2
#define BUTTON_IN 2
#define PWM_LED_OUT 11
#define PWM_MAX 255 

// Operating mode: 0 - off, 1 - bright, 2 - mid, 3 - dim, 4 - flashing
int op_mode = 0;
bool button_pushed = false;
bool previous_button_state = false;
int PWM_OUT = 0;

void setup() {
  // put your setup code here, to run once:

attachInterrupt(digitalPinToInterrupt(BUTTON_IN), change_button_state, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

  check_button_state();

  adjust_pwm_to_opmode();

  send_pwm_to_led();

}

void change_button_state() {
  // switches button_pushed to true
  button_pushed = true;
  }

void check_button_state() {
  // checks if button is pushed and changes to next op mode if it is
  if (button_pushed && op_mode < 4) {
    op_mode = op_mode + 1;
  }
  if (button_pushed && op_mode == 4) {
    op_mode = 0;
  }
  button_pushed = 0;
}

void adjust_pwm_to_opmode() {
  // op mode is adjusted to op_mode
  switch (op_mode) {
    case 0:
      PWM_OUT = 0;
      break;
    case 1:
      PWM_OUT = PWM_MAX;
      break; 
    case 2:
      PWM_OUT = PWM_MAX/2;
      break;
    case 3:
      PWM_OUT = PWM_MAX/4;
      break;
    case 4:
      flash_led();
      break;
  }
}

void send_pwm_to_led() {
  analogWrite(PWM_LED_OUT, PWM_OUT);
}

void flash_led() {
  while(!button_pushed){
    analogWrite(PWM_LED_OUT, PWM_MAX);
    delay(500);
    analogWrite(PWM_LED_OUT, 0);
    delay(500);
  }
}



