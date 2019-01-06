p=$(shell nproc)

compile:
	@mkdir -p /tmp/ocean
	g++ -g main.cpp -o /tmp/ocean/main

run:
	/tmp/ocean/main


