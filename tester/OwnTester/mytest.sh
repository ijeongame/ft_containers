# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mytest.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 20:36:55 by hyunlee           #+#    #+#              #
#    Updated: 2021/11/24 20:36:56 by hyunlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SET=$(seq 0 4)

EOC="\e[0m"
BOLD="\e[1m"
YELLOW="\e[93m"

clear
printf "$YELLOW$BOLD READY TO TEST 🔴 🟠 🟡 🟢\n"
for i in $SET
do  sleep 0.5
    printf " .\n"
done
printf "$EOC"
