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

    TagByte::TagByte(std::string key) : Tag(key) {
        setType(TagType::TypeByte);
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

    TagShort::TagShort(std::string key) : Tag(key) {
        setType(TagType::TypeShort);
    }

    int32_t TagInt::getValue() {
        return value;
    }

    void TagInt::setValue(int32_t val) {
        value = val;
    }

    TagInt::TagInt(std::string key) : Tag(key) {
        setType(TagType::TypeInt);
    }

    int64_t TagLong::getValue() {
        return value;
    }

    void TagLong::setValue(int64_t val) {
        value = val;
    }

    TagLong::TagLong(std::string key) : Tag(key) {
        setType(TagType::TypeLong);
    }

    float TagFloat::getValue() {
        return value;
    }

    void TagFloat::setValue(float val) {
        value = val;
    }

    TagFloat::TagFloat(std::string key) : Tag(key) {
        setType(TagType::TypeFloat);
    }

    double TagDouble::getValue() {
        return value;
    }

    void TagDouble::setValue(double val) {
        value = val;
    }

    TagDouble::TagDouble(std::string key) : Tag(key) {
        setType(TagType::TypeDouble);
    }

    int8_t *TagByteArray::getValue() {
        return value;
    }

    void TagByteArray::setValue(int8_t *val) {
        value = val;
    }

    TagByteArray::TagByteArray(std::string key, int size) : Tag(key) {
        setType(TagType::TypeByteArray);
        TagByteArray::size = size;
    }

    int TagByteArray::getSize() {
        return size;
    }

    std::string TagString::getValue() {
        return value;
    }

    void TagString::setValue(std::string val) {
        value = val;
    }

    TagString::TagString(std::string key) : Tag(key) {
        setType(TagType::TypeString);
    }

    void TagList::appendValue(Tag *val) {
        list.push_back(val);
    }

    void TagList::deleteValue(int index) {
        Tag *tag = list[index];
        try {
            delete tag;
        }
        catch (int) {
            std::cout << "Dynamic Data Erase Error!!" << std::endl;
        }
        list.erase(list.begin() + index);
    }

    TagList::TagList(std::string key, TagType listType) : Tag(key) {
        setType(TagType::TypeList);
        TagList::listType = listType;
    }

    TagType TagList::getListType() {
        return listType;
    }

    void TagCompound::appendValue(Tag *val) {
        compound.push_back(val);
    }

    void TagCompound::deleteValue(int index) {
        Tag *tag = compound[index];
        try {
            delete tag;
        }
        catch (int) {
            std::cout << "Dynamic Data Erase Error!!" << std::endl;
        }
        compound.erase(compound.begin() + index);
    }

    TagCompound::TagCompound(std::string key) : Tag(key) {
        setType(TagType::TypeCompound);
    }

    int32_t *TagIntArray::getValue() {
        return value;
    }

    void TagIntArray::setValue(int32_t *val) {
        value = val;
    }

    TagIntArray::TagIntArray(std::string key, int size) : Tag(key) {
        setType(TagType::TypeIntArray);
        TagIntArray::size = size;
    }

    int TagIntArray::getSize() {
        return size;
    }
}
