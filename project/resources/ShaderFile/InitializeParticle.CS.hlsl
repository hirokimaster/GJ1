#include "Particle.hlsli"

// 最大数
static const uint32_t kMaxParticles = 1024;

RWStructuredBuffer<Particle> gParticles : register(u0);

RWStructuredBuffer<int32_t> gFreeListIndex : register(u1);
RWStructuredBuffer<uint32_t> gFreeList : register(u2);

[numthreads(1024, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID )
{
    uint32_t particleIndex = DTid.x;
    if (particleIndex < kMaxParticles)
    {
        gParticles[particleIndex] = (Particle) 0;
        gFreeList[particleIndex] = particleIndex;
    }
    
    if (particleIndex == 0)
    {
        gFreeListIndex[0] = kMaxParticles - 1;
    }
}