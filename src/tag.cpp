/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/
#include "../include/tag.h"

namespace libnbt {
    Tag::Tag() {
        Tag::key = "root";
    }

    Tag::Tag(std::string key) {
        Tag::key = key;
    }

    Tag::~Tag() {
    }

    void Tag::setKey(std::string key) {
        Tag::key = key;
    }

    std::string Tag::getKey() {
        return key;
    }

    void Tag::setType(TagType type) {
        Tag::type = type;
    }

    TagType Tag::getType() {
        return type;
    }

    int8_t TagByte::getValue() {
        return value;
    }

    void TagByte::setValue(int8_t val) {
        value = val;
    }

    int16_t TagShort::getValue() {
        return value;
    }

    void TagShort::setValue(int16_t val) {
        value = val;
    }

    int32_t TagInt::getValue() {
        return value;
    }

    void TagInt::setValue(int32_t val) {
        value = val;
    }

    int64_t TagLong::getValue() {
        return value;
    }

    void TagLong::setValue(int64_t val) {
        value = val;
    }

    float TagFloat::getValue() {
        return value;
    }

    void TagFloat::setValue(float val) {
        value = val;
    }

    double TagDouble::getValue() {
        return value;
    }

    void TagDouble::setValue(double val) {
        value = val;
    }

    int8_t *TagByteArray::getValue() {
        return value;
    }

    void TagByteArray::setValue(int8_t *val) {
        value = val;
    }

    std::string TagString::getValue() {
        return value;
    }

    void TagString::setValue(std::string val) {
        value = val;
    }

    std::vector<Tag *> *TagList::getValue() {
        return list;
    }

    void TagList::setValue(std::vector<Tag *> *val) {
        list = val;
    }

    void TagList::appendValue(Tag *val) {
        list->push_back(val);
    }

    void TagList::deleteValue(int index) {
        Tag *tag = (*list)[index];
        try {
            delete tag;
        }
        catch (int) {
            std::cout << "Dynamic Data Erase Error!!" << std::endl;
        }
        list->erase(list->begin() + index);
    }

    std::vector<Tag *> *TagCompound::getValue() {
        return compound;
    }

    void TagCompound::setValue(std::vector<Tag *> *val) {
        compound = val;
    }

    void TagCompound::appendValue(Tag *val) {
        compound->push_back(val);
    }

    void TagCompound::deleteValue(int index) {
        Tag *tag = (*compound)[index];
        try {
            delete tag;
        }
        catch (int) {
            std::cout << "Dynamic Data Erase Error!!" << std::endl;
        }
        compound->erase(compound->begin() + index);
    }

    int32_t *TagIntArray::getValue() {
        return value;
    }

    void TagIntArray::setValue(int32_t *val) {
        value = val;
    }

}
