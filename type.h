// typedef enum match
// {
// 	M_DOUBLE_QUOTE = '\"',
// 	M_SINGLE_QUOTE = '\'',
// 	M_INPUT_REDIR = '<',
// 	// M_HERE_DOC = '<<',
// 	M_OUTPUT_REDIR = '>',
// 	// M_APPEND_REDIR = '>>',
// 	M_PIPE = '|',
// }t_match;

typedef enum type
{
	T_NULL,
	T_COMMAND,
	T_DOUBLE_QUOTE,
	T_SINGLE_QUOTE,
	T_INPUT_REDIR,
	T_HERE_DOC,
	T_LIMITER,
	T_OUTPUT_REDIR,
	T_APPEND_REDIR,
	T_PIPE
}t_type;

typedef struct s_token
{
	t_type					type;
	char						*word;
	struct s_token	*next;
}	t_token;

