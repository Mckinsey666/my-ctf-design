#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char *name = NULL;
long age = 0;
long l[0x10];
char *n[0x10];

int read_int(){
    char buf[16];
    if( __read_chk(0,buf,15,15) <= 0 ){
        puts("read error");
        exit(1);
    }
    return (unsigned int)atoi(buf);
} 	


void add(){
    for( int i = 0 ; i < 0x10 ; ++i ){
        if( !n[i] ){
            puts( "Size of chunk:" );
            unsigned int size = read_int();

            n[i] = (char*)malloc( size );
            if( !n[i] ){
                puts("Alloc error!");
                exit(0);
            }
            l[i] = size;
            puts( "Leave something in the chunk:" );
            read( 0 , n[i] , size );
            puts( "done!" );
            return;
        }
    }
    puts("Full!");
    return ;
}

void edit(){
    printf("Index:");
    unsigned i = read_int();
    if( i > 9 ) {
        puts("Nop!");
        exit(0);
    }

    if( n[i] ){
        puts( "Leave something in the chunk:" );
        read( 0 , n[i] , l[i] );

        puts( "done!" );
        return;
    }
    
    puts("No such chunk!");
    return ;
}


void show(){
    printf("Index:");
    unsigned i = read_int();
    if( i > 9 ) {
        puts("Nop!");
        exit(0);
    }

    if( n[i] ) printf( "%s\n" , n[i] );
    else puts("No such chunk!");

    return ;
}


void info(){
    char buf[0x20];
    memset( buf , 0 , 0x20 );
    printf( "Name : %s\nAge: %ld\nchange your name? (1.yes/0.no)" , name , age  );
    unsigned int i = read_int();
    if( i ){
        printf( "New name:" );
        read( 0 , buf , 0x18 );
        char *tmp = realloc( name , strlen( buf ) );
        if( !tmp ){
            puts("Alloc error!");
            return;
        }
        strncpy( name , buf , strlen( buf ) );
    }
    return;
}

void menu(){
    puts("----------------");
    puts("1. add a chunk ");
    puts("2. edit a chunk ");
    puts("3. show a chunk ");
    puts("4. information ");
    puts("5. exit");
    puts("----------------");
    puts("Your choice:");
}

int main(){
    setvbuf(stdin,0,2,0);
	setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
    
    puts( "What's your name?" );
    name = (char*)malloc( 0x10 );
    read( 0 , name , 0x10 );

    puts( "What's your age?" );
    age = read_int();

    while(1){
        menu();
        switch( read_int() ){
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                show();
                break;
            case 4:
                info();
                break;
            case 5:
                printf("Bye!\n");
                _exit(0);
                break;
            default:
                puts("Invalid choice!");
                break;
        }  
    }

    return 0;
}