void setup() {
  // Налаштування серійного порту
  Serial.begin(9600);
  // Додатковий вивід для підтвердження початку роботи
  Serial.println("Arduino ready");
}

void loop() {
  // Перевірка, чи є вхідні дані
  if (Serial.available() > 0) {
    // Отримання повідомлення
    String message = Serial.readString();

    // Видалення символів нового рядка (\n або \r)
    message.trim();

    // Додавання "modified" без переходу на новий рядок
    message = message + " modified";

    // Відправка зміненого повідомлення назад
    Serial.println(message);

    // Додатковий вивід для підтвердження надсилання
    Serial.println("Message sent back to client");
  }
}
