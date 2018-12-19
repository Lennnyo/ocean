#include <mpi.h>
#include <stdio.h>

/*

In the following example, a token value is passed around by all processes in a ring-like fashion. The process with rank zero starts the ring and then waits for the token from the last process with rank size-1. The other processes wait for the token from their predecessor and send it to the next one. I used MPI_Ssend instead of MPI_Send since MPI_Send has a mutable behavior according to the size of the message that is: it has an asynchronous behavior if the message is short, otherwise it follows a synchronous schema.

*/

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int rank, size, token;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank==0) {
		MPI_Ssend(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("#0 -> #1\n");
		MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	} else {
		MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Ssend(&token, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);
		printf("#%d -> #%d\n", rank, (rank+1)%size);
	}
	MPI_Finalize();
	return 0;
}

