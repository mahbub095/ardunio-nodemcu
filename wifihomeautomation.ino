#include <ESP8266WiFi.h>

const char* ssid = "your username";
const char* password = "your hotspot password";

int valuea = LOW,valueb = LOW,valuec = LOW,valued = LOW,valuee = LOW,valuef = LOW,valueg = LOW,valueh = LOW,valuei = LOW,valuej = LOW;

WiFiServer server(80);



void setup() {
  Serial.begin(115200);
//  port.begin(115200);
  delay(10);


  

  // prepare GPIO2
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  

  
  digitalWrite(12, LOW);
  digitalWrite(14, LOW);
  digitalWrite(2, LOW);
  digitalWrite(0, LOW);
  
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
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
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
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
if (req.indexOf("/A") != -1)  {
    digitalWrite(14, HIGH);
    digitalWrite(12, LOW);
    
    valuea = HIGH;
  }
  if (req.indexOf("/a") != -1)  {
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
    
    valuea = LOW;
  }

 if (req.indexOf("/B") != -1)  {
    digitalWrite(0, HIGH);
    digitalWrite(2, LOW);
    
    valueb = HIGH;
  }
  if (req.indexOf("/b") != -1)  {
   digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    
    valueb = LOW;
  }


  
  client.flush();

   // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
 // client.print("Led pin is now: ");
  Serial.println("Client disonnected");  
}

