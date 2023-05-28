class A4988Shield {
  private:
    int steps;
    int step_pin;
    int dir_pin;
    int delayms;
    const int enable_pin = 8;

  public:
    A4988Shield(int motor_num) {
      pinMode(enable_pin, OUTPUT);
      digitalWrite(enable_pin, LOW);
      if (motor_num == 1) {
        step_pin = 2;
        dir_pin = 5;
      }
      else if (motor_num == 2) {
        step_pin = 3;
        dir_pin = 6;
      }
      else if (motor_num == 3) {
        step_pin = 4;
        dir_pin = 7;
      }
      else if (motor_num == 4) {
        step_pin = 12;
        dir_pin = 13;
      }
      pinMode(step_pin, OUTPUT);
      pinMode(dir_pin, OUTPUT);
    }

    void setSpeed(int delayms) {
      this->delayms = delayms;
    }

    void move(bool direction, int steps) {
      digitalWrite(dir_pin, direction);

      for (int i = 0; i < steps; i++) {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(delayms);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(delayms);
      }
    }
};
