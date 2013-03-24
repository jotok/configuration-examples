configuration-examples
======================

This repository contains source code examples demonstrating how to use lua and guile to process configuration files. The file params.txt in the root directory gives an example configuration file that we'd like replace. The folders lua/ and guile/ contain the solutions using those interpreters. The examples were written using lua 5.2 and guile 1.8.

params.txt is the configuration file for an imaginary record linkage program (that is, a program that tries to match records in two files that represent the same entity). The input is two text files with data in fixed-width columns. The program operates in passes, and each pass has a blocking stage and a matching stage. In the blocking stage, we bring records together which match exactly on indicated fields (called the blocking fields). In the matching stage we compute match score for each pair of records in a block using additional data columns. After all passes are completed, we output results.

params.txt was written to be easy to read using C's scanf function. Unfortunately, it's somewhat harder to read using a human. The first two lines of params.txt give the names of the files to be linked.

    /path/to/data/a_file.txt
    /path/to/data/another_file.txt

The next line is a row of three numbers. The first is the number of passes the program should make, and the second and third are flags indicating whether verbose output should be produced and whether summary output should be printed.

    2 1 0

The next lines give the number of blocking fields for each pass, and the number of matching fields for each pass. Since we've indicated that we want two passes, there should be two numbers on each line.

    2 2
    4 2

In this example, each pass will use 2 blocking fields. The first pass will use 4 matching fields and the second pass will use 2 matching fields. Next in params.txt are two sections describing the columns we want to use in each pass. The first section looks like this:

    zip    5   70  81
    flast  1   20  21
    last   20  20  21  uo  0.01  0.99
    first  20  0   0   uo  0.20  0.80
    mi     1   40  20  c   0.04  0.49
    hsnm   12  57  40  c   0.06  0.999
    0.1 0.9

The first two lines in this section correspond to the 2 blocking fields used in this pass. Each line contains four values: the field name, the field length, the location of the field in the first file, and the location of the field in the second file. After the blocking fields come the four matching fields. In addition to the four values that appear for the blocking fields, there are three additional values that describe how the fields should be matched. First is a character code indicating which matching function to use ("uo" refers to the fuzzy string matcher and "c" refers to an exact character-by-character match). The last two values are weights that determine how matches and non-matches should be valued. The last row in the above section consists of a pair of cutoff values that indicate how the computed match score should be categorized in the output.

There is an analogous section that describes the blocking fields, matching fields, and cutoff values for the second pass:

    hsnm   12  57  40
    last   20  20  21
    first  20  0   0   uo  0.20  0.80
    dob    8   41  43  d   0.3   0.7
    0.2 0.85

As I stated above, the purpose of this repository is to see how I could replace this configuration file with one written in lua or scheme.
