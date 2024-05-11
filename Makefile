
NAME := rotateMatrix
TEST := test

CXX := c++
CXXFLAGS = -Wall -Werror -Wextra -O -g
COMPILE = $(CXX) $(CXXFLAGS) -c
RM := rm -fr

OBJ_DIR := obj

SRC = 	main.cpp \
		checkInput.cpp \
		rotateMatrix.cpp \
		utilities.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

TEST_SRC =	test.cpp \
			checkInput.cpp \
			rotateMatrix.cpp \
			utilities.cpp

TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(TEST_SRC:.cpp=.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $@
	@printf "compilation successful [$@]\n"
	@printf "$@ created!\n"

$(TEST): $(OBJ_DIR) $(TEST_OBJ)
	@$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $@
	@printf "compilation successful [$@]\n"
	@printf "$@ created!\n"

$(OBJ_DIR)/%.o: %.cpp 	
	@$(COMPILE) $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

.PHONY: clean
clean:
	@$(RM) $(OBJ_DIR)
	@printf "removed dir $(OBJ_DIR)\n"

.PHONY: fclean
fclean: clean
	@$(RM) $(NAME)
	@printf "removed binary $(NAME)\n"

.PHONY: tclean
tclean: clean
	@$(RM) $(TEST)
	@printf "removed binary $(TEST)\n"

.PHONY: re
re: fclean all
