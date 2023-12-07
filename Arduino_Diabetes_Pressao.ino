/*
  Simple POST client for ArduinoHttpClient library
  Connects to server once every five seconds, sends a POST request
  and a request body

  created 14 Feb 2016
  modified 22 Jan 2019
  by Tom Igoe
  
  this example is in the public domain
 */
#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// Wifi Settings ///////
const char* ssid = "goldar";
const char* password = "mesmera1301";

char serverAddress[] = "192.168.1.102";  // server address
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(3000);
  }
  Serial.print("Conectou a REDE WIFI: " );
  Serial.println(WiFi.SSID());
}

void loop() {
  Serial.println("making POST request");
  String contentType = "application/json";
  String postData = "{\"id\":1,\"personId\":1,\"date\":\"2022-12-14T14:57:06.844Z\",\"sistolica\":9,\"diastolica\":1,\"categoria\":1,\"batimentos\":140}";

  client.post("/api/Hiper/Create", contentType, postData);
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait five seconds");
  delay(150000);
}
