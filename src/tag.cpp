#include <cstdint>
#include "include/tag.h"

namespace libnbt {

    NBTBase *NBTBase::createNewByType(uint8_t id) {
        switch (id) {
            case 0:
                return new NBTTagEnd();
            case 1:
                return new NBTTagByte();
            case 2:
                return new NBTTagShort();
            case 3:
                return new NBTTagInt();
            case 4:
                return new NBTTagLong();
            case 5:
                return new NBTTagFloat();
            case 6:
                return new NBTTagDouble();
            case 7:
                return new NBTTagByteArray();
            case 8:
                return new NBTTagString();
            case 9:
                return new NBTTagList();
            case 10:
                return new NBTTagCompound();
            case 11:
                return new NBTTagIntArray();
            default:
                return nullptr;
        }
    }

    bool NBTBase::equals(NBTBase *tag) {
        if (typeid(tag) != typeid(this)) {
            return false;
        } else {
            return this->getType() == tag->getType();
        }
    }

    string NBTTagShort::toString() {
        return to_string(this->data) + "s";
    }

    TAG_TYPE NBTTagShort::getType() {
        return SHORT;
    }

    NBTBase *NBTTagShort::copy() {
        return new NBTTagShort(this->data);
    }

    void NBTTagShort::write(uint8_t *data) {

    }

    void NBTTagShort::read(uint8_t *data, int depth) {

    }

