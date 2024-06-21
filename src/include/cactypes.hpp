#pragma once

struct ALMADEN_CAC_RECORD {
    int processId;
    float cpuConsumption;
    float memoryConsumption;
    char* url;
};

struct ALMADEN_CAC_NODE {
    ALMADEN_CAC_RECORD record;
    ALMADEN_CAC_NODE* next;
};
