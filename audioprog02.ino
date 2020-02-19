#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            input;           //xy=142,346
AudioMixer4              mixer1;         //xy=368,357
AudioOutputI2S           output;           //xy=371,453
AudioAnalyzeFFT256       fft;       //xy=598,356
AudioConnection          patchCord1(input, 0, mixer1, 0);
AudioConnection          patchCord2(input, 1, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0, output, 0);
AudioConnection          patchCord4(mixer1, 0, output, 1);
AudioConnection          patchCord5(mixer1, fft);
AudioControlSGTL5000     audioShield;     //xy=352,582
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

const int outPin1=1;
const int outPin2=2;

const int pwmPin1=3;
const int pwmPin2=4;
const int pwmPin3=5;
const int pwmPin4=6;

void setup() {
  
  AudioMemory(20);
  
  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(1);

  fft.windowFunction(AudioWindowHanning256);


  pinMode(outPin1, OUTPUT);
  pinMode(outPin2, OUTPUT);
    
}

void loop() {
  float n, sum=0;
  int i;

  if(fft.available()){
    Serial.print("FFT: ");
    for (i=0; i<2; i++) {
      n = fft.read(i)*10000;
    // Serial.print(n);
   //  Serial.print("   ");
     sum+=n;
    }
   // Serial.println();
  

  sum=sum/2;
  if(sum>225) sum=225;
  Serial.print(sum);
  Serial.println();
  }
  
  analogWrite(pwmPin1, sum);
  analogWrite(pwmPin2, sum);
  analogWrite(pwmPin3, sum);
  analogWrite(pwmPin4, sum);

  digitalWrite(outPin1, HIGH);
  digitalWrite(outPin2, LOW);

}
