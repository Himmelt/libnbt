/*******************************************************************************
 * Created by Himmelt on 2016/8/18.
 * Copyright (c) 2015-2016. Himmelt All rights reserved.
 * https://opensource.org/licenses/MIT
 ******************************************************************************/
#ifndef LIBNBT_TAG_H
#define LIBNBT_TAG_H

#pragma once

#include <iostream>
#include <vector>

namespace libnbt {

    enum class TagType {
        TagEnd,
        TagByte, TagShort, TagInt, TagLong, TagFloat, TagDouble,
        TagByteArray, TagString,
        TagList, TagCompound,
        TagIntArray
    };

    class Tag {
    private:
        TagType type;
        std::string key;
    public:
        Tag();

        Tag(std::string key);

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
        int8_t getValue();

        void setValue(int8_t val);
    };

    class TagShort : public Tag {
    private:
        int16_t value;
    public:
        int16_t getValue();

        void setValue(int16_t val);
    };

    class TagInt : public Tag {
    private:
        int32_t value;
    public:
        int32_t getValue();

        void setValue(int32_t val);
    };

    class TagLong : public Tag {
    private:
        int64_t value;
    public:
        int64_t getValue();

        void setValue(int64_t val);
    };

    class TagFloat : public Tag {
    private:
        float value;
    public:
        float getValue();

        void setValue(float val);
    };

    class TagDouble : public Tag {
    private:
        double value;
    public:
        double getValue();

        void setValue(double val);
    };

    class TagByteArray : public Tag {
    private:
        int8_t *value;
    public:
        int8_t *getValue();

        void setValue(int8_t *val);
    };

    class TagString : public Tag {
    private:
        std::string value;
    public:
        std::string getValue();

        void setValue(std::string val);
    };

    class TagList : public Tag {
    private:
        TagType listType;
        std::vector<Tag *> *list;
    public:
        std::vector<Tag *> *getValue();

        void setValue(std::vector<Tag *> *val);

        void appendValue(Tag *val);

        void deleteValue(int index);
    };

    class TagCompound : public Tag {
    private:
        std::vector<Tag *> *compound;
    public:
        std::vector<Tag *> *getValue();

        void setValue(std::vector<Tag *> *val);

        void appendValue(Tag *val);

        void deleteValue(int index);
    };

    class TagIntArray : public Tag {
    private:
        int32_t *value;
    public:
        int32_t *getValue();

        void setValue(int32_t *val);
    };
}

#endif //LIBNBT_TAG_H
