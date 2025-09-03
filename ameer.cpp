#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

void exportGFXorSWF(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inFile(inputFilePath, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Could not open input file: " << inputFilePath << std::endl;
        return;
    }

    inFile.seekg(285, std::ios::beg);
    if (inFile.fail()) {
        std::cerr << "Error: Failed to seek to offset 285 in input file." << std::endl;
        inFile.close();
        return;
    }

    uint32_t gfxFileSize;
    inFile.read(reinterpret_cast<char*>(&gfxFileSize), sizeof(uint32_t));
    if (inFile.fail()) {
        std::cerr << "Error: Failed to read GFX/SWF file size." << std::endl;
        inFile.close();
        return;
    }

    std::vector<char> gfxData(gfxFileSize);
    inFile.read(gfxData.data(), gfxFileSize);
    if (inFile.fail()) {
        std::cerr << "Error: Failed to read GFX/SWF file data." << std::endl;
        inFile.close();
        return;
    }

    uint32_t extraDataSize;
    inFile.read(reinterpret_cast<char*>(&extraDataSize), sizeof(uint32_t));
    if (inFile.fail()) {
        std::cerr << "Error: Failed to read ExtraData size." << std::endl;
        inFile.close();
        return;
    }
    std::ofstream outFile(outputFilePath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Could not open output file: " << outputFilePath << std::endl;
        inFile.close();
        return;
    }

    outFile.write(gfxData.data(), gfxFileSize);
    if (outFile.fail()) {
        std::cerr << "Error: Failed to write GFX/SWF data to output file." << std::endl;
    }
    else {
        std::cout << "Successfully exported GFX/SWF to: " << outputFilePath << std::endl;
    }

    inFile.close();
    outFile.close();
}

void importGFXorSWF(const std::string& inputUexpFilePath, const std::string& inputGfxFilePath, const std::string& outputUexpFilePath) {
    std::ifstream gfxFile(inputGfxFilePath, std::ios::binary | std::ios::ate);
    if (!gfxFile) {
        std::cerr << "Error: Could not open GFX/SWF file: " << inputGfxFilePath << std::endl;
        return;
    }

    std::streamsize gfxFileSize = gfxFile.tellg();
    gfxFile.seekg(0, std::ios::beg);

    std::vector<char> gfxData(gfxFileSize);
    gfxFile.read(gfxData.data(), gfxFileSize);
    if (gfxFile.fail()) {
        std::cerr << "Error: Failed to read GFX/SWF file data." << std::endl;
        gfxFile.close();
        return;
    }
    gfxFile.close();

    std::ifstream inUexpFile(inputUexpFilePath, std::ios::binary | std::ios::ate);
    if (!inUexpFile) {
        std::cerr << "Error: Could not open input .uexp file: " << inputUexpFilePath << std::endl;
        return;
    }

    std::streamsize uexpSize = inUexpFile.tellg();
    inUexpFile.seekg(0, std::ios::beg);
    std::vector<char> uexpData(uexpSize);
    inUexpFile.read(uexpData.data(), uexpSize);
    if (inUexpFile.fail()) {
        std::cerr << "Error: Failed to read .uexp file data." << std::endl;
        inUexpFile.close();
        return;
    }
    inUexpFile.close();

    std::vector<char> newUexpData;
    newUexpData.reserve(285 + sizeof(uint32_t) + gfxFileSize + sizeof(uint32_t));

    newUexpData.insert(newUexpData.end(), uexpData.begin(), uexpData.begin() + 285);

    uint32_t newGfxFileSize = static_cast<uint32_t>(gfxFileSize);
    newUexpData.insert(newUexpData.end(), reinterpret_cast<char*>(&newGfxFileSize), reinterpret_cast<char*>(&newGfxFileSize) + sizeof(uint32_t));

    newUexpData.insert(newUexpData.end(), gfxData.begin(), gfxData.end());

    size_t extraDataSizeOffset = 285 + sizeof(uint32_t) + gfxFileSize;
    if (extraDataSizeOffset + sizeof(uint32_t) <= uexpSize) {
        newUexpData.insert(newUexpData.end(), uexpData.begin() + extraDataSizeOffset, uexpData.end());
    }
    else {
        std::cerr << "Warning: ExtraData size or data could not be copied due to insufficient .uexp file size." << std::endl;
    }

    std::ofstream outUexpFile(outputUexpFilePath, std::ios::binary);
    if (!outUexpFile) {
        std::cerr << "Error: Could not open output .uexp file: " << outputUexpFilePath << std::endl;
        return;
    }

    outUexpFile.write(newUexpData.data(), newUexpData.size());
    if (outUexpFile.fail()) {
        std::cerr << "Error: Failed to write new .uexp file." << std::endl;
    }
    else {
        std::cout << "Successfully imported GFX/SWF into new .uexp file: " << outputUexpFilePath << std::endl;
    }

    outUexpFile.close();
}

int main() {
    std::cout << "AmeerXoshnaw UEXP SWF Export Import for Kingdom Hearts 3\n";
    std::cout << "1. Export GFX/SWF from .uexp\n";
    std::cout << "2. Import GFX/SWF to .uexp\n";
    std::cout << "Select an option (1 or 2): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        std::string inputUexpPath, outputGfxPath;
        std::cout << "Enter the path to the input .uexp file: ";
        std::getline(std::cin, inputUexpPath);
        std::cout << "Enter the path for the output .gfx or .swf file: ";
        std::getline(std::cin, outputGfxPath);

        exportGFXorSWF(inputUexpPath, outputGfxPath);
    }
    else if (choice == 2) {
        std::string inputUexpPath, inputGfxPath, outputUexpPath;
        std::cout << "Enter the path to the original .uexp file: ";
        std::getline(std::cin, inputUexpPath);
        std::cout << "Enter the path to the edited .gfx or .swf file: ";
        std::getline(std::cin, inputGfxPath);
        std::cout << "Enter the path for the output .uexp file: ";
        std::getline(std::cin, outputUexpPath);

        importGFXorSWF(inputUexpPath, inputGfxPath, outputUexpPath);
    }
    else {
        std::cerr << "Invalid option selected. Please choose 1 or 2." << std::endl;
    }

    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}