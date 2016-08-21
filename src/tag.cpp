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

    std::vector<Tag *> TagList::getValue() {
        return list;
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

    std::ostream &operator<<(std::ostream &out, Tag *_tag) {
        switch (_tag->getType()) {
            case TagType::TypeEnd: {
                out << "======TypeEnd=========" << std::endl;
                break;
            }
            case TagType::TypeByte: {
                TagByte *tag = (TagByte *) _tag;
                out << ">>TagByte>>" << tag->getKey() << ">>" << tag->getValue() << std::endl;
                break;
            }
            case TagType::TypeShort: {
                TagShort *tag = (TagShort *) _tag;
                out << ">>TagShort>>" << tag->getKey() << ">>" << tag->getValue() << std::endl;
                break;
            }
            case TagType::TypeInt: {
                TagInt *tag = (TagInt *) _tag;
                out << ">>TagInt>>" << tag->getKey() << ">>" << tag->getValue() << std::endl;
                break;
            }
            case TagType::TypeLong: {
                TagLong *tag = (TagLong *) _tag;
                out << ">>TagLong>>" << tag->getKey() << ">>" << tag->getValue() << std::endl;
                break;
            }
            case TagType::TypeFloat: {
                TagFloat *tag = (TagFloat *) _tag;
                out << ">>TagFloat>>" << tag->getKey() << ">>" << tag->getValue() << std::endl;
                break;
            }
            case TagType::TypeDouble: {
                TagDouble *tag = (TagDouble *) _tag;
                out << ">>TagDouble>>" << tag->getKey() << ">>" << tag->getValue() << std::endl;
                break;
            }
            case TagType::TypeByteArray: {
                TagByteArray *tag = (TagByteArray *) _tag;
                out << ">>TagByteArray>>" << tag->getKey() << ">>";
                for (int i = 0; i < tag->getSize(); i++) {
                    if (i % 8 == 0) out << ">>";
                    out << std::hex << (0xff & tag->getValue()[i]) << " ";
                    if (i % 8 == 0) out << std::endl;
                }
                out << std::endl;
                break;
            }
            case TagType::TypeIntArray: {
                TagIntArray *tag = (TagIntArray *) _tag;
                out << ">>TagIntArray>>" << tag->getKey() << ">>";
                for (int i = 0; i < tag->getSize(); i++) {
                    if (i % 8 == 0) out << ">>";
                    out << tag->getValue()[i] << " ";
                    if (i % 8 == 0) out << std::endl;
                }
                out << std::endl;
                break;
            }
            case TagType::TypeString: {
                TagString *tag = (TagString *) _tag;
                out << ">>TagString>>" << tag->getKey() << ">>" << tag->getValue() << std::endl;
                break;
            }
            case TagType::TypeList: {
                TagList *tag = (TagList *) _tag;
                std::vector<Tag *> list = tag->getValue();
                int size = (int) list.size();

                out << ">>TagList>>" << tag->getKey() << ">>";

                switch (tag->getListType()) {
                    case TagType::TypeEnd:
                        out << "You should not see this,if you,some thing was wrong!" << std::endl;
                        break;
                    case TagType::TypeByte:
                        out << "ListByte>>" << std::endl;
                        break;
                    case TagType::TypeShort:
                        out << "ListShort>>" << std::endl;
                        break;
                    case TagType::TypeInt:
                        out << "ListInt>>" << std::endl;
                        break;
                    case TagType::TypeLong:
                        out << "ListLong>>" << std::endl;
                        break;
                    case TagType::TypeFloat:
                        out << "ListFloat>>" << std::endl;
                        break;
                    case TagType::TypeDouble:
                        out << "ListDouble>>" << std::endl;
                        break;
                    case TagType::TypeByteArray:
                        out << "ListByteArray>>" << std::endl;
                        break;
                    case TagType::TypeIntArray:
                        out << "ListIntArray>>" << std::endl;
                        break;
                    case TagType::TypeString:
                        out << "ListString>>" << std::endl;
                        break;
                    case TagType::TypeList:
                        out << "ListList>>" << std::endl;
                        break;
                    case TagType::TypeCompound:
                        out << "ListCompound>>" << std::endl;
                        break;
                }
                for (int i = 0; i < size; i++) {
                    out << "--" << list[i];
                }
                break;
            }
            case TagType::TypeCompound: {
                TagCompound *tag = (TagCompound *) _tag;
                std::vector<Tag *> compound = tag->getValue();
                int size = (int) compound.size();

                out << ">>TagCompound>>" << tag->getKey() << ">>";

                for (int i = 0; i < size; i++) {
                    out << "~~" << compound[i];
                }
                break;
            }
        }
        return out;
    }

}
