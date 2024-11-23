struct request {
    char id[100];
    char action[100];
    char res[100];
};

struct response {
    char msg[100];
};

program AUTH {
    version A1 {
        response afisare(request) = 1;
    } = 1;
} = 1;