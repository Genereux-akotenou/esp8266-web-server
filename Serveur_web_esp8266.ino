#include <ESP8266WiFi.h>

//some parameters
const String wifiName = "";
const String wifiPass = "";
const int    ledPin   = 13;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  //let try to connect to WIFI
  Serial.print("ESP8266 TRYING TO CONNECT NETWORK =>  ");
  Serial.println(wifiName);
  WiFi.begin(wifiName, wifiPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(". ");
  }
  Serial.print("\nConnected\n");
 
  //let start our web server
  server.begin();
  Serial.println("================= Server started =================");
  Serial.print("Use this url to connect :\t\thttps://");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  //check connexion
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  //waiting  our user send something
  Serial.println("user = new Action()");
  while(!client.available()){
    delay(1);
  }
 
  //get url to find user action
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  //traitment
  int value = LOW;
  if (request.indexOf("/device1=on") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/device1=off") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
  //reponse client
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'/>");
  client.println("<title>IoT - MANAGER PAGE</title>");
  client.println("<style>");
  client.println("a{ text-decoration: none; font-weight: bold;} h2{font-size: 1em; text-align: center;} table{border-collapse: collapse; width: 100%;}");
  client.println("td{border: 1px solid #f08713; padding: 0.2em;} table tr td:last-of-type{width: 200px;}");
  client.println("table tr:first-of-type{font-weight: bold;}button:hover{background-color: #f08713; border: 1px solid #ddd;border-radius: 5px;color: white;cursor: pointer;}</style>");
  client.println("</head>");
  client.println("<body style='background-color: #2c94c4; margin: 0;'>");
  client.println("<header style='color: black; padding: 0.5em; background-color: #0068b8; margin: auto;'>");
  client.println("<h1 style='text-align: center; color: black; padding: 0.5em; background-color: #fff; display: inline-block; margin: auto; border-radius: 10px; font-size: 1em;'>ESP8266 - MANAGER PAGE</h1>");
  client.println("<h1 style='text-align: center; color: black; padding: 0.5em; background-color: #fff; display: inline-block; margin: auto; border-radius: 10px; font-size: 1em; float: right; background-color: #f08713;'>WiFi : ");
  client.print(wifiName);
  client.println("</h1></header>");
  client.println("<div id='mainPage' style='width: 90%; margin: auto; background-color: whitesmoke; position: relative; top: 1.5em;'>");
  client.println("<table>");
  client.println("<tr>");
  client.println("<td>id</td>");
  client.println("<td>device name</td>");
  client.println("<td>status</td>");
  client.println("<td>action</td>");
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td>1</td>");
  client.println("<td>red led</td>");
  client.println("<td>");
  if(value == HIGH) {
    client.print("<span style='color: red;'>on</span>");
  } else {
    client.print("<span style='color: black;'>off</span>");
  }
  client.println("</td>");
  client.println("<td>");
  client.println("<a href='/device1=on'><button style='height: 30px; width: 90px;'> ON </button></a>");
  client.println("<a href='/device1=off'><button style='height: 30px; width: 90px;'> OFF </button></a>");
  client.println("</td>");
  client.println("</tr>");
  client.println("</table>");
  client.println("</div>");
  client.println("<div style='position: absolute; bottom: 0.8em; right: 0.8em; padding: 0.5em; background-color: #f08713; border-radius: 10px; color: white; transition: all .5s ease-in; width: auto;' id='login'><a href=''>disconnect</a></div>");
  client.println("</body>");
  client.println("</html>");
    
  delay(1);
  Serial.println("task done");
}
