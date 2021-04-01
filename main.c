#include <stdio.h> //printf
#include <unistd.h> //write, lseek, close, read
#include <sys/types.h> //lseek, open
#include <stdlib.h> //malloc
#include <sys/stat.h> //open
#include <fcntl.h> //open

/*
 * *buf => dans les prototypes de fonctions ==> série de caractères
 * */

/*
 * man 2 open
 * open = fonction qui sert à ouvrir ou créer un fichier. Elle renvoit un file descriptor (fd / fildes) qui est un chiffre qui permet
 *      d'identifier le fichier en question Donc, d'y accéder/de le modifier grâce à d'autres foncitons
 *      int open(const char '*pathname', int 'flags', mode_t 'mode');
 * * */

/*
 * man close
 * close = fonction qui permet de "fermer" le fildes afin qu'il ne référence plus aucun fichier. Le fildes ainsi libéré
 *      peut-être réuitilisé pour d'autres buts. Un peu comme le free() pour libérer la mémoire "reservée" lors d'un malloc
 *      int close(int 'fd');
 * */

/*
 * man 2 read
 * read = fonction qui lit dans un fichier (identiifié par fildes) jusqu'à 'count' octet
 *      ssize_t read(int 'fd', void '*buf', size_t 'count');
 * */

/*
 * man 2 write
 * write = écrit jusqu'à 'count' octet dans le fichier associé au 'fd' (fildes) depuis le tampon pointé par 'buf'
 *       ssize_t write(int 'fd', const void '*buf', size_t 'count');
 * */

/*
 * man malloc
 * malloc = alloue 'size' octets de mémoire et renvoie un pointeur sur la mémoire allouée
 *      void *malloc(size_t 'size');
 * */

/*
 * man free cf man malloc
 * fee = libère l'espace pointé par 'ptr' qui avait été alloué précédemment via un appel de malloc
 *      void free(void '*ptr');
 * */

/*
 * man 2 lseek
 * lseek = fonction utilisée pour placer la tête de lecture/écriture dans un fichier
 *      Si lseek fonctionne, elle renvoit le nouvel emplacement (en octet) depuis le début du fichier
 *      Si lseek échoue, elle renvoie (off_t)-1 + un code d'erreur dans errno
 *      off_t lseek(int 'fd', off_t 'offset', int 'whence');
 * */

/*
 * MODE OP
 * open fichier source pour générer fildes => read le contenu grâce au fildes
 * open pour créer un nouveau fichier /!\ utiliser my_putrevstr() pour nom du fichier en reverse + générer son fildes => write dedans grâce au fildes
 * */

int my_strlen(char*    str) {
    int i;


    for (i = 0; str[i] != '\0'; ++i);

    return (i);
}

char	*create_new_file(char *arg)
{
	int		len;
	char	*new_name;
	int		i = 0;
	int		y = 0;




	len = my_strlen(arg);
	new_name = malloc(sizeof(char) * len + 1);
	for (i = 0; i <= len ; i++)
	{
		new_name[i] = arg[i];
	}
	i--;//remonte au niveau du \0
	y = len - 1; //y se trouve un char en amont de \0
	while (arg[i] != '/')
	{
		i--;//on fait remonter i avant le nom de fichier, sur le slash
	}
	i++; //on place i sur la premiere lettre du nom de fichier
	while (i < len)
	{
		new_name[y] = arg[i];//inverse lettres de la partie nom de fichier
		y--;
		i++;
	}
	return (new_name);
}

int main(int argc, char **argv) {
	int		fd_input = 0;
	int		fd_output = 0;
	char	*file_name;

	(void)argc;
	if (open(argv[1], O_RDONLY) == -1) //if (open(argv[1])) => argv[0] = nom du programme et argv[1] = nom du 1er argument, ici le fichier à copier
		return -1;
	file_name = create_new_file(argv[1]);
	printf("file_name = %s\n", file_name);
	close(fd_input);
	close(fd_output);
    return 0;
}

