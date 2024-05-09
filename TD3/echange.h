#ifndef ECHANGE_H
#define ECHANGE_H

template <typename T>
void echange( T &a, T &b){
    T temp(a);
    a = b;
    b = temp;
};

#endif // ECHANGE_H
