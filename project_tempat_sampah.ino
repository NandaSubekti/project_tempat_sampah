#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

DHT dht(A3, DHT11);
#define DHTPIN A3
#define DHTTYPE DHT11

Servo servo_1;
Servo servo_2;

int s1,s2,s3;

float kelembaban;
float h;
bool dht11=false;
bool metal=false;
bool nonmetal=false;
bool nonorganik=false;
bool organik=false;

int m=0;
int metal_1 = 12;
int metal_2 = 11;

int data_metal_1 = 0;
int data_metal_2 = 0;


int proxy_1 = 13;
int proxy_2 = A2;

int data_proxy_1 = 0;
int data_proxy_2 = 0;

//inisial pin ultrasonik
const unsigned int TRIG_PIN_1=2;
const unsigned int ECHO_PIN_1=4;

const unsigned int TRIG_PIN_2=5;
const unsigned int ECHO_PIN_2=6;

const unsigned int TRIG_PIN_3=7;
const unsigned int ECHO_PIN_3=8; 
 

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {

  Serial.begin(115200);
  dht.begin();
  
  lcd.init();  
  lcd.begin (20, 4); 
  lcd.backlight(); 
  
  lcd.setCursor(0,0);
  lcd.print("   hello everyone");
  lcd.setCursor(0,1);
  lcd.print("     konichiwaa");
  
  pinMode(metal_1,INPUT);
  pinMode(metal_2,INPUT);

  pinMode(proxy_1,INPUT);
  pinMode(proxy_2,INPUT);

  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);

  servo_1.attach(9);
  servo_2.attach(10);
  servo_1.write(90);
  servo_2.write(90);
}
int sonar1(void)
{
  digitalWrite(TRIG_PIN_1, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_1, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_1, LOW);
  int jarak1=pulseIn(ECHO_PIN_1,HIGH);
  return (jarak1 = jarak1/58);
}
int sonar2(void)
{
  digitalWrite(TRIG_PIN_2, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_2, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_2, LOW);
  int jarak2=pulseIn(ECHO_PIN_2,HIGH);
  return (jarak2 = jarak2/58);
}
int sonar3(void)
{
  digitalWrite(TRIG_PIN_3, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_3, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_3, LOW);
  int jarak3=pulseIn(ECHO_PIN_3,HIGH);
  return (jarak3 = jarak3/58);
}
void sendnode(){
  if (sonar1()<11){
    s1=1;
  }
  else if (sonar1()>11){
    s1=0;
  }
  if (sonar2()<11){
    s2=1;
  }
  else if (sonar2()>11){
    s2=0;
  }
  if (sonar3()<11){
    s3=1;
  }
  else if (sonar3()>11){
    s3=0;
  }
  Serial.print ("#");
  Serial.print (s1);
  Serial.print ("#");
  Serial.print (s2);
  Serial.print ("#");
  Serial.print (s3);
  Serial.println ("#$");
  delay (100);
 
}
void lcd_tempat_sampah(){
  if (s2 == 1){
    lcd.setCursor(0,2);
    lcd.print("   Sampah Metal   ");
    lcd.setCursor(0,3);
    lcd.print("[ Terdeteksi Penuh ]");
  }
  else if (s1 == 1){
    lcd.setCursor(0,2);
    lcd.print("   Sampah Organik   ");
    lcd.setCursor(0,3);
    lcd.print("[ Terdeteksi Penuh ]");
  }
  else if (s3 == 1){
    lcd.setCursor(0,2);
    lcd.print(" Sampah NonOrganik");
    lcd.setCursor(0,3);
    lcd.print("[ Terdeteksi Penuh ]");
  }
}
void Data_Sensor(){
  data_metal_1 = digitalRead(metal_1); 
  data_metal_2 = digitalRead(metal_2);
  kelembaban = dht.readHumidity();

  data_proxy_1 = digitalRead(proxy_1);
  data_proxy_2 = digitalRead(proxy_2);

}
void proxy(){
  if (data_proxy_1 == 0){
    for (int b=0; b<100; b++){
      delay(50);  
    }
    m = 1;
  }
  else {
    m = 0;
    int b=0;
  }
}
void dht1(){
  {
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  }
  
  if (data_proxy_2 == 0){
   
    for (int b=0; b<100; b++){
      delay(10);  
    }
    delay(500);
    kelembaban=h;
    h=dht.readHumidity();
  }
  else{
    int b=0;  
  }
}

void sensor(){
  if ((m == 1 ) && (data_metal_1 == 0 || data_metal_2 == 0)){ 
    delay(2000);
    metal = true;
    nonmetal=false;
  }
  else if ((m == 1 ) && (data_metal_1 == 1 && data_metal_2 == 1)){
    delay(2000);
    nonmetal=true;
  }
  else if ((data_proxy_2 == 0) &&( h < 75 )){
    
    nonorganik=true;
      Serial.print (h);
  }
  else if ((data_proxy_2 == 0) && (h > 75 )){
    
    organik=true;
     Serial.print (h);
  }
}
void resetkondisi(){
  metal=false;
  nonmetal=false;
  nonorganik=false;
  organik=false;
}
void pemilah(){
  if (metal == true){
    lcd.setCursor(0,3);
    lcd.print(" Sampah Terdeteksi");
    lcd.setCursor(0,1);
    lcd.print("=== Jenis Sampah ===");
    lcd.setCursor(0,2);
    lcd.print("    >>>>Metal<<<<   ");
    delay(1000);
    servo_1.write(180);             
    delay(2000);
    servo_1.write(90);
    delay(100);
    resetkondisi();
    return;                                       
  }
  else if (nonmetal == true){
    lcd.setCursor(0,3);
    lcd.print(" Sampah Terdeteksi");
    lcd.setCursor(0,1);
    lcd.print("=== Jenis Sampah ===");
    lcd.setCursor(0,2);
    lcd.print("  >>>>NonMetal<<<<  ");
    delay(1000);
    servo_1.write(0);                                   
    delay(2000);
    servo_1.write(90);
    delay(100);
    resetkondisi();
    return;                                      
  }

  else if (nonorganik == true){
    lcd.setCursor(0,3);
    lcd.print(" Sampah Terdeteksi");
    lcd.setCursor(0,1);
    lcd.print("=== Jenis Sampah ===");
    lcd.setCursor(0,2);
    lcd.print(" >>>>Non Organik<<<<  ");
    
    delay(1000); 
    servo_2.write(180);                                    
    delay(2000);
    servo_2.write(90);
    delay(100);
    resetkondisi();
    return;                                   
  }
  else if (organik == true){
    lcd.setCursor(0,3);
    lcd.print(" Sampah Terdeteksi");
    lcd.setCursor(0,1);
    lcd.print("=== Jenis Sampah ===");
    lcd.setCursor(0,2);
    lcd.print("  >>>>Organik<<<<  ");
    delay(1000); 
    servo_2.write(0);               
    delay(2000);
    servo_2.write(90); 
    delay(100);
    resetkondisi();
    return;                                    
  }
}

void loop() {
  Data_Sensor();
  dht1();
  sensor();
  pemilah();
  proxy();
  sendnode();
  lcd_tempat_sampah();

  if (s1 == 0 && s2 == 0 && s3 ==0){
    lcd.setCursor(0,0);
    lcd.print("   Masukan Sampah");
    lcd.setCursor(0,1);
    lcd.print("   >>>>Disini<<<<  ");
  }

  
  
}  
