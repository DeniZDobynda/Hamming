#include "hemming.h"
#include "math.h"

hemming::hemming()
{

}

QString hemming::code(char* text)
{
    if (text.length() != 7) return NULL;

    int p = ((int)text.data()[0]+int(text.data()[1])+int(text.data()[3])+int(text.data()[4])+int(text.data()[6]),
                   int(text.data()[0])+int(text.data()[2])+int(text.data()[3])+int(text.data()[5])+int(text.data()[6]),
                   int(text.data()[1])+int(text.data()[2])+int(text.data()[3]),
                   int(text.data()[4])+int(text.data()[5])+int(text.data()[6]) );

    for(int i = 0; i < 3; ++i)
    {
        if ( p[i] % 2 == 0)
        {
            p[i] = 0;
        }else{
            p[i] = 1;
        }
    }

    QString result = "";
    result.append(QString(p[0]));
    result.append(QString(p[1]));
    result.append(text.data()[0]);
    result.append(QString(p[2]));
    result.append(text.data()[1]);
    result.append(text.data()[2]);
    result.append(text.data()[3]);
    result.append(QString(p[3]));
    result.append(text.data()[4]);
    result.append(text.data()[5]);
    result.append(text.data()[6]);

    return result;
}

int hemming::decode(QString text)
{
    if (text.length() != 11) return NULL;

    int error = 0;

   int  p = {0, int(text.data()[2])+int(text.data()[4])+int(text.data()[6])+int(text.data()[8])+int(text.data()[10]),
                       int(text.data()[2])+int(text.data()[5])+int(text.data()[6])+int(text.data()[9])+int(text.data()[10]),
                       int(text.data()[4])+int(text.data()[5])+int(text.data()[6]),
                       int(text.data()[8])+int(text.data()[9])+int(text.data()[10]) }

    for ( int i = 1; i < 5; ++i)
   {
       if ( p[i] % 2 == 0)
       {
           p[i] = 0;
       }else{
           p[i] = 1;
       }

       int two = 1;

       for ( k = 0; k <= i-1; ++i)
       {
           two *= 2;
       }

       if ( p[i] != int(text.data()[two-1]))
       {
           error += two;
       }
   }

   return error;
}
