
import pandas as pd
import matplotlib.pyplot as plt

# Read CSV produced by --bench mode
DF = pd.read_csv('playlist_reverse_runtime_cpp.csv')
DF['avg_ms'] = DF['avg_us'] / 1000.0
DF['stdev_ms'] = DF['stdev_us'] / 1000.0

plt.figure(figsize=(8,5))
plt.errorbar(DF['n'], DF['avg_ms'], yerr=DF['stdev_ms'], fmt='o-', capsize=6,
             color='#1f77b4', label='Average runtime (±σ)')
plt.title('Playlist reversal: runtime vs n (C++)')
plt.xlabel('Playlist size n (tracks)')
plt.ylabel('Runtime (ms)')
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig('playlist_reverse_runtime_cpp.png', dpi=150)
print('Wrote playlist_reverse_runtime_cpp.png')
