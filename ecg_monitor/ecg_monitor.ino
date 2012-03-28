#define ST_SEND 0x01

unsigned long values[3];

long currentMillis = 0;
long lastMillis = 0;
int interval = 10;
byte state = 0;
int ledState = LOW;

char rbuff[255];

int i = 0;




void setup(){
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  
  Serial.begin(38400);
  
  digitalWrite(11, HIGH);
  delay(1000);
  Serial.print("\r\n+STWMOD=0\r\n");
  delay(100);
  Serial.print("\r\n+STNA=DIY_HA\r\n");
  delay(100);
  Serial.print("\r\n+STPIN=0000\r\n");
  delay(100);
  Serial.print("\r\n+STAUTO=0\r\n");
  delay(100);
  Serial.print("\r\n+STOAUTO=1\r\n");
  delay(2000);
  Serial.print("\r\n+INQ=1\r\n");
  delay(1000);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH); 
  
};

int strcmp(const char * s1, const char * s2) {
  return 0;
}

int readLine(char * str, int max) {
  int count = 0;
  while(count < max-1 && (str[count] = Serial.read()) != '\n') {
    ++count;
  } 
  str[count] = '\0';
  return count;
}

void loop(){
  currentMillis = millis();
  if (Serial.available()) {
    if ('s' == Serial.read() ) {
      state ^= ST_SEND;
      if (state & ST_SEND == ST_SEND) ledState = HIGH;
      else ledState = LOW;
      digitalWrite(13, ledState);
    }
  }
  
  if (currentMillis - lastMillis >= interval && (state & ST_SEND == ST_SEND)) {
    lastMillis = currentMillis;

    for(i = 0; i < 3; ++i) {
      values[i] = 0;
//      For double precision
//      values[i] = analogRead(2*i);
//      values[i] = values[i] << 10;
      values[i] += analogRead(2*i + 1);
    } 
    
    Serial.write((byte *) values, 12);
  }
  
  
};
