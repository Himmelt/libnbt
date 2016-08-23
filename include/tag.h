/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/
#ifndef LIBNBT_TAG_H
#define LIBNBT_TAG_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace libnbt {

    enum class TagType {
        TypeEnd,
        TypeByte, TypeShort, TypeInt, TypeLong, TypeFloat, TypeDouble,
        TypeByteArray, TypeString,
        TypeList, TypeCompound,
        TypeIntArray
    };

    class Tag {

    private:
        TagType type;
        std::string key = "";
        bool inlist = false;
    public:
        Tag();

        Tag(std::string key);

        Tag(bool _inlist);

        bool isInlist();

        void setInlist(bool _inlist);

        ~Tag();

        void setKey(std::string key);

        std::string getKey();

        void setType(TagType type);

        TagType getType();

    };

    class TagByte : public Tag {

    private:
        int8_t value;
    public:
        TagByte(std::string key);

        TagByte(bool _inlist);

        int8_t getValue();

        void setValue(int8_t val);
    };

    class TagShort : public Tag {
    private:
        int16_t value;
    public:
        TagShort(std::string key);

        TagShort(bool _inlist);

        int16_t getValue();

        void setValue(int16_t val);
    };

    class TagInt : public Tag {
    private:
        int32_t value;
    public:
        TagInt(std::string key);

        TagInt(bool _inlist);

        int32_t getValue();

        void setValue(int32_t val);
    };

    class TagLong : public Tag {
    private:
        int64_t value;
    public:
        TagLong(std::string key);

        TagLong(bool _inlist);

        int64_t getValue();

        void setValue(int64_t val);
    };

    class TagFloat : public Tag {
    private:
        float value;
    public:
        TagFloat(std::string key);

        TagFloat(bool _inlist);

        float getValue();

        void setValue(float val);
    };

    class TagDouble : public Tag {
    private:
        double value;
    public:
        TagDouble(std::string key);

        TagDouble(bool _inlist);

        double getValue();

        void setValue(double val);
    };

    class TagByteArray : public Tag {
    private:
        int8_t *value;
        int size;
    public:
        TagByteArray(std::string key, int size);

        TagByteArray(bool _inlist, int size);

        int8_t *getValue();

        int getSize();

        void setValue(int8_t *val);
    };

    class TagString : public Tag {
    private:
        std::string value = "";
    public:
        TagString(std::string key);

        TagString(bool _inlist);

        std::string getValue();

        void setValue(std::string val);
    };

    class TagList : public Tag {
    private:
        TagType listType;
        std::vector<Tag *> list;
    public:
        TagList(std::string key, TagType listType);

        TagList(bool _inlist, TagType listType);

        TagType getListType();

        std::vector<Tag *> getValue();

        void appendValue(Tag *val);

        void deleteValue(int index);
    };

    class TagCompound : public Tag {
    private:
        std::vector<Tag *> compound;
    public:
        TagCompound(std::string key);

        TagCompound(bool _inlist);

        std::vector<Tag *> getValue();

        void appendValue(Tag *val);

        void deleteValue(int index);
    };

    class TagIntArray : public Tag {
    private:
        int32_t *value;
        int size;
    public:
        TagIntArray(std::string key, int size);

        TagIntArray(bool _inlist, int size);

        int getSize();

        int32_t *getValue();

        void setValue(int32_t *val);
    };

    std::ostream &operator<<(std::ostream &out, Tag *_tag);

    std::fstream &operator<<(std::fstream &out, Tag *_tag);

    std::ostream &operator<<(std::ostream &out, TagType type);

    std::fstream &operator<<(std::fstream &out, TagType type);

}

#endif //LIBNBT_TAG_H
