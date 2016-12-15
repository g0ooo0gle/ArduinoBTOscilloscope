/*
  Bluetoothオシロ

 */

#include <Utility.h>
 

// 各種変数初期化
const int analogInPin = A0;  // 波形入力用pin
const int LEDPin = 13; // デバッグ用LED
int counter = 0;//ループ用カウンタ変数
int counter2 = 0;//ループ用カウンタ変数
//int WAVE[100]; //波形保存用バッファ



void setup() {
  // シリアル通信開始
  Serial.begin(9600);

  //ADC高速化関数(分周比変更)
  setADCFrequency(ADC_DIV32);
}

void loop() {
  //要素数881くらいまではいけそう
  int WAVE[100]; //バッファ1
  int WAVE2[100]; //バッファ2
  
  
  
  //高速ADC_____________________________________
  //バッファ1
  for( counter=0; counter<100; counter++ ){
    WAVE[counter] = analogRead(analogInPin);
  }
  //バッファ2
  for( counter2=0; counter2<100; counter2++ ){
    WAVE2[counter2] = analogRead(analogInPin);
  }
  //モジュール送信_____________________________
  digitalWrite(LEDPin, HIGH);
  //バッファ１
  int counter = 0;
  for( counter=0; counter<100; counter++ ){
    digitalWrite(LEDPin, HIGH);
    
    Serial.print(counter);
    Serial.print(",");
    Serial.println(WAVE[counter]);
    digitalWrite(LEDPin, LOW);
    //delay(10);
  }

  //バッファ2
  int counter2 = 0;
  for( counter2=0; counter2<100; counter2++ ){
    digitalWrite(LEDPin, HIGH);
    
    Serial.print(counter2+100);
    Serial.print(",");
    Serial.println(WAVE2[counter2]);
    digitalWrite(LEDPin, LOW);
    //delay(10);
  }
  
    delay(10);
  
}
