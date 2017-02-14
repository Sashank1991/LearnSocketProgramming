all: raceCond raceCond2 semaphoreUsage setGetOptions dtServer dtClientIP4 dtClientIP6

raceCond: raceCond.c
	gcc -pthread -o raceCond raceCond.c

raceCond2: raceCond2.c
	gcc -pthread -o raceCond2 raceCond2.c

semaphoreUsage: semaphoreUsage.c
	gcc -pthread -o semaphoreUsage semaphoreUsage.c

setGetOptions: setGetOptions.c
	gcc -o setGetOptions setGetOptions.c

dtServer: dtServer.c
	gcc -o dtServer dtServer.c

dtClientIP4: dtClientIP4.c
	gcc -o dtClientIP4 dtClientIP4.c

dtClientIP6: dtClientIP6.c
	gcc -o dtClientIP6 dtClientIP6.c
