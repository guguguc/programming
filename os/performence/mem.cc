#include <malloc.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE (8 * 1024 * 1024)
int table[8] = {1, 4, 16, 64, 256, 256 << 1, 256 << 2, 256 << 3};

struct mem_info {
    mem_info(void *p, int sz) : m_ptr(p), m_sz(sz){ }
    void *m_ptr;
    size_t m_sz;
};

template <typename T>
class Payload {
public:
    Payload(size_t sz) : m_sz(sz) {
        m_array = new T[sz];
        std::cout << "new " << m_sz * sizeof(T) << " bytes\n";
    }
    ~Payload() {
        delete []m_array;
        std::cout << "delete " << m_sz * sizeof(T) << " bytes\n";
    }

private:
    size_t m_sz;
    T *m_array;
};

void test_malloc()
{
    std::vector<mem_info> vecPtr;
    for (size_t i = 1; i <= MAX_SIZE; i <<= 1)
    {
        void *p = malloc(i);
        std::cout << "malloc " << i << " bytes\n";
        std::system("read");
        vecPtr.push_back(mem_info(p, i));
    }
    for (const auto &mi : vecPtr) {
        free(mi.m_ptr);
        std::cout << "free " << mi.m_sz << " bytes\n";
        std::system("read");
    }
}

void test_new()
{
    std::vector<Payload<char>*> vecPtr;
    for (size_t i = 1; i < MAX_SIZE; i <<= 2) {
        auto *p = new Payload<char>(1 << 14);
        std::system("read");
        vecPtr.push_back(p);
    }
    for (const auto &p : vecPtr) {
        delete p;
        std::system("read");
    }
}

void test_new_random()
{
    std::vector<Payload<char>*> vecPtr;
    for (size_t i = 1; i < 32; ++i) {
        auto *p = new Payload<char>(table[std::rand() % 8] << 4);
        getchar();
        vecPtr.push_back(p);
    }
    for (const auto &p : vecPtr) {
        delete p;
        getchar();
    }
}

int main()
{
    mallopt(M_MMAP_THRESHOLD, 0);
    if (int pid = fork()) {
    } else {
        test_new_random();
    }
    int wstatus;
    wait(&wstatus);
    return 0;
}
