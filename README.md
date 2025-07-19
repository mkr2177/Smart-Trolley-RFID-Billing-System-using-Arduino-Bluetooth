# 🛒 Smart Trolley RFID Billing System using Arduino + Bluetooth

An Arduino-based **RFID Smart Trolley System** designed for supermarkets or smart retail stores. This system automatically **adds/removes items**, calculates **total bills**, and communicates with a **Bluetooth app or terminal**.

## 🚀 Features

- ✅ Scan items using RFID cards
- ➕ Add or ❌ remove products using push buttons
- 📟 Real-time display of item name and total bill on 16x2 LCD
- 📲 Sends cart updates to a Bluetooth terminal/app (via HC-05)
- 🔄 Easily expandable with more items and RFID tags

---

## 🔧 Technologies & Components Used

| Component           | Description                          |
|---------------------|--------------------------------------|
| Arduino UNO         | Microcontroller                      |
| RC522 RFID Module   | For item scanning                    |
| HC-05 Bluetooth     | For wireless communication           |
| 16x2 LCD            | To display item & billing details    |
| Push Buttons (2)    | To Add and Remove items              |
| Breadboard + Wires  | Circuit connections                  |

---

## 📦 How It Works

1. 🛍️ Each product is assigned an RFID tag.
2. ✅ When scanned, LCD shows item name and prompts for Add/Remove.
3. 🔘 On button press:
   - **Add**: Adds to cart and updates total.
   - **Remove**: Deletes from cart and updates total.
4. 📡 The total and actions are also sent to a Bluetooth terminal (e.g., Serial Bluetooth Terminal app).


## 📸 Demo Screenshots

### 🖼️ App Preview

![Screenshot 1](Screenshot%20(1312).png)
![Screenshot 2](Screenshot%20(1313).png)
![Screenshot 3](Screenshot%20(1314).png)

