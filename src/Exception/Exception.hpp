#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <iostream>
using namespace std;

class BaseException{
public:
    virtual void printMessage() =0;
};

/**
 * @brief Menghandle kasus tipe salah
 *
 * * Kasus:
 *      1. Diinginkan itemNonTool -> isTool = false
 *      2. Diinginkan itemTool -> isTool = true
 */
class InvalidTypeException: public BaseException{
private:
    bool isTool;
public:
    InvalidTypeException(bool isTool);
    void printMessage();
};

/**
 * @brief Exception untuk menghandle apabila ada item dengan nama dan tipe yang tidak sama distack
 * 
 */
class NotSameException: public BaseException{
public:
    NotSameException();
    void printMessage();
};
/**
 * @brief Menghandle kasus collectionn penuh ketika ditambahkan item
 * 
 */
class FullCollectionException: public BaseException{
public:
    FullCollectionException();
    void printMessage();
};

/**
 * @brief Menghandle kasus error dalam perhitungan 
 * 
 */

class ArithmeticException: public BaseException{
private:
    //Given -> Angka yang diberikan
    //Need -> Angka maksimal (need > 0) atau minimal (need <0) yang tersedia
    int given;
    int need;
public:
    ArithmeticException(int given, int need);
    void printMessage();
};

/**
 * @brief Exception paling 'bawah' yang digunakan untuk mencetak Exception
 * 
 */
class OperationFailedException: public BaseException{
private:
    BaseException* exc;
public:
    OperationFailedException(BaseException* exc);

    void printMessage();
};

#endif
