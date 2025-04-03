#include <WiFi.h>
#include <HTTPClient.h>

// Замените на данные вашей Wi-Fi сети
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

void setup() {
    Serial.begin(115200);
    
    // Подключение к Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Подключение к Wi-Fi");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    
    Serial.println();
    Serial.println("Подключено к Wi-Fi!");
    
    // Отправка HTTP GET запроса
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Укажите URL вашего сервера
        http.begin("http://example.com"); // Замените на ваш URL
        int httpResponseCode = http.GET();

        // Проверка кода ответа
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode); // Код ответа
            Serial.println(response); // Ответ сервера
        } else {
            Serial.print("Ошибка при отправке запроса: ");
            Serial.println(httpResponseCode);
        }
        
        http.end(); // Завершить соединение
    }
}

void loop() {
    // Здесь можно добавлять код для периодической работы
}
