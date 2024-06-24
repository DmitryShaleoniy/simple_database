//База данных содержит сведения о домах в районе : улица, номер дома, тип дома, количество квартир, суммарная площадь.
//Программа должна формировать бинарный файл типа «структура», добавлять и удалять данные, а также воспринимать каждый 
//из перечисленных запросов и давать на него ответ.
//1. Определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного.
//2. Определять, каких типов домов в районе больше.Найти их суммарную площадь.
//3. Определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице.
//Для обработки файла и выбора типа обработки использовать консольное меню.

#include <iostream>
#include <windows.h>

struct House {
    int id;
    char street[21];
    int number;
    char type[16];
    int flats;
    float square;
    int floors;
};

void SetHome(House &home) {
    printf("\nвведите название улицы (символьная строка):\n");
    getchar();
    gets_s(home.street);
    OemToCharA(home.street, home.street);
    printf("\nвведите номер дома (целое число):\n");
    scanf("%d", &home.number);
    printf("\nвведите тип дома (символьная строка):\n");
    getchar();
    gets_s(home.type);
    OemToCharA(home.type, home.type);
    printf("\nвведите количество квартир в доме (целое число):\n");
    scanf("%d", &home.flats);
    printf("\nвведите суммарную площадь квартир в доме (вещестевенное число):\n");
    scanf("%f", &home.square);
    printf("\nвведите количество этажей в доме(целое число):\n");
    scanf("%d", &home.floors);
}

