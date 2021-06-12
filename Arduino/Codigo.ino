//Saida do sensor ultrassonico
int pinOutput = 2;
//Entrada do sensor ultrassonico
int pinIntput = 3;

//Parametros de calculo da distancia do sensor ultrassonico
float TempoEcho = 0;
const float VelocidadeSom_mpors = 340;
const float VelocidadeSom_mporus = 0.000340;

//Entrada do sensor de força
int peso=0;
int sensorForca=A1;

void setup(){
  pinMode(pinOutput, OUTPUT);
  digitalWrite(pinOutput, LOW);
  pinMode(pinIntput, INPUT);

  Serial.begin(9600);
  delay(100);
}

void loop() {
  //Leitura da temperatura e calculo para conversao em celsius
  int tmp = analogRead(A0);
  float voltage = (tmp * 5.0)/1024;
  float milliVolt = voltage * 1000;
  float celsius = (milliVolt-500)/10; 

  //Leitura da distancia e calculo para distania em cm
  DisparaPulsoUltrassonico();
  TempoEcho = pulseIn(pinIntput, HIGH);
  float distancia = (CalculaDistancia(TempoEcho)*100);

  //Leitura da forca aplicada no sensor
  peso = analogRead(sensorForca);

  //Leitura da rotacao
  float rotacao = map(analogRead(A2), 0, 1023, 0, 10000);

  //Construcao da estrutura JSON
  Serial.print("{ 'dados': { 'temperatura' : ");
  Serial.print(celsius);
  Serial.print(", 'distancia' : ");
  Serial.print(distancia);
  Serial.print(", 'peso' : ");
  Serial.print(peso);
  Serial.print(", 'rotacao' : ");
  Serial.print(rotacao);
  Serial.println("}}");

  delay(1000);
}

void DisparaPulsoUltrassonico(){
  digitalWrite(pinOutput, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinOutput, LOW);
}

float CalculaDistancia(float tempo_us){
  return((tempo_us*VelocidadeSom_mporus)/2);
}
