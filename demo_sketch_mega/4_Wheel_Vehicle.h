#include "CNC_A4988_Shield.h"

class four_wheel_vehicle {
  private:
    bool CW = HIGH;
    bool CCW = LOW;
    int microStepPin;
    int driving_speed = 200;
//  int turning_speed = 500;

    A4988Shield m1 = A4988Shield(1);
    A4988Shield m2 = A4988Shield(2);
    A4988Shield m3 = A4988Shield(3);
    A4988Shield m4 = A4988Shield(4);


  public:
    four_wheel_vehicle() {
      setAllMotorsSpeed(driving_speed);
    }

    void run_forward(int steps) {
      for (int x = 0; x < steps; x++) {
        m1.move(CW, 1);
        m2.move(CW, 1);
        m3.move(CW, 1);
        m4.move(CW, 1);
      }
    }

    void run_backward(int steps) {
      for (int x = 0; x < steps; x++) {
        m1.move(CCW, 1);
        m2.move(CCW, 1);
        m3.move(CCW, 1);
        m4.move(CCW, 1);
      }
    }

    void run_right(int steps) {
      for (int x = 0; x < steps; x++) {
        m1.move(CCW, 1);
        m2.move(CW, 1);
        m3.move(CW, 1);
        m4.move(CCW, 1);
      }
    }

    void run_left(int steps) {
      for (int x = 0; x < steps; x++) {
        m1.move(CW, 1);
        m2.move(CCW, 1);
        m3.move(CCW, 1);
        m4.move(CW, 1);
      }
    }

    void run_forward_right(int steps) {
  for (int x = 0; x < steps; x++) {
    m1.move(CW, 1);
    m2.move(CW, 1);
    m3.move(CW, 0);  // Stop motor 3 to move diagonally
    m4.move(CW, 0);  // Stop motor 4 to move diagonally
  }
}

void run_forward_left(int steps) {
  for (int x = 0; x < steps; x++) {
    m1.move(CW, 0);  // Stop motor 1 to move diagonally
    m2.move(CW, 0);  // Stop motor 2 to move diagonally
    m3.move(CW, 1);
    m4.move(CW, 1);
  }
}

void run_backward_right(int steps) {
  for (int x = 0; x < steps; x++) {
    m1.move(CCW, 1);
    m2.move(CCW, 1);
    m3.move(CW, 0);  // Stop motor 3 to move diagonally
    m4.move(CW, 0);  // Stop motor 4 to move diagonally
  }
}

void run_backward_left(int steps) {
  for (int x = 0; x < steps; x++) {
    m1.move(CCW, 0);  // Stop motor 1 to move diagonally
    m2.move(CCW, 0);  // Stop motor 2 to move diagonally
    m3.move(CCW, 1);
    m4.move(CCW, 1);
  }
}

    void rotate_cw(int steps) {
      for (int x = 0; x < steps; x++) {
        m1.move(CCW, 1);
        m2.move(CCW, 1);
        m3.move(CW, 1);
        m4.move(CW, 1);
      }
    }

    void rotate_ccw(int steps) {
      for (int x = 0; x < steps; x++) {
        m1.move(CW, 1);
        m2.move(CW, 1);
        m3.move(CCW, 1);
        m4.move(CCW, 1);
      }
    }

    

    void setAllMotorsSpeed(int speedDelay) {
      m1.setSpeed(speedDelay);
      m2.setSpeed(speedDelay);
      m3.setSpeed(speedDelay);
      m4.setSpeed(speedDelay);
    }
};
