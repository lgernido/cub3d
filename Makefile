###########################################################################
#### SOURCES

SRC_FOLDER	= srcs/


PARSING_DIR = parsing/
PARSING_FILES = $(addprefix $(PARSING_DIR), parse_file.c check_map.c fill_struct.c clean_all.c \
parse_colors.c utils.c init_struct.c fill_map.c to_cub.c)

SRC_FILES	= main.c exec_init.c clean_exit.c drawing_utils.c handle_keyboard.c\
						draw_line.c exec_solo.c raycaster.c mouse.c mini_map_init.c\
						draw_mini_map.c verify_texture.c $(PARSING_FILES)

BUILD = build/


OBJ_FILES	= $(addprefix $(BUILD),$(SRC_FILES:%.c=%.o))

OBJ_FILES_BONUS = $(addprefix $(SRC_FOLDER_BONUS), $(SRC_FILES_BONUS:%.c=%.o))

DEPS = $(OBJ_FILES:.o=.d)

###########################################################################
#### ARGUMENTS

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
OBJFLAGS = -MMD -MP

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)libft.a
INCLUDE		= 
INCLUDE_BONUS = 
INCLUDE_PATH = includes/
MLX_PATH	= mini_libx/
MLX_INCLUDE = mini_libx/libmlx_Linux.a -L/usr/lib/X11 -lXext -lX11 -lm -lz

RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
RESET	=	\033[0m

###########################################################################
#### RULES

$(NAME): $(OBJ_FILES) $(INCLUDES)
	@make -C $(LIBFT_PATH) --no-print-directory -s
	@make -C $(MLX_PATH) --no-print-directory -s
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(MLX_INCLUDE) $(LIBFT) -o $(NAME)
	@echo "$(MAGENTA)Les fichiers modifiés sont: $?$(RESET)"
	@echo "$(GREEN)Compilation réussie !$(RESET)"

build/%.o: srcs/%.c
	@mkdir -p ${BUILD}
	@mkdir -p $(BUILD)/$(PARSING_DIR)
	@echo "$(YELLOW)Compilation de $*$(RESET)"
	@$(CC) $(CFLAGS) $(OBJFLAGS) -I$(INCLUDE_PATH) -I$(LIBFT_PATH) -I/usr/include -I$(MLX_PATH) -c $< -o $@

-include $(DEPS)

all : $(NAME)

bonus : all

clean :
	@rm -rf ${BUILD}
	@rm -f *.o ${OBJ_FILES_BONUS}
	@make clean -C $(LIBFT_PATH) --no-print-directory -s
	@make clean -C $(MLX_PATH) --no-print-directory -s
	@echo "$(CYAN) Nettoyage des fichiers intermédiaires $(RESET)"

fclean : clean
	@rm -f ${NAME}
	@make fclean -C $(LIBFT_PATH) --no-print-directory -s
	@echo "$(GREEN) Nettoyage terminé $(RESET)"

re : fclean all

.PHONY : all clean fclean re bonus
