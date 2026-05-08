# 14 - Concurrency: Threading, Multiprocessing, and Asyncio
#
# Python has 3 concurrency models — pick the right one:
#   threading        — I/O-bound tasks (network, disk) — limited by the GIL
#   multiprocessing  — CPU-bound tasks (heavy computation) — true parallelism
#   asyncio          — many concurrent I/O tasks — single thread, very efficient

import time
import threading
import multiprocessing
import asyncio
import concurrent.futures

def banner(title): print(f"\n{'='*10} {title} {'='*10}")


# =========================================================
# THREADING — good for I/O-bound work
# =========================================================
banner("Threading")

def download(url, delay):
    print(f"  Start download: {url}")
    time.sleep(delay)               # simulates I/O wait
    print(f"  Done:  {url}")

# Sequential — takes sum of all delays
start = time.perf_counter()
download("file_a.zip", 0.3)
download("file_b.zip", 0.2)
download("file_c.zip", 0.1)
print(f"Sequential: {time.perf_counter()-start:.2f}s")

# Threaded — all run concurrently, takes only the longest delay
start = time.perf_counter()
threads = [
    threading.Thread(target=download, args=("file_a.zip", 0.3)),
    threading.Thread(target=download, args=("file_b.zip", 0.2)),
    threading.Thread(target=download, args=("file_c.zip", 0.1)),
]
for t in threads: t.start()
for t in threads: t.join()         # wait for all to finish
print(f"Threaded:   {time.perf_counter()-start:.2f}s")


# --- Thread safety with a Lock ---
banner("Lock (thread safety)")
counter = 0
lock    = threading.Lock()

def increment(n):
    global counter
    for _ in range(n):
        with lock:                  # only one thread at a time
            counter += 1

counter = 0
ts = [threading.Thread(target=increment, args=(10000,)) for _ in range(5)]
for t in ts: t.start()
for t in ts: t.join()
print(f"Counter (expected 50000): {counter}")


# =========================================================
# MULTIPROCESSING — good for CPU-bound work
# =========================================================
banner("Multiprocessing")

def cpu_task(n):
    return sum(x**2 for x in range(n))

nums = [500_000, 600_000, 400_000, 700_000]

start = time.perf_counter()
results_seq = [cpu_task(n) for n in nums]
print(f"Sequential: {time.perf_counter()-start:.2f}s")

start = time.perf_counter()
with multiprocessing.Pool() as pool:
    results_par = pool.map(cpu_task, nums)
print(f"Parallel:   {time.perf_counter()-start:.2f}s")

assert results_seq == results_par


# =========================================================
# CONCURRENT.FUTURES — higher-level API for both models
# =========================================================
banner("concurrent.futures")

def fetch(url):
    time.sleep(0.1)     # simulated I/O
    return f"data from {url}"

urls = [f"https://api.example.com/item/{i}" for i in range(8)]

# ThreadPoolExecutor for I/O
start = time.perf_counter()
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as ex:
    futures = {ex.submit(fetch, url): url for url in urls}
    for future in concurrent.futures.as_completed(futures):
        print(f"  {future.result()}")
print(f"ThreadPool: {time.perf_counter()-start:.2f}s")


# =========================================================
# ASYNCIO — best for many concurrent I/O tasks in one thread
# =========================================================
banner("Asyncio")

async def async_fetch(session_id, delay):
    print(f"  Fetch {session_id} started")
    await asyncio.sleep(delay)      # yield control while "waiting"
    print(f"  Fetch {session_id} done")
    return f"result_{session_id}"

async def main():
    # Run all fetches concurrently
    tasks = [
        asyncio.create_task(async_fetch(i, 0.1 * (i % 3 + 1)))
        for i in range(6)
    ]
    results = await asyncio.gather(*tasks)
    print(f"All results: {results}")

start = time.perf_counter()
asyncio.run(main())
print(f"Asyncio: {time.perf_counter()-start:.2f}s")
