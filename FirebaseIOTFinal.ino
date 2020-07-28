//

/***
EJERCICIO DE LECTURA FIREBASE ARDUINO
03:D6:42:23:03:D1:0C:06:73:F7:E2:BD:29:47:13:C3:22:71:37:1B
con ejer.. de escritura
https://console.firebase.google.com/u/1/project/final-iot-8d7e7/database/final-iot-8d7e7/data/~2F
***/
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "final-iot-8d7e7.firebaseio.com"
#define FIREBASE_AUTH "I7VymUeQJbxgxfDdzOsE2VNW5YN3qRlAo7ua02aa"
#define WIFI_SSID "MOVISTAR_9BCF"
#define WIFI_PASSWORD "j72FdT2GFcdkpQGWTPwB"

//Declarando los pines de los leds
int pinLed1 = D0;
int pinMot2 = D1;


void setup() {
    //DECLARANDO EL MODO DE LOS PINES EN EL SETUP
  pinMode(pinLed1, OUTPUT);
  pinMode(pinMot2, OUTPUT);
 
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
  //Lectura Simple
  String led = Firebase.getString("dispositivoIOT/led");
  String motor = Firebase.getString("dispositivoIOT/motor");
 
  Serial.println(led); 
  Serial.println(motor); 
  
 if(led.equals("1")){
    Serial.println("LED 1 ENCENDIDO");
    digitalWrite(pinLed1,HIGH);
  }else{
    Serial.println("LED 1 APAGADO");
    digitalWrite(pinLed1,LOW);
  }
  
 if(motor.equals("1")){
    Serial.println("MOTOR ENCENDIDO");
    digitalWrite(pinMot2,HIGH);
  }else{
    Serial.println("MOTOR APAGADO");
    digitalWrite(pinMot2,LOW);
  }

  
  //----------------------------------
  // Esribir en modo simple
  float sound = readSonido();
  Serial.print("Intensidad de sonido: ");
  Serial.println(sound);
  Firebase.setFloat("sensores/sonido", sound);
  // handle error
  if (Firebase.failed()) {
      Serial.print("No se ha podido actualizar: ");
      Serial.println(Firebase.error());  
      return;
  }
  float gas = readGas();
  Serial.print("Partes por millon de Gas: ");
  Serial.println(gas);
  Firebase.setFloat("sensores/gas", gas);
  // handle error
  if (Firebase.failed()) {
      Serial.print("No se ha podido actualizar: ");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
}
float readSonido()
{
    return random(0, 180);
}
float readGas()
{
    return random(210, 410);
}
