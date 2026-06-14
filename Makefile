INC_DIR	:= ./incs
SRC_DIR	:= ./srcs
PAR_DIR	:= $(SRC_DIR)/parsing
OBJ_DIR	:= ./objs

VPATH	:= $(SRC_DIR):$(PAR_DIR)

SRCS	:= main.cpp

SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS	:= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:%.cpp=%.o)))

FLAGS	:= -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)
CC		:= /usr/bin/g++

TARGET	:= ft_irc

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ_DIR) $(OBJS)
	$(CC) $(FLAGS)  $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: re fclean clean all