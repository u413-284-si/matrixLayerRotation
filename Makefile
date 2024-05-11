
NAME := rotateMatrix

CXX := c++
CXXFLAGS = -Wall -Werror -Wextra -O -g
COMPILE = $(CXX) $(CXXFLAGS) -c
RM := rm -fr

OBJ_DIR := obj

SRC = 	main.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: %.cpp 	
	$(COMPILE) $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

.PHONY: clean
clean:
	$(RM) $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
