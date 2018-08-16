#define BENCHMARK "OSU MPI%s Gather Latency Test"
/*
 * Copyright (C) 2002-2018 the Network-Based Computing Laboratory
 * (NBCL), The Ohio State University.
 *
 * Contact: Dr. D. K. Panda (panda@cse.ohio-state.edu)
 *
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level OMB directory.
 */
#include <osu_util.h>

int
main (int argc, char *argv[])
{
    int i, numprocs, rank, size;
    double latency = 0.0, t_start = 0.0, t_stop = 0.0;
    double timer=0.0;
    double avg_time = 0.0, max_time = 0.0, min_time = 0.0;
    char * sendbuf = NULL, * recvbuf = NULL;
    int po_ret;
    size_t bufsize;
    options.bench = COLLECTIVE;
    options.subtype = LAT;

    set_header(HEADER);
    set_benchmark_name("osu_gather");
    po_ret = process_options(argc, argv);

    if (PO_OKAY == po_ret && NONE != options.accel) {
        if (init_accel()) {
            fprintf(stderr, "Error initializing device\n");
            exit(EXIT_FAILURE);
        }
    }

    MPI_CHECK(MPI_Init(&argc, &argv));
    MPI_CHECK(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
    MPI_CHECK(MPI_Comm_size(MPI_COMM_WORLD, &numprocs));

    switch (po_ret) {
        case PO_BAD_USAGE:
            print_bad_usage_message(rank);
            MPI_CHECK(MPI_Finalize());
            exit(EXIT_FAILURE);
        case PO_HELP_MESSAGE:
            print_help_message(rank);
            MPI_CHECK(MPI_Finalize());
            exit(EXIT_SUCCESS);
        case PO_VERSION_MESSAGE:
            print_version_message(rank);
            MPI_CHECK(MPI_Finalize());
            exit(EXIT_SUCCESS);
        case PO_OKAY:
            break;
    }

    if(numprocs < 2) {
        if (rank == 0) {
            fprintf(stderr, "This test requires at least two processes\n");
        }

        MPI_CHECK(MPI_Finalize());
        exit(EXIT_FAILURE);
    }

    if ((options.max_message_size * numprocs) > options.max_mem_limit) {
        options.max_message_size = options.max_mem_limit / numprocs;
    }

    if (0 == rank) {
        bufsize = options.max_message_size * numprocs;
        if (allocate_memory_coll((void**)&recvbuf, bufsize, options.accel)) {
            fprintf(stderr, "Could Not Allocate Memory [rank %d]\n", rank);
            MPI_CHECK(MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE));
        }
        set_buffer(recvbuf, options.accel, 1, bufsize);
    }

    if (allocate_memory_coll((void**)&sendbuf, options.max_message_size,
                options.accel)) {
        fprintf(stderr, "Could Not Allocate Memory [rank %d]\n", rank);
        MPI_CHECK(MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE));
    }
    set_buffer(sendbuf, options.accel, 0, options.max_message_size);

    print_preamblek(rank);

    for(size=options.min_message_size; size <= options.max_message_size; size *= 2) {
        if (size > LARGE_MESSAGE_SIZE) {
            options.skip = options.skip_large;
            options.iterations = options.iterations_large;
        }

        if(size >= 530000){
          break;
        }

        MPI_CHECK(MPI_Barrier(MPI_COMM_WORLD));

        int a, b, trials = 1000;
        double avgk = 0, sum = 0, sum2 = 0;
        double nums_ls[1000];
        for(a = 0; a < trials; a++){

            timer=0.0;
            for(i=0; i < options.iterations + options.skip ; i++) {
                t_start = MPI_Wtime();
                MPI_CHECK(MPI_Gather(sendbuf, size, MPI_CHAR, recvbuf, size, MPI_CHAR, 0,
                        MPI_COMM_WORLD));
                t_stop = MPI_Wtime();

                if(i>=options.skip){
                    timer+=t_stop-t_start;
                }
                MPI_CHECK(MPI_Barrier(MPI_COMM_WORLD));

            }

            MPI_CHECK(MPI_Barrier(MPI_COMM_WORLD));

            latency = (timer * 1e6) / options.iterations;

            MPI_CHECK(MPI_Reduce(&latency, &min_time, 1, MPI_DOUBLE, MPI_MIN, 0,
                    MPI_COMM_WORLD));
            MPI_CHECK(MPI_Reduce(&latency, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0,
                    MPI_COMM_WORLD));
            MPI_CHECK(MPI_Reduce(&latency, &avg_time, 1, MPI_DOUBLE, MPI_SUM, 0,
                    MPI_COMM_WORLD));
            avg_time = avg_time/numprocs;
            sum += avg_time;
            nums_ls[a] = avg_time;
        }
        avgk = sum/trials;
        for(b = 0; b < trials; b++){
            sum2 += pow(nums_ls[b] - avgk, 2);
        }
        sum2 = sum2/1000;
        double sigma = sqrt(sum2);
        print_statsk(rank, size, avg_time, avgk, sigma);
    }

    if (0 == rank) {
        free_buffer(recvbuf, options.accel);
    }
    free_buffer(sendbuf, options.accel);

    MPI_CHECK(MPI_Finalize());

    if (NONE != options.accel) {
        if (cleanup_accel()) {
            fprintf(stderr, "Error cleaning up device\n");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

/* vi: set sw=4 sts=4 tw=80: */
