#include <iostream>
#include <exception>
#include <initializer_list>

template <typename T>
class List
{
    struct Node
    {
        T data_;
        friend class List;

    private:
        Node *prev;
        Node *next;
        Node(const T &data) : data_{data}, prev{nullptr}, next{nullptr} {}
    };

    int size_;
    Node *head;
    Node *tail;
    Node *end_ = new Node(T{});

public:
    List() : size_{0}, head{nullptr}, tail{nullptr} {}
    List(const std::initializer_list<T> &list) : size_{0}
    {
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            push_back(*it);
        }
    }
    List(const List &second):size_{0}
    {
        Node *temp = second.head;
        while (temp)
        {
            push_back(temp->data_);
            temp = temp->next;
        }
    }
    List(List &&second)
    {
        head = second.head;
        tail = second.tail;
        size_ = second.size_;
        second.head = nullptr;
        second.tail = nullptr;
        second.size_ = 0;
    }
    List &operator=(const List &second)
    {
        if (&second == this)
            return *this;
        clear();
        Node *temp = second.head;
        while (temp)
        {
            push_back(temp->data_);
            temp = temp->next;
        }
        return *this;
    }
    List &operator=(List &&second)
    {
        if (&second == this)
            return *this;
        clear();
        head = second.head;
        tail = second.tail;
        size_ = second.size_;
        second.head = nullptr;
        second.tail = nullptr;
        second.size_ = 0;
        return *this;
    }
    ~List()
    {
        clear();
        delete end_;
        end_ = nullptr;
    }

    void push_back(const T &data)
    {
        Node *new_ = new Node(data);
        if (empty())
            head = tail = new_;
        else
        {
            tail->next = new_;
            new_->prev = tail;
            tail = new_;
        }
        end_->prev = tail;
        new_ = nullptr;
        ++size_;
    }
    void push_front(const T &data)
    {
        Node *new_ = new Node(data);
        if (empty())
            head = tail = new_;
        else
        {
            head->prev = new_;
            new_->next = head;
            head = new_;
        }
        new_ = nullptr;
        ++size_;
    }
    void pop_back()
    {
        if (size_ == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node *temp = tail->prev;
            temp->next = nullptr;
            tail->prev = nullptr;
            delete tail;
            tail = temp;
            temp = nullptr;
        }
        end_->prev = tail;
        --size_;
    }
    void pop_front()
    {
        if (size_ == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            Node *temp = head->next;
            temp->prev = nullptr;
            head->next = nullptr;
            delete head;
            head = temp;
            temp = nullptr;
        }
        --size_;
    }
    bool empty() { return size_ == 0; }
    size_t size() { return size_; }
    void insert(size_t index, const T &data)
    {
        if (empty())
        {
            push_back(data);
            return;
        }
        else if (index > size_)
            throw std::out_of_range("index > size!");
        else
        {
            Node *new_ = new Node(data);
            size_t i = index;
            Node *temp = head;
            while (i > 0)
            {
                temp = temp->next;
                --i;
            }
            new_->prev = temp->prev;
            new_->next = temp;
            if (index > 0)
                temp->prev->next = new_;
            temp->prev = new_;
            if (index == 0)
                head = new_;
            new_ = nullptr;
            end_->prev = tail;
            ++size_;
        }
    }
    void clear()
    {
        Node *temp = head;
        while (temp)
        {
            temp = temp->next;
            delete head;
            head = temp;
        }
        tail = nullptr;
        size_ = 0;
    }
    void print()
    {
        if (size_ == 0)
            std::cout << "Empty!" << std::endl;
        else
        {
            Node *temp = head;
            while (temp)
            {
                std::cout << temp->data_ << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }
    class iterator
    {
        Node *ptr = nullptr;

    public:
        iterator(Node *p) : ptr{p} {}
        T &operator*() { return ptr->data_; }
        Node *operator->() { return ptr; }
        iterator operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp = *this;
            ptr = ptr->next;
            return temp;
        }
        iterator operator--()
        {
            if (ptr == nullptr)
                return *this;
            ptr = ptr->prev;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp = *this;
            ptr = ptr->prev;
            return temp;
        }
        bool operator==(iterator i) { return ptr == i.ptr; }
        bool operator!=(iterator i) { return ptr != i.ptr; }
    };
    iterator begin() { return head; }
    iterator end() { return end_; }
};

int main(int argc, char const *argv[])
{
    return 0;
}
