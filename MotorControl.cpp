#include "MotorControl.h"
#include "soc/gpio_struct.h" // For direct register access
#include "soc/gpio_periph.h"
#include "rom/gpio.h"        // For PIN_FUNC_SELECT macro

// Global speed variable defined here (must match extern in header)
int baseSpeed = 128;

// ---------- Low-level GPIO setup functions ----------
static void setPinOutput(int pin) {
  // Configure the pin as a GPIO pin
  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[pin], PIN_FUNC_GPIO);
  // Set pin as output
  GPIO.enable_w1ts = (1 << pin);
}

static void setPinHigh(int pin) {
  GPIO.out_w1ts = (1 << pin);
}

static void setPinLow(int pin) {
  GPIO.out_w1tc = (1 << pin);
}

// Helper function to set motor direction and speed
static void setMotor(int dirA, int dirB, int pwmChannel, bool forward, int speedVal) {
  if (forward) {
    // forward: A = HIGH, B = LOW
    setPinHigh(dirA);
    setPinLow(dirB);
  } else {
    // backward: A = LOW, B = HIGH
    setPinLow(dirA);
    setPinHigh(dirB);
  }
  ledcWrite(pwmChannel, speedVal);
}

void initMotors() {
  // Setup direction pins as GPIO outputs
  setPinOutput(FL_DIR_A); setPinOutput(FL_DIR_B);
  setPinOutput(FR_DIR_A); setPinOutput(FR_DIR_B);
  setPinOutput(RL_DIR_A); setPinOutput(RL_DIR_B);
  setPinOutput(RR_DIR_A); setPinOutput(RR_DIR_B);

  // Setup LEDC channels for PWM
  // Using a frequency of 5000 Hz and 8-bit resolution
  ledcAttach(FL_PWM, 5000, 8);
  ledcAttach(FR_PWM, 5000, 8);
  ledcAttach(RL_PWM, 5000, 8);
  ledcAttach(RR_PWM, 5000, 8);

  stopAllMotors();
}

void stopAllMotors() {
  setPinLow(FL_DIR_A); setPinLow(FL_DIR_B); ledcWrite(0, 0);
  setPinLow(FR_DIR_A); setPinLow(FR_DIR_B); ledcWrite(1, 0);
  setPinLow(RL_DIR_A); setPinLow(RL_DIR_B); ledcWrite(2, 0);
  setPinLow(RR_DIR_A); setPinLow(RR_DIR_B); ledcWrite(3, 0);
}

void moveForward() {
  // Move all motors forward
  setMotor(FL_DIR_A, FL_DIR_B, 0, true, baseSpeed);
  setMotor(FR_DIR_A, FR_DIR_B, 1, true, baseSpeed);
  setMotor(RL_DIR_A, RL_DIR_B, 2, true, baseSpeed);
  setMotor(RR_DIR_A, RR_DIR_B, 3, true, baseSpeed);
}

void moveBackward() {
  // Move all motors backward
  setMotor(FL_DIR_A, FL_DIR_B, 0, false, baseSpeed);
  setMotor(FR_DIR_A, FR_DIR_B, 1, false, baseSpeed);
  setMotor(RL_DIR_A, RL_DIR_B, 2, false, baseSpeed);
  setMotor(RR_DIR_A, RR_DIR_B, 3, false, baseSpeed);
}

void moveLeft() {
  // Strafe left: FL backward, FR forward, RL forward, RR backward
  setMotor(FL_DIR_A, FL_DIR_B, 0, false, baseSpeed);
  setMotor(FR_DIR_A, FR_DIR_B, 1, true, baseSpeed);
  setMotor(RL_DIR_A, RL_DIR_B, 2, true, baseSpeed);
  setMotor(RR_DIR_A, RR_DIR_B, 3, false, baseSpeed);
}

void moveRight() {
  // Strafe right: FL forward, FR backward, RL backward, RR forward
  setMotor(FL_DIR_A, FL_DIR_B, 0, true, baseSpeed);
  setMotor(FR_DIR_A, FR_DIR_B, 1, false, baseSpeed);
  setMotor(RL_DIR_A, RL_DIR_B, 2, false, baseSpeed);
  setMotor(RR_DIR_A, RR_DIR_B, 3, true, baseSpeed);
}

void rotateLeft() {
  // Rotate left: FL backward, FR forward, RL forward, RR backward
  setMotor(FL_DIR_A, FL_DIR_B, 0, false, baseSpeed);
  setMotor(FR_DIR_A, FR_DIR_B, 1, true, baseSpeed);
  setMotor(RL_DIR_A, RL_DIR_B, 2, true, baseSpeed);
  setMotor(RR_DIR_A, RR_DIR_B, 3, false, baseSpeed);
}

void rotateRight() {
  // Rotate right: FL forward, FR backward, RL backward, RR forward
  setMotor(FL_DIR_A, FL_DIR_B, 0, true, baseSpeed);
  setMotor(FR_DIR_A, FR_DIR_B, 1, false, baseSpeed);
  setMotor(RL_DIR_A, RL_DIR_B, 2, false, baseSpeed);
  setMotor(RR_DIR_A, RR_DIR_B, 3, true, baseSpeed);
}
