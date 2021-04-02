#include <unistd.h> //write, lseek, close, read
#include <sys/types.h> //lseek, open
#include <stdlib.h> //malloc
#include <sys/stat.h> //open
#include <fcntl.h> //open




#include <stdio.h> //printf A ENLEVEEEEEEER



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

void my_putchar(char c)
{
	write(1, &c, 1);
	//write(1 = sortie standard, &c = adresse où est stockée la variable, 1 = on n'affiche qu'un seul caractère)
}

// *str = pointeur => commence au 1er caractère d'une string et s'arrête au \0 
void my_putstr(char*   str)
{
	int i;
	i=0;
	while(str[i])
	{
		my_putchar(str[i]);
		i++;
	}
}

int my_strlen(char*    str) {
	int i;

	for (i = 0; str[i] != '\0'; ++i);

	return (i);
}

char	*reverse_name(char *arg)
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

int *create_index_table(char *content)
{
	int		nb_words = 1;//car on a verifie que le fichier n'est pas vide
	int		i = 0;
	int		y;
	int 	*indexes;

	while (content[i])	
	{
		if (content[i] == '\n')
		{
			nb_words++;
		}
		i++;
	}
	//printf("nb_words = %d\n", nb_words);
	indexes = malloc(sizeof(int) * nb_words + 1);
	//rempli le tableau d'index de -1 pour avoir une valeure d'arret plus tard
	for (i = 0; i < nb_words + 1; i++)	
	{
		indexes[i] = -1;
	}
	//for (i = 0; i < nb_words; i++)
	//	printf("index %d = %d\n", i, indexes[i]);
	indexes[0] = 0;
	i = 0;//i navigue le long de content
	y = 1;//y navigue dans le tableau d'index
	while (content[i])
	{
		if (content[i] == '\n' && content[i + 1])
		{
			indexes[y] = i + 1;
			y++;
		}
		i++;
	}
	//for (i = 0; i < nb_words + 1; i++)
	//	printf("index %d = %d\n", i, indexes[i]);
	return (indexes);
}


void write_line(int fd_output, char *content, int word_start)
{
	while (content[word_start] != '\n')//on ecrit dans fichier depuis debut du mot jusau'au \n
	{
		write(fd_output, &(content[word_start]), 1);
		word_start++;
	}
	write(fd_output, "\n", 1);//on ajoute un \n a la fin pour aller a la ligne avant prochaine ligne
}

void sort_lines(int fd_output, char *content, int *indexes)
{
	int		ascii;
	int		i;
	int		word_start;

	ascii = 32; //ascii for space, osef des ascii précédents qui sont des char non imprimables
	i = 0;//pour plus de clarté, word_start contient index de la premiere lettre du mot//pour plus de clarté, word_start contient index de la premiere lettre du mot
	while (ascii <= 126) //fait tous les char speciaux et les chiffres
	{
		while (indexes[i] != -1)//condition d'arret, quand a checké tous les mots
		{
			word_start = indexes[i];//pour plus de clarté, word_start contient index de la premiere lettre du mot
			if (content[word_start] == ascii)
			{
				write_line(fd_output, content, word_start);
			}
			i++;
		}
		i = 0;
		ascii++;
		if (ascii == 65)//on saute les lettres majuscules
		{
			ascii = 91;
		}
		if (ascii == 97)//on saute les lettres minuscules
		{
			ascii = 123;;
		}
	}
	ascii = 65;
	while (ascii < 90) //checker lettres maj ET min 
	{
		while (indexes[i] != -1)
		{
			word_start = indexes[i];
			//ascii + 32 car il y a 32 entre la majuscule d'une lettre et sa minuscule sur la table
			if (content[word_start] == ascii || content[word_start] == ascii + 32)
			{
				write_line(fd_output, content, word_start);
			}
			i++;
		}
		ascii++;
		i = 0;
	}
}

int main(int argc, char **argv) {
	int		fd_input = 0;
	int		fd_output = 0;
	char	*file_name;
	int		nb_of_chars;
	char	*content;
	int		*indexes;
	//int		index;


	(void)argc;
	if ((fd_input = open(argv[1], O_RDONLY)) == -1)
		return -1;
	file_name = reverse_name(argv[1]);
	//	printf("file_name = %s\n", file_name);
	if ((fd_output = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0777)) == -1)
		return -1;
	free(file_name);
	//lseek renvoi le nombre de char dans le fichier (car on place le curseur de
	//lecture a la fin
	nb_of_chars = lseek(fd_input, 0, SEEK_END);
	//printf("nb_of_chars = %d\n", nb_of_chars);
	if (nb_of_chars == 0)	
	{
		my_putstr("Input file is empty");
		return 0;
	}
	//creer string qui peux accueillir le contenu du fichier
	content = malloc(sizeof(char) * nb_of_chars);
	//je me remet au debut du fichier
	lseek(fd_input, 0, SEEK_SET);
	//enregistrement du contenu du fichier dans content
	read(fd_input, content, nb_of_chars);
	//	printf("content = %s\n", content);
	indexes = create_index_table(content);
	//la fonction suivante classe selon premier char du mot et l'ecrit dans le fichier
	sort_lines(fd_output, content, indexes);
	close(fd_input);
	close(fd_output);
	free(content);
	free(indexes);
	return 0;
}

//attention a bien suppriemer le fichier txt.unetnoc entre deux appels du programme sinon
//les outputs vont s'ajouter les uns a la suite des autres
