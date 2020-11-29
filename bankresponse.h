#ifndef BANKRESPONSE_H
#define BANKRESPONSE_H

enum ResponseStatus {
    OK, NOT_FOUND, ERROR, NOT_ENOUGH, BLOCKED
};

template<class Value>
class BankResponse {
    const ResponseStatus _status;
    const Value *_value;
public:
    BankResponse(const Value& val) : _status(ResponseStatus::OK), _value(new Value(val)) {}
    BankResponse(const ResponseStatus resp) : _status(resp), _value(nullptr) {}
    BankResponse(Value&& val) : _status(ResponseStatus::OK), _value(new Value(val)) {}
    BankResponse(BankResponse&& b) : _status(b._status), _value(b._value) {b._value = nullptr;}
    ~BankResponse(){ delete _value; }

    const Value& value() const {
        return *_value;
    }

    ResponseStatus status() const {
        return _status;
    }
};

template <>
struct BankResponse<ResponseStatus> {
    const ResponseStatus _status;
    BankResponse(const ResponseStatus s) : _status(s){}
};

#endif // BANKRESPONSE_H
