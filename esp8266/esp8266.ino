
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "project-tempat-sampah-otomatis-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "SiPAcKQZBtYz0E4FHxyq1AMthLdmHg0vaU1OyJ39"
#define WIFI_SSID "Hernan"
#define WIFI_PASSWORD "dewigita"

bool parsing = false;
String sData,data[4];

void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void printorganik(){
  Firebase.setFloat("/Hasil_Pembacaan/Organik", data[1].toInt());
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(50);
  
}
void printnonorganik(){
  Firebase.setFloat("/Hasil_Pembacaan/Non_Organik", data[3].toInt());
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(50);
  
}
void printMetal(){
  Firebase.setFloat("/Hasil_Pembacaan/Metal", data[2].toInt());
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(50);
}

void loop() {
  printMetal();
  printnonorganik();
  printorganik();
 while (Serial.available()>0){
  char inchar = Serial.read();
  sData += inchar;
  if (inchar == '$'){
    parsing=true;
  }
  if (parsing){
    int q=0;
    for (int i=0;i < sData.length();i++){
      if (sData[i] == '#'){
        q++;
        data[q] = " ";
      }
      else{
        data[q] += sData[i];
      }
    }
    parsing = false;
    sData="";
  }
 }
}
