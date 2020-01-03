/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */
%token  WORD
%token  ASSIGNMENT_WORD
%token  NAME
%token  IO_NUMBER
/* The following are the operators (see XBD Operator)
   containing more than one character. */
%token  DLESS  DGREAT  LESSAND  GREATAND  LESSGREAT  DLESSDASH
/*      '<<'   '>>'    '<&'     '>&'      '<>'       '<<-'   */
/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */
complete_command : list separator
                 | list
                 ;
/*
list             : list separator    and_or
                 |                   and_or
                 ;
*/

list             : and_or list_next
                 ;
list_next        : separator and_or list_next
                 | EMPTY
                 ;
/*
and_or           :               pipeline
                 | and_or AND_IF pipeline
                 | and_or OR_IF  pipeline
*/

and_or           : pipeline and_or_list
                 ;
and_or_list      : AND_IF pipeline and_or_list
                 | OR_IF pipeline and_or_list
				 | EMPTY
				 ;
/*
_pipeline         :              command
                 | _pipeline '|' command
                 ;
*/ 

_pipeline         : command _pipe_list
                 ;
_pipe_list        : '|' command _pipe_list
                 | EMPTY
				 ;
command          : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
cmd_name         : WORD                   /* Apply rule 7a */
                 ;
cmd_word         : WORD                   /* Apply rule 7b */
                 ;
/*cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
*/
cmd_prefix       : io_redirect cmd_prefix_list
                 | ASSIGNMENT_WORD cmd_prefix_list
				 ;
cmd_prefix_list  : io_redirect cmd_prefix_list
                 | ASSIGNMENT_WORD cmd_prefix_list
				 | EMPTY
				 ;
/*
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
*/
cmd_suffix       : io_redirect cmd_suffix_list
                 | WORD cmd_suffix_list
				 ;
cmd_suffix_list  | io_redirect cmd_suffix_list
                 | WORD cmd_suffix_list
                 | EMPTY;
_io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here
                 | IO_NUMBER io_here
                 ;
io_file          : '<'       filename
                 | LESSAND   filename
                 | '>'       filename
                 | GREATAND  filename
                 | DGREAT    filename
                 | LESSGREAT filename
                 ;
filename         : WORD                      /* Apply rule 2 */
                 ;
io_here          : DLESS     here_end
                 | DLESSDASH here_end
                 ;
here_end         : WORD                      /* Apply rule 3 */
                 ;
separator        : '&'
                 | ';'
                 ;
