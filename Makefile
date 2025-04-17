HASH_CHECKER = hash_checker
WORKER = worker
CLEAN_SHM = clean_shm
CC = gcc
CFLAGS = -Werror -Wextra -Wall

# SOURCE FOLDERS ==============================================================#

SRC_DIR = src

# OBJECTS FOLDERS =============================================================#

OBJ_DIR_HASH_CHECKER = obj_hash_checker
OBJ_DIR_WORKER = obj_worker
OBJ_DIR_CLEAN_SHM = obj_clean_shm

# INCLUDES FOLDERS ============================================================#

PATH_INCLUDES = includes

# SOURCES LIST ================================================================#

SRC_WORKER = \
hash.c \
debug.c \
init_shm.c \
rand.c \
worker.c \
solve_hashes.c \
benchmark.c \

SRC_HASH_CHECKER = \
hash_checker.c \
hash.c \

SRC_CLEAN_SHM = \
clean_shm.c \

# OBJECTS LIST ================================================================#

OBJ_WORKER = $(SRC_WORKER:%.c=obj_worker/%.o)
OBJ_HASH_CHECKER = $(SRC_HASH_CHECKER:%.c=obj_hash_checker/%.o)
OBJ_CLEAN_SHM = $(SRC_CLEAN_SHM:%.c=obj_clean_shm/%.o)

# GENERIC RULES ===============================================================#

all: $(WORKER) $(HASH_CHECKER) $(CLEAN_SHM)

#hash_checker: $(HASH_CHECKER)
#
#clean_shm: $(CLEAN_SHM)

clean:
	$(RM) $(OBJ_WORKER)
	$(RM) $(OBJ_HASH_CHECKER)
	$(RM) $(OBJ_CLEAN_SHM)

fclean: clean
	$(RM) $(WORKER)
	$(RM) $(HASH_CHECKER)
	$(RM) $(CLEAN_SHM)

re: clean fclean all

$(HASH_CHECKER): $(OBJ_HASH_CHECKER)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ_HASH_CHECKER)

$(WORKER): $(OBJ_WORKER)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ_WORKER)

$(CLEAN_SHM): $(OBJ_CLEAN_SHM)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ_CLEAN_SHM)

$(OBJ_DIR_HASH_CHECKER)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $< -I $(PATH_INCLUDES)

$(OBJ_DIR_WORKER)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $< -I $(PATH_INCLUDES)

$(OBJ_DIR_CLEAN_SHM)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $< -I $(PATH_INCLUDES)

-include $(OBJ_WORKER:.o=.d)
-include $(OBJ_HASH_CHECKER:.o=.d)
