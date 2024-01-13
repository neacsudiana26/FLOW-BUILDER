#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int CountParagraphs(const string &content, const regex &pattern) {
    sregex_iterator iter(content.begin(), content.end(), pattern);
    sregex_iterator end;

    int paragraphCount = 0;

    for (; iter != end; ++iter) {
        ++paragraphCount;
    }

    return paragraphCount;
}

int main() {
    // Open the input file
    ifstream inputFile("Output.txt");

    if (!inputFile.is_open()) {
        cout << "Unable to open the input file." << endl;
        return 1;
    }

    // Read the entire content of the file into a string
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Close the input file
    inputFile.close();

    // Construct the regular expression pattern
    string patternString = "\\*\\*\\*[^\\*]*\\*\\*\\*";
    regex pattern(patternString);

    // Count how many paragraphs match the pattern
    int paragraphCount = CountParagraphs(content, pattern);

    cout << "Number of paragraphs matching the pattern: " << paragraphCount << endl;

    // Rest of your code...
    // Note: The rest of your existing code has been omitted for brevity.

    return 0;
}