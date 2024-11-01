# Physical Computing "PopPW"
📌 Project นี้เป็นส่วนหนึ่งในรายวิชา PHYSICAL COMPUTING 06016409 ภาคเรียนที่ 1 ปีการศึกษา 2567\
คณะเทคโนโลยีสารสนเทศ สาขาเทคโนโลยีสารสนเทศ สถาบันเทคโนโลยีพระจอมเกล้าเจ้าคุณทหารลาดกระบัง

## บทคัดย่อ
“โครงงาน PopPW” เป็นการพัฒนาเกมเพื่อผ่อนคลายความเครียดสำหรับนักศึกษาที่เรียนวิชา Physical Computing\
โดยมีแนวคิดในการนำเทคโนโลยีมาประยุกต์ใช้ในการสร้างเกมที่สนุกสนานและมีประโยชน์ เกมนี้มีลักษณะ คล้ายกับเกม PopCat\
แต่มีการพัฒนาระบบเพิ่มเติม สามารถกดคลิ๊กได้ผ่าน Website และกดผ่าน Switch บนตัว Board\
โดยค่าของคะแนนที่ได้จะมีการเชื่อมโยงกัน โครงงานยังมีการเผยแพร่โค้ดโปรแกรมเพื่อให้ผู้สนใจสามารถนำไปศึกษาและพัฒนาต่อยอดได้\
ผ่าน Github repository ซึ่งเป็นการส่งเสริมการแบ่งปันความรู้และพัฒนาชุมชนผู้พัฒนาเกมต่อไป

## ภาพรวมวงจร
> ![Circuit](https://github.com/zenkoub/PC-PopPW/blob/3cebd1051ed2abb545242101dc01bb4e3d68098e/circuitComponents/Circuit.png "Circuit")

## อุปกรณ์ที่ใช้งาน
* #### Arduino UNO R4 Wi-Fi
> ![Arduino Uno Screenshot](https://github.com/zenkoub/PC-PopPW/blob/63904f5d601fd48dbd01d3925087302760309e19/circuitComponents/ArduinoUNOR4WiFi.png "Arduino UNO R4 Wi-Fi")

* #### Breadboard
> ![Breadboardd Screenshot](https://github.com/zenkoub/PC-PopPW/blob/63904f5d601fd48dbd01d3925087302760309e19/circuitComponents/Breadboard.png "Breadboard")

* #### Passive Buzzer       
> ![Buzzer Screenshot](https://github.com/zenkoub/PC-PopPW/blob/63904f5d601fd48dbd01d3925087302760309e19/circuitComponents/PassiveBuzzer.png "Passive Buzzer")

* #### Switch Button
> ![Button Screenshot](https://github.com/zenkoub/PC-PopPW/blob/63904f5d601fd48dbd01d3925087302760309e19/circuitComponents/SwitchButton.png "Switch Button")

* #### 20x4 LCD Panel
> ![(LCD](https://github.com/zenkoub/PC-PopPW/blob/3cebd1051ed2abb545242101dc01bb4e3d68098e/circuitComponents/LCD.png "LCD")

* #### I2C Adapter
> ![(ky-008) i2c Screenshot](https://github.com/zenkoub/PC-PopPW/blob/3cebd1051ed2abb545242101dc01bb4e3d68098e/circuitComponents/I2C_Adapter.png "I2C Adapter")

* #### Jumper Wires
> ![Kwire Screenshot](https://github.com/zenkoub/PC-PopPW/blob/3cebd1051ed2abb545242101dc01bb4e3d68098e/circuitComponents/JumperWires.png "Wire")

* #### Resistor
> ![resistor Screenshot](https://github.com/zenkoub/PC-PopPW/blob/3cebd1051ed2abb545242101dc01bb4e3d68098e/circuitComponents/Resistor.png "Resistor")

## Poster
![Poster Show](https://github.com/zenkoub/PC-PopPW/blob/63904f5d601fd48dbd01d3925087302760309e19/Poster/PosterPopPW.png "png Poster")
[Poster](https://github.com/zenkoub/PC-PopPW/blob/5a164542471b24d45939dc8b442a7a700a66216b/Poster/Poster.pdf "pdf")

### Clip VDO แนะนำโปรเจกต์
[YouTube](https://youtu.be/D-wrWCKwDfg?si=71cXJXo3C85lzNu7 "Physical Computing - Project 1/2567 : PopPW")

## Library ที่ใช้งาน
```c++
#include <Keypad.h>
```

## การตั้งค่าตัวแปรและ Pin
```c++
#define SIZE 4

const byte LIGHT_PIN = A0;
const byte BUTTON_PIN = 2;
const byte LASER_PIN = 3;
const byte BUZZER_PIN = 13;
char TEXT[SIZE][SIZE] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
const byte COLS[SIZE] = {8, 7, 6, 5};
const byte ROWS[SIZE] = {12, 11, 10, 9};
char pass[SIZE] = {'A', '6', '8', '#'};
bool toggle = false;
bool detect = false;
short checkPass = 0;
Keypad myKey = Keypad(makeKeymap(TEXT), ROWS, COLS, SIZE, SIZE);
```

## ฟังก์ชันที่สำคัญ
* ฟังก์ชันการเปิดปิด Laser ด้วย Push Button
```c++
if (digitalRead(BUTTON_PIN) == HIGH && !toggle) {
    toggle = !toggle;
    Serial.println("Switch On");
    digitalWrite(LASER_PIN, HIGH);
  } else if (digitalRead(BUTTON_PIN) == HIGH && toggle) {
    toggle = !toggle;
    digitalWrite(LASER_PIN, LOW);
    Serial.println("Switch Off");
  }
  delay(150);
  Serial.println(analogRead(LIGHT_PIN));
  if (analogRead(LIGHT_PIN) > 550) {
    detect = true;
  }
  ```
* ฟังก์ชันการเปิดใช้งาน Keypad
```c++
if (myKey.getKey() == '*')
```
* ฟังก์ชันการรับรหัสผ่านจาก Keypad
  * ในที่นี้ รหัสผ่านที่ใช้ในการปิดเสียง Buzzer คือ "A68#"
```c++
for (short i = 0; i < SIZE; i++) {
    tone(BUZZER_PIN, 500);
    if (myKey.waitForKey() == pass[i]) {
        checkPass++;
        tone(BUZZER_PIN, 700);
    } else {
        checkPass = 0;
        tone(BUZZER_PIN, 2000);
        i = 0;
    }
}
```

## สมาชิกผู้จัดทำ
| รหัสนักศึกษา | ชื่อ - นามสกุล |
| -------- | ------- |
| 66070024 | นายคู่บุญ กฤตเนติทัศน์ |
| 66070065 | นายณัฐวิชช์ พิพัฒน์จิรกุล |
| 66070070 | นายทนันทน์สรณ์ ศิริรัตน์ |
| 66070110 | นางสาวเบญญาภา ยมภักดี |
