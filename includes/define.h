#ifndef DEFINE_H
# define DEFINE_H

# define ERROR -1
# define SUCCESS 0

# define FALSE	0
# define TRUE	1

# define LOOP 1

# define ON 1
# define OFF 0

# define ERRCMD		"command not found"
# define ERRDIR		"No such file or directory"
# define ERR
enum	e_token
{
	NONE,
	OR,
	AND,
	PIPE,
	CMD,
	S_QUOTE,
	D_QUOTE,
	STR,
	INP_RD,
	OUT_RD,
	APP_RD,
	HERE_DOC,
	PARENS,
};

enum	e_type
{
	TK_OR,
	TK_AND,
	TK_PIPE,
	TK_WORD,
	TK_PARENS
};

#endif