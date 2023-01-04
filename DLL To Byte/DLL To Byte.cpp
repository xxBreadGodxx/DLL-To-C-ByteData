#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

int main()
{
    std::cout << "Enter the file path to the DLL: ";
    std::string filePath;
    std::getline(std::cin, filePath);

    std::vector<char> dllBytes;

    std::ifstream stream(filePath, std::ios::binary);
    if (stream)
    {
        stream.seekg(0, std::ios::end);
        std::streampos fileSize = stream.tellg();
        stream.seekg(0, std::ios::beg);

        dllBytes.resize(fileSize);
        stream.read(dllBytes.data(), fileSize);
    }

    // dllBytes now contains the contents of the DLL file as a std::vector<char>

    std::ofstream outputStream("dll_bytes.bin", std::ios::binary);
    if (outputStream)
    {
        outputStream.write(dllBytes.data(), dllBytes.size());
    }
    else
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }

    std::ofstream outputStream2("dll_bytes.txt", std::ios::out);
    if (outputStream2)
    {
        outputStream2 << "const char data[] = {\n";
        for (std::size_t i = 0; i < dllBytes.size(); ++i)
        {
            if (i % 12 == 0)
            {
                outputStream2 << "    ";
            }
            outputStream2 << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)dllBytes[i];
            if (i != dllBytes.size() - 1)
            {
                outputStream2 << ",";
            }
            if (i % 12 == 11)
            {
                outputStream2 << "\n";
            }
            else
            {
                outputStream2 << " ";
            }
        }
        outputStream2 << "};\n";
    }
    else
    {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}
