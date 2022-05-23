SET=$(seq 0 4)

EOC="\e[0m"
BOLD="\e[1m"
YELLOW="\e[93m"

clear
printf "$YELLOW$BOLD READY TO TEST 🔴 🟠 🟡 🟢\n"
for i in $SET
do sleep 0.5
	printf " .\n"
done
printf "$EOC"
