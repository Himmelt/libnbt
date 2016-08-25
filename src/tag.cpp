/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/
#include "../include/tag.h"

namespace libnbt {

    Tag::Tag() {
        _inlist = true;
    }

    Tag::Tag(string _key) {
        key = _key;
        _inlist = false;
    }

    bool Tag::inlist() {
        return _inlist;
    }

    string Tag::getKey() {
        return key;
    }

    void Tag::setKey(string _key) {
        key = _key;
    }

    Type Tag::getType() {
        return type;
    }

    void Tag::setType(Type _type) {
        type = _type;
    }

    TagComp::TagComp() : Tag() {
        setType(Type::Comp);
    }

    TagComp::TagComp(Type _ltype) : Tag() {
        setType(Type::List);
        ltype = _ltype;
    }

    TagComp::TagComp(string _key) : Tag(_key) {
        setType(Type::Comp);
    }

    TagComp::TagComp(string _key, Type _ltype) : Tag(_key) {
        setType(Type::List);
        ltype = _ltype;
    }

    vector<Tag *> &TagComp::getVal() {
        return val;
    }

    void TagComp::addVal(Tag *tag) {
        val.push_back(tag);
    }

    std::ostream &operator<<(std::ostream &out, Tag *_tag) {

        switch (_tag->getType()) {
            case Type::End: {
                out << "If you see this,it must be sth wrong!";
                break;
            }
            case Type::Byte: {
                TagByte *tag = (TagByte *) _tag;
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << (0xff & tag->getVal());
                break;
            }
            case Type::Short: {
                TagShort *tag = (TagShort *) _tag;
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getVal();
                break;
            }
            case Type::Int: {
                TagInt *tag = (TagInt *) _tag;
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getVal();
                break;
            }
            case Type::Long: {
                TagLong *tag = (TagLong *) _tag;
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getVal();
                break;
            }
            case Type::Float: {
                TagFloat *tag = (TagFloat *) _tag;
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getVal();
                break;
            }
            case Type::Double: {
                TagDouble *tag = (TagDouble *) _tag;
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << tag->getVal();
                break;
            }
            case Type::BytA: {
                TagBytA *tag = (TagBytA *) _tag;
                size_t arraySize = tag->getVal().size();
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << "[";
                for (size_t i = 0; i < arraySize; i++) {
                    out << (0xff & tag->getVal()[i]);
                    if (i < arraySize - 1)out << ",";
                }
                out << "]";
                break;
            }
            case Type::IntA: {
                TagIntA *tag = (TagIntA *) _tag;
                size_t arraySize = tag->getVal().size();
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << "[";
                for (size_t i = 0; i < arraySize; i++) {
                    out << tag->getVal()[i];
                    if (i < arraySize - 1)out << ",";
                }
                out << "]";
                break;
            }
            case Type::String: {
                TagString *tag = (TagString *) _tag;
                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";
                out << "\"" << tag->getVal() << "\"";
                break;
            }
            case Type::List: {
                TagComp *tag = (TagComp *) _tag;
                std::vector<Tag *> list = tag->getVal();
                int listSize = (int) list.size();

                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";

                out << "[";

                for (int i = 0; i < listSize; i++) {
                    out << list[i];
                    if (i < listSize - 1) out << ",";
                }
                out << "]";
                break;
            }
            case Type::Comp: {
                TagComp *tag = (TagComp *) _tag;
                std::vector<Tag *> Comp = tag->getVal();
                size_t CompSize = Comp.size();



                if (!tag->inlist())
                    out << "\"" << tag->getKey() << "\":";

                out << "{";

                for (size_t i = 0; i < CompSize; i++) {
                    out << Comp[i];
                    if (i < CompSize - 1) out << ",";
                }
                out << "}";
                break;
            }
        }
        return out;
    }

    std::fstream &operator<<(std::fstream &out, Tag *_tag) {

        switch (_tag->getType()) {
            case Type::End: {
                out << "If you see this,it must be sth wrong!";
                break;
            }
            case Type::Byte: {
                TagByte *tag = (TagByte *) _tag;
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::Byte << (int16_t) key.size();

                    //out.write((char*)(&(key.size())))
                    out.write(key.c_str(), key.size());
                }
                out << tag->getVal();
                break;
            }
            case Type::Short: {
                TagShort *tag = (TagShort *) _tag;
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::Short << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out << tag->getVal();
                break;
            }
            case Type::Int: {
                TagInt *tag = (TagInt *) _tag;
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::Int << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out << tag->getVal();
                break;
            }
            case Type::Long: {
                TagLong *tag = (TagLong *) _tag;
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::Long << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out << tag->getVal();
                break;
            }
            case Type::Float: {
                TagFloat *tag = (TagFloat *) _tag;
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::Float << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out << tag->getVal();
                break;
            }
            case Type::Double: {
                TagDouble *tag = (TagDouble *) _tag;
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::Double << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out << tag->getVal();
                break;
            }
            case Type::BytA: {
                TagBytA *tag = (TagBytA *) _tag;
                int32_t arraySize = (int32_t) tag->getVal().size();
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::BytA << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out << arraySize;
                for (int i = 0; i < arraySize; i++) {
                    out << tag->getVal()[i];
                }
                break;
            }
            case Type::IntA: {
                TagIntA *tag = (TagIntA *) _tag;
                int32_t arraySize = (int32_t) tag->getVal().size();
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::IntA << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out << arraySize;
                for (int i = 0; i < arraySize; i++) {
                    out << tag->getVal()[i];
                }
                break;
            }
            case Type::String: {
                TagString *tag = (TagString *) _tag;
                std::string value = tag->getVal();
                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::String << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }
                out.write(value.c_str(), value.size());
                break;
            }
            case Type::List: {
                TagComp *tag = (TagComp *) _tag;
                std::vector<Tag *> list = tag->getVal();
                int32_t listSize = (int32_t) list.size();

                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::List << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }

                out << tag->getType() << listSize;

                for (int i = 0; i < listSize; i++) {
                    out << list[i];
                }
                break;
            }
            case Type::Comp: {
                TagComp *tag = (TagComp *) _tag;
                std::vector<Tag *> Comp = tag->getVal();
                int CompSize = (int) Comp.size();

                if (!tag->inlist()) {
                    std::string key = tag->getKey();
                    out << Type::Comp << (int16_t) key.size();
                    out.write(key.c_str(), key.size());
                }

                for (int i = 0; i < CompSize; i++) {
                    out << Comp[i];
                }
                out << Type::End;
                break;
            }
        }
        return out;
    }

    std::ostream &operator<<(std::ostream &out, Type type) {
        switch (type) {
            case Type::End:
                out << "TypeEnd";
                break;
            case Type::Byte:
                out << "TypeByte";
                break;
            case Type::Short:
                out << "TypeShort";
                break;
            case Type::Int:
                out << "TypeInt";
                break;
            case Type::Long:
                out << "TypeLong";
                break;
            case Type::Float:
                out << "TypeFloat";
                break;
            case Type::Double:
                out << "TypeDouble";
                break;
            case Type::BytA:
                out << "TypeByteA";
                break;
            case Type::String:
                out << "TypeString";
                break;
            case Type::List:
                out << "TypeList";
                break;
            case Type::Comp:
                out << "TypeComp";
                break;
            case Type::IntA:
                out << "TypeIntArray";
                break;
        }
        return out;
    }

    std::fstream &operator<<(std::fstream &out, Type type) {
        out << (0xff & (int8_t) type);
        return out;
    }
}
