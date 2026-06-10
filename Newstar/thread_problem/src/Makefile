.PHONY: all
.PHONY: clean

all:
	gcc ./main.c ./manager.c ./account.c -lcrypto -lpthread  -o ./bin/main
	touch ./bin/user.db
clean:
	rm ./bin/*
