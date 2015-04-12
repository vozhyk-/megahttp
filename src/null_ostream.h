#ifndef NULL_OSTREAM_H
#define NULL_OSTREAM_H

class null_buffer : public std::streambuf
{
public:
    int overflow (int c) { return c; }
};

class null_ostream : public std::ostream
{
    null_buffer null_buf;
public:
    null_ostream() : std::ostream(&null_buf) {}
};

#endif // NULL_OSTREAM_H
