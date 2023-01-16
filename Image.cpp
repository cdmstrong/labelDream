#include "image.h"


Image2d::Image2d() {

}


Image2d::~Image2d() {

}
void Image2d::addLabel(labelType &an) {
    cout << "addLabel" << endl;
    this->labelList.push_back(an);
}

