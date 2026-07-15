INC_DIR	:= ./incs
SRC_DIR	:= ./srcs
INI_DIR	:= $(SRC_DIR)/Class
SRV_DIR	:= $(INI_DIR)/Server
OBJ_DIR	:= ./objs
BON_DIR := ./bonus
BON_EX	:= $(BON_DIR)/ircbot

VPATH	:= $(SRC_DIR):$(INI_DIR):$(SRV_DIR)

SRCS	:= main.cpp
INITS	:= Channel.cpp Client.cpp
SRVS	:= Server.cpp handler.cpp events.cpp replyMsg.cpp channelUtils.cpp

SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRCS))
INI_FILES := $(addprefix $(INI_DIR)/, $(INITS))
SRV_FILES := $(addprefix $(SRV_DIR)/, $(SRVS))

OBJS	:=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:%.cpp=%.o))) \
			$(addprefix $(OBJ_DIR)/, $(notdir $(INITS:%.cpp=%.o))) \
			$(addprefix $(OBJ_DIR)/, $(notdir $(SRVS:%.cpp=%.o)))

FLAGS	:= -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)
CC		:= /usr/bin/g++

TARGET	:= ircserv

ifeq ($(OPTI),yes)
	FLAGS += -O3
endif

ifeq ($(DEBUG),yes)
	FLAGS += -g
endif

ifeq ($(HARD),yes)
	FLAGS += -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Winit-self -ansi -fno-elide-constructors -pedantic-errors
endif

all: $(TARGET)

bonus: $(TARGET)
	make -C $(BON_DIR)

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
	@if [ -f "$(BON_EX)" ]; then \
		$(MAKE) -C $(BON_DIR) fclean; \
	fi

re: fclean all

.PHONY: re fclean clean all
