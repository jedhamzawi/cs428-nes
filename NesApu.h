#pragma once
class NesApu : public ProcessingUnit {
public:
	void step_to(int t_master_clock) override;
};