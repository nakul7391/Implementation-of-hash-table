TARGET:=a.out
SOURCES:=$(wildcard *.c)

${TARGET} : ${SOURCES}
					gcc ${SOURCES} -o ${TARGET}

auto :
		gcc ${SOURCES} -o ${TARGET}

list :
		gcc -D LIST ${SOURCES} -o ${TARGET}

clean :
			rm ${TARGET}
