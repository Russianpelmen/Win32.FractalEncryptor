#include "Common.hpp"

bool CryptFile(
    const std::string& FileNameForEncryption,
    cryptor::KEY_TYPE& KEY,
    const std::string& FILE_Extension
) {
    std::ifstream File(FileNameForEncryption, std::ios::binary | std::ios::ate);
    if (!File.is_open()) return EXIT_FAILURE;

    size_t fileSize = File.tellg();
    File.seekg(0, std::ios::beg);

    cryptor::p_BYTE BYTEArray = new cryptor::BYTE[fileSize];
    File.read(reinterpret_cast<char*>(BYTEArray), fileSize);
    File.close();

    cryptor::DATA_TYPE CryptData = cryptor::Crypt(KEY, BYTEArray, fileSize);

    std::ofstream Encfile(FileNameForEncryption + FILE_Extension, std::ios::binary);
    Encfile.write(reinterpret_cast<char*>(CryptData), fileSize);
    Encfile.close();

    delete[] BYTEArray;
    delete[] CryptData;

    return EXIT_SUCCESS;
}

bool DeCryptFile(
    const std::string& FileNameForDecryption,
    cryptor::KEY_TYPE& KEY,
    const std::string& FILE_Extension
) {
    std::ifstream File(FileNameForDecryption, std::ios::binary | std::ios::ate);
    if (!File.is_open()) return EXIT_FAILURE;

    size_t fileSize = File.tellg();
    File.seekg(0, std::ios::beg);

    cryptor::p_BYTE BYTEArray = new cryptor::BYTE[fileSize];
    File.read(reinterpret_cast<char*>(BYTEArray), fileSize);
    File.close();

    cryptor::DATA_TYPE DECryptData = cryptor::DeCrypt(KEY, BYTEArray, fileSize);

    std::string outputFileName = cryptor::RemoweEX::RemoweEX(FileNameForDecryption, FILE_Extension);
    std::ofstream DeEncfile(outputFileName, std::ios::binary);
    DeEncfile.write(reinterpret_cast<char*>(DECryptData), fileSize);
    DeEncfile.close();

    delete[] BYTEArray;
    delete[] DECryptData;

    return EXIT_SUCCESS;
}