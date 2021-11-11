#include <stdio.h>
#include <stdlib.h>

int min_delka_hesel = 0;
int ascii_tabulka[93];
int unikatni_znaky = 0;
double pocet_hesel = 0, delka_hesel;

//projde retezec a zjisti jestli obsahuje male pismeno
int malaPismena(char str[]){
    int mala_pismena = 0;

    for(int i = 0; str[i] != '\0'; i++){
        if( (str[i] >= 'a' && str[i] < 'z')){
            mala_pismena = 1;
            break;
        }
    } 
    return (mala_pismena)? 1 : 0;
}
//projde retezec a zjisti jestli obsahuje velke pismeno
int velkaPismena(char str[]){
    int velka_pismena = 0;

    for(int i = 0; str[i] != '\0'; i++){
        if( (str[i] >= 'A' && str[i] < 'Z')){
            velka_pismena = 1;
            break;
        }
    } 
    return (velka_pismena)? 1 : 0;
}
//projde retezec a zjisti jestli obsahuje cislo
int numCisla(char str[]){
    int num_cisla = 0;

    for(int i = 0; str[i] != '\0'; i++){
        if( (str[i] >= '0' && str[i] < '9')){
            num_cisla = 1;
            break;
        }
    } 
    return (num_cisla)? 1 : 0;
}
//projde retezec a zjisti jestli obsahuje specialni znak
int specialniZnaky(char str[]){
    int specialni_znaky = 0;
 
    for(int i = 0; str[i] != '\0'; i++){
        if( (str[i] >= ' ' && str[i] < '0') || (str[i] > '9' && str[i] < 'A') || (str[i] > 'Z' && str[i] < 'a') || (str[i] > 'z' && str[i] <= '~') ){
            specialni_znaky = 1;
            break;
        }
    } 
    return (specialni_znaky)? 1 : 0;
}
//zjisti delku retezce
int delka_retezce(char str[]){
    int i;

    for(i = 0; str[i] != '\0'; i++){
    } 
    return i;

}
//porovna delky vsech hesel a zjisti nejmensi delku hesla
void minDelkaHesla(int length){

    if(min_delka_hesel == 0 || length < min_delka_hesel){
        min_delka_hesel = length;
    }
}

//zjisti vsechny znaky v textovem dokumentu
void vsechny_znaky(char str[]){
    int i;
    
    for(i = 0; str[i] != '\0'; i++){
        for(int z = 0; z < 94; z++){
            if(str[i] == z+32){
                ascii_tabulka[z] = 1;
            }
        }
    }
}

//porovna dva retezce jselti jsou stejne
int porovnej_string(char str1[], char str2[]){
    int i = 0;

    while(str1[i] == str2[i]){
        if(str1[i] == '\0' || str2[i] == '\0'){
            break;
        } 
        i++;
    } 
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 1;
    } 
    return 0;
}

//funkce pro praci s heslem
int prace_s_heslem(char str[], int potrebny_level, int potrebny_param){

    int level = 0, param = 0, potrebny_pram_na_level2 = potrebny_param, c = 0;
    pocet_hesel++;
    delka_hesel += delka_retezce(str);
    minDelkaHesla(delka_retezce(str));
    vsechny_znaky(str);
    //level 1 (obsahuje velke a male pismeno)
    if(malaPismena(str) && velkaPismena(str)){
        level++;
    }
    //level 2 (parametry)
    if(potrebny_level > 1){
        if(potrebny_param > 4){
            potrebny_pram_na_level2 = 4;
        }   
        if(malaPismena(str)){
            param++;
        } 
        if(velkaPismena(str)){
            param++;
        } 
        if(numCisla(str)){
            param++;
        } 
        if(specialniZnaky(str)){
            param++;
        }
        if(param >= potrebny_pram_na_level2){
            level++;
        }
    }
    //level 3 
    if(potrebny_level > 2){
        c = 0;

        for(int i = 0; str[i] != '\0'; i++){
            if(str[i] == str[i+1]){
                c++;
            }
        }
        if(c+1 < potrebny_param){
            level++;
        }
    }

    //level 4 
    if(potrebny_level > 3){
        c = 0;

        for(int i = 0; str[i] != '\0'; i++){
            if(str[i] == str[i+potrebny_param]){
                c++;
            }
        }
        if(c < potrebny_param){
            level++;
        }
    }   
    if(potrebny_level == level){
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]){
    //dva argumenty programu
    int level, param;
    //promene pro kontrolu datoveho typu 
    char *endptr, *endptr1;
    //zjisteni tretiho argumentu
    char *stats;

    if(argc > 3){
        strtoul(argv[3], &stats, 10);
    }
    //kontrola argumentu
    if(argc < 3){
        printf("Chybi nejaky argument!\n");
        return 1;
    }
    level = strtoul(argv[1], &endptr, 11);
    //kontrola parametru LEVEL, zda je ve spravnem tvaru
    if(endptr[0] != '\0'){
        printf("Chybny tvar argumentu LEVEL!\n");
        return 1;
    }
    //kontrola parametru LEVEL
    if(level < 1 || level > 4){
        printf("Chybne zadany argument LEVEL, LEVEL musi byt cele cislo v intervalu <1, 4>\n");
        return 1;
    }
    param = strtoul(argv[2], &endptr1, 12);
    //kontrola parametru PARAM, zda je ve spravnem tvaru
    if(endptr1[0] != '\0'){
        printf("Chybny tvar argumentu PARAM!\n");
        return 1;
    }
    //kontrola parametru PARAM
    if(param < 1){
        printf("Chybne zadany argument PARAM, PARAM musi byt cele kladne cislo v intervalu\n");
        return 1;
    }


    int c, i;
    char heslo[104];

    while ((c = getchar()) != EOF) {
        if(c == '\n'){
            //zkontroluje jestli heslo neobsahuje vice jak 100 znaku
            if(delka_retezce(heslo) > 100){
                printf("Heslo nemuze mit vice nez 100 znaku!\n");
                continue;
            }
            heslo[i] = '\0';
            //kontrola jestli heslo splnuje podminky
            if(prace_s_heslem(heslo, level, param)){
                printf("%s \n", heslo);
            }
            i=0;
            continue;
        }
        heslo[i] = c;
        i++;
    }
    //urci pocet jedinecnich znaku v textovem dokumentu
    for(i = 0; i < 94; i++){
        if(ascii_tabulka[i] == 1){
            unikatni_znaky++;
        }
    }
    //porovna --stats z tretim argumentem programu (pokud se rovnaji vypise statistiku)
    if(porovnej_string(stats, "--stats")){

        printf("Statistika:\n");
        printf("Ruznych znaku: %d\n", unikatni_znaky);
        printf("Minimalni delka: %d\n", min_delka_hesel);
        printf("Prumerna delka: %.1f", delka_hesel/pocet_hesel);

    }
    return 0;
}