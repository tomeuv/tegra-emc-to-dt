print-emc-timings.c includes the board file from linux-l4t and prints the data in the DT format that is expected by upstream.

Run `make test` to try it out.

See within the code for hardcoded values that can be changed to print the data for boards other than Jetson TK1.

To update to newer releases of linux-l4t, copy board-ardbeg-memory.c and modify it as needed. See older commits for an example.
