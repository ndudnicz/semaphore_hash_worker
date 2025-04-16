HASH_CHECKER = hash_checker
WORKER = worker
CC = gcc
CFLAGS = #-Werror -Wextra -Wall

# SOURCE FOLDERS ==============================================================#

SRC_DIR = src

# OBJECTS FOLDERS =============================================================#

OBJ_DIR_HASH_CHECKER = obj_hash_checker
OBJ_DIR_WORKER = obj_worker

# INCLUDES FOLDERS ============================================================#

PATH_INCLUDES = includes

# SOURCES LIST ================================================================#

SRC_WORKER = \
hash.c \
debug.c \
init_shm.c \
rand.c \
worker.c \

SRC_HASH_CHECKER = \
hash_checker.c \
hash.c \

# OBJECTS LIST ================================================================#

OBJ_WORKER = $(SRC_WORKER:%.c=obj_worker/%.o)
OBJ_HASH_CHECKER = $(SRC_HASH_CHECKER:%.c=obj_hash_checker/%.o)

# GENERIC RULES ===============================================================#

all: $(WORKER) $(HASH_CHECKER)

hash_checker: $(HASH_CHECKER)

clean:
	$(RM) $(OBJ_WORKER)
	$(RM) $(OBJ_HASH_CHECKER)

fclean: clean
	$(RM) $(WORKER)
	$(RM) $(HASH_CHECKER)

re: clean fclean all

$(HASH_CHECKER): $(OBJ_HASH_CHECKER)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ_HASH_CHECKER)

$(WORKER): $(OBJ_WORKER)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ_WORKER)

$(OBJ_DIR_HASH_CHECKER)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $< -I $(PATH_INCLUDES)

$(OBJ_DIR_WORKER)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $< -I $(PATH_INCLUDES)

-include $(OBJ_WORKER:.o=.d)
-include $(OBJ_HASH_CHECKER:.o=.d)
