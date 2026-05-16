import subprocess
import matplotlib.pyplot as plt


subprocess.run(['gcc', '-O2', 'pthread.c', '-o', 'matrix', '-lpthread'])

sizes = [100, 250, 500, 750, 1000, 1500, 2000, 2500]
threads = [1, 2, 4, 8, 16]
results = {}

for N in sizes:
    results[N] = []
    for t in threads:
        result = subprocess.run(['./matrix', str(N), str(t)], capture_output=True, text=True)
        _, _, time_ms = result.stdout.strip().split(',')
        results[N].append(float(time_ms))

plt.figure(figsize=(12, 8))

for t_idx, t in enumerate(threads):
    times = [results[N][t_idx] for N in sizes]
    plt.plot(sizes, times, 'o-', label=f'{t} потоков', linewidth=2, markersize=6)

plt.xlabel('Размер матрицы (N x N)')
plt.ylabel('Время выполнения (мс)')
plt.title('Зависимость времени умножения матриц от размера и количества потоков')
plt.legend(loc='upper left', bbox_to_anchor=(1, 1))
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig('thread.png', dpi=150, bbox_inches='tight')
plt.show()