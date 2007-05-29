#include "../syx/syx.h"

int
main (int argc, char *argv[])
{
  SyxParser *parser;
  SyxLexer *lexer;
  SyxMethod *method;
  SyxMethodContext *context;
  SyxProcess *process;
  GError *error = NULL;
  GTimer *timer;

  syx_init ("..");
  syx_build_basic ();

#define INTERPRET(text)							\
  lexer = syx_lexer_new (text);						\
  method = syx_method_new ();						\
  parser = syx_parser_new (lexer, method, NULL, FALSE, NULL);		\
  g_assert (syx_parser_parse (parser, &error) == TRUE);			\
  context = syx_method_context_new (method, syx_nil, NULL, NULL);	\
  process = syx_process_new (context);					\
  syx_scheduler_add_process (process);

  timer = g_timer_new ();

  /*  INTERPRET ("method 'Process 1' print. 'Process 1' print.'Process 1' print.'Process 1' print.'Process 1' print. 'Process 1' print");
  INTERPRET ("method 'Process 2' print. 'Process 2' print.'Process 2' print.'Process 2' print.'Process 2' print. 'Process 2' print");
  INTERPRET ("method 'Process 3' print. 'Process 3' print.'Process 3' print.'Process 3' print.'Process 3' print. 'Process 3' print");*/
  INTERPRET ("method"\
	     "['Process 1' print. 'Process 1' print.'Process 1' print.'Process 1' print.'Process 1' print. 'Process 1' print] fork."\
	     "['Process 2' print. 'Process 2' print.'Process 2' print.'Process 2' print.'Process 2' print. 'Process 2' print] fork."\
	     "['Process 3' print. 'Process 3' print.'Process 3' print.'Process 3' print.'Process 3' print. 'Process 3' print] fork");
  //  g_assert (g_slist_length (syx_scheduler_get_processes ()) == 3);

  g_timer_start (timer);
  syx_scheduler_run ();
  g_timer_stop (timer);

  g_print("Time elapsed: %f\n", g_timer_elapsed (timer, NULL));
  g_timer_destroy (timer);

  return 0;
}