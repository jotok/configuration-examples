#include <libguile.h>

void*
read_config(void *nothing) {
    scm_dynwind_begin(0);

    scm_c_primitive_load("param_file_desc.scm");
    scm_c_primitive_load("params.scm");

    SCM config = scm_variable_ref(scm_c_lookup("config"));
    SCM symbol = scm_from_locale_symbol("directory");
    SCM directory = scm_assq_ref(config, symbol);
    char *c_directory = scm_to_locale_string(directory);
    scm_dynwind_free(c_directory);
    printf("directory: %s\n", c_directory);

    symbol = scm_from_locale_symbol("filea");
    SCM filea = scm_assq_ref(config, symbol);
    char *c_filea = scm_to_locale_string(filea);
    scm_dynwind_free(c_filea);
    printf("filea: %s\n", c_filea);

    symbol = scm_from_locale_symbol("fileb");
    SCM fileb = scm_assq_ref(config, symbol);
    char *c_fileb = scm_to_locale_string(fileb);
    scm_dynwind_free(c_fileb);
    printf("fileb: %s\n", c_fileb);

    scm_dynwind_end();
    return NULL;
}

int
main(void) {
    scm_with_guile(read_config, NULL);
    return 0;
}
