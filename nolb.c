#include "nolb.h"

/************/
/*** ARGS ***/
/************/
void parse_args(Nolb_Args* nargs, int argc, char** argv) {
    if (argc < 2 || argc > 4) {
        log_error("Wtf bro?");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "test") || !strcmp(argv[i], "t") || !strcmp(argv[i], "-t"))
            nargs->test = true;
        else if (!strcmp(argv[i], "debug") || !strcmp(argv[i], "d") || !strcmp(argv[i], "-d"))
            nargs->debug = true;
        else if (isdigit(argv[i][0]))
            nargs->day = argv[i];
    }
}
/************/
/*** CMDs ***/
/************/
void cmd_comp(Nolb_Cmd* cmd, Nolb_Args* nargs) {
    cmd_append(cmd, "gcc-15");
    if (nargs->debug) cmd_append(cmd, "-g");
}
void cmd_flags(Nolb_Cmd* cmd) { cmd_append(cmd, "-Wall", "-Wextra", "-std=c23", "-pedantic"); }
void cmd_print(Nolb_Cmd* cmd) {
    char cs[1024] = {0};
    for (int i = 0; i < (int)cmd->count; ++i) {
        strcat(cs, " ");
        strcat(cs, cmd->items[i]);
    }
    log_info("Running %s", cs);
}
void print_delim() {
    printf("\n##############\n\n");
}
/************/
/*** MAIN ***/
/************/
int main(int argc, char** argv) {
    // nolb_rebuild();

    Nolb_Args nargs = {0};
    parse_args(&nargs, argc, argv);

    log_info("## Day %s ## (test:%d, debug:%d)", nargs.day, nargs.test, nargs.debug);

    Nolb_Cmd cmd = {0};

    if (folder_already_exists(&nargs)) {
        char* in = construct_string("%s/main.c", nargs.day);
        char* out = construct_string("%s/main", nargs.day);
        cmd_comp(&cmd, &nargs);
        cmd_flags(&cmd);
        cmd_append(&cmd, "-o", out);
        cmd_append(&cmd, in);
        cmd_print(&cmd);
        if (run_cmd(&cmd) != 0) {
            log_error("Build failed");
            exit(EXIT_FAILURE);
        }
        cmd.count = 0;
        chdir(nargs.day);
        if (nargs.debug) cmd_append(&cmd, "gdb");
        cmd_append(&cmd, "./main");
        if (nargs.test && !nargs.debug) cmd_append(&cmd, "test");
        cmd_print(&cmd);
        
        print_delim();
        if (run_cmd(&cmd) != 0) {
            log_error("Run failed");
            exit(EXIT_FAILURE);
        }
        print_delim();

    } else {
        scaffold(&nargs);
    }
}
