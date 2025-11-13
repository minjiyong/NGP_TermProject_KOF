#pragma once
#include "protocol.h"

void InitializeNetwork();
void ShutdownNetwork();    
bool NetworkConnected();      
void SendInputToServer(P_MOVE_STATE m, P_ATTACK_STATE a, P_GUARD_STATE g, P_HIT_STATE h);
void GetPointCloud(int* size, float** points);

extern int global_delay;
extern std::atomic_int active_clients;