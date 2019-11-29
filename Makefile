# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 23:20:41 by sleonard          #+#    #+#              #
#    Updated: 2019/11/29 14:21:00 by sleonard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
# MAIN
# ============================================================================ #

MAIN_FILES =					\
		main.c					\
		error.c					\
		exit_clean.c			\

MAIN_DIR =						\
	$(SRC_DIR)

MAIN_OBJ = $(addprefix $(OBJ_DIR), $(MAIN_FILES:.c=.o))

# ============================================================================ #
# HOOKS
# ============================================================================ #

HOOKS_FILES =					\
		event_processing.c		\
		moves.c					\

HOOKS_DIR =						\
	$(SRC_DIR)hooks/

HOOKS_OBJ = $(addprefix $(OBJ_DIR), $(HOOKS_FILES:.c=.o))

# ============================================================================ #
# OPEN_CL
# ============================================================================ #

OPEN_CL_FILES =					\
		cl_files_parser.c		\
		cl_init.c				\
		cl_render.c				\
		cl_memory_management.c	\

OPEN_CL_DIR =					\
	$(SRC_DIR)open_cl/

OPEN_CL_OBJ = $(addprefix $(OBJ_DIR), $(OPEN_CL_FILES:.c=.o))

# ============================================================================ #
# DEBUG
# ============================================================================ #

DEBUG_FILES =					\
		debug_print_objects.c	\
		debug_utils.c			\

DEBUG_DIR =						\
	$(SRC_DIR)debug/

DEBUG_OBJ = $(addprefix $(OBJ_DIR), $(DEBUG_FILES:.c=.o))

# ============================================================================ #
# INIT
# ============================================================================ #

INIT_FILES =					\
		init.c					\
		init_scene.c			\

INIT_DIR =						\
	$(SRC_DIR)init/

INIT_OBJ = $(addprefix $(OBJ_DIR), $(INIT_FILES:.c=.o))

# ============================================================================ #
# MATH UTILS
# ============================================================================ #

MATH_UTILS_FILES =				\
		math_utils.c			\
		rotation.c				\
		vector_math.c			\
		vector_math2.c			\

MATH_UTILS_DIR =				\
	$(SRC_DIR)math_utils/

MATH_UTILS_OBJ = $(addprefix $(OBJ_DIR), $(MATH_UTILS_FILES:.c=.o))

# ============================================================================ #
# PARSING
# ============================================================================ #

PARSING_FILES =					\
		camera_getter.c			\
		light_getter.c			\
		object_getter.c			\
		object_parsing_utils.c	\
		parsing_loops.c			\
		scene_config_parser.c	\

PARSING_DIR =					\
	$(SRC_DIR)parsing/

PARSING_OBJ = $(addprefix $(OBJ_DIR), $(PARSING_FILES:.c=.o))

# ============================================================================ #
# RENDER
# ============================================================================ #

RENDER_FILES =					\
		render.c				\

RENDER_DIR =					\
	$(SRC_DIR)render/

RENDER_OBJ = $(addprefix $(OBJ_DIR), $(RENDER_FILES:.c=.o))

# ============================================================================ #
# SDL UTILS
# ============================================================================ #

SDL_UTILS_FILES =				\
		sdl_loop.c				\

SDL_UTILS_DIR =					\
	$(SRC_DIR)SDL_utils/

SDL_UTILS_OBJ = $(addprefix $(OBJ_DIR), $(SDL_UTILS_FILES:.c=.o))

# ============================================================================ #
# BUILD FRACTOL
# ============================================================================ #

NAME =							\
	RTv1

OBJ =							\
	$(MAIN_OBJ)					\
	$(INIT_OBJ)					\
	$(DEBUG_OBJ)				\
	$(OPEN_CL_OBJ)				\
	$(HOOKS_OBJ)				\
	$(MATH_UTILS_OBJ)			\
	$(PARSING_OBJ)				\
	$(RENDER_OBJ)				\
	$(SDL_UTILS_OBJ)			\

LIBFT =							\
	./libft/libft.a

FT_PRINTF = 					\
	./libft/ft_printf/

OBJ_DIR =						\
	./temp/

SRC_DIR =						\
	./sources/

COMPILE_FLAGS = 				\
	-Wall -Wextra -Werror -O2

INCLUDES =						\
	./includes/

SDL_DIR =						\
	./SDL2_libs/

SDL_INCL =								\
	$(SDL_DIR)SDL2.framework/Headers	\

COMPILE = clang $(COMPILE_FLAGS) -I $(INCLUDES) -I $(LIBFT_INC) -I $(SDL_INCL)

OPEN_CL_FRAMEWORK = -framework OpenCL

SDL2_FRAMEWORK = -rpath ./SDL2_libs -F$(SDL_DIR) -framework SDL2

RTV1_LIBS = -L $(LIBFT_DIR) -lft -L $(FT_PRINTF) -lftprintf $(SDL2_FRAMEWORK) $(OPEN_CL_FRAMEWORK)

all : update $(NAME)

update:
	@git submodule init
	@git submodule update

$(NAME) : $(LIBFT) $(MINILIBX_LIB) $(OBJ_DIR) $(OBJ)
	$(COMPILE) $(RTV1_LIBS) $(OBJ) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(MAIN_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(OPEN_CL_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(DEBUG_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(INIT_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(HOOKS_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(MATH_UTILS_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(PARSING_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(RENDER_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(SDL_UTILS_DIR)%.c
	$(COMPILE) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re : fclean $(NAME)

# ============================================================================ #
# 						LIBFT
# ============================================================================ #

LIBFT_DIR =				\
	./libft/			\

LIBFT_INC = 			\
	./libft/includes/	\

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@make printf -C $(LIBFT_DIR)
