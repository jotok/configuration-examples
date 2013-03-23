directory "/path/to/data"
files {"a_file.txt", "another_file.txt"}
flags {verbose=true, summary=false}

fields {
--   name     length  starta  startb
    {"first",     20,      0,      0},
    {"last",      20,     20,     21},
    {"mi",         1,     40,     20},
    {"hsnm",      12,     57,     40},
    {"dob",        8,     41,     43},
    {"zip",        5,     70,     81},
    {"flast",      1,     20,     21}
}

strategy {
    block = {"zip", "flast"},
    match = {
        {"last", fuzzy_string, 0.01, 0.99},
        {"first", fuzzy_string, 0.20, 0.80},
        {"midin", exact, 0.04, 0.49},
        {"hsnm", exact, 0.06, 0.999}
    },
    output_cutoffs = {0.1, 0.9}
}

strategy {
    block = {"hsnm", "last"},
    match = {
        {"first", fuzzy_string, 0.20, 0.80},
        {"dob", date, 0.3, 0.7}
    },
    output_cutoffs = {0.2, 0.85}
}
