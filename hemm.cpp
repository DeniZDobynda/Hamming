#include <stdlib.h>
#include <QMainWindow>

QString code(const char* text)
{
    //must have 7 digits
    if (text[7] != '\0') return NULL;

    //creating set from 4 controlling bits (referense to binary arithmeticks)
    int p[4] = {text[0]-'0'+text[1]-'0'+text[3]-'0'+text[4]-'0'+text[6]-'0',
                        text[0]-'0'+text[2]-'0'+text[3]-'0'+text[5]-'0'+text[6]-'0',
                        text[1]-'0'+text[2]-'0'+text[3]-'0',
                        text[4]-'0'+text[5]-'0'+text[6]-'0' };

    //checking for odd or even
    for(int i = 0; i <= 3; ++i)
    {
        if ( p[i] % 2 == 0)  //if odd
        {
            p[i] = 0;   //than "0"
        }else{
            p[i] = 1;       //else "1"
        }
    }

    char* p_char = new char[2];

    //set result using controll bits

    QString result = "";
    itoa(p[0], p_char, 10);
    result.append(p_char);
    itoa(p[1], p_char, 10);
    result.append(p_char);
    result.append(text[0]);
    itoa(p[2], p_char, 10);
    result.append(p_char);
    result.append(text[1]);
    result.append(text[2]);
    result.append(text[3]);
    itoa(p[3], p_char, 10);
    result.append(p_char);
    result.append(text[4]);
    result.append(text[5]);
    result.append(text[6]);

    return result;
}

int decode(char* text)
{
    //must have 11 bits
    if (text[11] != '\0') return NULL;

    int error = 0;
    //variable for storing pointer of error


    //recalculating controll bits
    int  p[5] = {0, text[2]-'0'+text[4]-'0'+text[6]-'0'+text[8]-'0'+text[10]-'0',
                 text[2]-'0'+text[5]-'0'+text[6]-'0'+text[9]-'0'+text[10]-'0',
                 text[4]-'0'+text[5]-'0'+text[6]-'0',
                 text[8]-'0'+text[9]-'0'+text[10]-'0' };

    for ( int i = 1; i < 5; ++i)
    {
        if ( p[i] % 2 == 0)     //checking for odd/even
        {
            p[i] = 0;
        }else{
            p[i] = 1;
        }

        int two = 1;    //two in 0 degree

        //fast power 2 to i
        for (int k = 0; k < i-1; ++k)
        {
            two *= 2;
        }

        //checking recalculated bits if equal to having bits
        if ( p[i] != text[two-1]-'0')
        {
            error += two;       //if not match, error += 2^i
        }
    }
    //returning pointer to error
    return error;
}

QString decode_to_original(char* text)
{
    //must have 11 digits
    if ( text[11] != '\0') return NULL;

    //getting pointer of error
    int err = decode(text);

    //if have error
    if ( err )
    {
        //correct error
        if ( text[err-1] == '0' )
        {
            text[err-1] = '1';
        }else{
            text[err-1] = '0';
        }
    }

    QString result = "";

    //taking only 7 digits without controll bits
    result.append(text[2]);
    result.append(text[4]);
    result.append(text[5]);
    result.append(text[6]);
    result.append(text[8]);
    result.append(text[9]);
    result.append(text[10]);

    return result;
}


