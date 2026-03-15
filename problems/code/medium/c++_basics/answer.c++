
#include <cstdint>
#include <iostream>

class Answer
{
    public:
        Answer():
            _a(0),
            _b(0)
        {}

        Answer(uint32_t a):
            _a(a),
            _b(0)
        {}

        Answer(uint16_t b):
            _a(0),
            _b(b)
        {}

        Answer(uint32_t a, uint16_t b):
            _a(a),
            _b(0)
        {}

        // Copy constructor
        Answer(const Answer& other):
            _a(other._a),
            _b(other._b)
        {}

        // Destructor
        ~Answer()
        {
            _a = 0;
            _b = 0;
        }

        // 'a' getter
        uint32_t a() const { return _a; }

        // 'b' getter
        uint16_t b() const { return _b; }

        Answer operator+(const Answer& other)
        {
            uint32_t a_sum = this->_a + other._a;
            uint16_t b_sum = this->_b + other._b;
            return Answer(a_sum, b_sum);
        }

        Answer& operator+=(const Answer& rhs)
        {
            this->_a = rhs._a;
            this->_b = rhs._b;
            return *this;
        }

        Answer& operator=(const Answer& other)
        {
            _a = other._a;
            _b = other._b;
            return *this;
        }

        bool operator==(const Answer& rhs)
        {
            return (this->_a == rhs._a) && (this->_b == rhs._b);
        }

    private:
        uint32_t _a;
        uint16_t _b;
};


class AnswerAdvanced
{
    public:
        AnswerAdvanced():
            _sz(0),
            _data(nullptr),
            _has_data(false)
        {}

        AnswerAdvanced(size_t sz):
            _sz(sz),
            _data(new int[sz]),
            _has_data(false)
        {}

        // Copy constructor
        AnswerAdvanced(const AnswerAdvanced& other)
        {
            this->_sz = other._sz;
            this->_data = new int[this->_sz];
            this->_has_data = other._has_data;
            if (this->_has_data)
            {
                std::copy(other._data, other._data + other._sz, this->_data);
            }
        }

        // Move constructor
        AnswerAdvanced(AnswerAdvanced&& other)
        {
            _data = other._data;
            _sz = other._sz;
            _has_data = other._has_data;
            other._data = nullptr;
            other._sz = 0;
            other._has_data = false;
        }

        ~AnswerAdvanced()
        {
            delete _data;
            _sz = 0;
            _has_data = false;
        }

        AnswerAdvanced& operator=(AnswerAdvanced& other)
        {
            
        }

        const int* data() const { return _data; }
        size_t sz() const { return _sz; }
        bool has_data() const { return _has_data; }

        friend std::ostream& operator<<(std::ostream& os, const AnswerAdvanced& obj);

    private:
        size_t _sz;
        bool _has_data;
        int* _data;
};


std::ostream& operator<<(std::ostream& os, const AnswerAdvanced& obj)
{
    os << "AnswerAdvanced(Size=" << obj._sz << ", HasData=" <<
        (obj._has_data ? "TRUE" : "FALSE") << ")" << std::endl;
    return os;
}
