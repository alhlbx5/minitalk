CLSRC				= client.c
CLOBJ				= $(CLSRC:.c=.o)
CLNAME				= client

SVSRC				= server.c
SVOBJ				= $(SVSRC:.c=.o)
SVNAME				= server

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror

all:				ft_printf/libftprintf.a $(CLNAME) $(SVNAME)

$(CLNAME):			$(CLSRC)
					$(CC) $(CFLAGS) $(CLSRC) -L ft_printf -lftprintf -o $(CLNAME)

$(SVNAME):			$(SVSRC)
					$(CC) $(CFLAGS) $(SVSRC) -L ft_printf -lftprintf -o $(SVNAME)

ft_printf/libftprintf.a:
					make -C ./ft_printf all

clean:
					make -C ./ft_printf clean
					rm -f $(CLOBJ) $(SVOBJ)

fclean:				clean
					make -C ./ft_printf fclean
					rm -f $(CLNAME) $(SVNAME)

re: 				fclean all

bonus:				all