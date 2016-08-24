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
#include <typeinfo>

namespace libnbt {

    using namespace std;

    enum class Type {
        End,
        Byte, Short, Int, Long, Float, Double,
        BytA, String,
        List, Comp,
        IntA
    };

    class Tag {
    private:
        string key;
        Type type;
        bool _inlist;
    public:

        Tag();

        Tag(string _key);

        bool inlist();

        string getKey();

        void setKey(string _key);

        Type getType();

        void setType(Type _type);

    };

    template<class T>
    class TagData : public Tag {
    private:
        T val;

        void setDataType() {
            if (typeid(T) == typeid(int8_t))setType(Type::Byte);
            if (typeid(T) == typeid(int16_t))setType(Type::Short);
            if (typeid(T) == typeid(int32_t))setType(Type::Int);
            if (typeid(T) == typeid(int64_t))setType(Type::Long);
            if (typeid(T) == typeid(float))setType(Type::Float);
            if (typeid(T) == typeid(double))setType(Type::Double);
            if (typeid(T) == typeid(std::string))setType(Type::String);
            if (typeid(T) == typeid(vector<int8_t>))setType(Type::BytA);
            if (typeid(T) == typeid(vector<int32_t>))setType(Type::IntA);
        }

    public:
        TagData() : Tag() {
            setDataType();
        }

        TagData(string _key) : Tag(_key) {
            setDataType();
        }

        T &getVal() {
            return val;
        }

        void setVal(T _val) {
            val = _val;
        }
    };

    typedef TagData<int8_t> TagByte;
    typedef TagData<int16_t> TagShort;
    typedef TagData<int32_t> TagInt;
    typedef TagData<int64_t> TagLong;
    typedef TagData<float> TagFloat;
    typedef TagData<double> TagDouble;
    typedef TagData<string> TagString;
    typedef TagData<vector<int8_t>> TagBytA;
    typedef TagData<vector<int32_t>> TagIntA;

    class TagComp : public Tag {
    private:
        vector<Tag *> val;
        Type ltype;
    public:
        TagComp();

        TagComp(Type _ltype);

        TagComp(string _key);

        TagComp(string _key, Type _ltype);

        vector<Tag *> &getVal();

        void addVal(Tag *tag);
    };


    std::ostream &operator<<(std::ostream &out, Tag *_tag);

    std::fstream &operator<<(std::fstream &out, Tag *_tag);

    std::ostream &operator<<(std::ostream &out, Type type);

    std::fstream &operator<<(std::fstream &out, Type type);

}

#endif //LIBNBT_TAG_H
