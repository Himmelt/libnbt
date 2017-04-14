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
                return NULL;
        }
    }

    bool NBTBase::equals(NBTBase *tag) {
        if (typeid(tag) != typeid(this)) {
            return false;
        } else {
            return this->getId() == tag->getId();
        }
    }

    string NBTTagShort::toString() {
        return NULL;
    }

    uint8_t NBTTagShort::getId() {
        return NULL;
    }

    NBTBase *NBTTagShort::copy() {
        return NULL;
    }

    void NBTTagShort::write(uint8_t *data) {

    }

    void NBTTagShort::read(uint8_t *data, int depth) {

    }

    string NBTTagInt::toString() {
        return NULL;
    }

    uint8_t NBTTagInt::getId() {
        return NULL;
    }

    NBTBase *NBTTagInt::copy() {
        return NULL;
    }

    void NBTTagInt::write(uint8_t *data) {

    }

    void NBTTagInt::read(uint8_t *data, int depth) {

    }

    string NBTTagLong::toString() {
        return NULL;
    }

    uint8_t NBTTagLong::getId() {
        return NULL;
    }

    NBTBase *NBTTagLong::copy() {
        return NULL;
    }

    void NBTTagLong::write(uint8_t *data) {

    }

    void NBTTagLong::read(uint8_t *data, int depth) {

    }

    string NBTTagFloat::toString() {
        return NULL;
    }

    uint8_t NBTTagFloat::getId() {
        return NULL;
    }

    NBTBase *NBTTagFloat::copy() {
        return NULL;
    }

    void NBTTagFloat::write(uint8_t *data) {

    }

    void NBTTagFloat::read(uint8_t *data, int depth) {

    }

    string NBTTagDouble::toString() {
        return NULL;
    }

    uint8_t NBTTagDouble::getId() {
        return NULL;
    }

    NBTBase *NBTTagDouble::copy() {
        return NULL;
    }

    void NBTTagDouble::write(uint8_t *data) {

    }

    void NBTTagDouble::read(uint8_t *data, int depth) {

    }

    string NBTTagByteArray::toString() {
        return NULL;
    }

    uint8_t NBTTagByteArray::getId() {
        return NULL;
    }

    NBTBase *NBTTagByteArray::copy() {
        return NULL;
    }

    void NBTTagByteArray::write(uint8_t *data) {

    }

    void NBTTagByteArray::read(uint8_t *data, int depth) {

    }

    string NBTTagString::toString() {
        return NULL;
    }

    uint8_t NBTTagString::getId() {
        return NULL;
    }

    NBTBase *NBTTagString::copy() {
        return NULL;
    }

    void NBTTagString::write(uint8_t *data) {

    }

    void NBTTagString::read(uint8_t *data, int depth) {

    }

    string NBTTagList::toString() {
        return NULL;
    }

    uint8_t NBTTagList::getId() {
        return NULL;
    }

    NBTBase *NBTTagList::copy() {
        return NULL;
    }

    void NBTTagList::write(uint8_t *data) {

    }

    void NBTTagList::read(uint8_t *data, int depth) {

    }

    string NBTTagCompound::toString() {
        return NULL;
    }

    uint8_t NBTTagCompound::getId() {
        return 10;
    }

    NBTBase *NBTTagCompound::copy() {
        return NULL;
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

    string NBTTagIntArray::toString() {
        return NULL;
    }

    uint8_t NBTTagIntArray::getId() {
        return NULL;
    }

    NBTBase *NBTTagIntArray::copy() {
        return NULL;
    }

    void NBTTagIntArray::write(uint8_t *data) {

    }

    void NBTTagIntArray::read(uint8_t *data, int depth) {

    }

    string NBTTagEnd::toString() {
        return "END";
    }

    uint8_t NBTTagEnd::getId() {
        return 0;
    }

    NBTBase *NBTTagEnd::copy() {
        return new NBTTagEnd();
    }

    void NBTTagEnd::write(uint8_t *data) {

    }

    void NBTTagEnd::read(uint8_t *data, int depth) {

    }

    string NBTTagByte::toString() {
        return to_string(this->data) + "b";
    }

    uint8_t NBTTagByte::getId() {
        return 1;
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
}
