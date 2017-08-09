/**
EEPROM mock
**/

#ifndef __EEPROM_h__
#define __EEPROM_h__

#include <stdint.h>
#include <gmock/gmock.h>

class EEPROM_ {
  public:
    uint8_t read(int a);
    void write(int a,  uint8_t b);

    //Functionality to 'get' and 'put' objects to and from EEPROM.
    template<typename T> T &get(int idx, T &t);
    template<typename T> const T &put(int idx, const T &t);
};

extern EEPROM_ EEPROM;

class EEPROMMock {
  public:
    MOCK_METHOD1(read, uint8_t(int));
    MOCK_METHOD2(write, void(int, uint8_t));

    MOCK_METHOD3(get, void(int idx, void* data, int size));
    MOCK_METHOD3(put, void(int idx, void* data, int size));
};

EEPROMMock* EEPROMMockInstance();
void releaseEEPROMMock();

extern EEPROMMock* p_EEPROMMock;

template<typename T> T &EEPROM_::get(int idx, T &t) {
    assert (p_EEPROMMock != NULL);
    p_EEPROMMock->get(idx, (void*)&t, (int)sizeof(t));
    return t;
}

template<typename T> const T &EEPROM_::put(int idx, const T &t) {
    assert(p_EEPROMMock != NULL);
    p_EEPROMMock->put(idx, (void*)&t, (int)sizeof(t));
    return t;
}

#endif
