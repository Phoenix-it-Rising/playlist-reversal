# In‑Place Playlist Order Reversal with Runtime Benchmarking

This project implements an **in‑place playlist reversal algorithm** that changes the playbackorder of tracks from:

1, 2, 3, 4, 5

to:

5, 4, 3, 2, 1

without allocating additional memory. The project also includes a benchmarking
tool to measure true runtime across varying playlist sizes.

---

## Features
- In‑place playlist order reversal (two‑pointer swap)
- Θ(n) time complexity and Θ(1) auxiliary space
- Command‑line interface for file‑based or direct input
- Runtime benchmarking with CSV output
- Python‑based runtime visualization (PNG or SVG)

---

## Algorithm Overview
The playlist is reversed using two indices:
- One pointer starts at the front of the playlist
- One pointer starts at the back
- Elements are swapped while the pointers move inward

This approach avoids copying the playlist and minimizes memory usage.

---

## Usage

### Reverse a playlist from a file
```bash
playlist-reversal playlist.txt
```

Reverse tracks passed on the command line
playlist-reversal --tracks song1.mp3 song2.mp3 song3.mp3 song4.mp3 song5.mp3

Runtime Benchmarking
Measure true runtime across different playlist sizes:
playlist-reversal --bench --trials 300 --sizes 500,1500,2500

This produces:
playlist_reverse_runtime_cpp.csv


Runtime Plot
The plot below shows average runtime (milliseconds) versus playlist size n,
with ±1σ error bars. The near‑linear trend confirms the expected Θ(n) runtime behavior.
playlist_reverse_runtime_cpp.png

Build Instructions (Single‑File MSVC)
Using Visual Studio Build Tools (Developer Command Prompt):
Shellcl /O2 /EHsc /std:c++17 src\main.cpp src\playlist.cpp /Fe:playlist-reversal.exe

Or in VS Code:

Terminal → Run Task → Build playlist-reversal (MSVC)
Press F5 to run


Notes

play() is a placeholder function; integrate real audio playback as needed.
Runtime variance reflects typical OS scheduling noise for micro‑benchmarks.


Complexity

Time Complexity: Θ(n)
Auxiliary Space: Θ(1)


License
MIT

---

```markdown
playlist_reverse_runtime_cpp.png
