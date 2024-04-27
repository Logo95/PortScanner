#pragma once
#include <string>
#include <vector>

// Класс ValidCheck предназначен для проверки и хранения конфигурационных параметров приложения.
class ValidCheck {
public:
    // Конструктор анализирует аргументы командной строки.
    ValidCheck(int argc, char* argv[]);
    // Проверяет, валидны ли параметры.
    bool isValid() const;
    // Возвращает IP-адрес.
    std::string getIpAddress() const;
    // Возвращает начальный порт.
    int getStartPort() const;
    // Возвращает конечный порт.
    int getEndPort() const;

private:
    // Проверяет корректность IP-адреса.
    bool validateIpAddress(const std::string& ip) const;
    // Проверяет корректность номера порта.
    bool validatePort(const std::string& portStr) const;

    bool validConfig; // Флаг валидности конфигурации.
    std::string ipAddress; // IP-адрес для сканирования.
    int startPort; // Начальный порт диапазона.
    int endPort; // Конечный порт диапазона.
};
