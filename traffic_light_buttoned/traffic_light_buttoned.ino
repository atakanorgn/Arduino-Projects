const int green = 9;
const int yellow = 10;
const int red = 11;

void setup() {
  // Initialise etmek için
pinMode(green, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(red, OUTPUT);

}

void loop() {
  // Kodun döngü kısmı

 digitalWrite(green, HIGH);
 delay(3000);
 digitalWrite(green, LOW);

 digitalWrite(yellow, HIGH);
 delay(2000);
 digitalWrite(yellow, LOW);

 digitalWrite(red, HIGH);
 delay(3000);
 digitalWrite(red, LOW);

}
