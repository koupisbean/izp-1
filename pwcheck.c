/*
    @name 1. Projekt IZP - overovani sily hesel (prace s textem)
    @author Jan Kopecký (xkopec59@stud.fit.vutbr.cz)
*/

#include <stdio.h>
#include <stdlib.h>

//pro funkci minLengthOfPassword()
//"globalni" promena pro minimalni delku hesla, vzdy obsahuje minimalni delku
int min_length_password = 0;

//pro funkci allChars()
//kazdy index bude obsahovat 1 nebo 0 (pokud se ASCII znak nachazi)
int ascii_table[93];
//vsechny 1 sectene z pole ascii_table 
int unique_chars = 0;

//pro funkci handlePasswords()
double count_password = 0, length_of_passwords;



/* 
    zkontroluje retezec zda obsahuje urcite znaky

    @param type typ kontroly
    @param str retezec pro kontrolu
    @return 1 pokud retezec obsahuje minimalne jeden znak z urcite skupiny (type)

    type 0 => lowercase
    type 1 => uppercase
    type 2 => numbers 

*/
int isSomething(int type, char str[]){
    int condition = 0, max,min;

    //zvoli se maximalni a minimalni pozadavky pro kontrolu
    switch(type){
        case 0:
            min = 'a';
            max = 'z';
            break;
        case 1:
            min = 'A';
            max = 'Z';
            break;
        case 2:
            min = '0';
            max = '9';
            break;
    }

    //cyklus pro kontrolu retezce
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= min && str[i] <= max){
            condition = 1;
            break;
        }
    }

    return (condition)? 1 : 0;

}

/* 
    zkontroluje retezec zda obsahuje specialni znaky

    @param str retezec pro kontrolu
    @return 1 pokud retezec obsahuje minimalne jeden specialni znak

*/
int isSpecialChars(char str[]){

    int special_chars = 0;

    //cyklus pro kontrolu retezce 
    for(int i = 0; str[i] != '\0'; i++){
 
        if( (str[i] >= ' ' && str[i] < '0') || (str[i] > '9' && str[i] < 'A') || (str[i] > 'Z' && str[i] < 'a') || (str[i] > 'z' && str[i] <= '~') ){
            special_chars = 1;
            break;
        }

    }

    return (special_chars)? 1 : 0;

}

/* 
    zjisti delku retezce

    @param str retezec pro zjisteni
    @return delka retezce

*/
int stringLength(char str[]){

    int i;
    for(i = 0; str[i] != '\0'; i++){
        //silence is gold
    }
    return i;

}

/* 
    porovna delky hesel mezi sebou a ziska nejmensi delku hesla

    @param length delka hesla
*/
void minLengthOfPassword(int length){

    //nejdriv se musi nastavit min_length_password na delku (pri prvni kontrole hesla), pote se porovna heslo s kterym se pracuje a min_length_password
    if(min_length_password == 0 || length < min_length_password){
        min_length_password = length;
    }

}

/* 
    zjisti vsechny znaky ze vsech hesel

    @param length delka hesla
*/
void allChars(char str[]){
  
    int i;

    for(i = 0; str[i] != '\0'; i++){

        for(int z = 0; z < 94; z++){

            if(str[i] == z+32){
                ascii_table[z] = 1;
            }

        }

    }

}

/* 
    zkontroluje pokud se 2 retezec rovnaji

    @param str1 prvni retezec pro kontrolu
    @param str2 prvni retezec pro kontrolu
*/
int stringCompare(char str1[], char str2[])
{
    int i = 0;

    //dokud se charakter ze str1 rovna charakteru ze str2 cyklus pracuje
    while(str1[i] == str2[i])
    {
        //jestli se jeden z charakteru rovna konec radku => ukonci se cyklus a vrati se chybne hlasky
        if(str1[i] == '\0' || str2[i] == '\0'){
            break;
        }
        i++;
    }

    //pokud se oba charaktery rovnaji konec radku 
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 1;
    }
    
    return 0;
}


