#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN A0  // Changed from 9 to A0 to avoid conflict with HC-05
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Bluetooth Communication
#define BTSerial Serial  // Uses Hardware Serial

// LCD Pin Configuration (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Push Button Pins for Add & Remove
#define ADD_BUTTON 8
#define REMOVE_BUTTON 9

// Item Structure
struct Item {
  String name;
  String rfid;
  int price;
};

const int itemCount = 2;
Item itemList[itemCount] = {
  {"Salt", "73 62 02 29", 100},
  {"Milk", "03 06 DB 13", 50},
};

int totalBill = 0;
String scannedItems[10];
int scannedCount = 0;

void setup() {
  BTSerial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  lcd.begin(16, 2);
  lcd.print("Smart Trolley");
  delay(2000);
  lcd.clear();

  pinMode(ADD_BUTTON, INPUT_PULLUP);
  pinMode(REMOVE_BUTTON, INPUT_PULLUP);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String tagID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    tagID += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    tagID += String(mfrc522.uid.uidByte[i], HEX);
  }
  tagID.toUpperCase();
  tagID.trim();

  bool itemFound = false;
  for (int i = 0; i < itemCount; i++) {
    if (tagID == itemList[i].rfid) {
      itemFound = true;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Scan: " + itemList[i].name);
      lcd.setCursor(0, 1);
      lcd.print("A:Add R:Remove");

      bool decisionMade = false;
      while (!decisionMade) {
        if (digitalRead(ADD_BUTTON) == LOW) {
          totalBill += itemList[i].price;
          scannedItems[scannedCount++] = tagID;
          BTSerial.println(itemList[i].name + " Added! Rs " + String(itemList[i].price));

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(itemList[i].name + " Added!");

          decisionMade = true;
        } else if (digitalRead(REMOVE_BUTTON) == LOW) {
          if (isItemScanned(tagID)) {
            totalBill -= itemList[i].price;
            removeScannedItem(tagID);
            BTSerial.println(itemList[i].name + " Removed!");

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(itemList[i].name + " Removed!");
          } else {
            BTSerial.println("No item to remove.");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("No item to remove");
          }
          decisionMade = true;
        }
      }
      break;
    }
  }

  if (!itemFound) {
    BTSerial.println("Unknown RFID: " + tagID);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unknown Item");
  }

  BTSerial.println("Total Bill: Rs " + String(totalBill));
  lcd.setCursor(0, 1);
  lcd.print("Total: Rs " + String(totalBill));

  delay(2000);
}

void removeScannedItem(String tagID) {
  for (int i = 0; i < scannedCount; i++) {
    if (scannedItems[i] == tagID) {
      for (int j = i; j < scannedCount - 1; j++) {
        scannedItems[j] = scannedItems[j + 1];
      }
      scannedCount--;
      break;
    }
  }
}

bool isItemScanned(String tagID) {
  for (int i = 0; i < scannedCount; i++) {
    if (scannedItems[i] == tagID) {
      return true;
    }
  }
  return false;
}
