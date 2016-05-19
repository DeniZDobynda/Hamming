#ifndef HEMMING_H
#define HEMMING_H
#include <QMainWindow>

class hemming
{
public:
    hemming();

    QString code(char* text);

    int decode(QString text);
};

#endif // HEMMING_H
