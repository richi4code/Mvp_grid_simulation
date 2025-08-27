#include "generator.hpp"
#include <algorithm>

Generator::Generator(const GeneratorConfig& cfg)
: cfg_(cfg),
  
  st_{cfg.id, cfg.nodeIndex, true, cfg.maxOutput, 0},
  rng_(cfg.seed),
  jitter_(cfg.jitterLo, cfg.jitterHi),
  fail_(cfg.pFail)
{}

void Generator::step() {
    if (st_.active) {
        if (fail_(rng_)) {                
            st_.active = false;
            st_.currentOutput = 0;
            st_.downTimeHours = 0;
        } else {                            
            int target = cfg_.baseSetpoint + jitter_(rng_);
            st_.currentOutput = clamp_value(target, 0, cfg_.maxOutput);
        }
    } else {                                
        st_.currentOutput = 0;
        st_.downTimeHours++;
        if (st_.downTimeHours >= cfg_.recoverAfter) {
            st_.active = true;              
        }
    }
}

GeneratorState Generator::state() const { return st_; }
