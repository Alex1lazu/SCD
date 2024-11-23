struct request {
    string id<>;
    string action<>;
    string res<>;
};

struct answer {
    string resp<>;
};

program AUTH {
    version A1 {
        int afisare(string) = 1;
    } = 1;
} = 1;