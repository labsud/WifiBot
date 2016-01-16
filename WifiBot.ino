#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//#define SMARTCONFIG
//#define DEBUG

const char* ssid = "LABSud";
const char* password = "Open Hardware & Open Source";

#define DR 0
#define DL 2
#define ER 5
#define EL 4

MDNSResponder mdns;

ESP8266WebServer server(80);

unsigned long startTime;
byte flag = 0;

void setup() {

#ifdef DEBUG
  //start serial link
  Serial.begin(115200);
#endif

  // init pins and do a simple running test
  pinMode(DR, OUTPUT);
  pinMode(DL, OUTPUT);
  pinMode(ER, OUTPUT);
  pinMode(EL, OUTPUT);

  digitalWrite(DR, 0);
  digitalWrite(DL, 0);

  analogWrite(ER, 500);
  analogWrite(EL, 500);

  delay(2000);

  analogWrite(ER, 0);
  analogWrite(EL, 0);

  digitalWrite(DR, 0);
  digitalWrite(DL, 0);

  // smart config
#ifdef SMARTCONFIG

  WiFi.beginSmartConfig();

#ifdef DEBUG
  Serial.println("Waiting SmartConfig ...");
#endif

  while (WiFi.smartConfigDone() != 1) {

    delay(1000);

#ifdef DEBUG
    Serial.print(".");
#endif
  }

#ifdef DEBUG
  Serial.println(" SmartConfig Success");
#endif

#else

  WiFi.begin(ssid, password);

#ifdef DEBUG
  Serial.println("");
#endif

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG
    Serial.print(".");
#endif
  }

#ifdef DEBUG
  Serial.println(" ");
#endif

#endif

  delay(1000);

  // start mDNS so you can access robot using wifibot.local URL
  if (mdns.begin("wifibot", WiFi.localIP())) {
#ifdef DEBUG
    Serial.println("MDNS responder started");
#endif
  }

// set up server answers
  server.on("/wifibot/r", turnRight);
  server.on("/wifibot/l", turnLeft);
  server.on("/wifibot/f", forward);
  server.on("/wifibot/b", backward);
  server.on("/wifibot/analog", analog);
  server.on("/wifibot/klaxon", klaxon);
//  server.on("/", root); // password

  server.begin(); //server is started


#ifdef DEBUG
  Serial.print("Server started, IP = "); //display IP
  Serial.println(WiFi.localIP());
#endif


}

void loop() {

//manage server
  server.handleClient();

  
//if no response is received during a certain time, set off motors
  if (millis() >= startTime + 500 && flag == 0) {

    flag = 1;
    analogWrite(ER, 0);
    analogWrite(EL, 0);

  }

}

//void root() {
//
//  char page[] = "<p><a href=\"l\"><button>Left</button></a></p></br><p><a href=\"r\"><button>Right</button></a></p></br><p><a href=\"f\"><button>For</button></a></p></br><p><a href=\"b\"><button>Back</button></a></p></br>";
//  server.send(200, "text/html", page);
//
//}

void klaxon() {

  
}


void analog() {

  int rlValue = server.arg("rl").toInt();
  int fbValue = server.arg("fb").toInt() * (-1);

  int leftValue = fbValue - rlValue;
  int rightValue = fbValue + rlValue;

  moveMotor(leftValue, rightValue);

}

void turnRight() {

  moveMotor(900, 0);

}

void turnLeft() {

  moveMotor(0, 900);


}

void forward() {

  moveMotor(900, 900);

}

void backward() {

  moveMotor(-900, -900);

}

void moveMotor(int left, int right) {

int measureLight=analogRead(A0);

  char page[10];
  itoa(measureLight,page,10);
  server.send(200, "text/html", page);

#ifdef DEBUG
  Serial.print("moveMotor : left = ");
  Serial.print(left);
  Serial.print("  right = ");
  Serial.println(right);
#endif

  left = constrain(left, -1023, 1023);
  right = constrain(right, -1023, 1023);

  if (left >= -600 && left <= 600) left = 0;
  if (right >= -600 && right <= 600) right = 0;

  digitalWrite(DR, right < 0 ? 1 : 0);
  digitalWrite(DL, left < 0 ? 1 : 0);

  analogWrite(ER, abs(right));
  analogWrite(EL, abs(left));

  startTime = millis();
  flag = 0;
  

}


