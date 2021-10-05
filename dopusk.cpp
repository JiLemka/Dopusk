#include <iostream>
#include <memory>
#include <stdexcept>

//Мефедов А.М.

class StackL {
public:
    StackL() = default;
    StackL(const StackL& s);
    StackL& operator=(const StackL& rhs);
    ~StackL();
    bool is_empty() const noexcept;
    void push(const float value);
    void pop() noexcept;
    float& top();
    const float& top() const;
private:
    struct Node {
        float value = 0.0f;
        Node* next = nullptr;
    };
private:
    Node* head_ = nullptr;
};
 
 
StackL::StackL(const StackL& s) {
    if (s.is_empty()) {
        head_ = nullptr;
        return;
    }
    auto rhs_ptr = s.head_;
    auto this_ptr = new Node;
    head_ = this_ptr;
    while (rhs_ptr != nullptr) {
        this_ptr->value = rhs_ptr->value;
        if (rhs_ptr->next != nullptr) {
            this_ptr->next = new Node{ 0, nullptr };
            this_ptr = this_ptr->next;
        }
        rhs_ptr = rhs_ptr->next;
    }
}

StackL& StackL::operator=(const StackL& rhs) {
    if (rhs.is_empty()) { head_ = nullptr; return (*this); }
    StackL rhs_copy(rhs);
    while (!this->is_empty()) {
        this->pop();
    }
    auto rhs_ptr = rhs_copy.head_;
    auto this_ptr = new Node;
    head_ = this_ptr;
    while (rhs_ptr != nullptr) {
        this_ptr->value = rhs_ptr->value;
        if (rhs_ptr->next != nullptr) {
            this_ptr->next = new Node{ 0, nullptr };
            this_ptr = this_ptr->next;
        }
        rhs_ptr = rhs_ptr->next;
    }
    return (*this);
}

StackL::~StackL() {
    while (!this->is_empty()) {
        this->pop();
    }
}

bool StackL::is_empty() const noexcept {
    return head_ == nullptr;
}

void StackL::push(const float value) {
    if (head_ == nullptr) {
        head_ = new Node({ value, nullptr });
    }
    else {
        head_ = new Node({ value, head_ });
    }
}

void StackL::pop() noexcept {
    if (!is_empty()) {
        auto new_head_ = head_->next;
        delete head_;
        head_ = new_head_;
    }
}

float& StackL::top() {
    if (head_ == nullptr) throw std::out_of_range("Stack is empty");
    return head_->value;
}

const float& StackL::top() const {
    if (head_ == nullptr) throw std::out_of_range("Stack is empty");
    return head_->value;
}

int main() {
    StackL st;
    st.push(44);
    st.push(33);
    st.push(22);
    st.push(11);
    st = st;
    std::cout << st.top() << "\n";
    st.pop();
    std::cout << st.top() << "\n";
    std::cout << st.is_empty() << "\n";
    st.push(100);
    StackL st2(st);
    StackL st3 = st2;
    st3.pop();
    std::cout << "st2 top elements is " << st2.top() << "\n";
    std::cout << "st3 top elements is " << st3.top() << "\n";
    return 0;
}