#include "./Exception.hpp"

InvalidTypeException::InvalidTypeException(bool isTool){
    this->isTool = isTool;
}

void InvalidTypeException::printMessage(){
    cout << "Diiinginkan tipe " << (this->isTool? "item Tool" : "item Non Tool");
    cout << " tetapi diberikan tipe " << (this->isTool? "item Non Tool" : "item Tool") << endl; 
}
NotSameException::NotSameException(){}

void NotSameException::printMessage(){
    cout << "Kedua item memilki nama dan tipe yang berbeda" << endl;
}

FullCollectionException::FullCollectionException(){}

void  FullCollectionException::printMessage(){
    cout << "Tempat Menyimpan penuh!" << endl;
}

ArithmeticException::ArithmeticException(int given, int need){
    this->given = given;
    this->need = need;
}

void ArithmeticException::printMessage(){
    cout << "Diberikan angka " << this->given << (this->need < 0? " padahal minimal " : "padahal maksimal") << abs(this->need) << endl;
}

OperationFailedException::OperationFailedException(BaseException* exc){
    this->exc = exc;
}

void OperationFailedException::printMessage(){
    cout << "Operasi gagal dengan pesan kesalahan: " << endl;
    (this->exc)->printMessage();
}

