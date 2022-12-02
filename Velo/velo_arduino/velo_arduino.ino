#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#define PIN D1
#define NUMPIXELS 24
const char *ssid = "Velo";
const char *password = "pingpong";

int luminosite = 150;
int R,G,B;
bool clignotantGaucheStatut = false;
bool clignotantDroitStatut = false;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Serveur
WiFiServer server(80);
String header;
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 5000;

void setup() {

  Serial.begin(115200);

  pixels.begin();
  pixels.fill(pixels.Color(20, 20, 20));
  pixels.show();

  Serial.println("Démarrage du wifi");
  WiFi.softAP(ssid, password,1,false,1);

  ArduinoOTA.setHostname("esp-velo");
  ArduinoOTA.setPassword("pingpong");

   ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();

  server.begin();
  pixels.fill(pixels.Color(luminosite,luminosite,0));
}

void loop() {

  ArduinoOTA.handle();

  WiFiClient client = server.available(); 

  if (!client) {
     clignotement();
     return;
  }

  Serial.println("Client connected");
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if( request.indexOf("/LuminositeUp") != -1 && luminosite < 240){
    luminosite += 15;
    Serial.printf("Augmentation luminosite : %d \n", luminosite);
  } 

  if( request.indexOf("/LuminositeDown") != -1 && luminosite > 15){
    luminosite -= 15 ;
    Serial.printf("Réduction luminosite : %d \n", luminosite);
  }

  if( request.indexOf("/Gauche") != -1){
    clignotantGaucheStatut = !clignotantGaucheStatut;
    Serial.print("Bascule clignotant gauche : ");
    Serial.println(clignotantGaucheStatut);
  }

  if( request.indexOf("/Droit") != -1){
    clignotantDroitStatut = !clignotantDroitStatut;
    Serial.print("Bascule clignotant droit : ");
    Serial.println(clignotantGaucheStatut);
  }


  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("");

  // Display the HTML web page
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" charset=\"utf-8\"> ");

  client.printf("<p>Luminosité : %d </p>",luminosite);
  client.println("<a href=\"/LuminositeUp\">Augmenter : +15</a><br>");
  client.println("<a href=\"/LuminsoteDown\">Réduire : -15</a><br>");
  client.println("<a href=\"/Gauche\">Clignonant gauche </a><br>");
  client.println("<a href=\"/Droit\">Clignonant droit</a><br>");
  
  client.println("</body></html>");
  client.println();
      
  Serial.println("");
    
  clignotement();
  if(clignotantGaucheStatut) clignotantGauche();
  if(clignotantDroitStatut) clignotantDroit();

/*
    pixels.setBrightness(100);
    pixels.show();
    delay(500);
    pixels.setBrightness(15);
    pixels.show();
    delay(500);
    */
    //infinite();
    //fade(0, 24, 55, 0, 0, 10, 1000, 3000);
      

      //for(short int i = 0 ; i< 3 ; i++) clignotement();
      //for(short int i = 0 ; i< 3 ; i++) clignotantGauche();
      //restore();
      //for(short int i = 0 ; i< 3 ; i++) clignotantDroit();
      //restore();
      //fade(0, 24, 55, 0, 55, 200, 1000, 3000);
  

}

void clignotement(){
  restore();
  for( short i = 0 ; i < NUMPIXELS ; i++){
    pixels.setPixelColor(i, pixels.Color(luminosite,0, 0));
  }
  pixels.show();
  delay(500);
  for( short i = 0 ; i < NUMPIXELS ; i++){
    pixels.setPixelColor(i, pixels.Color(20, 0, 0));
  }
  pixels.show();
  delay(500);

}

void clignotantGauche(){

  for( short i = NUMPIXELS /2 ; i < NUMPIXELS ; i++){
    pixels.setPixelColor(i, pixels.Color(200, 40, 0));
  }
  pixels.show();
  delay(500);
  for( short i = NUMPIXELS /2 ; i < NUMPIXELS ; i++){
    pixels.setPixelColor(i, pixels.Color(20, 4, 0));
  }
  pixels.show();
  delay(500);

}

void clignotantDroit(){

  for( short i = 0 ; i < NUMPIXELS /2 ; i++){
    pixels.setPixelColor(i, pixels.Color(200, 40, 0));
  }
  pixels.show();
  delay(500);
  for( short i = 0 ; i < NUMPIXELS /2 ; i++){
    pixels.setPixelColor(i, pixels.Color(20, 4, 0));
  }
  pixels.show();
  delay(500);

}

void restore(){
    for( short i = 0 ; i < NUMPIXELS ; i++){
    pixels.setPixelColor(i, pixels.Color(200, 0, 0));
  }
}

void infinite(){

  for(short i = 0 ; i < NUMPIXELS ; i++){
    delay(100);
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(50, 50, 50));
  
    pixels.show();
  }

}

void fade(short start, short end, short pourcentage_R, short pourcentage_G, short pourcentage_B, short luminosite, short dureeUp, short dureeDown){

  // On convertit pour remettre sur 8 bits;
  if (pourcentage_R) pourcentage_R = 255 * pourcentage_R /100;
  if (pourcentage_G) pourcentage_G = 255 * pourcentage_G /100;
  if (pourcentage_B) pourcentage_B = 255 * pourcentage_B /100;

  // duree en ms
  dureeUp = dureeUp / luminosite;
  dureeDown = dureeDown / luminosite;

  for( short i = 1 ; i < luminosite ; i++ ){
    for(short j = start; j < end ; j++){
      pixels.setPixelColor(j,pixels.Color(pourcentage_R*i/luminosite, pourcentage_G*i/luminosite, pourcentage_B*i/luminosite));
    }
    pixels.show();
    delay(dureeUp);
  }

  for( short i = luminosite ; i > 0 ; i-- ){
    for(short j = start; j < end ; j++){
      pixels.setPixelColor(j,pixels.Color( pourcentage_R*i/luminosite,  pourcentage_G*i/luminosite,  pourcentage_B*i/luminosite));
    }
    pixels.show();
    delay(dureeDown);
  }

}
