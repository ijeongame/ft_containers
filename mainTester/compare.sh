EOC="\e[0m"
BOLD="\e[1m"
RED="\e[91m"
GREEN="\e[92m"

if [ $? -eq 0 ]; then \
	printf "$BOLD mytester: $1\t[ ✅ ]$EOC\n"; \
else \
	printf "$RED$BOLD mytester: $1\t[ ❌ ]$EOC\n"; \
fi

sleep 0.5
