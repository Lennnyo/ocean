p=$(shell nproc)

compile:
	@mkdir -p /tmp/mpiring
	mpicxx ring.cpp -o /tmp/mpiring/ring

run:
	mpirun -n $(p) /tmp/mpiring/ring

edit:
	@gedit --new-window ring.cpp makefile &

install:
	sudo apt-get install libopenmpi-dev openmpi-bin
