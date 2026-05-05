
import csv, os
from pathlib import Path

csv_file = Path('playlist_reverse_runtime_cpp.csv')
svg_file = Path('playlist_reverse_runtime_cpp.svg')

rows = []
with csv_file.open() as f:
    r = csv.DictReader(f)
    for line in r:
        rows.append({
            'n': int(line['n']),
            'avg_ms': float(line['avg_us'])/1000.0,
            'stdev_ms': float(line['stdev_us'])/1000.0
        })

ns  = [r['n'] for r in rows]
ys  = [r['avg_ms'] for r in rows]
ymin, ymax = min(ys), max(ys)
pad = (ymax - ymin) if ymax > ymin else 1.0
ymin = max(0.0, ymin - 0.05*pad)
ymax = ymax + 0.10*pad

W, H = 800, 500
ML, MR, MT, MB = 70, 20, 40, 60
CW, CH = W-ML-MR, H-MT-MB

def X(n):
    a, b = min(ns), max(ns)
    return ML + (n-a)*CW/((b-a) if b>a else 1)

def Y(v):
    return MT + CH - (v - ymin)*CH/((ymax-ymin) if ymax>ymin else 1)

svg = []
svg.append(f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}">')
svg.append('<style>.t{font-family:Segoe UI,Arial,sans-serif;font-size:12px}</style>')
svg.append(f'<text class="t" x="{W/2}" y="{MT-15}" text-anchor="middle" font-size="16">Playlist reversal: runtime vs n (C++)</text>')
# axes
svg.append(f'<line x1="{ML}" y1="{H-MB}" x2="{W-MR}" y2="{H-MB}" stroke="#000"/>')
svg.append(f'<line x1="{ML}" y1="{MT}" x2="{ML}" y2="{H-MB}" stroke="#000"/>')
svg.append(f'<text class="t" x="{W/2}" y="{H-20}" text-anchor="middle">Playlist size n (tracks)</text>')
svg.append(f'<text class="t" x="20" y="{H/2}" transform="rotate(-90,20,{H/2})" text-anchor="middle">Runtime (ms)</text>')

# ticks
for n in ns:
    x = X(n)
    svg.append(f'<line x1="{x}" y1="{H-MB}" x2="{x}" y2="{H-MB-6}" stroke="#000"/>')
    svg.append(f'<text class="t" x="{x}" y="{H-MB+18}" text-anchor="middle">{n}</text>')
for i in range(6):
    v = ymin + i*(ymax-ymin)/5.0
    y = Y(v)
    svg.append(f'<line x1="{ML}" y1="{y}" x2="{ML-6}" y2="{y}" stroke="#000"/>')
    svg.append(f'<text class="t" x="{ML-10}" y="{y+4}" text-anchor="end">{v:.3f}</text>')
    svg.append(f'<line x1="{ML}" y1="{y}" x2="{W-MR}" y2="{y}" stroke="#ccc" stroke-dasharray="3,3"/>')

# polyline + points
pts = []
for r in rows:
    x, y = X(r['n']), Y(r['avg_ms'])
    pts.append((x,y))
    svg.append(f'<circle cx="{x}" cy="{y}" r="4" fill="#1f77b4"/>')
svg.append(f'<polyline points="{' '.join(f"{x},{y}" for x,y in pts)}" fill="none" stroke="#1f77b4" stroke-width="2"/>')

# legend
svg.append(f'<rect x="{W-MR-160}" y="{MT}" width="150" height="40" fill="#fff" stroke="#000"/>')
svg.append(f'<line x1="{W-MR-150}" y1="{MT+20}" x2="{W-MR-120}" y2="{MT+20}" stroke="#1f77b4" stroke-width="2"/>')
svg.append(f'<circle cx="{W-MR-120}" cy="{MT+20}" r="4" fill="#1f77b4"/>')
svg.append(f'<text class="t" x="{W-MR-110}" y="{MT+24}">Average runtime</text>')

svg.append('</svg>')
svg_file.write_text('
'.join(svg), encoding='utf-8')
print(f'Wrote {svg_file}')
