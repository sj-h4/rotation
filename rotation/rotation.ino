#include <MsTimer2.h>

volatile unsigned int nw = 0;
volatile unsigned int od = 0;
volatile unsigned int cnt = 0;
volatile double cnt_t = 0;
volatile double rpm = 0;
volatile unsigned int tmr2_f = 0;

//スリット数
volatile unsigned int slit_num = 0;

//校正用の時速
//volatile double sp = 0;

void int_cnt() {
  cnt++;
}

void int_tmr2() {
  nw = cnt;
  cnt_t = (nw + od) / 2;
  od = nw;
  cnt = 0;
  tmr2_f = 1;
}

void setup() {
  Serial.begin(9600);
  //while(!Serial);
  pinMode(2, INPUT);
  Serial.println("RMP");
  attachInterrupt(0, int_cnt, RISING);
  MsTimer2::set(500, int_tmr2);
  MsTimer2::start();
}

void loop() {
  if (tmr2_f == 1) {
    tmr2_f = 0;
    rpm = cnt_t * 2 * 60 / slit_num;
    Serial.print("cnt_t = ");
    Serial.print(cnt_t);
    Serial.print("  RPM = ");
    Serial.println(rpm);
    //Serial.print(rpm * 2105 * 60 / 1000000);
  }
}
