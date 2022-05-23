# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compare.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 20:36:59 by hyunlee           #+#    #+#              #
#    Updated: 2021/11/24 20:37:04 by hyunlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EOC="\e[0m"
BOLD="\e[1m"
RED="\e[91m"
GREEN="\e[92m"

if [ $? -eq 0 ]; then \
	printf "$BOLD own_tester: $1\t[ ✅ ]$EOC\n"; \
else \
	printf "$RED$BOLD own_tester: $1\t[ ❌ ]$EOC\n"; \
fi

sleep 0.5
