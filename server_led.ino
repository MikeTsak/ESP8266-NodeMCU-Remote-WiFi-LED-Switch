//Mike Tsak 2023

#include <ESP8266WiFi.h>
#define LED D2  // LED at GPIO4 D2
 
const char* ssid = "SSID";   //enter your wi-fi name
const char* password = "Password";    //enter the wifi password
unsigned char status_led=0;

WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);   
  pinMode(LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(LED_BUILTIN, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // digitalWrite(LED, HIGH);
 
  // Start the server
  server.begin();
  Serial.println("Server started at...");
  Serial.println(WiFi.localIP());
 
}
 
void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while (! client.available())
  {
    delay (1);
  }
  
 
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  // Match the request
  
  if (req.indexOf("/ledoff") != -1)  {
    status_led=0;
    digitalWrite(LED, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/ledon") != -1)
  {
    status_led=1;
    digitalWrite(LED,HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED ON");
  }
 
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println(""); 

client.println("<!DOCTYPE HTML>");
client.println("<HTML>");
client.println("<H1> LED CONTROL </H1>");
client.println("<br />");

client.println("<H2> Turn on and off the on board LED and the LED on D2 </H2>");
client.println("<br />");

client.println("<H3> Suggested board <a href='https://raw.githubusercontent.com/MikeTsak/ESP8266-NodeMCU-Remote-WiFi-LED-Switch/main/circuit.png'>here</a> </H3>");
client.println("<br />");
 
 client.println("<a href=\"/ledon\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED ON </button> </a>");
 client.println("<a href=\"/ledoff\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LED OFF </button> </a>");
 client.println("<br />");
  client.println("<a href='https://miketsak.gr/'>miketsak.gr</>");
 client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
