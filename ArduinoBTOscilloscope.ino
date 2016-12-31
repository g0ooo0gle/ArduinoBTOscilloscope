/*
  Bluetoothオシロ

 */

//#include <Utility.h>
 

// 各種変数初期化
const int analogInPin = A0;  // 波形入力用pin
const int LEDPin = 13; // デバッグ用LED




void setup() {
  // シリアル通信開始
  Serial.begin(9600);

  //ADC高速化関数(分周比変更)
  //setADCFrequency(ADC_DIV32);

  #ifndef cbi
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
  #endif
  #ifndef sbi
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
  #endif

  cbi(ADCSRA,ADPS2) ;
  sbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  
}

void loop() {
  //要素数881くらいまではいけそう
  int WAVE[256]; //バッファ
  unsigned long Time[256]; //サンプル時間変数
  
  unsigned int counter = 0; 

  //高速ADC_____________________________________
  //バッファ
  for( counter=0; counter<256; counter++ ){
    Time[counter]=micros();
    WAVE[counter] = analogRead(analogInPin);
    delayMicroseconds(2);
  }
  //モジュール送信_____________________________
  digitalWrite(LEDPin, LOW);
  //バッファ表示
  unsigned int counter2 = 0; 
  for( counter2=0; counter2<256; counter2++ ){
    digitalWrite(LEDPin, HIGH);
    Serial.print(Time[counter2]);
    Serial.print(",");
    Serial.println(WAVE[counter2]);
    //Serial.print("#");
    digitalWrite(LEDPin, LOW);
    //delay(10);
  }
 
    delay(5000);
  
}
