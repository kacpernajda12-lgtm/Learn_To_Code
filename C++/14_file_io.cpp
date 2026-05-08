// 14 - File I/O
// Read and write files using <fstream>.
// Always check whether the file opened before reading/writing.

#include <iostream>
#include <fstream>    // ifstream, ofstream, fstream
#include <sstream>    // stringstream (parse lines)
#include <string>
#include <vector>

struct Student {
    std::string name;
    int         age;
    double      grade;
};

// =========================================================
// WRITE — ofstream (output file stream)
// =========================================================
void writeTextFile(const std::string& path) {
    std::ofstream file(path);               // creates or truncates
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open " + path);
    }

    file << "Alice,20,9.2\n";
    file << "Bob,22,7.8\n";
    file << "Carol,21,8.5\n";
    file << "Dave,23,6.1\n";

    // file.close() is called automatically by destructor (RAII)
    std::cout << "Written to " << path << "\n";
}

// =========================================================
// READ LINE BY LINE — ifstream (input file stream)
// =========================================================
std::vector<Student> readCSV(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Cannot open " + path);

    std::vector<Student> students;
    std::string line;

    while (std::getline(file, line)) {         // read one line at a time
        if (line.empty()) continue;

        std::stringstream ss(line);            // parse CSV fields
        Student s;
        std::string token;

        std::getline(ss, s.name,  ',');
        std::getline(ss, token,   ','); s.age   = std::stoi(token);
        std::getline(ss, token,   ','); s.grade = std::stod(token);

        students.push_back(s);
    }
    return students;
}

// =========================================================
// APPEND — open with std::ios::app flag
// =========================================================
void appendToFile(const std::string& path, const Student& s) {
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) throw std::runtime_error("Cannot open " + path);
    file << s.name << "," << s.age << "," << s.grade << "\n";
    std::cout << "Appended " << s.name << "\n";
}

// =========================================================
// BINARY WRITE / READ
// =========================================================
void binaryDemo(const std::string& path) {
    // Write three ints as raw binary
    std::ofstream out(path, std::ios::binary);
    int data[] = {10, 20, 30};
    out.write(reinterpret_cast<char*>(data), sizeof(data));
    out.close();

    // Read them back
    std::ifstream in(path, std::ios::binary);
    int buf[3];
    in.read(reinterpret_cast<char*>(buf), sizeof(buf));
    std::cout << "Binary read: " << buf[0] << " " << buf[1] << " " << buf[2] << "\n";
}

// =========================================================
// SEEK — random access within a file
// =========================================================
void seekDemo(const std::string& path) {
    std::fstream file(path, std::ios::in | std::ios::out);
    if (!file) return;

    file.seekg(0, std::ios::end);                    // seek to end
    std::streampos size = file.tellg();              // get position = file size
    std::cout << "File size: " << size << " bytes\n";

    file.seekg(0, std::ios::beg);                    // rewind to start
    std::string first;
    std::getline(file, first);
    std::cout << "First line: " << first << "\n";
}

// =========================================================
int main() {
    const std::string csvPath    = "students.csv";
    const std::string binPath    = "data.bin";

    // Write
    writeTextFile(csvPath);

    // Append
    appendToFile(csvPath, {"Eve", 24, 9.9});

    // Read
    auto students = readCSV(csvPath);
    std::cout << "\n--- Students ---\n";
    for (const auto& s : students) {
        std::cout << s.name << " | age " << s.age << " | grade " << s.grade << "\n";
    }

    // Seek demo
    std::cout << "\n--- Seek ---\n";
    seekDemo(csvPath);

    // Binary
    std::cout << "\n--- Binary ---\n";
    binaryDemo(binPath);

    return 0;
}
