#define UNLOCK 0
#define LOCK 1

int locked = UNLOCK;

void critical_section()
{
retry:
    if (locked != UNLOCK) {
        goto retry;
    }
    locked = LOCK;
    // critical_section
    locked = UNLOCK;
}

int main()
{
    return 0;
}
