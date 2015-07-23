int sendall(int s, char *buf, int len, int flags) {
    int total = 0;
    int n = 0;
    while (total < len) {
        n = (int) send(s, buf + total, (size_t)(len - total), flags);
        if (n == -1) break;
        total += n;
    }
    return (n == -1 ? -1 : total);
}
