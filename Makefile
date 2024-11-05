# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 14:50:48 by tchow-so          #+#    #+#              #
#    Updated: 2024/10/28 09:13:38 by tchow-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
# NAMES & PATHS                                                                #
# ============================================================================ #

NAME		= $(NAME_SERVER) $(NAME_CLIENT)
NAME_SERVER	= server
NAME_CLIENT	= client

BONUS		= $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
NAME_SERVER_BONUS	= server_bonus
NAME_CLIENT_BONUS	= client_bonus

SRC_SERVER	= server.c
SRC_CLIENT	= client.c
SRC_UTILS	= utils.c
SRC_SERVER_BONUS	= server_bonus.c
SRC_CLIENT_BONUS	= client_bonus.c client_handler_bonus.c

BUILD_DIR	= .build
OBJS_SERVER 	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_SERVER:.c=.o)))
OBJS_CLIENT	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_CLIENT:.c=.o)))
OBJS_UTILS	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_UTILS:.c=.o)))
OBJS_SERVER_BONUS 	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_SERVER_BONUS:.c=.o)))
OBJS_CLIENT_BONUS	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_CLIENT_BONUS:.c=.o)))

LIBFT_DIR	= libft
LIBFT_ARC	= $(LIBFT_DIR)/libft.a


# ============================================================================ #
# COMPILER, FLAGS & COMMANDS                                                   #
# ============================================================================ #

CC	= cc
CFLAGS	= -Wall -Wextra -Werror
CFLAGS	+= -g

MAKE	= make -C

RM	= rm -rf
AR	= ar rcs
MKDIR	= mkdir -p


# ============================================================================ #
# RULES                                                                        #
# ============================================================================ #

##@ COMPILATION RULES

all: $(NAME)	## Compile minitalk

$(NAME): $(LIBFT_ARC) $(BUILD_DIR) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_UTILS)
	@printf "$(GRN)>> Generated object files$(RES)\n\n"
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(OBJS_UTILS) $(LIBFT_ARC) -o $(NAME_SERVER)
	@printf "$(GRN)>> Compiled Server$(RES)\n\n"
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(OBJS_UTILS) $(LIBFT_ARC) -o $(NAME_CLIENT)
	@printf "$(GRN)>> Compiled Client$(RES)\n\n"

bonus: $(BONUS)	## Compile minitalk with bonus features (required by subject)

$(BONUS): $(LIBFT_ARC) $(BUILD_DIR) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS) $(OBJS_UTILS)
	@printf "$(GRN)>> Generated object files (bonus version)$(RES)\n\n"
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(OBJS_UTILS) $(LIBFT_ARC) -o $(NAME_SERVER_BONUS)
	@printf "$(GRN)>> Compiled Server (bonus version)$(RES)\n\n"
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(OBJS_UTILS) $(LIBFT_ARC) -o $(NAME_CLIENT_BONUS)
	@printf "$(GRN)>> Compiled Client (bonus version)$(RES)\n\n"

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(RES)\n\n"

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_ARC):
	$(MAKE) $(LIBFT_DIR)
	@printf "$(GRN)>> Created Libft archive$(RES)\n\n"

##@ CLEAN-UP RULES

clean:	## Remove object files
	$(RM) $(BUILD_DIR)
	$(MAKE) $(LIBFT_DIR) clean
	@printf "$(GRN)>> Removed object files$(RES)\n\n"

fclean: clean	## Remove executable files
	$(RM) $(NAME) $(BONUS)
	@printf "$(GRN)>> Removed executable files$(RES)\n\n"
	$(MAKE) $(LIBFT_DIR) fclean
	@printf "$(GRN)>> Removed Libft archive$(RES)\n\n"

re: fclean all	## Purge and recompile


##@ HELP

help:	## Display this help info
	@awk 'BEGIN { \
		FS = ":.*##"; \
		printf "\n$(WHI_B)USAGE$(RES)\n\t$(YEL)make$(RES)$(CYA)\t \
		<target>$(RES)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
		printf "\t$(CYA_B)%-15s$(RES) %s\n", $$1, $$2 } \
		/^##@/ { printf "\n$(WHI_B)%s$(RES)\n", \
		substr($$0, 5) } ' Makefile
	@printf "\n"

.PHONY: all bonus clean fclean re help


# ============================================================================ #
# UTILS: SHELL FORMATTING                                                      #
# ============================================================================ #

# Reset to default
RES = \033[0m

# Regular text colors
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYA = \033[0;36m
WHI = \033[0;37m

# Bold text colors
RED_B = \033[1;31m
GRN_B = \033[1;32m
YEL_B = \033[1;33m
BLU_B = \033[1;34m
MAG_B = \033[1;35m
CYA_B = \033[1;36m
WHI_B = \033[1;37m