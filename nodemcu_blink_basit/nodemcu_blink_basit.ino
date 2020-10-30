//Mucitpilot 2020
//Blynk ve ESP8266 Kullanımı Örneği
#define BLYNK_PRINT Serial
//#ifndef UNIT_TEST
#include <Arduino.h>
//#endif

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define led D2
int butondurumu=0;

// Blynk uygulamasından aldığınız anahtar(token)'ı buraya giriyoruz.
char auth[] = "**************";

// Wifi ayarlarınız buraya girilecek.
// şifresiz ağlar içi şifreyi "" olarak bırakın.
char ssid[] = "************";
char pass[] = "************";

BlynkTimer timer; //senkronu sağlamak için bir sayaç nesnesi oluşturuluyor.

/////////////////Blynk üzerinden ESP'ye komut gönderme/////////////////////////////////////
BLYNK_WRITE(V1) //uygulamada tanımladığımız değişken ismi olmalı (ör:V1, V2)
{
  int pinValue = param.asInt(); // Sanal v1 değişkeninden aldığımız veriyi bir değişkene atıyoruz.
  // Ayrıca veri tipine göre şunlar da kullanılabilir.:
  // String i = param.asStr();
  // double d = param.asDouble();

  if (pinValue==1){
    Serial.println(" AÇIK");
    digitalWrite(led,HIGH);
    butondurumu=1;
    }
  else {
      Serial.println(" KAPALI");
      digitalWrite(led,LOW);
       butondurumu=0;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////

////////////////ESP'den BLYNK uygulamasına veri gönderme//////////////////////////////////////


// aşağıdaki fonksiyon ile sunucuya her 1 sn'de bir veri göndereceğiz.
// Uygulama kısmında gösterge nesnesinin özelliği PUSH olarak ayarlanacak.
// Çok sık aralıkla veri göndermeniz (max sn'de 10 veri) sistem tarafından engellendiği için tasarıma dikkat etmek gerek.
void veriGonder()
{
  String h;
  if (butondurumu ==1){h="LED AÇIK";}
  else {h="LED KAPALI";}
  Blynk.virtualWrite(V2, h);

}
///////////////////////////////////////////////////////////////////////////////////////////////


void setup()
{
  
  Serial.begin(115200);
  pinMode(D2, OUTPUT);//D2 pinini çıkış olarak tanımladık
  Blynk.begin(auth, ssid, pass); //blynk'e bağlanıyoruz
  // Arzu edersebiz server'ı da detaylı olarak belirtebilirsiniz:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(1000L, veriGonder); //timer nesnesinin veri gönderme aralığını  ve hangi fonksiyon ile veri gönderileceğini tanımlıyoruz.
}

void loop()
{
  Blynk.run(); //Burası mümkün olduğunca boş olmalı. Blynk'in çalışma mantığı genel olarak bu şekilde. Loop içinde başka işlemler olunca Blynk sunucusu ile olan senkron bozulabiliyor.
  timer.run(); //zamanlamayı kontrol ediyor.
}
