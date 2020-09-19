class mcureg
{
public:
    enum access {UNDEF, C, R, S, W, RC, RS, RW, RSV, W1C, W1S};

    explicit mcureg(access access);
    virtual ~mcureg() = default;
};
