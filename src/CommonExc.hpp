#pragma once
#include <exception>
#include <string>

using namespace std;

class AdditionalInfo
{
private:
    string addInfo;
public:
    AdditionalInfo(string str) {
        addInfo = str;
    };
    string info(void) const {
        return addInfo;
    };
    virtual ~AdditionalInfo() {};
};

class OutRange : exception, AdditionalInfo
{
public:
    OutRange(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("Denied access to memory: " + info()).c_str();
    }
};


class MemoryAlloc : exception, AdditionalInfo
{
public:
    MemoryAlloc(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("Reserve memory: " + info()).c_str();;
    }
};


class EmptyContainer : exception, AdditionalInfo
{
public:
    EmptyContainer(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("EmptyContainer: " + info()).c_str();;; 
    }
};


class InputFail : exception, AdditionalInfo
{
public:
    InputFail(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("InputFail: " + info()).c_str();;; 
    }
};


class InfinityValue : exception, AdditionalInfo
{
public:
    InfinityValue(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("InfinityValue: " + info()).c_str();;; 
    }
};

