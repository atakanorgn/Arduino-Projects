// --- AKILLI PARK SENSÖRÜ (PİNLER: 3,4,5,11 ve Sensör 9-13) ---

const int green = 3;    
const int yellow = 4;   
const int red = 5;      
const int buzzer = 11;  // Buzzer

const int trigPin = 9;  // Tetikleyen sensör
const int echoPin = 7; // Yolu hesaplayan sensör

void setup() {
  // Elemanları initialise etme
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Sensör pinleri
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Bilgisayar çıktısı
  Serial.begin(9600);
  Serial.println("Sistem Baslatiliyor...");
}

void loop() {
  long duration;
  int distance;

  // Ölçüm Sinyali Gönder 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //  Yankıyı Dinle
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // --- FİLTRELEME VE KONTROL ---
  // Eğer mesafe 0 veya çok uzaksa
  if (distance == 0 || distance > 300) {
     Serial.println("HATA: Sensor okuyamiyor (0)!"); 
     distance = 999; // Hata ver ve distance'ı arttır
  } else {
     // Ekrana sonucu yaz
     Serial.print("Mesafe: ");
     Serial.print(distance);
     Serial.println(" cm");
  }

  // Işıkları söndür
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  // Buzzer'ı burada susturmuyoruz, aşağıda ritim vereceğiz.

  //
  if (distance < 20) {
    // --- ÇOK YAKIN (KIRMIZI + HIZLI DIT DIT) ---
    digitalWrite(red, HIGH);
    
    // Fısıltı Modu (Sesi kısık - değer 10)
    analogWrite(buzzer, 10); 
    delay(50);
    digitalWrite(buzzer, LOW); // Sus
    delay(50);
  }
  else if (distance < 50) {
    // --- ORTA MESAFE (SARI + YAVAŞ DİİİT) ---
    digitalWrite(yellow, HIGH);
    
    // Fısıltı Modu
    analogWrite(buzzer, 10);
    delay(150);
    digitalWrite(buzzer, LOW); // Sus
    delay(150);
  }
  else {
    // --- GÜVENLİ (YEŞİL + SESSİZ) ---
    digitalWrite(green, HIGH);
    digitalWrite(buzzer, LOW); // Tamamen sus
    delay(100);
  }
}