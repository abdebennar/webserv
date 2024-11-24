#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

// Utility function to trim leading and trailing whitespace
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to check if a line starts with "server" and is valid
bool isServerStart(const std::string& line) {
    std::string trimmed = trim(line);
    return trimmed == "server" || trimmed == "server{" || trimmed == "server {";
}

// Function to check if a line starts with "location" and ends with "{"
bool isLocationStart(const std::string& line) {
    size_t pos = line.find("location");
    if (pos != std::string::npos) {
        size_t openBracket = line.find("{", pos);
        std::string path = line.substr(pos + 8, openBracket - (pos + 8));
        path.erase(0, path.find_first_not_of(" \t"));
        path.erase(path.find_last_not_of(" \t") + 1);
        return !path.empty() && openBracket == line.length() - 1;
    }
    return false;
}

int main() {
    std::ifstream configFile("test.conf"); // Replace with your file path
    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open config file.\n";
        return 1;
    }

    std::vector<std::map<std::string, std::string> > servers;
    std::map<std::string, std::string> currentServer;

    bool inServer = false;
    bool inLocation = false;

    int serverBracketCount = 0;  // Tracks `{` and `}` balance in `server` blocks
    int locationBracketCount = 0;  // Tracks `{` and `}` balance in `location` blocks

    std::string line;
    while (std::getline(configFile, line)) {
        line = trim(line);

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        // Handle start of a "server" block
        if (isServerStart(line)) 
		{
            if (inServer) {
                std::cerr << "Syntax Error: Nested server blocks are not allowed.\n";
                return 1;
            }
            inServer = true;

            // Check if `{` is present immediately
            if (line.find("{") != std::string::npos) {
                ++serverBracketCount;
            } else {
                // Expect `{` on the next line
                std::getline(configFile, line);
                line = trim(line);
                if (line != "{") {
                    std::cerr << "Syntax Error: Missing '{' after server declaration.\n";
                    return 1;
                }
                ++serverBracketCount;
            }
            continue;
        }

        // Handle start of a "location" block
        if (isLocationStart(line)) {
            if (!inServer) {
                std::cerr << "Syntax Error: Location block outside of server block.\n";
                return 1;
            }
            inLocation = true;
            ++locationBracketCount;
            continue;
        }

        // Handle closing brackets
        if (line == "}") {
            if (inLocation) {
                --locationBracketCount;
                if (locationBracketCount == 0) {
                    inLocation = false; // End of location block
                }
            } else if (inServer) {
                --serverBracketCount;
                if (serverBracketCount == 0) {
                    inServer = false; // End of server block
                    servers.push_back(currentServer); // Save completed server
                    currentServer.clear(); // Reset for next server
                }
            } else {
                std::cerr << "Syntax Error: Unmatched closing bracket.\n";
                return 1;
            }
            continue;
        }

        // Handle key-value pairs
        size_t semicolonPos = line.find(';');
        size_t firstspace = line.find_first_of(' ');
        if (semicolonPos != std::string::npos) {
            std::string key = trim(line.substr(0, firstspace));
            std::string value = trim(line.substr(firstspace + 1));

            if (key.empty() || value.empty()) {
				std::cout << key << " : " << value << std::endl;
                std::cerr << "Syntax Error: Malformed key-value pair.\n";
                return 1;
            }

            if (inServer) {
                currentServer[key] = value;
            } else if (inLocation) {
                currentServer["location_" + key] = value; // Prefix location settings
            } else {
                std::cerr << "Syntax Error: Key-value pair outside of valid block.\n";
                return 1;
            }
        } else {
            std::cerr << "Syntax Error: Missing ';' at the end of the line.\n";
            return 1;
        }
    }

    // Final checks for unmatched brackets
    if (serverBracketCount != 0) {
        std::cerr << "Syntax Error: Unmatched brackets in server block.\n";
        return 1;
    }
    if (locationBracketCount != 0) {
        std::cerr << "Syntax Error: Unmatched brackets in location block.\n";
        return 1;
    }

    configFile.close();

    // Print parsed servers
    for (size_t i = 0; i < servers.size(); ++i) {
        std::cout << "Server " << i + 1 << ":\n";
        for (std::map<std::string, std::string>::iterator it = servers[i].begin(); it != servers[i].end(); ++it) {
            std::cout << "  " << it->first << ": " << it->second << "\n";
        }
    }

    return 0;
}
