#pragma once
#include <string>
#include <vector>

// ����� ValidCheck ������������ ��� �������� � �������� ���������������� ���������� ����������.
class ValidCheck {
public:
    // ����������� ����������� ��������� ��������� ������.
    ValidCheck(int argc, char* argv[]);
    // ���������, ������� �� ���������.
    bool isValid() const;
    // ���������� IP-�����.
    std::string getIpAddress() const;
    // ���������� ��������� ����.
    int getStartPort() const;
    // ���������� �������� ����.
    int getEndPort() const;

private:
    // ��������� ������������ IP-������.
    bool validateIpAddress(const std::string& ip) const;
    // ��������� ������������ ������ �����.
    bool validatePort(const std::string& portStr) const;

    bool validConfig; // ���� ���������� ������������.
    std::string ipAddress; // IP-����� ��� ������������.
    int startPort; // ��������� ���� ���������.
    int endPort; // �������� ���� ���������.
};
