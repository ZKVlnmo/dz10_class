#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cstdint>
#include <thread>
using namespace std;

class BitReader {
private:
    std::ifstream file;
    unsigned char buffer;
    int bitCount; // Сколько бит осталось в буфере

public:
    BitReader(const std::string& filename) : buffer(0), bitCount(0) {
        file.open(filename, std::ios::binary);
    }

    // Возвращает true, если бит успешно прочитан. Результат пишется в bit.
    bool readBit(int& bit) {
        if (bitCount == 0) {
            char c;
            if (!file.get(c)) {
                return false; // Конец файла или ошибка
            }
            buffer = static_cast<unsigned char>(c);
            bitCount = 8;
        }

        // Извлекаем старший бит (от 7-го к 0-му)
        bit = (buffer >> (bitCount - 1)) & 1;
        bitCount--;
        return true;
    }

    bool is_open() const { return file.is_open(); }
};

void threadFunc(int ind, int n, int k) {
    int st = ((n * ind) / k);
    int en = ((n * (ind+1)) / k);

    
}

int main() {
    string filePath = "input.txt";
    int fileSize = filesystem::file_size(filePath)*8;
    cout << "Размер файла: " << fileSize << '\n';
    BitReader reader(filePath);
    if (!reader.is_open()) return 1;

    int bit;
    size_t count = 0;

    while (reader.readBit(bit) && count < fileSize) {
        std::cout << bit;
        count++;
    }
    std::cout << std::endl;

    return 0;
}
