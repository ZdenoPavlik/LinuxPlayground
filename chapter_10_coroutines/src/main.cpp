/*
https://www.modernescpp.com/index.php/c-20-coroutines-the-first-overview
https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html
*/

#include <coroutine>
#include <iostream>

struct promise_type
{
    promise_type get_return_object()
    {
        return {};
    }
    std::suspend_never initial_suspend()
    {
        return {};
    }
    std::suspend_never final_suspend() noexcept
    {
        return {};
    }
    void unhandled_exception() {}
};

struct Awaiter
{
    std::coroutine_handle<>* hp_ = nullptr;
    constexpr bool await_ready() const noexcept
    {
        return false;
    }
    void await_suspend(std::coroutine_handle<> h)
    {
        *hp_ = h;
    }
    constexpr void await_resume() const noexcept {}
};

promise_type counter(std::coroutine_handle<>* continuation_out)
{
    Awaiter a{continuation_out};
    for(unsigned i = 0;; ++i)
    {
        co_await a;
        std::cout << "counter: " << i << std::endl;
    }
}

int main()
{
    std::coroutine_handle<> h;
    counter(&h);
    for(int i = 0; i < 3; ++i)
    {
        std::cout << "In main function\n";
        h();
    }
    h.destroy();

    return 0;
}
