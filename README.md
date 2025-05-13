### Concurrency hash solving project
This project uses a semaphore (shared memory space) to store hashing data

Multiple processes can compete to solve the hash and store the result in the semaphore

The project uses a custom non cryptographic hash function

### How to run
```bash
# The first process will create and init the semaphore
# Then it will start to solve the hash data
# Here is an example of the first process running with a BOARD_SIZE of 3
$> make
$> ./worker -h
# -d is debug mode : it will print the hash value and the nonce at every step
usage: ./worker [-d] [-h]
$> ./worker
{ worker_id: 1675, shm_fd: 3, first: 1, board_address : 0x104690000 }
Board element 0: value=133224369533559, solved=0, solver_id=0, nonce=0, hash=0x00000000
Board element 1: value=30219719685878, solved=0, solver_id=0, nonce=0, hash=0x00000000
Board element 2: value=47924507749822, solved=0, solver_id=0, nonce=0, hash=0x00000000
Worker 1675: Solving hash for value 133224369533559
Worker 1675: Found nonce 277939868 for value 133224369533559, hash(133224647473427): 0xFF29E882 (4280936578) in 0.911936 seconds
Worker 1675: Solving hash for value 47924507749822
Worker 1675: Found nonce 392526340 for value 47924507749822, hash(47924900276162): 0xFFF3527D (4294136445) in 0.473808 seconds
Worker 1675: Solving hash for value 30219719685878
Worker 1675: Found nonce 1284578711 for value 30219719685878, hash(30221004264589): 0xFF64D134 (4284797236) in 0.178484 seconds
Results:
Worker 1675 solved 3 hashes
```

```bash
# The clean_shm and hash_checker are here for debug purposes
# The clean_shm will remove the semaphore manually
# The hash_checker will check if the hash is correct
$> ./hash_checker 7601024695107
Hash of 7601024695107 is: 0xffff36b4 (4294915764)
Hash validate: 1
```