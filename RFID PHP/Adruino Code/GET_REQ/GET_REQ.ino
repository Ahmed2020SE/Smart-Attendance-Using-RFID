#include <ESP8266WiFi.h>
const char* ssid     = "";
const char* password = "";
String id;
const char* host = "192.168.0.103";

int result;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password); //works!

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);

  //Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String writeURL = "/update.php";
  String url = "/reader.php";
  
  url += "?card_id=317086940";
  writeURL += "?field=20";
  /*url += "aaaa";
  url += "&pin=";
  url += "bbbb";
  url += "&cost=";
  url += "cccc";
*/
  //Serial.print("Requesting URL: ");
  //Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  
  /***** Reading From Client *****/
  while (client.connected())
    {
      if (client.available())
      {
        //Serial.println("Client Connected ...");
        /*reading From Client*/
       String line = client.readStringUntil('\n');
       Serial.println(line);
       id=line;
       // int myIndex =line.indexOf("1");
        
       /* if(line.substring(myIndex) == "1" ) {
            Serial.print("Requesting Writer URL: ");
            Serial.println(writeURL);
            // This will send the request to the server
           client.print(String("GET ") + writeURL + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

            if (client.connected())
            {
              if (client.available())
              {
                Serial.println(" Connected to Writer");
               }
            }*/

               
        }
        else
        {
          Serial.println("FAILED");
        }
        //result =find_text(line , "Number of rows = 1");
       // Serial.print(result);
        
      }
    //}
    Serial.print("Your ID: ");
    Serial.println(id);
  delay(5000);
  /** End of Reading Response From Client ***/
  
  //Serial.println();
  //Serial.println("closing connection");
}


