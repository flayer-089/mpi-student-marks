#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv); // Initialize MPI environment

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (size < 3) {
        if (rank == 0)
            cout << "Please run with at least 3 processes." << endl;
        MPI_Finalize();
        return 0;
    }

    // Part 1: Student Marks

    if (rank == 0) {
        int studentMarks = 75; 
        MPI_Send(&studentMarks, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        cout << "Process 0 (University Server) sent student marks: " 
             << studentMarks << endl;
    } 
    else if (rank == 1) {
        int receivedMarks;
        MPI_Recv(&receivedMarks, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Process 1 (Counselor System) received student marks: " 
             << receivedMarks << endl;
    }

    MPI_Barrier(MPI_COMM_WORLD); // To synchronize before next part

    // PART 2: Student Attendance

    if (rank == 0) {
        int totalClasses = 48;
        MPI_Send(&totalClasses, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
        cout << "Process 0 (University Server) sent total classes: " << totalClasses << endl;
    } 
    else if (rank == 1) {
        int classesAttended = 36;
        MPI_Send(&classesAttended, 1, MPI_INT, 2, 2, MPI_COMM_WORLD);
        cout << "Process 1 (Counselor System) sent classes attended: " << classesAttended << endl;
    } 
    else if (rank == 2) {
        int totalClasses, classesAttended;
        MPI_Recv(&totalClasses, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&classesAttended, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        float attendancePercent = (float)classesAttended / totalClasses * 100;
        cout << "Process 2 (Attendance Processor) calculated attendance: " 
             << attendancePercent << "%" << endl;
    }

    MPI_Finalize(); 
    return 0;
}
