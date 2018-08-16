# Point to point communication test
The one point to point communication test I performed on theta was the multiple bandwidth/messaging rate test. This test was chosen to be performed because it is capable of being run on multiple processes whereas most of the others can only be run on exactly two processes. This allows us to run on more than two mpi ranks per node. There is a point to point test which collects latency using multiple processes but we have data from when these tests were run on Theta after it was build which used bandwidth. [Said data is contained in this document.](https://cug.org/proceedings/cug2017_proceedings/includes/files/pap113s2-file1.pdf)

An exact copy of the test file in this directory is also built into the singularity container I used.

The spreadsheet for the graphs, included as images in this directory, of the results of the osu_mbw_mr tests can be found at these links:
- [test 1](https://docs.google.com/spreadsheets/d/1kZ_MBM-RuiVDrP20JQLMVIH0PyEUXASnteJ1SaLM0Pc/edit#gid=0)
- [test 2](https://docs.google.com/spreadsheets/d/1_tYkE-LRYofnb2ea5McQlOwvzIl33QQJ8DWqpxDn5cQ/edit#gid=0)
- [combined testing data graphs](https://docs.google.com/spreadsheets/d/1JNQwb7qelzrXGPQNC4XDiTOzDwLcvz1RgQJbiyya2y8/edit#gid=0)
