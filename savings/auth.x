struct request {
    string id<>;
    string action<>;
    string res<>;
};

program AUTH {
    version A1 {
        string<> afisare(request) = 1;
    } = 1;
} = 0x23451111;