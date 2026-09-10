import time
import multiprocessing

def prime_sieve(limit=5000000):
    primes = [True] * limit
    p = 2
    while p * p < limit:
        if primes[p]:
            for i in range(p * p, limit, p):
                primes[i] = False
        p += 1
    return sum(primes[2:])

def run_benchmark(threads):
    start = time.time()
    processes = []
    for _ in range(threads):
        p = multiprocessing.Process(target=prime_sieve)
        processes.append(p)
        p.start()
    for p in processes:
        p.join()
    print(f"Threads: {threads} | Time: {time.time() - start:.2f} s")

if __name__ == '__main__':
    for n in [1, 2, 4, 8, 16, 32]:
        for i in range(3):
            run_benchmark(n)
