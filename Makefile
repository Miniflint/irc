INC_DIR	:= ./incs
SRC_DIR	:= ./srcs
OBJ_DIR	:= ./objs
SRCS	:= main.cpp
SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS	:= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
FLAGS	:= -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)
CC		:= /usr/bin/g++

TARGET	:= ircs

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ_DIR) $(OBJS)
	$(CC) $(FLAGS)  $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: re fclean clean all