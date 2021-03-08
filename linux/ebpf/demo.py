#!/usr/bin/python
from bcc import BPF
from time import sleep

program = """
BPF_HASH(clones);

int hello(void *ctx) {
    u64 uid;
    u64 counter = 0;
    u64 *p;

    uid = bpf_get_current_uid_gid() & 0xffffffff;
    p = clones.lookup(&uid);
    if (p != 0) {
        counter = *p;
    }
    counter++;
    clones.update(&uid, &counter);
    // bpf_trace_printk("id: %ld: hello, world", uid);
    return 0;
}
"""

b = BPF(text=program)
clone = b.get_syscall_fnname(b"clone")
b.attach_kprobe(event=clone, fn_name="hello")
# b.trace_print()

while True:
    sleep(2)
    s = ""
    if len(b["clones"].items()):
        for k, v in b["clones"].items():
            s += f"ID: {k.value}: {v.value} \t"
            print(s)
    else:
        print("no entry yet")
