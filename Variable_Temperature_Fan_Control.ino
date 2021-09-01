#include <Keypad.h>
#include <dht.h>
#include <LiquidCrystal.h>
#include <AFMotor.h>
#define dht_pin A8

dht DHT;

LiquidCrystal lcd(53, 51, 49, 47, 45, 43);

AF_DCMotor motor(4);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {22, 25, 26, 29};
byte colPins[COLS] = {30, 33, 34, 37};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

static const unsigned long REFRESH_INTERVAL1 = 2000;
static unsigned long lastRefreshTime1 = 0;

int a = 1;
int b = 1;
int c = 0;
int f = 1;
int g = 1;
int h = 1;
int l = 1;
int m = 0;
long t = 25;
int v = 1;
int w = 1;
int y = 0;


void setup() {
  lcd.begin(16, 2);
  motor.setSpeed(128);
  motor.run(RELEASE);
  Serial.begin(9600);
}

void loop() {

  char menu = customKeypad.getKey();

  DHT.read22(dht_pin);

  float temperature = DHT.temperature;

  if ((millis() - lastRefreshTime1 >= REFRESH_INTERVAL1) || m == 0) { //Refreshes Temperature every 2 seconds

    if (m == 1) {
      lastRefreshTime1 += REFRESH_INTERVAL1;
    }

    m = 1;
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print(" Deg C");
    Serial.println(temperature, 2);

    if (temperature > t && v == 1) {
      motor.run(BACKWARD);
    }

    if (temperature <= t && v == 1) {
      motor.run(RELEASE);
    }

  }

  lcd.setCursor(0, 1);
  lcd.print("PRESS * FOR MENU");

  if (menu == '1' && v == 0) {
    motor.run(BACKWARD);
  }

  if (menu == '0' && v == 0) {
    motor.run(RELEASE);
  }

  if (menu == '*') {

    for (int z  = 0; z < 1; z += 0) {
      menu = ' ';
      char menu_choice;
      unsigned long k = millis();

      if (temperature > t && v == 1) {
        motor.run(BACKWARD);
      }

      if (temperature <= t && v == 1) {
        motor.run(RELEASE);
      }

      while (y != 1) {

        if (a == 1 && y != 1) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("A) Temp Setpoint");
          lcd.setCursor(0, 1);
          lcd.print("B) Fan Speed");
          a = 0;
        }

        menu_choice = customKeypad.getKey();

        if (menu_choice) {
          y = 1;
          a = 1;
        }

        if ((millis() - k >= REFRESH_INTERVAL1) && y != 1) {
          k += REFRESH_INTERVAL1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("C) Manual/Auto ");
          lcd.setCursor(0, 1);
          lcd.print("D) Exit Menu");
          c = 0;

          while (c != 1) {

            menu_choice = customKeypad.getKey();

            if (menu_choice) {
              y = 1;
              a = 1;
              c = 1;
            }

            if ((millis() - k >= REFRESH_INTERVAL1) && y != 1) {
              k += REFRESH_INTERVAL1;
              a = 1;
              c = 1;
            }
          }
        }
      }

      if (menu_choice) {

        y = 0;

        for (int i = 0; i < 1; i += 0) {

          if (menu_choice == 'A') { //TEMP SETPOINT

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter Temp Point");
            delay(500);
            g = 1;

            for (int j = 0; j < 1; j += 0) {
              char temp_digit1 = customKeypad.getKey();

              if (temp_digit1 == 'A' || temp_digit1 == 'B' || temp_digit1 == 'C' || temp_digit1 == 'D' || temp_digit1 == '*' || temp_digit1 == '#') {
                g = 0;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Invalid Key");
                delay(1000);
                j = 1;
                temp_digit1 = ' ';
              }

              if (temp_digit1 && g == 1) {
                lcd.setCursor(0, 1);
                lcd.print(temp_digit1);

                k = 0;
                h = 1;

                for (int k = 0; k < 1; k += 0) {
                  char temp_digit2 = customKeypad.getKey();

                  if (temp_digit2 == 'A' || temp_digit2 == 'B' || temp_digit2 == 'C' || temp_digit2 == 'D' || temp_digit2 == '*' || temp_digit2 == '#') {
                    h = 0;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Invalid Key");
                    delay(1000);
                    k = 1;
                    j = 1;
                    temp_digit2 = ' ';
                  }

                  if (temp_digit2 && h == 1) {
                    lcd.setCursor(1, 1);
                    lcd.print(temp_digit2);
                    lcd.print(" Degrees C");
                    delay(1000);

                    t = (10 * (temp_digit1 - '0') + (temp_digit2 - '0'));

                    if (temperature > t && v == 1) {
                      motor.run(BACKWARD);
                    }

                    if (temperature <= t && v == 1) {
                      motor.run(RELEASE);
                    }

                    k++;
                    j++;
                  }

                }

              }
            }
            if (g == 1 && h == 1) {
              lcd.clear();
              i++;
            }
          }
          else if (menu_choice == 'B') { //FAN SPEED CONTROL

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Pick A Number");
            lcd.setCursor(0, 1);
            lcd.print("From 20 - 99");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("To Set Fan Speed");
            lcd.setCursor(0, 1);

            int s = 0;
            int t = 0;
            l = 1;
            f = 1;

            while (s != 1) {
              char speed1 = customKeypad.getKey();

              if (speed1 == '0' || speed1 == '1') {
                l = 0;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Number Too Small");
                delay(1000);
                s = 1;
                speed1 = ' ';
              }

              if (speed1 == 'A' || speed1 == 'B' || speed1 == 'C' || speed1 == 'D' || speed1 == '*' || speed1 == '#') {
                l = 0;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Invalid Key");
                delay(1000);
                s = 1;
                speed1 = ' ';
              }

              if (speed1 && l == 1) {
                lcd.print(speed1);
                while (t != 1) {
                  char speed2 = customKeypad.getKey();

                  if (speed2 == 'A' || speed2 == 'B' || speed2 == 'C' || speed2 == 'D' || speed2 == '*' || speed2 == '#') {
                    f = 0;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Invalid Key");
                    delay(1000);
                    s = 1;
                    t = 1;
                    speed1 = ' ';
                    speed2 = ' ';
                  }

                  if (speed2 && f == 1) {
                    lcd.print(speed2);
                    lcd.print("%");
                    delay(1000);
                    motor.setSpeed( (int) (((0.1 * (speed1 - '0')) + (0.01 * (speed2 - '0'))) * 255));
                    speed1 = ' ';
                    speed2 = ' ';
                    t = 1;
                    s = 1;
                  }
                }
              }

            }
            if (f == 1 && l == 1) {
              lcd.clear();
              i++;
            }
          }

          else if (menu_choice == 'C') { //SWITCH TO MANUAL OR AUTOMATIC
            lcd.clear();

            int q = 0;
            w = 1;

            lcd.setCursor(0, 0);
            lcd.print("A: Manual B:Auto");
            lcd.setCursor(0, 1);

            while (q != 1) {

              char manual_or_auto = customKeypad.getKey();

              if (manual_or_auto != 'A' && manual_or_auto != 'B' && manual_or_auto) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Invalid Key");
                delay(1000);
                q = 1;
                w = 0;
                manual_or_auto = ' ';
              }

              if (manual_or_auto == 'A') {
                lcd.print(manual_or_auto);
                delay(1000);
                motor.run(RELEASE);
                v = 0;
                q = 1;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Manual Control");
                lcd.setCursor(0, 1);
                lcd.print("Has Been Enabled");
                delay(2500);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Press 1 Or 0 On");
                lcd.setCursor(0, 1);
                lcd.print("The Main Screen");
                delay(2500);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("To Turn The Fan");
                lcd.setCursor(0, 1);
                lcd.print("On Or Off.");
                delay(2500);
              }

              else if (manual_or_auto == 'B') {
                lcd.print(manual_or_auto);
                delay(1000);
                v = 1;
                q = 1;
              }

            }
            if (w == 1) {
              i++;
            }
          }

          else if (menu_choice == 'D') {
            lcd.clear();
            menu_choice = ' ';
            i++;
            z++;
          }

          else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Invalid Option");
            delay(1000);
            lcd.clear();
            i++;
          }
        }
      }
    }
  }
}
