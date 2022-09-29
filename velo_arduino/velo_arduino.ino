#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define PIN D1
#define NUMPIXELS 24
const char *ssid = "Velo";
const char *password = "pingpong";

int luminosite = 30;

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

  Serial.println("Starting AP");
  WiFi.softAP(ssid, password,1,false,1);
  
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  pixels.fill(pixels.Color(luminosite,0,0));
}

void loop() {

  WiFiClient client = server.available(); 

  if (!client) {
     clignotement();
     return;
  }

  Serial.println("Client connected");
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if( request.indexOf("/UP") != -1 && luminosite < 240){
    luminosite += 15;
    Serial.printf("Augmentation luminosite : %d \n", luminosite);
  } 

  if( request.indexOf("/DOWN") != -1 && luminosite > 15){
    luminosite -= 15 ;
    Serial.printf("Réduction luminosite : %d \n", luminosite);
  } 

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("");

  // Display the HTML web page
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" charset=\"utf-8\"> ");

  client.print("<p>Luminosité : </p>");
  client.println("Augmenter <a href=\"/UP\">+15</a><br>");
  client.println("Réduire <a href=\"/DOWN\">-15</a><br>");
  
  client.println("</body></html>");
  client.println();
      
  Serial.println("");
    
  clignotement();

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
    pixels.setPixelColor(i, pixels.Color(luminosite, 0, 0));
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

