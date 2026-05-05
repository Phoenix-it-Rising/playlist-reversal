
#pragma once
#include <string>
#include <vector>

namespace playlist {

// Load playlist from a text file (one path per line)
std::vector<std::string> load_from_file(const std::string& path);

// Reverse order in place (two-pointer swap)
void reverse_in_place(std::vector<std::string>& tracks);

// Placeholder playback stub
void play(const std::string& trackPath);

} // namespace playlist
