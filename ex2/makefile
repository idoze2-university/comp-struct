ifndef k
override k=0
endif

ifndef x
override x=20
endif

clean:
	rm kefel.s create_asm main

create:
	gcc kefel.c -o create_asm

run: create
	./create_asm $(k)

test: run
	gcc test.c kefel.s -o main
	echo '\n\n\n\n' && echo $(k) $(x)| ./main



