#pragma once
#include "ViewUpdateContract.h"

class BackgroundPresenter: public Presenter<bool> {

public:
	BackgroundPresenter() = default;

	std::function<void(float)> getUpdateSource() override;
};
