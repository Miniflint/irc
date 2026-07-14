INC_DIR		:= ./incs
SRC_DIR		:= ./srcs
CLASS_DIR	:= $(SRC_DIR)/Class
OBJ_DIR		:= ./objs

VPATH	:= $(SRC_DIR):$(CLASS_DIR)

SRCS	:= main.cpp
CLASS	:= Bot.cpp

SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRCS))
INI_FILES := $(addprefix $(CLASS_DIR)/, $(CLASS))

OBJS	:=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:%.cpp=%.o))) \
			$(addprefix $(OBJ_DIR)/, $(notdir $(CLASS:%.cpp=%.o)))

FLAGS	:= -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)
CC		:= /usr/bin/g++

TARGET	:= ircbot

ifeq ($(OPTI),yes)
	FLAGS += -O3
endif

ifeq ($(HARD),yes)
	FLAGS += -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Winit-self -ansi -fno-elide-constructors -pedantic-errors
endif

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
