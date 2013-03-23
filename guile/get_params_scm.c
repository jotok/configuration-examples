#include <libguile.h>

void*
read_config(void *nothing) {
    scm_dynwind_begin(0);

    scm_c_primitive_load("param_file_desc.scm");
    scm_c_primitive_load("params.scm");

    // print the data directory
    SCM config = scm_variable_ref(scm_c_lookup("config"));
    SCM symbol = scm_from_locale_symbol("directory");
    SCM directory = scm_assq_ref(config, symbol);
    char *c_directory = scm_to_locale_string(directory);
    scm_dynwind_free(c_directory);
    printf("directory: %s\n", c_directory);

    // print the value of the summary flag
    symbol = scm_from_locale_symbol("summary");
    SCM summary = scm_assq_ref(config, symbol);
    printf("summary: %d\n", scm_is_true(summary));

    // print the name, length, and column parameters for the first field
    SCM fields = scm_variable_ref(scm_c_lookup("config-fields"));
    SCM f = scm_list_ref(fields, scm_from_int(0));
    symbol = scm_car(f);
    char *c_name = scm_to_locale_string(scm_symbol_to_string(symbol));
    printf("%s %d %d %d\n", c_name,
                            scm_to_int(scm_list_ref(f, scm_from_int(1))),
                            scm_to_int(scm_list_ref(f, scm_from_int(2))),
                            scm_to_int(scm_list_ref(f, scm_from_int(3))));
    free(c_name);

    // print the number of blocking fields in the first strategy
    SCM strategies = scm_variable_ref(scm_c_lookup("config-strategies"));
    SCM strategy = scm_list_ref(strategies, scm_from_int(0));
    symbol = scm_from_locale_symbol("block");
    SCM list = scm_assq_ref(strategy, symbol);
    printf("number of blocking fields: %d\n", scm_to_int(scm_length(list)));

    scm_dynwind_end();
    return NULL;
}

int
main(void) {
    scm_with_guile(read_config, NULL);
    return 0;
}
