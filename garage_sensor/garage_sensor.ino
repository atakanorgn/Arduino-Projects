// --- KARARLI PARK SENSÖRÜ (FİLTRELİ) ---

const int green = 3;
const int yellow = 5;
const int red = 7;
const int buzzer = 11; 

const int trigPin = 8;
const int echoPin = 9;

void setup() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // 1. Ölçüm Yap
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // --- FİLTRELEME BÖLÜMÜ ---
  // Eğer sensör hata verip 0 döndürdüyse veya çok saçma büyük bir sayıysa:
  // Bu ölçümü YOK SAY ve güvenli (Yeşil) modda kal.
  if (distance == 0 || distance > 300) {
     Serial.println("Hata: 0 okundu (Görmezden geliniyor)");
     distance = 999;
  } else {
     Serial.print("Mesafe: ");
     Serial.print(distance);
     Serial.println(" cm");
  }

  // Önce temizlik
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);

  // 2. Karar Mekanizması
  if (distance < 15) {
    // --- KIRMIZI ---
    digitalWrite(red, HIGH);
    analogWrite(buzzer, 10); // Sesi biraz arttırdım duyulsun diye
    delay(150);
    digitalWrite(buzzer, LOW);
    delay(150);
  }
  else if (distance < 23) {
    // --- SARI ---
    digitalWrite(yellow, HIGH);
    analogWrite(buzzer, 10);
    delay(400);
    digitalWrite(buzzer, LOW);
    delay(400);
  }
  else {
    // --- YEŞİL ---
    digitalWrite(green, HIGH);
    digitalWrite(buzzer, LOW);
  }
}