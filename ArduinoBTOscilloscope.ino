/*
  Bluetoothオシロ

 */

/*
 
 参考：http://ehbtj.com/electronics/arduino-utility-library/
    Divisor   |  Frequency(kHz)
  ------------+------------------
   ADC_DIV2   |      8000
   ADC_DIV4   |      4000
   ADC_DIV8   |      2000
   ADC_DIV16  |      1000
   ADC_DIV32  |      500
   ADC_DIV64  |      250
   ADC_DIV128 |      125
   AD変換器のクロック変更
   サンプリング周波数は13クロック必要。
   サンプリング：38.46153846153846kHz
*/
#include <Utility.h>

// 各種変数初期化
const int analogInPin = A0;  // 波形入力用pin
const int LEDPin = 13; // デバッグ用LED

void setup() {
  // シリアル通信開始
  Serial.begin(9600);

  //ADC高速化関数(分周比変更)
  setADCFrequency(ADC_DIV4);
/*
  #ifndef cbi
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
  #endif
  #ifndef sbi
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
  #endif

  cbi(ADCSRA,ADPS2) ;
  sbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
 */ 
  //LED出力設定
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  //要素数881くらいまではいけそう
  int WAVE[128]; //バッファ
  unsigned long Time[128]; //サンプル時間変数
  
  unsigned int counter = 0; 
  
  Serial.println("e");//クリア命令文字"e"送信
  
  
  //高速ADC_____________________________________
  //バッファ
  for( counter=0; counter<128; counter++ ){
    Time[counter]=micros();
    WAVE[counter] = analogRead(analogInPin);
    delayMicroseconds(2);
  }
  //モジュール送信______________________________
  //送信ループ
  unsigned int counter2 = 0; 
  for( counter2=0; counter2<128; counter2++ ){
    //digitalWrite(LEDPin, LOW);
    Serial.print(Time[counter2]-Time[0]);//最初にサンプリングした点を0に修正
    delay(10);
    Serial.print(",");
    delay(10);
    Serial.println(WAVE[counter2]);
    delay(10);
    //digitalWrite(LEDPin, HIGH);
    delay(10);
  }
    //delay(10);
    Serial.println("e");//バッファデータ終了完了。クリア命令文字"e"送信
    delay(10);
    //digitalWrite(LEDPin, HIGH);
  
}
