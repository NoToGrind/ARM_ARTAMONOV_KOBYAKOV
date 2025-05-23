#include <DHT.h>
#define DHTPIN 2
DHT dht(DHTPIN, DHT11); 


int aPin = A0; // Аналоговый вход для датчика
int ledPins[5] = {4,5,6,7,8}; // Пины для светодиодов
int avalue = 0; // Переменная для хранения значения с датчика
int countled = 5; // Количество активных светодиодов
int minvalue = 100; // Минимальное значение (полный полив)
int maxvalue = 800; // Максимальное значение (критическая сухость)
int k;
int g1=200;
int g2=230;
int g3=280;
int g4=380;
int i=2;


int sensorPin=A1;
int lPin=9;
int val=0;

int zled=11;
int pirPin=10;
int pirValue;
  

void setup() 
{
  //датчик влажности почвы
  Serial.begin(9600); // Инициализация Serial-порта
  for(int i=0; i<5; i++) 
  {
    pinMode(ledPins[i], OUTPUT); // Настройка светодиодов как OUTPUT
  }
  Serial.println("Система мониторинга влажности почвы запущена");
  digitalWrite(ledPins[i], HIGH);
  Serial.println();
  Serial.println();

  //фоторезистор
  pinMode(sensorPin, INPUT);
  pinMode(lPin, OUTPUT);

  //влажность воздуха
  dht.begin();

  //Движение
  pinMode(zled, OUTPUT);          // Установка пин как выход
  pinMode(pirPin, INPUT);
  digitalWrite(zled, LOW);
  
  
}






void loop() 
{
  
  //датчик влажности почвы
  avalue = analogRead(aPin); // Чтение значения с датчика
  Serial.print("Ценость почвы = "); Serial.println(avalue); // Вывод в монитор
  k=avalue;
  countled = map(avalue, maxvalue, minvalue, 0, 7); // Масштабирование
  countled = constrain(countled,0,7);
  if (k<g1 and i!=0)
  {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[i], LOW);
    i=0;
    Serial.println("Избыток влажности почвы ");
  }
  else if (k>=g1 and k<g2 and i!=1)
  {
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[i], LOW);
    i=1;
    Serial.println("Высокий уровень влажности почвы ");
  }
  else if (k>=g2 and k<g3 and i!=2)
  {
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[i], LOW);
    i=2;
    Serial.println("Нормальный уровень влажности почвы ");
  }
  else if (k>=g3 and k<=g4 and i!=3)
  {
    digitalWrite(ledPins[3], HIGH);
    digitalWrite(ledPins[i], LOW);
    i=3;
    Serial.println("Низкий уровень влажности почвы ");
  }
  else if (k>g4 and i!=4)
  {
    digitalWrite(ledPins[4], HIGH);
    digitalWrite(ledPins[i], LOW);
    i=4;
    Serial.println("Недостаточный уровень влажности почвы ");
  }
  

  //Влажность воздуха
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру
  Serial.print("Влажность: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C "); //Вывод показателей на экран
  

  //Фоторезистор
  val = analogRead(sensorPin);
  analogWrite(lPin, val/4);
  Serial.print(val);
  Serial.println(" -коэффицент освещености");
  Serial.println();

  //движения
  pirValue = digitalRead(pirPin);    // Считываем значение от датчика движения
  if (pirValue == 1)                 // Если движение есть, делаем задержку в 3 с.
  {               
    digitalWrite(zled, HIGH);
  } 
  else 
  {
    digitalWrite(zled, LOW);
  }
 

  
  

  delay(10000); // Задержка 1 сек
}





