### Concurrency hash solving project
This project uses a semaphore (shared memory space) to store hashing datas

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
{ worker_id: 11469, shm_fd: 3, first: 1, board_address : 0x102714000 }
Board element 0: value=110019521365287, solved=0, solver_id=0, nonce=0, hash=0x00000000
Board element 1: value=80143520188431, solved=0, solver_id=0, nonce=0, hash=0x00000000
Board element 2: value=7599560828455, solved=0, solver_id=0, nonce=0, hash=0x00000000
Worker 11469: Solving hash for value 80143520188431
Worker 11469: Found nonce 1499904107 for value 80143520188431, hash(80145020092538): 0xFF64D134 (4284797236) in 2.746249 seconds
Worker 11469: Solving hash for value 110019521365287
Worker 11469: Found nonce 837602410 for value 110019521365287, hash(110020358967697): 0xFFE1EC0F (4292996111) in 0.252060 seconds
Worker 11469: Solving hash for value 7599560828455
Worker 11469: Found nonce 1463866652 for value 7599560828455, hash(7601024695107): 0xFFFF36B4 (4294915764) in 1.654943 seconds
Results:
Worker 11469 solved 3 hashes
```

```bash
# The clean_shm and hash_checker are here for debug purposes
# The clean_shm will remove the semaphore manually
# The hash_checker will check if the hash is correct
$> ./hash_checker 7601024695107
Hash of 7601024695107 is: 0xffff36b4 (4294915764)
Hash validate: 1
```