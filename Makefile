###########################################################################
#### SOURCES

SRC_FOLDER	= srcs/

SRC_FILES	= main.c mlx_init.c parse_file.c check_map.c fill_struct.c clean_all.c \
parse_colors.c utils.c init_struct.c fill_map.c

BUILD = build/


OBJ_FILES	= $(addprefix $(BUILD),$(SRC_FILES:%.c=%.o))
OBJ_FILES_BONUS = $(addprefix $(SRC_FOLDER_BONUS), $(SRC_FILES_BONUS:%.c=%.o))

###########################################################################
#### ARGUMENTS

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Werror -Wextra  -g3

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)libft.a
INCLUDE		= 
INCLUDE_BONUS = 
INCLUDE_PATH = includes/
MLX_PATH	= mlx/
MLX_INCLUDE = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

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
	@echo "$(YELLOW)Compilation de $*$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(LIBFT_PATH) -I/usr/include -I$(MLX_PATH) -c $< -o $@

all : $(NAME)

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

.PHONY : all clean fclean re
