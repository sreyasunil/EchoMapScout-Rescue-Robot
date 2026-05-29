#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Redmi 11 Prime";
const char* password = "hahahaha";

// Create server
WebServer server(80);

// Motor pins
int IN1 = 26;
int IN2 = 25;
int IN3 = 33;
int IN4 = 32;

// Gas sensor
#define GAS_SENSOR 34

int gasValue;

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

// -------- API Routes --------
void handleForward() {
  forward();
  server.send(200, "text/plain", "Forward");
}

void handleBackward() {
  backward();
  server.send(200, "text/plain", "Backward");
}

void handleLeft() {
  left();
  server.send(200, "text/plain", "Left");
}

void handleRight() {
  right();
  server.send(200, "text/plain", "Right");
}

void handleStop() {
  stopMotors();
  server.send(200, "text/plain", "Stop");
}

// Gas API
void handleGas() {
  int total = 0;
  int validReadings = 0;

  for (int i = 0; i < 10; i++) {
    int val = analogRead(GAS_SENSOR);

    if (val > 0) {   // ignore zero readings
      total += val;
      validReadings++;
    }

    delay(10);
  }

  int gasValue = (validReadings > 0) ? total / validReadings : 0;

  Serial.println(gasValue);

  server.send(200, "application/json", "{\"gas\":" + String(gasValue) + "}");
}

// -------- Setup --------
void setup() {
  Serial.begin(115200);

  analogReadResolution(12);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Routes
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  server.on("/gas", handleGas);

  server.begin();
}

// -------- Loop --------
void loop() {
  server.handleClient();
}  