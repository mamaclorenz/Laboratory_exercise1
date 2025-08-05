#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;
using namespace std;

void listAllFiles(const fs::path& dirPath) {
    cout << "Files in directory: " << dirPath << "\n";
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        cout << entry.path().filename() << "\n";
    }
}

void listFilesByExtension(const fs::path& dirPath) {
    string ext;
    cout << "Enter file extension (e.g., .txt): ";
    cin >> ext;
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.path().extension() == ext) {
            cout << entry.path().filename() << "\n";
        }
    }
}

void listFilesByPattern(const fs::path& dirPath) {
    string pattern;
    cout << "Enter pattern (e.g., test): ";
    cin >> pattern;
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.path().filename().string().find(pattern) != string::npos) {
            cout << entry.path().filename() << "\n";
        }
    }
}

void listFiles(const fs::path& dirPath) {
    int choice;
    cout << "\n[1] List All Files\n[2] List by Extension\n[3] List by Pattern\nChoice: ";
    cin >> choice;
    switch (choice) {
        case 1: listAllFiles(dirPath); break;
        case 2: listFilesByExtension(dirPath); break;
        case 3: listFilesByPattern(dirPath); break;
        default: cout << "Invalid choice.\n";
    }
}

void createDirectory() {
    string dirName;
    cout << "Enter new directory name: ";
    cin >> dirName;
    if (fs::exists(dirName)) {
        cout << "Error: Directory already exists.\n";
    } else {
        fs::create_directory(dirName);
        cout << "Directory created successfully.\n";
    }
}

void changeDirectory(fs::path& currentPath) {
    string newPath;
    cout << "Enter path to change to: ";
    cin >> newPath;
    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        currentPath = newPath;
        cout << "Changed directory to: " << currentPath << "\n";
    } else {
        cout << "Error: Invalid directory path.\n";
    }
}

void mainMenu() {
    fs::path currentPath = fs::current_path();
    int choice;
    do {
        cout << "\n--- Directory Management System ---\n";
        cout << "Current Directory: " << currentPath << "\n";
        cout << "[1] List Files\n[2] Create Directory\n[3] Change Directory\n[4] Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: listFiles(currentPath); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(currentPath); break;
            case 4: cout << "Exiting program...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 4);
}

int main() {
    mainMenu();
    return 0;
}
