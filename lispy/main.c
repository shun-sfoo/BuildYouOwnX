#include "mpc.h"
#include <stdio.h>
#include <stdlib.h> /* free */

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32

#include <string.h>

static char buffer[2048];

/* Fake readline function */
char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(*char *unused) {}

#elif defined(__linux)

#include <editline/history.h>
#include <editline/readline.h>

#elif defined(__APPLE__)

#include <editline/readline.h>

#endif

int main(int argc, char **argv) {

  /*Create Some Parrses */
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispy = mpc_new("lispy");
  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT, /* regex description */
            "                                        \
  number   : /-?[0-9]+/ ;                            \
  operator : '+' | '-' | '*' | '/' ;                 \
  expr     : <number> | '(' <operator> <expr>+ ')' ; \
  lispy    : /^/ <operator> <expr>+ /$/ ;            \
  ",
            Number, Operator, Expr, Lispy);

  /* Print Version and Exit Information */
  puts("Lispy Version 0.0.0.0.2");
  puts("Press Ctrl+c to Exit\n");

  /* In a nerver ending loop */
  while (1) {
    /* Output our prompt and get input */
    char *input = readline("lispy> ");

    /* Add input to history*/
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* On Success and delete the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise print and delete the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    /* Free retrieved input */
    free(input);
  }

  /* Undefine and delete our parsers */
  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}
