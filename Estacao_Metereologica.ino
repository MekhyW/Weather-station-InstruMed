// Incluindo as bibliotecas necessárias
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

// Definindo constantes do código
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_BMP280 bmp;
const int DHT_pino = 7;
DHT dht(DHT_pino, DHT22);
uint8_t SimboloGrau[] = {0x07,0x05,0x07,0x00,0x00,0x00,0x00,0x00};
uint8_t SimboloOhm[] = {0x00,0x00,0x0E,0x0A,0x1B,0x00,0x00,0x00};

float Temperatura, umid;
int le_lum; float tensao, res, Luminosidade;

// Criando função que mostra os nomes dos integrantes, série e o nome do projeto. 
void NomesTurmaProjeto(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Felipe Catapano");
  lcd.setCursor(0, 1);
  lcd.print("Thomas Chabro");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enzo Cunha");
  lcd.setCursor(0, 1);
  lcd.print("Felipe Drummond");
  delay(2000);
  lcd.clear();
  lcd.print("TURMA B");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Projeto Estacao");
  lcd.setCursor(0, 1);
  lcd.print("Metereologica!");
  delay(2000);
}

void setup() {
  analogReference(INTERNAL);
  dht.begin();
  bmp.begin(0x76);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, SimboloGrau);
  lcd.createChar(1, SimboloOhm);
  NomesTurmaProjeto();
}

void loop() {
  // Medindo a temperatura (Sensor LM35)
  int bin = analogRead(A0);
  // Convertendo o valor lido para uma tensão
  float ddp = (bin*1.1)/1023.0;
  // Calculando a temperatura junto com sua calibração
  Temperatura = ddp * 99.62571869 + 0.0057542347;
  // Lendo a temperatura no display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Temperatura: ");
  lcd.setCursor (0, 1);
  lcd.print (Temperatura);
  lcd.write(0);
  lcd.print("C");
  delay(2000);

  // Medindo a umidade (Sensor DHT22)
  float le_umid = dht.readHumidity();
  umid = le_umid*0.954248905 -1.870287298;
  // Lendo a umidade no display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Umidade: ");
  lcd.setCursor (0, 1);
  lcd.print (umid);
  lcd.print(" %");
  delay(2000);
  
  // Medindo a luminosidade
  le_lum = analogRead(A1);
  tensao = (le_lum/1023.0)*1.1;
  res = tensao*100000.0/(5.0 - tensao);
  Luminosidade = pow(10, 6.5 - 1.25*log10(res));
  // Lendo a luminosidade no display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Luminosidade: ");
  lcd.setCursor (0, 1);
  lcd.print(Luminosidade);
  lcd.print(" Lux");
  delay(2000);
  
  // Medindo a pressão
  float press = (bmp.readPressure())/100.0;
  // Lendo a luminosidade no display LCD
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("Pressao: ");
  lcd.setCursor (0, 1);
  lcd.print (press);
  lcd.print(" hPa");
  delay(2000);
}
