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





int main(int argc, char **argv) {
    printf("hello %s!\n", (argc > 1 ? argv[1] : "world"));
    return 0;
}

