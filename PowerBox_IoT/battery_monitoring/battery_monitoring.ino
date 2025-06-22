//**************** IMPORTING LIBRARIES **************
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
//***************************************************

//**************** PIN DECLEARATION ******************
#define v1 A0
#define v2 A1
#define v3 A2
#define C1 A3
#define C2 A4
#define ac  A5
//********************************************************

float ex_ref = 4.99;

float adc = 0;
float adv = 0;

float cell_1 = 0.00;
float cell_2 = 0.00;
float cell_3 = 0.00;

float batt = 0.00;
float Chargin_curr = 0.00;
float disChargin_curr = 0.00;

float reso_2 = 0.987/(9.92 + 0.987 );    //0.23256;
float reso_1 = 0.214/(2.18 + 0.214 );
float reso_3 = 0.96/(4.64 + 0.96 );

SoftwareSerial myserial(9,10);



float read_adc(int pin);
float read_dc_current(int pin,float offset);
float read_dc_voltage(float voltage, float res);

void setup(){
analogReference(EXTERNAL);
myserial.begin(4800);
  // put your setup code here, to run once:
Serial.begin(115200);
}



void loop() {
  StaticJsonDocument<512> doc;
// StaticJsonBuffer<1600> jsonBuffer;
//  ********** BATT CELLS READER ****************
  cell_1 = read_dc_voltage(read_adc(v1),reso_1);
//  cell_2 = read_dc_voltage(read_adc(v2),reso_2) - cell_1;
//  cell_3 = read_dc_voltage(read_adc(v3),reso_3) - (cell_2 + cell_1) ;
//  batt = read_dc_voltage(read_adc(v3),reso_3);
//**********************************************************/

//******************* CURRENT READER *******************
  Chargin_curr =  read_dc_current(C2,0.3);  //offset 0.3
  disChargin_curr = read_dc_current(C1,0);
           //map(read_adc(Cin),2.55,4.5,0,20);
//*******************************************************
   
//   put your main code here, to run repeatedly:
Serial.println("cell 1 = " + String(cell_1));
//Serial.println("cell 2 = " + String(cell_2));
//Serial.println("cell 3 = " + String(cell_3));
//Serial.println("cin = " + String(Chargin_curr));
//Serial.println("cout = " + String(disChargin_curr));
Serial.println("");

//  doc["c1"] = cell_1;
//   doc["c2"] = cell_2;
//    doc["c3"] = cell_3;
//     doc["b"] =  batt;
//       doc["ci"] =  Chargin_curr;
//        doc["co"] =  disChargin_curr;
//   String output;
//  serializeJsonPretty(doc, output);    
//Serial.println(output);
//serializeJson(doc,myserial);
////myserial.print(output);
delay(1000);
}


float read_adc(int pin){
  adv =   analogRead(pin)/1.024;  //adc/100;
  float output_adc = adv*ex_ref/1000;
  return output_adc;
}


float read_dc_current(int pin,float offset){
   for(int i =0; i < 100; i++){
 adc = adc + analogRead(pin)/1.024;
  delay(1);
  } 
  adc = adc/100;
 float output_current = (((adc*ex_ref/1000) - 2.54)*10) - offset;

 
if(output_current < 0){
  output_current = output_current * -1;
 }
 if(output_current < 0.5){
  output_current = 0.00;
 }
 else{
  output_current = output_current;
 }
  return output_current;
}


float read_dc_voltage(float voltage, float res){
  float read_1 = voltage/res;
  return read_1; 
}
