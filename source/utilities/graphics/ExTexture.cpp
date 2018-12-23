#include "ExTexture.h"

void ExTexture::init() {
    wFrame = this->getSize().x;
    hFrame = this->getSize().y;
}

void ExTexture::createMultiTexture(std::string type,
                                   unsigned int rows, unsigned int columns,
                                   unsigned int wFrame, unsigned int hFrame) {

    this->type = type;

    this->rows = rows;
    this->columns = columns;

    this->wFrame = wFrame;
    this->hFrame = hFrame;
}

