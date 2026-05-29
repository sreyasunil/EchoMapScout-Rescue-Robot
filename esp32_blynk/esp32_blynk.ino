// -------- Blynk --------
#define BLYNK_TEMPLATE_ID "TMPL3ZlN_6NGh"
#define BLYNK_TEMPLATE_NAME "EchoMapScout"
#define BLYNK_AUTH_TOKEN "_QAw4qyJwyfcJ8lEZFZvFsrbui-UxAkl"

#include <WiFi.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>

// -------- WiFi --------
const char* ssid = "realme 11 5G";
const char* password = "00000000";

// -------- Server --------
WebServer server(80);

// -------- Pins --------
int IN1 = 26;
int IN2 = 25;
int IN3 = 33;
int IN4 = 32;

#define GAS_SENSOR 34

int gasValue;
int gasThreshold = 800;

BlynkTimer timer;

// -------- Movement --------
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// -------- Web Routes --------
void handleForward() { forward(); server.send(200, "text/plain", "Forward"); }
void handleBackward() { backward(); server.send(200, "text/plain", "Backward"); }
void handleLeft() { left(); server.send(200, "text/plain", "Left"); }
void handleRight() { right(); server.send(200, "text/plain", "Right"); }
void handleStop() { stopMotors(); server.send(200, "text/plain", "Stop"); }

void handleGas() {
  int total = 0, count = 0;

  for (int i = 0; i < 10; i++) {
    int val = analogRead(GAS_SENSOR);
    if (val > 0) {
      total += val;
      count++;
    }
    delay(5);
  }

  int avg = (count > 0) ? total / count : 0;
  server.send(200, "application/json", "{\"gas\":" + String(avg) + "}");
}

// -------- Blynk Gas --------
void checkGas() {
  gasValue = analogRead(GAS_SENSOR);

  Blynk.virtualWrite(V5, gasValue);

  if (gasValue > gasThreshold) {
    Blynk.logEvent("gas_alert", "⚠ Gas detected!");
  }
}

// -------- Blynk Controls --------
BLYNK_WRITE(V0) {
  if (param.asInt()) forward();
  else stopMotors();
}

BLYNK_WRITE(V1) {
  if (param.asInt()) backward();
  else stopMotors();
}

BLYNK_WRITE(V2) {
  if (param.asInt()) left();
  else stopMotors();
}

BLYNK_WRITE(V3) {
  if (param.asInt()) right();
  else stopMotors();
}

// -------- Setup --------
void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(12);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  // ✅ Blynk + WiFi
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  Serial.println("Connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Web routes
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  server.on("/gas", handleGas);

  server.begin();

  // Timer
  timer.setInterval(500L, checkGas);
}

// -------- Loop --------
void loop() {
  Blynk.run();
  timer.run();
  server.handleClient();
} this is the blynk app code