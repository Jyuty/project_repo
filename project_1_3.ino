#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <vector>
#include <string>

using namespace std;

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

vector <string> symb = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
vector <string> Morze = {"01", "1000", "1010", "100", "0", "0010", "110", "0000", "00", "0111", "101", "0100", "11", "10", "111", "0110", "1101", "010", "000", "1", "001", "0001", "011", "1001", "1011", "1100",
"11111", "01111", "00111", "00011", "00001", "00000", "10000", "11000", "11100", "11110"};
vector <string> output;
vector <string> ol_output;

int i = 0;

const int PIN_LFT = 8; //пин для джойстика(только одну ось)
const int PIN_RHT = 7; //n-ный пин для кнопки джойстика

const int PIN_MID = 6; //пин для кнопки отправки
const int PIN_BUTTON = 5;

 void setup(void) {
   u8g2.begin();
   Serial.begin(9600);
   pinMode(PIN_LFT, INPUT_PULLUP);
   pinMode(PIN_RHT, INPUT_PULLUP);
   pinMode(PIN_MID, INPUT_PULLUP);
   pinMode(PIN_BUTTON, INPUT_PULLUP);
   
   pinMode(LED_BUILTIN, OUTPUT); //пин для светодиода
}

void loop() {
  // put your main code here, to run repeatedly:
   /*u8g2.clearBuffer();          // clear the internal memory
     u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
     u8g2.drawStr(58,29, alpha[i].c_str());  // write something to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
     delay(3000);*/
     u8g2.clearBuffer();          // clear the internal memory
     u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
     u8g2.drawStr(58,29, symb[i].c_str());  // write something to the internal memory
     u8g2.sendBuffer();
     digitalWrite(LED_BUILTIN, LOW);
     if(digitalRead(PIN_RHT) == LOW)
        i = (i+1) / 36;
     if(digitalRead(PIN_LFT) == LOW)
     {
      i -= 1;
      if(i == -1)
        i = 35;
     }
     delay(100);
     Serial.println(i);
     u8g2.clearBuffer();          // clear the internal memory
     u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
     u8g2.drawStr(58,29, symb[i].c_str());  // write something to the internal memory
     u8g2.sendBuffer();
     if(digitalRead(PIN_MID) == HIGH)
     {
        output.push_back(Morze[i]);
        ol_output.push_back(symb[i]);
     }
     if(digitalRead(PIN_BUTTON) == LOW)
     {
        for(int j = 0; j < output.size(); j++)
        {
          u8g2.clearBuffer();          // clear the internal memory
          u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
          u8g2.drawStr(58,29, ol_output[j].c_str());  // write something to the internal memory
          u8g2.sendBuffer();
          for(int u = 0; u < output[j].size(); u++)
          {
            if(output[j][u] == '1')
            {
              digitalWrite(LED_BUILTIN, HIGH);
              delay(1000);
              digitalWrite(LED_BUILTIN, LOW);
              delay(100);
            }
            else
            {
              digitalWrite(LED_BUILTIN, HIGH);
              delay(400);
              digitalWrite(LED_BUILTIN, LOW);
              delay(100);
            }
          }
        }
        output.clear();
        i = 0;
     }
}
