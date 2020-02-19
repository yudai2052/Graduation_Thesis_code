#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            input;           //xy=173,210
AudioOutputI2S           output;           //xy=377,328
AudioMixer4              mixer1;         //xy=391,226
AudioAnalyzeFFT1024      fft;      //xy=609,227
AudioConnection          patchCord1(input, 0, mixer1, 0);
AudioConnection          patchCord2(input, 1, mixer1, 1);
AudioConnection          patchCord3(input, 0, output, 0);
AudioConnection          patchCord4(input, 0, output, 1);
AudioConnection          patchCord5(mixer1, fft);
AudioControlSGTL5000     audioShield;     //xy=308,463


const int myInput = AUDIO_INPUT_LINEIN;


const int outPin1=1;
const int outPin2=2;

const int pwmPin1=3;
const int pwmPin2=4;
const int pwmPin3=5;
const int pwmPin4=6;

void setup() {

  AudioMemory(12);

  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(1);

  fft.windowFunction(AudioWindowHanning1024);

  pinMode(outPin1, OUTPUT);
  pinMode(outPin2, OUTPUT);

}

void loop() {
  float n, sum=0;
  int i;

  if(fft.available()){
    Serial.print("FFT: ");
    for(i=0; i<2; i++){
      n=fft.read(i)*10000;
     // Serial.print(n);
      //Serial.println();
      sum+=n;
    }
    //Serial.println();
    
    sum=sum/2;
    if(sum>255) sum=255;
    Serial.print(sum);
    Serial.println(); 

    if(sum==255){
      digitalWrite(outPin1, HIGH);  //%100
      digitalWrite(outPin2, LOW);
      delay(9.4);  
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, LOW);
      delay(0.0);
    }
    else if(sum>205){
      digitalWrite(outPin1, HIGH);  //%80
      digitalWrite(outPin2, LOW);
      delay(7.52);  
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, LOW);
      delay(1.88);
    }
    else if(sum>128){
      digitalWrite(outPin1, HIGH);  //50%
      digitalWrite(outPin2, LOW);
      delay(4.7);  
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, LOW);
      delay(4.7);
    }
    else if(sum>64){
      digitalWrite(outPin1, HIGH);  //%25
      digitalWrite(outPin2, LOW);
      delay(2.35); 
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, LOW);
      delay(7.05);
    }
    else if(sum>26){
      digitalWrite(outPin1, HIGH);  //10%
      digitalWrite(outPin2, LOW);
      delay(0.94);  
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, LOW);
      delay(8.46);
    }
    else {
      digitalWrite(outPin1, HIGH);  //0%
      digitalWrite(outPin2, LOW);
      delay(0.0);  
      digitalWrite(outPin1, LOW);
      digitalWrite(outPin2, LOW);
      delay(9.4);
    }
  }
  

}
