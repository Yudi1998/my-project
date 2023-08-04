#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
 #include <MFRC522.h>
 #define SS_PIN D4
#define RST_PIN D3
#define SENSOR  D1
#define LED_G D8 //define green LED pin
#define LED_R D2 //define red LED
#define RELAY D0 //relay pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 5.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

const char* ssid = "Nokia";                  // Your wifi Name       
const char* password = "355qwerty";          // Your wifi Password

const char *host = "192.168.43.85"; //Your pc or server (database) IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
 pinMode (D2, INPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  Serial.println("Put your card to the reader...");
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);

 
  
 
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  
}


void loop() {
  // put your main code here, to run repeatedly:
      //Declare object of class HTTPClient

  bool statuspb = digitalRead(D2); 
  if(statuspb == 1)
    {
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, LOW);
   flowMilliLitres = 0;
    }else{
     if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "37 28 46 B5") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(200);

    digitalWrite(RELAY, LOW);
    digitalWrite(LED_G, HIGH);
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    delay(DENIED_DELAY);
    digitalWrite(LED_R, LOW);
  }

   
    currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    
    pulse1Sec = pulseCount;
    pulseCount = 0;

    
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    
    flowMilliLitres = (flowRate / 60) * 1000;

    totalMilliLitres = flowMilliLitres;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");
   
   
    }
  // Look for new cards
  
  }
  
HTTPClient http;  
   
  String flowMilliLitresSend, postData;
  flowMilliLitresSend =(flowMilliLitres);   //String to interger conversion
 
  //Post Data
  postData = "flowMilliLitres=" + flowMilliLitresSend;
  
  http.begin("http://192.168.43.85/Nodemcu_ldr/i_db.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  //Serial.println("LDR Value=" + ldrvalue);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println("flowMilliLitres=" + flowMilliLitresSend);
  
  http.end();  //Close connection

  delay(500);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
  
}
