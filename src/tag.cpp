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

    bool Tag::isInlist() {
        return inlist;
    }

    void Tag::setInlist(bool _inlist) {
        inlist = _inlist;
    }

    Tag::Tag(bool _inlist) {
        Tag();
        inlist = _inlist;
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

    TagByte::TagByte(bool _inlist) : Tag(_inlist) {
        setType(TagType::TypeByte);
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

    TagShort::TagShort(bool _inlist) : Tag(_inlist) {
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

    TagInt::TagInt(bool _inlist) : Tag(_inlist) {
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

    TagLong::TagLong(bool _inlist) : Tag(_inlist) {
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

    TagFloat::TagFloat(bool _inlist) : Tag(_inlist) {
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

    TagDouble::TagDouble(bool _inlist) : Tag(_inlist) {
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

    TagByteArray::TagByteArray(bool _inlist, int size) : Tag(_inlist) {
        setType(TagType::TypeByteArray);
        TagByteArray::size = size;
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

    TagString::TagString(bool _inlist) : Tag(_inlist) {
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

    std::vector<Tag *> TagList::getValue() {
        return list;
    }

    TagList::TagList(bool _inlist, TagType listType) : Tag(_inlist) {
        setType(TagType::TypeList);
        TagList::listType = listType;
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

    std::vector<Tag *> TagCompound::getValue() {
        return compound;
    }

    TagCompound::TagCompound(bool _inlist) : Tag(_inlist) {
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

    TagIntArray::TagIntArray(bool _inlist, int size) : Tag(_inlist) {
        setType(TagType::TypeIntArray);
        TagIntArray::size = size;
    }

    std::ostream &operator<<(std::ostream &out, Tag *_tag) {
        switch (_tag->getType()) {
            case TagType::TypeEnd: {
                out << "}";
                break;
            }
            case TagType::TypeByte: {
                TagByte *tag = (TagByte *) _tag;
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getValue();
                break;
            }
            case TagType::TypeShort: {
                TagShort *tag = (TagShort *) _tag;
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getValue();
                break;
            }
            case TagType::TypeInt: {
                TagInt *tag = (TagInt *) _tag;
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getValue();
                break;
            }
            case TagType::TypeLong: {
                TagLong *tag = (TagLong *) _tag;
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getValue();
                break;
            }
            case TagType::TypeFloat: {
                TagFloat *tag = (TagFloat *) _tag;
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getValue();
                break;
            }
            case TagType::TypeDouble: {
                TagDouble *tag = (TagDouble *) _tag;
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getValue();
                break;
            }
            case TagType::TypeByteArray: {
                TagByteArray *tag = (TagByteArray *) _tag;
                int arraySize = tag->getSize();
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << "[";
                for (int i = 0; i < arraySize; i++) {
                    out << (0xff & tag->getValue()[i]);
                    if (i < arraySize - 1)out << ",";
                }
                out << "]";
                break;
            }
            case TagType::TypeIntArray: {
                TagIntArray *tag = (TagIntArray *) _tag;
                int arraySize = tag->getSize();
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << "[";
                for (int i = 0; i < arraySize; i++) {
                    out << tag->getValue()[i];
                    if (i < arraySize - 1)out << ",";
                }
                out << "]";
                break;
            }
            case TagType::TypeString: {
                TagString *tag = (TagString *) _tag;
                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";
                out << "\"" << tag->getValue() << "\"";
                break;
            }
            case TagType::TypeList: {
                TagList *tag = (TagList *) _tag;
                std::vector<Tag *> list = tag->getValue();
                int listSize = (int) list.size();

                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";

                out << "[";

                for (int i = 0; i < listSize; i++) {
                    out << list[i];
                    if (i < listSize - 1) out << ",";
                }
                out << "]";
                break;
            }
            case TagType::TypeCompound: {
                TagCompound *tag = (TagCompound *) _tag;
                std::vector<Tag *> compound = tag->getValue();
                int compoundSize = (int) compound.size();

                if (!tag->isInlist())
                    out << "\"" << tag->getKey() << "\":";

                out << "{";

                for (int i = 0; i < compoundSize; i++) {
                    out << compound[i];
                    if (i < compoundSize - 1) out << ",";
                }
                out << "}";
                break;
            }
        }
        return out;
    }

    std::ostream &operator<<(std::ostream &out, TagType type) {
        switch (type) {
            case TagType::TypeEnd:
                out << "TypeEnd";
                break;
            case TagType::TypeByte:
                out << "TypeByte";
                break;
            case TagType::TypeShort:
                out << "TypeShort";
                break;
            case TagType::TypeInt:
                out << "TypeInt";
                break;
            case TagType::TypeLong:
                out << "TypeLong";
                break;
            case TagType::TypeFloat:
                out << "TypeFloat";
                break;
            case TagType::TypeDouble:
                out << "TypeDouble";
                break;
            case TagType::TypeByteArray:
                out << "TypeByteArray";
                break;
            case TagType::TypeString:
                out << "TypeString";
                break;
            case TagType::TypeList:
                out << "TypeList";
                break;
            case TagType::TypeCompound:
                out << "TypeCompound";
                break;
            case TagType::TypeIntArray:
                out << "TypeIntArray";
                break;
        }
        return out;
    }

}
