
#include "playlist.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using clock_type = std::chrono::high_resolution_clock;

// --------------------- Usage ---------------------
static void print_usage() {
    std::cout
        << "Usage:\n"
        << "  playlist-reversal <playlist.txt>\n"
        << "  or: playlist-reversal --tracks <song1> <song2> ...\n"
        << "\nBenchmark (CSV):\n"
        << "  playlist-reversal --bench [--trials N] [--sizes 500,1500,2500]\n";
}

// --------------------- Sizes parser ---------------------
static std::vector<int> parse_sizes(const std::string& s) {
    std::vector<int> out;
    std::stringstream ss(s);
    std::string tok;
    while (std::getline(ss, tok, ',')) {
        try { out.push_back(std::stoi(tok)); } catch (...) {}
    }
    if (out.empty()) out = { 500, 1500, 2500 };
    return out;
}

// --------------------- Helper to synthesize playlists (no lambda) ---------------------
static std::vector<std::string>
make_synth_playlist(int n, std::mt19937& rng,
                    std::uniform_int_distribution<int>& lenDist,
                    std::uniform_int_distribution<int>& chDist) {
    std::vector<std::string> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
        int L = lenDist(rng);
        std::string s;
        s.reserve(L);
        for (int k = 0; k < L; ++k) {
            s.push_back(char('a' + chDist(rng)));
        }
        v.push_back(s + ".mp3");
    }
    return v;
}

// --------------------- Benchmark & CSV ---------------------
static void bench_reverse_csv(int trials, const std::vector<int>& sizes) {
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> lenDist(5, 20);
    std::uniform_int_distribution<int> chDist(0, 25);

    std::ofstream csv("playlist_reverse_runtime_cpp.csv");
    if (!csv) {
        std::cerr << "Failed to open playlist_reverse_runtime_cpp.csv for writing\n";
        return;
    }
    csv << "n,avg_us,stdev_us,min_us,max_us,trials\n";

    for (int n : sizes) {
        std::vector<double> us;
        us.reserve(trials);

        for (int t = 0; t < trials; ++t) {
            // synthesize n tracks
            auto tracks = make_synth_playlist(n, rng, lenDist, chDist);

            // time in-place reversal
            auto t0 = clock_type::now();
            playlist::reverse_in_place(tracks);
            auto t1 = clock_type::now();

            double dt = std::chrono::duration<double, std::micro>(t1 - t0).count();
            us.push_back(dt);
        }

        // stats
        double sum = 0.0; for (double x : us) sum += x;
        double avg = sum / us.size();

        double var = 0.0; for (double x : us) var += (x - avg) * (x - avg);
        var /= us.size();
        double stdev = std::sqrt(var);

        auto mm = std::minmax_element(us.begin(), us.end());
        double mn = *mm.first, mx = *mm.second;

        // write CSV row
        csv << n << "," << std::fixed << std::setprecision(6)
            << avg << "," << stdev << ","
            << mn << "," << mx << "," << trials << "\n";

        // console
        std::cout << "n=" << n
                  << " avg="   << (avg   / 1000.0) << " ms"
                  << " stdev=" << (stdev / 1000.0) << " ms"
                  << " min="   << (mn    / 1000.0) << " ms"
                  << " max="   << (mx    / 1000.0) << " ms\n";
    }

    std::cout << "Wrote playlist_reverse_runtime_cpp.csv\n";
}

// --------------------- main ---------------------
int main(int argc, char** argv) {
    using namespace playlist;

    if (argc < 2) {
        print_usage();
        return 0;
    }

    // Benchmark mode
    if (std::string(argv[1]) == "--bench") {
        int trials = 300;
        std::vector<int> sizes = { 500, 1500, 2500 };

        for (int i = 2; i < argc; ++i) {
            std::string a = argv[i];
            if (a == "--trials" && i + 1 < argc) {
                trials = std::stoi(argv[++i]);
            } else if (a == "--sizes" && i + 1 < argc) {
                sizes = parse_sizes(argv[++i]);
            }
        }

        bench_reverse_csv(trials, sizes);
        return 0;
    }

    // Normal mode: file vs --tracks
    std::vector<std::string> tracks;

    if (std::string(argv[1]) == "--tracks") {
        for (int i = 2; i < argc; ++i) tracks.emplace_back(argv[i]);
    } else {
        tracks = load_from_file(argv[1]);
    }

    if (tracks.empty()) {
        std::cerr << "No tracks loaded.\n";
        return 1;
    }

    std::cout << "Original order (" << tracks.size() << "):\n";
    for (const auto& t : tracks) std::cout << "  " << t << "\n";

    reverse_in_place(tracks);

    std::cout << "\nReversed order:\n";
    for (const auto& t : tracks) std::cout << "  " << t << "\n";

    std::cout << "\nPlaying in reversed order...\n";
    for (const auto& t : tracks) {
        play(t); // stub; plug your actual playback here
    }

    return 0;
}