    bool NBTTagShort::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagShort::equals(NBTBase *tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagShort *) tag)->data;
        } else {
            return false;
        }
    }

    string NBTTagShort::getString() {
        return NBTBase::getString();
    }

    string NBTTagInt::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagInt::getType() {
        return INT;
    }

    NBTBase *NBTTagInt::copy() {
        return nullptr;
    }

    void NBTTagInt::write(uint8_t *data) {

    }

    void NBTTagInt::read(uint8_t *data, int depth) {

    }

    bool NBTTagInt::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagInt::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagInt::getString() {
        return NBTBase::getString();
    }

    string NBTTagLong::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagLong::getType() {
        return LONG;
    }

    NBTBase *NBTTagLong::copy() {
        return nullptr;
    }

    void NBTTagLong::write(uint8_t *data) {

    }

    void NBTTagLong::read(uint8_t *data, int depth) {

    }

    bool NBTTagLong::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagLong::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagLong::getString() {
        return NBTBase::getString();
    }

    string NBTTagFloat::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagFloat::getType() {
        return FLOAT;
    }

    NBTBase *NBTTagFloat::copy() {
        return nullptr;
    }

    void NBTTagFloat::write(uint8_t *data) {

    }

    void NBTTagFloat::read(uint8_t *data, int depth) {

    }

    bool NBTTagFloat::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagFloat::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagFloat::getString() {
        return NBTBase::getString();
    }

    string NBTTagDouble::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagDouble::getType() {
        return DOUBLE;
    }

    NBTBase *NBTTagDouble::copy() {
        return nullptr;
    }

    void NBTTagDouble::write(uint8_t *data) {

    }

    void NBTTagDouble::read(uint8_t *data, int depth) {

    }

    bool NBTTagDouble::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagDouble::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagDouble::getString() {
        return NBTBase::getString();
    }

    string NBTTagByteArray::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagByteArray::getType() {
        return BYTE_ARRAY;
    }

    NBTBase *NBTTagByteArray::copy() {
        return nullptr;
    }

    void NBTTagByteArray::write(uint8_t *data) {

    }

    void NBTTagByteArray::read(uint8_t *data, int depth) {

    }

    bool NBTTagByteArray::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagByteArray::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagByteArray::getString() {
        return NBTBase::getString();
    }

    string NBTTagString::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagString::getType() {
        return STRING;
    }

    NBTBase *NBTTagString::copy() {
        return nullptr;
    }

    void NBTTagString::write(uint8_t *data) {

    }

    void NBTTagString::read(uint8_t *data, int depth) {

    }

    bool NBTTagString::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagString::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagString::getString() {
        return NBTBase::getString();
    }

    string NBTTagList::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagList::getType() {
        return LIST;
    }

    NBTBase *NBTTagList::copy() {
        return nullptr;
    }

    void NBTTagList::write(uint8_t *data) {

    }

    void NBTTagList::read(uint8_t *data, int depth) {

    }

    bool NBTTagList::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagList::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagList::getString() {
        return NBTBase::getString();
    }

    string NBTTagCompound::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagCompound::getType() {
        return COMPOUND;
    }

    NBTBase *NBTTagCompound::copy() {
        return nullptr;
    }

    void NBTTagCompound::write(uint8_t *data) {

    }

    void NBTTagCompound::read(uint8_t *data, int depth) {

    }

    size_t NBTTagCompound::getSize() {
        return this->tagMap.size();
    }

    void NBTTagCompound::setTag(string key, NBTBase *value) {
        this->tagMap.insert({key, value});
    }

    bool NBTTagCompound::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagCompound::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagCompound::getString() {
        return NBTBase::getString();
    }

    NBTBase *NBTTagCompound::getTag(string key) {
        if (hasKey(key)) {
            return tagMap.at(key);
        }
        return nullptr;
    }

    TAG_TYPE NBTTagCompound::getTagId(string key) {
        if (hasKey(key)) {
            return tagMap.at(key)->getType();
        }
        return END;
    }

    bool NBTTagCompound::hasKey(string key) {
        return tagMap.find(key) == tagMap.end();
    }

    bool NBTTagCompound::hasKey(string key, uint8_t type) {
        return hasKey(key) && tagMap.at(key)->getType() == type;
    }

    void NBTTagCompound::setByte(string key, uint8_t value) {
        if (hasKey(key, 1)) {
            ((NBTTagByte *) tagMap.at(key))->setByte(value);
        } else {
            tagMap.insert({key, new NBTTagByte(value)});
        }
    }

    void NBTTagCompound::setShort(string key, int16_t value) {

    }

    void NBTTagCompound::setInteger(string key, int32_t value) {

    }

    void NBTTagCompound::setLong(string key, int64_t value) {

    }

    void NBTTagCompound::setFloat(string key, float value) {

    }

    void NBTTagCompound::setDouble(string key, double value) {

    }

    void NBTTagCompound::setString(string key, string value) {

    }

    void NBTTagCompound::setByteArray(string key, vector<string> *value) {

    }

    void NBTTagCompound::setIntArray(string key, vector<int> *value) {

    }

    void NBTTagCompound::setBoolean(string key, bool value) {

    }

    string NBTTagIntArray::toString() {
        return nullptr;
    }

    TAG_TYPE NBTTagIntArray::getType() {
        return INT_ARRAY;
    }

    NBTBase *NBTTagIntArray::copy() {
        return nullptr;
    }

    void NBTTagIntArray::write(uint8_t *data) {

    }

    void NBTTagIntArray::read(uint8_t *data, int depth) {

    }

    bool NBTTagIntArray::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagIntArray::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagIntArray::getString() {
        return NBTBase::getString();
    }

    string NBTTagEnd::toString() {
        return "END";
    }

    TAG_TYPE NBTTagEnd::getType() {
        return END;
    }

    NBTBase *NBTTagEnd::copy() {
        return new NBTTagEnd();
    }

    void NBTTagEnd::write(uint8_t *data) {

    }

    void NBTTagEnd::read(uint8_t *data, int depth) {

    }

    bool NBTTagEnd::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    bool NBTTagEnd::equals(NBTBase *tag) {
        return NBTBase::equals(tag);
    }

    string NBTTagEnd::getString() {
        return NBTBase::getString();
    }

    string NBTTagByte::toString() {
        return to_string(this->data) + "b";
    }

    TAG_TYPE NBTTagByte::getType() {
        return BYTE;
    }

    NBTBase *NBTTagByte::copy() {
        return new NBTTagByte(this->data);
    }

    void NBTTagByte::write(uint8_t *data) {

    }

    void NBTTagByte::read(uint8_t *data, int depth) {

    }

    bool NBTTagByte::equals(NBTBase *tag) {
        if (NBTBase::equals(tag)) {
            return this->data == ((NBTTagByte *) tag)->data;
        } else {
            return false;
        }
    }

    bool NBTTagByte::hasNoTags() {
        return NBTBase::hasNoTags();
    }

    string NBTTagByte::getString() {
        return NBTBase::getString();
    }

}
