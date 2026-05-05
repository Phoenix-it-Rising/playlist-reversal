
# Playlist Reversal

Reverses the order of a playlist so tracks play as `5, 4, 3, 2, 1` instead of `1, 2, 3, 4, 5`.

## Usage
- From a file:
  ```
  playlist-reversal <playlist.txt>
  ```
- From command-line list:
  ```
  playlist-reversal --tracks song1.mp3 song2.mp3 song3.mp3 song4.mp3 song5.mp3
  ```
- Benchmark/timing + CSV output:
  ```
  playlist-reversal --bench --trials 300 --sizes 500,1500,2500
  ```
  This writes `playlist_reverse_runtime_cpp.csv` in the project folder.

## Plotting (Python)
Use either:
- `plot_csv_matplotlib.py` (requires `matplotlib` & `pandas`):
  ```
  python plot_csv_matplotlib.py
  ```
- `plot_csv_svg.py` (no external packages):
  ```
  python plot_csv_svg.py
  ```

## Build (single-file MSVC)
- VS Code: Terminal → Run Task → **Build playlist-reversal (MSVC)**, then F5 to run.
- Or Command Prompt in this folder:
  ```
  cl /O2 /EHsc /std:c++17 src\main.cpp src\playlist.cpp /Fe:playlist-reversal.exe
  ```

## Notes
- `play()` is a placeholder; integrate your real audio playback code.
- The reversal is in-place (two-pointer swap), Θ(n) time and Θ(1) aux space.