int PrintBase(FILE* f, int id) {
    House home;
    printf("\n-----------------------------------------------------ЕКАТЕРИНБУРГ-----------------------------------------------------\n");
    printf("\n---------------------------------------------------РАЙОН ПИОНЕРСКИЙ---------------------------------------------------\n");
    printf("\n| ID |        улица        | номер дома |    тип дома    | количество квартир | суммарная площадь | количество этажей |\n");
    while (fread(&home, sizeof(home), 1, f) > 0) {
        printf("|%4d|%21s|%12d|%16s|%20d|%19.3f|%19d|\n", home.id, home.street, home.number, home.type, home.flats, home.square, home.floors);
        id = home.id;
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    id++;
    return id;
}

int main() {
    setlocale(LC_ALL, "RU");
    int key, id = 1;
    char* buf;
    FILE* f;
    printf("выберите опцию:\n1)создать базу данных\n2)использовать существующую базу данных\n---------------------------------------\n");
    if (scanf("%d", &key), key == 1) {
        id = 1;
        f = fopen("file.dat", "wb");
        printf("\nвыберите опцию:\n1)добавить дом\n2)выход\n");
        while (scanf("%d", &key), key == 1) {
            House home;
            home.id = id;
            id++;
            SetHome(home);
            fwrite(&home, sizeof(home), 1, f);
            printf("\nвыберите опцию:\n1)добавить еще один дом\n2)выход\n");
        }
        fclose(f);
    }
    printf("\nсодержимое вашей базы данных:\n");
    f = fopen("file.dat", "rb");
    id = PrintBase(f, id);
    printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");
    int a;
    fclose(f);
    /*House SetID;
    f = fopen("file.dat", "rb");
    fseek(f, sizeof(House), 2);
    fwrite(&SetID, -1*sizeof(SetID), 1, f);
    id = SetID.id;
    fclose(f);*/
    while (scanf("%d", &a), a != 8) {
        switch (a) {
        case 1: {
            f = fopen("file.dat", "ab");
            printf("\nвыберите опцию:\n1)добавить дом\n2)выход\n");
            while (scanf("%d", &key), key == 1) {
                House home;
                home.id = id;
                id++;
                SetHome(home);
                fwrite(&home, sizeof(home), 1, f);
                printf("\nвыберите опцию:\n1)добавить еще один дом\n2)выход\n");
            }
            fclose(f);
            printf("\nсодержимое вашей базы данных:\n");
            f = fopen("file.dat", "rb");
            PrintBase(f, id);
            printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");        
            fclose(f);
            break;
            }
        case 2: {
            House ToDel;
            int id_del;
            id = 1;
            printf("\nвведите id дома, который вы хотите удалить:\n");
            scanf("%d", &id_del);
            FILE* buf = fopen("bufer.dat", "wb");
            f = fopen("file.dat", "rb");
            while (fread(&ToDel, sizeof(ToDel), 1, f) > 0) {
                if (ToDel.id != id_del) {
                    ToDel.id = id;
                    id++;
                    fwrite(&ToDel, sizeof(ToDel), 1, buf);
                }
            }
            fclose(f);
            fclose(buf);
            _unlink("file.dat");
            rename("bufer.dat", "file.dat");
            f = fopen("file.dat", "rb");
            PrintBase(f, id);
            printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");
            fclose(f);
            break;
            }
        case 3: {
            House Red;
            int id_red;
            id = 1;
            printf("\nвведите ID дома, данные которого вы хотите отредактировать:\n");
            scanf("%d", &id_red);
            FILE* buf = fopen("bufer.dat", "wb");
            f = fopen("file.dat", "rb");
            while (fread(&Red, sizeof(Red), 1, f) > 0) {
                if (Red.id != id_red) {
                    fwrite(&Red, sizeof(Red), 1, buf);                   
                }
                else {
                    int par;
                    printf("\nкакой параметр вы хотите отредактировать:\n1)улица\n2)номер\n3)тип\n4)кол-во квартир\n5)площадь\n6)кол-во этажей\n");
                    scanf("%d", &par);
                    switch (par) {
                    case 1: {
                        printf("\nвведите название улицы:\n");
                        getchar();
                        gets_s(Red.street); 
                        OemToCharA(Red.street, Red.street);
                        break;
                    }
                    case 2: {
                        printf("\nвведите номер дома:\n");
                        scanf("%d", &Red.number); break;
                    }
                    case 3: {
                        printf("\nвведите тип дома:\n");
                        getchar();
                        gets_s(Red.type); 
                        OemToCharA(Red.type, Red.type);
                        break;
                    }
                    case 4: {
                        printf("\nвведите кол-во квартир:\n");
                        scanf("%d", &Red.flats); break;
                    }
                    case 5: {
                        printf("\nвведите суммарную площадь:\n");
                        scanf("%f", &Red.square); break;
                    }
                    case 6: {
                        printf("\nвведите кол-во этажей:\n");
                        scanf("%d", & Red.floors); break;
                    }
                    }
                    fwrite(&Red, sizeof(Red), 1, buf);

                }
                id++;
            }
            fclose(f);
            fclose(buf);
            _unlink("file.dat");
            rename("bufer.dat", "file.dat");
            f = fopen("file.dat", "rb");
            PrintBase(f, id);
            printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");
            fclose(f);
            break;
            }
        case 4: {
            House Red;
            int id_red;
            id = 1;
            printf("\nвведите ID дома, данные которого вы хотите отредактировать:\n");
            scanf("%d", &id_red);
            FILE* buf = fopen("bufer.dat", "wb");
            f = fopen("file.dat", "rb");
            while (fread(&Red, sizeof(Red), 1, f) > 0) {
                if (Red.id != id_red) {
                    fwrite(&Red, sizeof(Red), 1, buf);
                }
                else {
                    SetHome(Red);
                    fwrite(&Red, sizeof(Red), 1, buf);
                }
                id++;
            }
            fclose(f);
            fclose(buf);
            _unlink("file.dat");
            rename("bufer.dat", "file.dat");
            f = fopen("file.dat", "rb");
            PrintBase(f, id);
            printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");
            fclose(f);
            break;
        }
        case 5: {
            printf("\nвведите  максимальную площадь:\n");
            float max_sq;
            int min_fl;
            scanf("%f", &max_sq);
            printf("\nвведите минимальное количество квартир:\n");
            scanf("%d", &min_fl);
            f = fopen("file.dat", "rb");
            House home;
            printf("\n---------------------------------------------------ПОДХОДЯЩИЕ  ДОМА---------------------------------------------------\n");
            printf("\n| ID |        улица        | номер дома |    тип дома    | количество квартир | суммарная площадь | количество этажей |\n");
            while (fread(&home, sizeof(home), 1, f) > 0) {
                if (home.flats >= min_fl && home.square <= max_sq)
                    printf("|%4d|%21s|%12d|%16s|%20d|%19.3f|%19d|\n", home.id, home.street, home.number, home.type, home.flats, home.square, home.floors);
            }
            printf("\n----------------------------------------------------------------------------------------------------------------------\n");
            rewind(f);
            printf("\nнажмите любую клавишу для продолжения\n");
            getchar();
            printf("\nсодержимое вашей базы данных:\n");
            PrintBase(f, id);
            printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");
            fclose(f);
            break;
        }
        case 6: {
            int NovoCount = 0;
            int KhrushCount = 0;
            int BrezhCount = 0;
            f = fopen("file.dat", "rb");
            House home;
            while (fread(&home, sizeof(home), 1, f) > 0) {
                if (strcmp(home.type, "Новострой") == 0) NovoCount++;
                else if (strcmp(home.type, "Хрущевка") == 0) KhrushCount++;
                else if (strcmp(home.type, "Брежневка") == 0) BrezhCount++;
            }
            fclose(f);
            char res[12];
            strcpy(res, "Новострой");
            int max = NovoCount, ResSqure = 0;
            if (KhrushCount > max) { max = KhrushCount; strcpy(res, "Хрущевка"); }
            if (BrezhCount > max) { max = BrezhCount; strcpy(res, "Брежневка"); }
            printf("\nв данном районе  больше всего домов типа: %s\n", res);
            printf("\n---------------------------------------------------ПОДХОДЯЩИЕ  ДОМА---------------------------------------------------\n");
            printf("\n| ID |        улица        | номер дома |    тип дома    | количество квартир | суммарная площадь | количество этажей |\n");
            f = fopen("file.dat", "rb");
            while (fread(&home, sizeof(home), 1, f) > 0) {
                if (strcmp(home.type, res) == 0) {
                    printf("|%4d|%21s|%12d|%16s|%20d|%19.3f|%19d|\n", home.id, home.street, home.number, home.type, home.flats, home.square, home.floors);
                    ResSqure += home.square;
                }
            }
            printf("\n----------------------------------------------------------------------------------------------------------------------\n");
            printf("\nсуммарная площадь домов типа %s = %d\n", res, ResSqure);
            rewind(f);
            printf("\nнажмите любую клавишу для продолжения\n");
            getchar();
            printf("\nсодержимое вашей базы данных:\n");
            PrintBase(f, id);
            printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");
            fclose(f);
            break;
        }
        case 7: {
            House home;
            int FloorMin;
            float SqRes = 0;
            char res[22];
            printf("\nвведите минимальное количество этажей:\n");
            scanf("%d", &FloorMin);
            printf("\n---------------------------------------------------ПОДХОДЯЩИЕ  ДОМА---------------------------------------------------\n");
            printf("\n| ID |        улица        | номер дома |    тип дома    | количество квартир | суммарная площадь | количество этажей |\n");
            f = fopen("file.dat", "rb");
            char** streets = (char**)malloc(0);
            int StreetsDim = 0;
            while (fread(&home, sizeof(home), 1, f) > 0) {
                if (home.floors >= FloorMin) {
                    printf("|%4d|%21s|%12d|%16s|%20d|%19.3f|%19d|\n", home.id, home.street, home.number, home.type, home.flats, home.square, home.floors);
                    int count = 0;
                    for (int i = 0; i < StreetsDim; i++) {
                        if (strcmp(*(streets + i), home.street) == 0) count++;
                    }
                    if (count == 0) {
                        StreetsDim++;
                        streets = (char**)realloc(streets, StreetsDim * sizeof(char*));
                        *(streets + (StreetsDim - 1)) = (char*)malloc(21);
                        strcpy(*(streets + (StreetsDim - 1)), home.street);
                    }
                }
            }
            printf("\n----------------------------------------------------------------------------------------------------------------------\n");
            rewind(f);
            printf("\nнайденные улицы:\n");
            for (int i = 0; i < StreetsDim; i++) {
                printf("%s\n", *(streets + i));
                free (* (streets + i));
            }
            free(streets);
            printf("\nввдеите улицу, общую площадь этих домов на которой необходимо получить:\n");
            getchar();
            gets_s(res);
            OemToCharA(res, res);
            while (fread(&home, sizeof(home), 1, f) > 0) {
                if (home.floors >= FloorMin && strcmp(res, home.street) == 0) {
                    SqRes += home.square;
                }
            }
            printf("\nполученная площадь: %.3f\n", SqRes);
            rewind(f);
            printf("\nнажмите enter для продолжения\n");
            getchar();
            printf("\nсодержимое вашей базы данных:\n");
            PrintBase(f, id);
            printf("выберите опцию:\n1)дополнить базу\n2)удалить позицию из базы\n3)редактировать позицию из базы\n4)Заменить строку базы\n5)определять, какие дома в районе имеют площадь, меньше заданной, и количество квартир, не меньше указанного\n6)определять, каких типов домов в районе больше.Найти их суммарную площадь\n7)определять улицы, на которых есть дома указанной этажности.Получить общую площадь этих домов на заданной улице\n8)Выход\n");
            fclose(f);
            break;
        }
        }
    }
}