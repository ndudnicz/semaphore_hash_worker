HASH_CHECKER = hash_checker
CC = gcc
CFLAGS = #-Werror -Wextra -Wall

# SOURCE FOLDERS ==============================================================#

SRC_DIR = .

# OBJECTS FOLDERS =============================================================#

OBJ_DIR = obj

# INCLUDES FOLDERS ============================================================#

PATH_INCLUDES = .

# SOURCES LIST ================================================================#

SRC = \
hash_checker.c \
hash.c \

# OBJECTS LIST ================================================================#

OBJ = $(SRC:%.c=obj/%.o)

# GENERIC RULES ===============================================================#

all: $(HASH_CHECKER)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(HASH_CHECKER)

re: clean fclean all

$(HASH_CHECKER): $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $< -I $(PATH_INCLUDES)

-include $(OBJ:.o=.d)
