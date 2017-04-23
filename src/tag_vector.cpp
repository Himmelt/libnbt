#include "stdafx.h"
#include "libnbt.h"

namespace libnbt {
    NBTTagByteArray::NBTTagByteArray() {
        this->array = new std::vector<int8_t>();
    }
    NBTTagByteArray::~NBTTagByteArray() {
        delete array;
    }
    void NBTTagByteArray::put(int8_t data) {
        this->array->push_back(data);
    }
    void NBTTagByteArray::set(size_t index, int8_t data) {
        if (index >= 0 && index < this->array->size()) {
            this->array->at(index) = data;
        }
    }
    int8_t NBTTagByteArray::get(size_t index) {
        return this->array->at(index);
    }
    size_t NBTTagByteArray::size() {
        return this->array->size();
    }
    void NBTTagByteArray::clear() {
        this->array->clear();
    }
    void NBTTagByteArray::remove(size_t index) {
        if (index >= 0 && index < array->size()) {
            array->erase(array->begin() + index);
        }
    }
    void NBTTagByteArray::read(std::istream & in) {
        clear();
        int32_t size = NBT::read_int(in);
        for (int i = 0; i < size; i++) {
            int8_t temp = NBT::read_byte(in);
            array->push_back(temp);
        }
    }
    void NBTTagByteArray::write(std::ostream & out) {
        int32_t size = (int32_t)array->size();
        NBT::write(out, size);
        for (int i = 0; i < size; i++) {
            int8_t temp = array->at(i);
            NBT::write(out, temp);
        }
    }
    bool NBTTagByteArray::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->array == ((NBTTagByteArray*)tag)->array;
        }
        return false;
    }

    NBTTagIntArray::NBTTagIntArray() {
        this->array = new std::vector<int32_t>();
    }

    NBTTagIntArray::~NBTTagIntArray() {
        delete array;
    }

    void NBTTagIntArray::put(int32_t data) {
        this->array->push_back(data);
    }
    void NBTTagIntArray::set(size_t index, int32_t data) {
        if (index >= 0 && index < this->array->size()) {
            this->array->at(index) = data;
        }
    }
    int32_t NBTTagIntArray::get(size_t index) {
        return this->array->at(index);
    }
    size_t NBTTagIntArray::size() {
        return this->array->size();
    }
    void NBTTagIntArray::clear() {
        this->array->clear();
    }
    void NBTTagIntArray::remove(size_t index) {
        if (index >= 0 && index < array->size()) {
            array->erase(array->begin() + index);
        }
    }
    void NBTTagIntArray::read(std::istream & in) {
        int32_t size = NBT::read_int(in);
        clear();
        for (int i = 0; i < size; i++) {
            int8_t temp = NBT::read_byte(in);
            array->push_back(temp);
        }
    }
    void NBTTagIntArray::write(std::ostream & out) {
        int32_t size = (int32_t)array->size();
        NBT::write(out, size);
        for (int i = 0; i < size; i++) {
            int8_t temp = array->at(i);
            NBT::write(out, temp);
        }
    }
    bool NBTTagIntArray::equals(NBTBase * tag) {
        if (NBTBase::equals(tag)) {
            return this->array == ((NBTTagIntArray*)tag)->array;
        }
        return false;
    }

    NBTTagList::NBTTagList() {
        this->list = new std::vector<NBTBase*>();
    }

    NBTTagList::NBTTagList(char child) {
        this->list = new std::vector<NBTBase*>();
        this->_child = child;
    }
    NBTTagList::~NBTTagList() {
        clear();
        delete list;
    }
    void NBTTagList::put(NBTBase * tag) {
        if (_child == tag->getType()) {
            list->push_back(tag);
        }
    }
    void NBTTagList::set(size_t index, NBTBase * tag) {
        if (index >= 0 && index < this->list->size()) {
            list->push_back(tag);
        }
    }
    NBTBase * NBTTagList::get(size_t index) {
        return list->at(index);
    }
    char NBTTagList::child() {
        return this->_child;
    }
    void NBTTagList::clear() {
        int size = (int)list->size();
        for (int i = 0; i < size; i++) {
            delete (list->at(i));
        }
        list->clear();
    }
    void NBTTagList::remove(size_t index) {
        if (index >= 0 && index < list->size()) {
            delete (list->at(index));
            list->erase(list->begin() + index);
        }
    }
    void NBTTagList::read(std::istream & in) {
        clear();
        in.get(_child);
        int32_t size = NBT::read_int(in);
        for (int i = 0; i < size; i++) {
            NBTBase *tag = NBT::create(_child);
            tag->read(in);
            list->push_back(tag);
        }
    }
    void NBTTagList::write(std::ostream & out) {
        int32_t size = (int32_t)list->size();
        out.put(_child);
        NBT::write(out, size);
        for (int i = 0; i < size; i++) {
            list->at(i)->write(out);
        }
    }
    bool NBTTagList::equals(NBTBase * tag) {
        if (NBTBase::equals(tag) && _child == ((NBTTagList*)tag)->child()) {
            ///
            return list->size() == ((NBTTagList*)tag)->list->size();
        }
        return false;
    }
}
