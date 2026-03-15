
template <typename T>
class Node
{
    public:
        Node():
            next(nullptr)
        {}

        Node(T value):
            next(nullptr),
            _value(value)
        {}

        T value() { return _value; }

        Node* get_node(unsigned int idx)
        {
            Node* cursor = this;
            while (idx && cursor != nullptr)
            {
                idx--;
                cursor = cursor->_next;
            }
        }

        Node* next() { return _next; }

        Node* append(Node* node)
        {

        }

    private:
        Node* _next;
        T _value;
};

template <typename T>
class List
{
    public:
        using Node_t = Node<T>;

        List():
            _head(nullptr),
            _tail(nullptr)
        {}

        void push(T& data)
        {
            Node_t* new_node = new Node_t(data);
            if (_head == nullptr)
            {
                _head = new_node;
                _tail = _head;
            }
            else
            {
                _tail.
            }
        }

    private:
        Node_t* _head;
        Node_t* _tail;
};
