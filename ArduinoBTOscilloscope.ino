/*
  Bluetoothオシロ

 */

#include <Utility.h>
 

// 各種変数初期化
const int analogInPin = A0;  // 波形入力用pin
const int LEDPin = 13; // デバッグ用LED
int counter = 0;//ループ用カウンタ変数
//int WAVE[512]; //波形保存用バッファ



void setup() {
  // シリアル通信開始
  Serial.begin(9600);

  //ADC高速化関数(分周比変更)
  setADCFrequency(ADC_DIV32);
}

void loop() {
  
  int WAVE[881]; //バッファ
  
  //高速ADC_____________________________________
  for( counter=0; counter<881; counter++ ){
    WAVE[counter] = analogRead(analogInPin);
  }
  
  //モジュール送信_____________________________
  digitalWrite(LEDPin, HIGH);
  int counter = 0;
  for( counter=0; counter<881; counter++ ){
    digitalWrite(LEDPin, HIGH);
    
    Serial.print(counter);
    Serial.print(",");
    Serial.println(WAVE[counter]);
    digitalWrite(LEDPin, LOW);
    //delay(10);
  }
    delay(1000);
  
}
