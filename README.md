# esp8266-web-server

#01 - connect to network

Open ino file with arduino IDE then set your network bssid and password.
const String wifiName = "";
const String wifiPass = "";

#02 - load program

Load this program into your eso8266
I use pin 13. so connect on led to connector D7(D7 match with pin 13)
and connect the second part to GND

#03 - Serial monitor

Go to serial arduino IDE monitor and get link to go to web server page. It should look like this

ESP8266 TRYING TO CONNECT NETWORK =>  reversort

. . . . . . . . . . . . 
Connected
================= Server started =================
Use this url to connect :		http://192.168.43.190

#04 - Connect and switch off-on led through your browser

past this link into your browser and enjoy
http://192.168.43.190

