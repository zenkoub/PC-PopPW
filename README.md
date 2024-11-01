# Physical Computing "PopPW"💥
    📌 Project นี้เป็นส่วนหนึ่งในรายวิชา PHYSICAL COMPUTING 06016409 ภาคเรียนที่ 1 ปีการศึกษา 2567
    คณะเทคโนโลยีสารสนเทศ สาขาเทคโนโลยีสารสนเทศ สถาบันเทคโนโลยีพระจอมเกล้าเจ้าคุณทหารลาดกระบัง

## บทคัดย่อ
        “โครงงาน PopPW” เป็นการพัฒนาเกมเพื่อผ่อนคลายความเครียดสำหรับนักศึกษาที่เรียนวิชา Physical Computing
    โดยมีแนวคิดในการนำเทคโนโลยีมาประยุกต์ใช้ในการสร้างเกมที่สนุกสนานและมีประโยชน์ เกมนี้มีลักษณะ คล้ายกับเกม PopCat
    แต่มีการพัฒนาระบบเพิ่มเติม สามารถกดคลิกได้ผ่าน Website และกดผ่าน Switch บนตัว Board โดยค่าของคะแนนที่ได้
    จะมีการเชื่อมโยงกัน โครงงานยังมีการเผยแพร่โค้ดโปรแกรมเพื่อให้ผู้สนใจสามารถนำไปศึกษาและพัฒนาต่อยอดได้ 
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
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiS3.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
```

## ฟังก์ชั่นการเชื่อมต่อ MQTT
* Arduino Side
```c++
int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Connecting to SSID: ");
    Serial.println(WIFI_SSID);
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(10000);
  }

void connectToMQTT() {
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);
  mqtt.onMessage(messageHandler);

  Serial.print("Connecting to MQTT broker");
  while (!mqtt.connect(MQTT_CLIENT_ID)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.println("Connected to MQTT broker!");

  mqtt.subscribe(subscription_TOPIC);
  Serial.println("Subscribed to topic: " + String(subscription_TOPIC));
}
```
* Web Server Side
```js
script.src = "https://unpkg.com/mqtt/dist/mqtt.min.js";

script.onload = () => {
  const client = mqtt.connect("ws://broker.hivemq.com:8000/mqtt");
  const topic = "/test/roblox";

  client.on("connect", () => {
    console.log("Connected to HiveMQ WebSocket broker");
    client.subscribe(topic, (err) => {
      if (err) {
        console.error("Subscription error:", err);
      } else {
        console.log(`Subscribed to topic: ${topic}`);
```

## ฟังก์ชันที่สำคัญ
* ฟังก์ชันการกดปุ่มเพิ่มคะแนน
```c++
void loop() {
  mqtt.loop();
  // Read the current state of the button
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && lastButtonState == LOW) {
    // Button pressed, load and display the pressed shape
    loadOriginalShape();
    displayShape();

    // Increment score
    score++;
    lcd.setCursor(7, 2); // Position for score
    lcd.print(score);

    sendToMQTT();

    // Play pop sound
    tone(buzzerPin, 1000, 200); // Tone at 1000Hz for 200ms
  } else if (buttonState == LOW && lastButtonState == HIGH) {
    // Button released, revert to original shape
    loadPressedShape();
    displayShape();
  }

  // Update lastButtonState to the current state
  lastButtonState = buttonState;
}
  ```
* ฟังก์ชัน Publish-Subscribe ผ่านบอร์ด
```C++
void sendToMQTT() {
  StaticJsonDocument<128> jsonDoc;
  jsonDoc["type"] = "increment";
  jsonDoc["from"] = "board";
  jsonDoc["value"] = score;

  char messageBuffer[128];
  serializeJson(jsonDoc, messageBuffer);

  mqtt.publish(subscription_TOPIC, messageBuffer);
  Serial.println("Published JSON to MQTT: " + String(messageBuffer));
}

void messageHandler(String &topic, String &payload) {
  Serial.print("Received message on topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  Serial.println(payload);

  StaticJsonDocument<128> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, payload);

  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }

  if (jsonDoc["type"] == "increment" && jsonDoc["from"] == "web") {
    int receivedScore = jsonDoc["value"];
    score = receivedScore;

    // Update LCD with the new score
    lcd.setCursor(7, 2);
    lcd.print("   ");  // Clear previous score
    lcd.setCursor(7, 2);
    lcd.print(score);

    Serial.print("Updated score from web: ");
    Serial.println(score);
  }
}
```
* ฟังก์ชัน Publish-Subscribe ผ่านเว็บไซต์
```js
client.on("message", (topic, message) => {
    console.log(`Received message: ${message.toString()} on topic: ${topic}`);
    const value = JSON.parse(message.toString());
    if (value.from == "board") {
      score = value.value;
      updateScore();
      img.src = swappedSrc;
      setTimeout(() => {
        img.src = originalSrc;
      }, 500);
    }
  });

window.publishMessage = () => {
    score++;
    updateScore();

    client.publish(
      topic,
      JSON.stringify({ type: "increment", from: "web", value: score }),
      (err) => {
        if (err) {
          console.error("Publish error:", err);
        } else {
          console.log("Message published:", {
            type: "increment",
            from: "web",
            value: score,
          });
        }
      }
    );
  };
```

## สมาชิกผู้จัดทำ
| รหัสนักศึกษา | ชื่อ - นามสกุล |
| -------- | ------- |
| 66070024 | นายคู่บุญ กฤตเนติทัศน์ |
| 66070065 | นายณัฐวิชช์ พิพัฒน์จิรกุล |
| 66070070 | นายทนันทน์สรณ์ ศิริรัตน์ |
| 66070110 | นางสาวเบญญาภา ยมภักดี |
