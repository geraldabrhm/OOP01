#include "./MainKrap.hpp"

MainKrap::MainKrap(){

}

MainKrap* MainKrap::getInstance(){
    if (instance == nullptr){
      instance = new MainKrap;
      return instance;
   }
}

