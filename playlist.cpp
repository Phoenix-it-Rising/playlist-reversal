#include "playlist.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

namespace playlist {

std::vector<std::string> load_from_file(const std::string& path) {
    std::vector<std::string> out;
    std::ifstream f(path);
    if (!f) {
        std::cerr << "Failed to open playlist file: " << path << "\n";
        return out;
    }
    std::string line;
    while (std::getline(f, line)) {
        // Trim minimal whitespace: remove leading/trailing spaces, tabs, CR/LF
        auto l = line.find_first_not_of(" \t\r\n");
        auto r = line.find_last_not_of(" \t\r\n");
        if (l == std::string::npos || r == std::string::npos) continue;
        out.push_back(line.substr(l, r - l + 1));
    }
    return out;
}

void reverse_in_place(std::vector<std::string>& tracks) {
    size_t i = 0;
    size_t j = tracks.empty() ? 0 : tracks.size() - 1;
    while (i < j) {
        std::swap(tracks[i], tracks[j]);
        ++i; --j;
    }
}

void play(const std::string& trackPath) {
    // Placeholder for your playback function; just print for now.
    std::cout << "Playing: " << trackPath << "\n";
}

} // namespace playlist
