# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 12:28:57 by mmarinel          #+#    #+#              #
#    Updated: 2022/05/28 16:31:17 by mmarinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SAY = say
NORMINETTE = norminette -R CheckForbiddenSourceHeader
CC = @gcc
CFLAGS = -I -Wall -Werror -Wextra -pthread -fsanitize=address -static-libsan -g
#CFLAGS = -I -Wall -Werror -Wextra -pthread

MANDATORY_OBJS = $(shell find . -name "*.c" -print | grep -v bonus.c | sed 's/\.c/\.o/g')
BONUS_OBJS = $(shell find . -name "*.c" -print | grep -v mand | sed 's/\.c/\.o/g')


####################### NORMINETTE #########################
$(shell
	NORM_ERRS=$(norminette -R CheckForbiddenSourceHeader | grep Error: | wc -l);
	ifeq (test $NORM_ERRS -gt 1; echo $$?, 0) 
			norm_fail = $(shell echo $NORM_ERRS "Norm Errors found!")
	else ifeq (test $NORM_ERRS -gt 0; echo $$?, 0)
		norm_fail = $(shell echo $NORM_ERRS "Norm Error found!")
		final_msg = "My disappointment is immeasurable and my day is ruined"
		final_msg_voice = Karen
	else
		norm_success = $(shell echo "No Norm Errors found!")
		final_msg = "Good Job, GG, you are a piece of shit"
		final_msg_voice = Karen
	endif
)

####################### Unvoiced Makes #########################
all:
	@$(MAKE) .ADD_MANDATORY SAY="say -o /dev/null"
bonus:
	@$(MAKE) .ADD_BONUS SAY="say -o /dev/null"
norm:
	@$(MAKE) n SAY="say -o /dev/null"
clean:
	@$(MAKE) cl SAY="say -o /dev/null"
fclean:
	@$(MAKE) fcl SAY="say -o /dev/null"

####################### VOCAL ASSISTANT #########################
say: .ADD_MANDATORY
bonus_say: .ADD_BONUS
norm_say: n
clean_say: cl
fclean_say: fcl
re_say: fclean_say say
re_bonus_say: fclean_say bonus_say



####################### CORE #######################################
do_bonus: $(NAME)
do_mandatory: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
ifeq ($(SAY),"say -o /dev/null")
	@$(MAKE) norm
else
	@$(MAKE) norm_say
endif
	@printf "building the project...\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\033[0;32mBuild Done!\n"
	@$(SAY) -v "karen" -r 20 "minishell, Compiled"
	@$(SAY) -v "$(final_msg_voice)" -r 60 "$(final_msg)"

n:
	@printf "checking the norm...\n\n"
	@echo "\033[0;33m"
	@for LINE in $$(find . -name "*.c" -print); do \
		if [$$(norminette -R CheckForbiddenSourceHeader $$LINE | grep Error! | wc -l) -ge 1 ]; then \
			norminette $$LINE; \
			echo "\n"; \
		fi \
	done;
	@for LINE in $$(find . -name "*.c" -print); do \
		if [$$(cat $$LINE | grep '//' | wc -l) -ge 1 ]; then \
			echo "\033[0;35mYour code has comments \033[0;38m(human check is always needed!)"; \
			echo "\n"; \
			break; \
		fi \
	done;
	@echo "\033[0;31m$(norm_fail)"
	@echo "\033[0;32m$(norm_success)"
	@echo "\033[0;37m"
	@$(SAY) -v "karen" -r 20 $(norm_success) ""
	@$(SAY) -v "karen" -r 20 $(norm_fail) ""

cl:
	@printf "removing Object files...\n"
	@/bin/rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@printf "\033[0;35mObject files removed!\n"
	@echo "\033[0;37m"
	@$(SAY) -v "karen" -r 20 "minishell, Object files, Destroyed"

fcl: cl
	@printf "removing program executable...\n"
	@/bin/rm -f philo; /bin/rm -f philo_bonus
	@printf "\033[0;35mExecutable removed!\n"
	@echo "\033[0;37m"
	@$(SAY) -v "karen" -r 20 "minishell, Destroyed"

re: fclean all

re_bonus: fclean bonus

.ADD_MANDATORY:
	@printf "\033[0;36mMaking Mandatory part\n"
		@echo "\033[0;37m"
	@$(SAY) -v "karen" -r 20 "Making, Mandatory part"
	@$(MAKE) do_mandatory OBJS="$(MANDATORY_OBJS)" NAME="philo"

.ADD_BONUS:
	@printf "\033[1;36mMaking Bonus part\n"
	@echo "\033[0;37m"
	@$(SAY) -v "karen" -r 20 "Making, Bonus part"
	@$(MAKE) do_bonus OBJS="$(BONUS_OBJS)" NAME="philo_bonus/philo_bonus"