/* 

    hlavni funkce pro praci s heslama

    @param str retezec hesla
    @param needed_level potrebny level (argument z cmd)
    @param needed_param potrebny parametr (argument z cmd)

*/
int handlePasswords(char str[], int needed_level, int needed_param){

    int level = 0, param = 0, needed_lvl2_param = needed_param, c = 0;

    //pricte ze se pracuje s heslem
    count_password++;

    //pricte k celkove delce hesel delku aktualniho hesla, s kterym pracujeme
    length_of_passwords += stringLength(str);

    //zjisti jake heslo ma nejmene znaku
    minLengthOfPassword(stringLength(str));

    //zjisti jake znaky se v hesle nachazi
    allChars(str);



    //prvni level - obsahuje alespon 1 velke a male pismeno
    if(isSomething(0, str) && isSomething(1, str)){
        level++;
    }

    //druhy level - prace s parametrama
    if(needed_level > 1){

        //pokud je param vetsi, nastavi maximalni param pro level 2 na 4
        if(needed_param > 4){
            needed_lvl2_param = 4;
        }

        //lowercase
        if(isSomething(0, str)){
            param++;
        }

        //uppercase
        if(isSomething(1, str)){
            param++;
        }
        
        //number
        if(isSomething(2, str)){
            param++;
        }

        if(isSpecialChars(str)){
            param++;
        }

        //pokud byly vsechny potrebne podminky splneny, splni se level
        if(param >= needed_lvl2_param){
            level++;
        }
    }

    //treti level
    if(needed_level > 2){

        c = 0;
        //projede charakter po charakteru
        for(int i = 0; str[i] != '\0'; i++){
            //zjisti pocet stejnych pismen vedle sebe
            // stejnych pismen vedle sebe je o + 1 (zapomene se pricist prvni pismeno)
            if(str[i] == str[i+1]){
                c++;
            }
        }

        //o+1 = pocet stejnych pismen vedle sebe
        //pokud je pocet stejnych pismen vedle sebe mensi nez param, pricte se level
        if(c+1 < needed_param){
            level++;
        }

    }

    //ctvrty level
    if(needed_level > 3){

        c = 0;
        //projede charakter po charakteru
        for(int i = 0; str[i] != '\0'; i++){

            //zjisti zda se charakter s indexem i rovna jako charakter s indexem i+param
            if(str[i] == str[i+needed_param]){
                c++;
            }

        }
        
        //c = pocet stejnych pismenek i a i+param
        //pokud je pocet stejnych pismenek i a i+param mensi jako potrebny parametr, pricte se level
        if(c < needed_param){
            level++;
        }

    }   

    //pokud je potrebny level stejny jako levely, ktere prosly, funkce se vyhodnoti jako uspesna
    if(needed_level == level){
        return 1;
    }

    return 0;

}

int main(int argc, char* argv[])
{
    //prvni a druhy argument programu
    int level, param, isstats = 0;
    
    // //pomocne promene pro kontrolu zda jsou argumenty ve tvaru string nebo int
    char *endptr, *endptr1;

    //pro zjisteni tretiho argumentu, zda se jedna o "--stats"
    char *stats;

    //kontrola parametru => jestli nechybi level/param
    if(argc < 3){
        printf("[CHYBA] :: Musite zadat vsechny argumenty!\n");
        printf(" ./pwcheck (LEVEL <1,4>) (PARAM <1, ..>) [--stats] \n");
        return EXIT_FAILURE;
    }

    //pokud prikaz obsahuje vice jak 3 argumenty vytvori se string z toho tretiho pro kontrolu na vypsani statistik
    if(argc > 3){
        strtoul(argv[3], &stats, 10);
        isstats = 1;
    }

    //prevede prvni argument na int
    level = strtoul(argv[1], &endptr, 11);

    //prevede druhy argument na int
    param = strtoul(argv[2], &endptr1, 12);

    //kontrola parametru LEVEL => musi byt v intervalu <1,4>
    if(level < 1 || level > 4){
        printf("[CHYBA] :: Chybne zadany argument LEVEL!\n");
        printf(" (LEVEL <1,4>) \n");
        return EXIT_FAILURE;
    }

    //kontrola parametru PARAM => musi byt cele kladne cislo
    if(param < 1){
        printf("[CHYBA] :: Chybne zadany argument PARAM!\n");
        printf(" (PARAM <1, ..>) \n");
        return EXIT_FAILURE;
    }

    //c = chars z funkce getchar()
    int c, i;
    //samostatne heslo ze vstupu, 104 => kdyby heslo bylo delsi jak 100 znaku, vypise se chyba
    char password[104];

    //postupne nacita charakter za charakterem dokud nedorazi na konec souboru 
    while ((c = getchar()) != EOF) {
        
        //pokud je konec radku
        if(c == '\n'){

            //kontrola pro heslo, zda je delsi jako 100 znaku
            if(stringLength(password) > 100){
                printf("[CHYBA] :: Heslo je delsi nez 100 znaku!\n");
                continue;
            }

            //nastavi posledni cast retezce password na konec retezce
            password[i] = '\0';

            //zjisti zda heslo odpovida podminkam, pokud ano, vypise heslo
            if(handlePasswords(password, level, param)){
                printf("%s \n", password);
            }

            //nastavi i na 0 coz znamena ze vymazene puvodni heslo
            i=0;

            //preskoci pridani \n do promene password
            continue;

        }

        //nacita heslo po charakteru do promene password
        password[i] = c;

        i++;

    }
    
    //secteni vsech 1 v poli ascii_table => zjisteni vsech ruznych znaku v heslech
    for(i = 0; i < 94; i++){

        if(ascii_table[i] == 1){
            unique_chars++;
        }

    }

    //porovna treti argument programu s retezcem "--stats", pokud se rovna, vypise statistiku
    if(isstats == 1 && stringCompare(stats, "--stats")){

        printf("\nStatistika:");
        printf("\nRuznych znaku: %d", unique_chars);
        printf("\nMinimalni delka: %d", min_length_password);
        printf("\nPrumerna delka: %.1f\n", length_of_passwords/count_password);

    }

    return EXIT_SUCCESS;

}
