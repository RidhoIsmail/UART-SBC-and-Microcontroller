#include <MPU9250.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16,2);
MPU9250 mpu;

int button1 = 2;
int button2 = 3;


// Variabel untuk menyimpan status tombol
int button1State = 0;
int button2State = 0;

int lastbutton1State = 0;
int lastbutton2State = 0;

bool Menu1 = false;
bool Menu2 = false;

void setup() {
  lcd.init();
  lcd.backlight();
  Wire.begin();
  lcd.print("  Welcome!!!!!");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("KOMPOR UPI!!!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("KREATIF!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("                             ");
  delay(200);
  lcd.setCursor(0, 1);
  lcd.print("INOVATIF!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("                             ");
  delay(200);
  lcd.setCursor(0, 1);
  lcd.print("PRODUKTIF!");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("                             ");
  lcd.setCursor(0, 1);
  lcd.print("                             ");
  lcd.setCursor(0, 0);
  lcd.print("Ridho Ismail N");
  lcd.setCursor(0, 1);
  lcd.print("AMK.004.24.17");
  delay(3000);
  // Inisialisasi pin tombol sebagai input
  pinMode(button1, INPUT); // Menggunakan resistor pull-up internal
  pinMode(button2, INPUT);
  // Tampilkan pesan awal
  
    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("Gagal terkoneksi, mohon periksa ulang alamat I2C");
            delay(5000);
        }
    }
  
  Menu();
  Serial.begin(9600);
}

void loop() {
  // Baca status tombol
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  
  // Jika tombol 1 ditekan, ubah status tampilan data
  if (button1State == HIGH) {
    tampil_data();
  }else if (button2State == HIGH && lastbutton2State == LOW){
    kirim_data(); 
  }
  // // Jika tampilan data diaktifkan, baca dan tampilkan nilai potensiometer
  // if(Menu1) {
  //   tampil_data();
  // }else if (Menu2){
  //   kirim_data();
  // }
  lastbutton1State = button1State;
  lastbutton2State = button2State;
}

void tampil_data(){
    lcd.setCursor(0, 1);
    lcd.print("                              ");
    lcd.setCursor(14,0);
    lcd.print("                             ");
    lcd.setCursor(0, 0);
    lcd.print("Nilai Gyroscope :");
    lcd.setCursor(0, 1);
    lcd.print(mpu.getGyroX(), 2);
    lcd.setCursor(5,1);
    lcd.print(",");
    lcd.setCursor(6,1);
    lcd.print(mpu.getGyroY(), 2);
    
}
void kirim_data(){
  lcd.setCursor(12,0);
  lcd.print("                             ");
//   // lcd.setCursor(0,1);
//   // lcd.print("                             ");
  lcd.setCursor(0,0);
  lcd.print("Data dikirim");
  lcd.setCursor(0,1);
  lcd.print("                                ");
  if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            Serial.print("[");
            Serial.print(mpu.getGyroX(), 3);
            Serial.print(",");
            Serial.print(mpu.getGyroY(), 3);
            Serial.print(",");
            Serial.print(mpu.getGyroZ(), 3);
            Serial.println("]");
            prev_ms = millis();
        }
    }
}
void Menu(){
  lcd.setCursor(0, 0);
  lcd.print("1.Tampilkan data");
  lcd.setCursor(0, 1);
  lcd.print("2.Kirim data    ");
}

