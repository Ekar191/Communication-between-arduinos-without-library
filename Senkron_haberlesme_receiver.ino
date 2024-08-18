#define echoPin 12 //Ultrasonik sensörün echo pini Arduino kartımızın 12.pinine bağladık
#define trigPin 13 //Ultrasonik sensörün trig pini Arduino kartımızın 13. pinine bağladık.

#define MotorR1 7 // L298N üzerindeki IN1 pinine bağlayın
#define MotorR2 6 //L298N üzerindeki IN2 pinine bağlayın
#define MotorRenable 9  // L298N üzerindeki enA pinine bağlayın
#define MotorL1 5 // L298N üzerindeki IN3 pinine bağlayın
#define MotorL2 4 // L298N üzerindeki IN4 pinine bağlayın
#define MotorLenable 3// L298N üzerindeki enB pinine bağlayın


//Yukarıdaki kısımda motor pinlerini tanımladık.


long sure, uzaklik; //süre ve uzaklık adında iki değişken tanımlıyoruz.

void setup() {


  // ultrasonik sensör Trig pininden ses dalgaları gönderdiği için OUTPUT (Çıkış),
  // göndermiş olduğıu bu dalgaları Echo pini ile geri aldığı için INPUT yani (Giriş) olarak tanımlanır.
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLenable, OUTPUT); 
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRenable, OUTPUT);
// yukarıdaki kısımda Motorlarımızı çıkış olarak tanımladık

  Serial.begin(9600);//  9600 baud rate üzerinden bir seri haberleşme başlattık

}

void loop() {


  digitalWrite(trigPin, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

  sure = pulseIn(echoPin, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = sure / 29.1 / 2; //ses dalgasının gidiş ve dönüşünden elde edilen süre uzaklık birimine çevriliyor

  Serial.println(uzaklik);

  if (uzaklik < 15) // Uzaklık 15'den küçük ise,
  {
    geri();  // 150 ms geri git
    delay(150);
    sag();  // 250 ms sağa dön
    delay(250);
  }
  else {  // değil ise,
    ileri(); // ileri git
  }

}

void ileri(){  // Robotun ileri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRenable, 250); // Sağ motorun hızı 150

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLenable, 250); // Sol motorun hızı 150
  
  
}


void sag(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRenable, 0); // Sağ motorun hızı 0 (Motor duruyor)

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLenable, 250); // Sol motorun hızı 150
  
  
}


void geri(){ // Robotun geri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi aktif
  analogWrite(MotorRenable, 150); // Sağ motorun hızı 150

  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi aktif
  analogWrite(MotorLenable, 150); // Sol motorun hızı 150
  
}