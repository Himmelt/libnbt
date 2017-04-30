#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {
    NBTTagByte::NBTTagByte() {
        this->type = TYPE_BYTE;
    }
    NBTTagByte::NBTTagByte(int8_t data) {
        this->type = TYPE_BYTE;
        this->data = data;
    }
    void NBTTagByte::set(int8_t data) {
        this->data = data;
    }
    int8_t NBTTagByte::get() {
        return this->data;
    }
    void NBTTagByte::read(std::istream & in) {
        data = NBT::read_byte(in);
    }
    void NBTTagByte::write(std::ostream & out) {
        NBT::write(out, data);
    }
    bool NBTTagByte::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagByte*)tag)->data;
        }
        return false;
    }

    NBTTagShort::NBTTagShort() {
        this->type = TYPE_SHORT;
    }

    NBTTagShort::NBTTagShort(int16_t data) {
        this->type = TYPE_SHORT;
        this->data = data;
    }
    void NBTTagShort::set(int16_t data) {
        this->data = data;
    }
    int16_t NBTTagShort::get() {
        return this->data;
    }
    void NBTTagShort::read(std::istream & in) {
        data = NBT::read_short(in);
    }
    void NBTTagShort::write(std::ostream & out) {
        NBT::write(out, data);
    }
    bool NBTTagShort::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagShort*)tag)->data;
        }
        return false;
    }

    NBTTagInt::NBTTagInt() {
        this->type = TYPE_INT;
    }

    NBTTagInt::NBTTagInt(int32_t data) {
        this->type = TYPE_INT;
        this->data = data;
    }
    void NBTTagInt::set(int32_t data) {
        this->data = data;
    }
    int32_t NBTTagInt::get() {
        return this->data;
    }
    void NBTTagInt::read(std::istream & in) {
        data = NBT::read_int(in);
    }
    void NBTTagInt::write(std::ostream & out) {
        NBT::write(out, data);
    }
    bool NBTTagInt::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagInt*)tag)->data;
        }
        return false;
    }

    NBTTagLong::NBTTagLong() {
        this->type = TYPE_LONG;
    }

    NBTTagLong::NBTTagLong(int64_t data) {
        this->type = TYPE_LONG;
        this->data = data;
    }
    void NBTTagLong::set(int64_t data) {
        this->data = data;
    }
    int64_t NBTTagLong::get() {
        return this->data;
    }
    void NBTTagLong::read(std::istream & in) {
        data = NBT::read_long(in);
    }
    void NBTTagLong::write(std::ostream & out) {
        NBT::write(out, data);
    }
    bool NBTTagLong::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagLong*)tag)->data;
        }
        return false;
    }

    NBTTagFloat::NBTTagFloat() {
        this->type = TYPE_FLOAT;
    }

    NBTTagFloat::NBTTagFloat(float_t data) {
        this->type = TYPE_FLOAT;
        this->data = data;
    }
    void NBTTagFloat::set(float_t data) {
        this->data = data;
    }
    float_t NBTTagFloat::get() {
        return this->data;
    }
    void NBTTagFloat::read(std::istream & in) {
        data = NBT::read_float(in);
    }
    void NBTTagFloat::write(std::ostream & out) {
        NBT::write(out, data);
    }
    bool NBTTagFloat::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagFloat*)tag)->data;
        }
        return false;
    }

    NBTTagDouble::NBTTagDouble() {
        this->type = TYPE_DOUBLE;
    }

    NBTTagDouble::NBTTagDouble(double_t data) {
        this->type = TYPE_DOUBLE;
        this->data = data;
    }
    void NBTTagDouble::set(double_t data) {
        this->data = data;
    }
    double_t NBTTagDouble::get() {
        return this->data;
    }
    void NBTTagDouble::read(std::istream & in) {
        data = NBT::read_double(in);
    }
    void NBTTagDouble::write(std::ostream & out) {
        NBT::write(out, data);
    }
    bool NBTTagDouble::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagDouble*)tag)->data;
        }
        return false;
    }

    NBTTagString::NBTTagString() {
        this->type = TYPE_STRING;
        this->data = new std::string();
    }

    NBTTagString::NBTTagString(std::string data) {
        this->type = TYPE_STRING;
        this->data = new std::string();
        *this->data = data;
    }
    NBTTagString::~NBTTagString() {
        delete data;
    }
    void NBTTagString::set(std::string data) {
        *this->data = data;
    }
    std::string NBTTagString::get() {
        return *this->data;
    }
    void NBTTagString::read(std::istream & in) {
        int16_t length = NBT::read_short(in);
        *this->data = NBT::read_string(in, length);
    }
    void NBTTagString::write(std::ostream & out) {
        int16_t length = (int16_t)data->size();
        NBT::write(out, length);
        out.write(data->c_str(), length);
    }
    bool NBTTagString::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagString*)tag)->data;
        }
        return false;
    }
}
